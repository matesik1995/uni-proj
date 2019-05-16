import teradata
from datetime import datetime
import argparse
import csv


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
	
	
def main(database_name, table_names, output_fn):
	udaExec = teradata.UdaExec()
	with open(output_fn, 'w' ,newline='') as csvfile:
		output = csv.writer(csvfile)
		with udaExec.connect(method="${method}", dsn="${dsn}") as session:
			_tables = {}
			for row in session.execute("SELECT TRIM(TableName) as table_name, TRIM(ColumnName) as column_name, TRIM(ColumnType) as column_type FROM dbc.columns WHERE DatabaseName = '{database_name}';".format(database_name=database_name)):
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
				print("\n\nProcessing table: {}".format(table))
				stmnt = "SELECT COUNT(*) as record_count, "
				stmnt += ", ".join([STATISTICS_QUERY_BY_TYPE[column.type].replace("%col%", column.name) for column in table.columns])
				stmnt += " FROM {database_name}.".format(database_name=database_name) + table.name + ";"
				 
				print("\n\nCreated statement: {}".format(stmnt))
				t1 = datetime.now()
				cur = session.execute(stmnt)
				row = cur.fetchone()
				execution_time = datetime.now() - t1
				
				print("\n\nResult:")
				print(row.columns)
				for column in row.columns:
					try:
						column_name, metric_name = column.split('___')
					except ValueError:
						column_name = '*'
						metric_name = column
					result_row = [table.name, column_name, metric_name, str(row[column]), str(execution_time)]
					output.writerow(result_row)
					print(result_row)
				print("\n\nExecution time: {}".format(execution_time))
		
		
if __name__=="__main__":
	parser = argparse.ArgumentParser(description='TeraDataProfiler v0.1')
	parser.add_argument('-d', '--database', default='vmtest', help='database name')
	parser.add_argument('-t', '--tables', metavar='TABLE_NAME', nargs='*', default=[], help='list of tables to be processed')
	parser.add_argument('-o', '--output', default='output.csv', help='output csv filename')
	args = parser.parse_args()
	main(args.database, args.tables, args.output)
