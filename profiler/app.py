import teradata
from datetime import datetime
import argparse


STATISTICS_QUERY_BY_TYPE = {
	"I": """record_count-COUNT(CAST(%col% as BIGINT)) AS %col%_nulls, 
			COUNT(DISTINCT CAST(%col% as BIGINT)) AS %col%_distincts,
			MIN(CAST(%col% as BIGINT)) %col%_minimum, 
			MAX(CAST(%col% as BIGINT)) as %col%_maximum, 
			SUM(CAST(%col% as BIGINT)) as %col%_sum,
			ROUND(STDDEV_POP(CAST(%col% as BIGINT)), 2) as %col%_standard_deviation, 
			AVG(CAST(%col% as BIGINT)) as %col%_mean""", # integer
	"F": """record_count-COUNT(%col%) AS %col%_nulls, 
			COUNT(DISTINCT %col%) AS %col%_distincts,
			MIN(%col%) %col%_minimum,
			MAX(%col%) as %col%_maximum,
			SUM(%col%) as %col%_sum, 
			ROUND(STDDEV_POP(%col%), 2) as %col%_standard_deviation,
			AVG(%col%) as %col%_mean""", # float
	"D": """record_count-COUNT(%col%) AS %col%_nulls, 
			COUNT(DISTINCT %col%) AS %col%_distincts, 
			MIN(%col%) %col%_minimum, 
			MAX(%col%) as %col%_maximum, 
			SUM(%col%) as %col%_sum, 
			ROUND(STDDEV_POP(%col%), 2) as %col%_standard_deviation,
			AVG(%col%) as %col%_mean""", # double
	"CF": """record_count-COUNT(%col%) AS %col%_nulls, 
			 COUNT(DISTINCT %col%) AS %col%_distincts""", # fixed character
	"CV": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts, 
			 %col%_nulls+SUM(CASE %col% WHEN '' THEN 1 ELSE 0 END) AS %col%_empties, 
			 SUM(CASE TRIM(%col%) WHEN '' THEN 1 ELSE 0 END) AS %col%_blanks,
			 AVG(LENGTH(%col%)),
			 MIN(LENGTH(%col%)),
			 MAX(LENGTH(%col%))""", # var. character
	"BF": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts""", # fixed binary
	"BV": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts""", # var. binary 
	"I2": """record_count-COUNT(CAST(%col% as BIGINT)) AS %col%_nulls, 
			COUNT(DISTINCT CAST(%col% as BIGINT)) AS %col%_distincts,
			MIN(CAST(%col% as BIGINT)) %col%_minimum, 
			MAX(CAST(%col% as BIGINT)) as %col%_maximum, 
			SUM(CAST(%col% as BIGINT)) as %col%_sum,
			ROUND(STDDEV_POP(CAST(%col% as BIGINT)), 2) as %col%_standard_deviation, 
			AVG(CAST(%col% as BIGINT)) as %col%_mean""", # SMALLINT
	"DA": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts""", # DATE
	"AT": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts""" # TIME
	"TS": """record_count-COUNT(%col%) AS %col%_nulls,
			 COUNT(DISTINCT %col%) AS %col%_distincts""" # TIME
}


class Table:
	def __init__(self, name):
		self.name = name
		self.columns = []
		
	def add_column(self, column):
		self.columns.append(column)
		
	def __repr__(self):
		return "Table(name='{}', columns={})".format(self.name, self.columns)

		
class Column:
	def __init__(self, name, type):
		self.name = name
		self.type = type
		
	def __repr__(self):
		return "Column(name='{}', type='{}')".format(self.name, self.type)
	
	
def main(table_names):
	udaExec = teradata.UdaExec()
	with udaExec.connect(method="${method}", dsn="${dsn}") as session:
		_tables = {}
		for row in session.execute("SELECT TRIM(TableName) as table_name, TRIM(ColumnName) as column_name, TRIM(ColumnType) as column_type FROM dbc.columns WHERE DatabaseName = '${dbName}';"):
			_tables.setdefault(row.table_name, Table(row.table_name)).add_column(Column(row.column_name, row.column_type))
		
		tables = {}
		if len(table_names) == 0:
			tables = _tables
		else:
			for t in table_names:
				if t not in _tables.keys():
					raise AttributeError("Invalid input table name: '{}' is not one of {}".format(t, _tables.keys()))
				tables[t] = _tables[t] 
		 
		for table in tables.values():
			print("Processing table: {}".format(table))
			stmnt = "SELECT COUNT(*) as record_count, "
			stmnt += ", ".join([STATISTICS_QUERY_BY_TYPE[column.type].replace("%col%", column.name) for column in table.columns])
			stmnt += " FROM ${dbName}." + table.name + ";"
			
			print("Created statement: {}".format(stmnt))
			t1 = datetime.now()
			cur = session.execute(stmnt)
			row = cur.fetchone()
			t2 = datetime.now()
			
			print("Result: \n{}".format("\n".join([c + ": " + str(row[c]) for c in row.columns])))
			print("Execution time: {}".format(t2 - t1))
		
		
if __name__=="__main__":
	parser = argparse.ArgumentParser(description='TeraDataProfiler v0.1')
	parser.add_argument('-t', '--tables', metavar='TABLE_NAME', nargs='*', default=[], help='list of tables to be processed.')
	args = parser.parse_args()
	main(args.tables)