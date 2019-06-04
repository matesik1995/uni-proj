import teradata
from datetime import datetime
import argparse
import csv

# Dictionary of kev:value pairs, where
#   key - is a symbol of column type
#   value - is a query to be performed to calculate all the statistics. `%col%` is replaced with column name.
#			Each metric should have alias in following format:
#				%col%___STAT_NAME
#			`___` is treated as safe delimeter between column name and calculated metric
STATISTICS_QUERY_BY_TYPE = {
	"I": """record_count-COUNT(CAST(%col% as BIGINT)) AS %col%___nulls, 
			COUNT(DISTINCT CAST(%col% as BIGINT)) AS %col%___distincts,
			MIN(CAST(%col% as BIGINT)) AS %col%___minimum, 
			MAX(CAST(%col% as BIGINT)) AS %col%___maximum, 
			SUM(CAST(%col% as BIGINT)) AS %col%___sum,
			ROUND(STDDEV_POP(CAST(%col% as BIGINT)), 2) AS %col%___standard_deviation, 
			AVG(CAST(%col% as BIGINT)) AS %col%___mean""", # integer
	"F": """record_count-COUNT(%col%) AS %col%___nulls, 
			COUNT(DISTINCT %col%) AS %col%___distincts,
			MIN(%col%) AS %col%___minimum,
			MAX(%col%) AS %col%___maximum,
			SUM(%col%) AS %col%___sum, 
			ROUND(STDDEV_POP(%col%), 2) AS %col%___standard_deviation,
			AVG(%col%) AS %col%___mean""", # float
	"D": """record_count-COUNT(%col%) AS %col%___nulls, 
			COUNT(DISTINCT %col%) AS %col%___distincts, 
			MIN(%col%) AS %col%___minimum, 
			MAX(%col%) AS %col%___maximum, 
			SUM(%col%) AS %col%___sum, 
			ROUND(STDDEV_POP(%col%), 2) AS %col%___standard_deviation,
			AVG(%col%) AS %col%___mean""", # double
	"CF": """record_count-COUNT(%col%) AS %col%___nulls, 
			 COUNT(DISTINCT %col%) AS %col%___distincts""", # fixed character
	"CV": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts, 
			 %col%___nulls+SUM(CASE %col% WHEN '' THEN 1 ELSE 0 END) AS %col%___empties, 
			 SUM(CASE TRIM(%col%) WHEN '' THEN 1 ELSE 0 END) AS %col%___blanks,
			 AVG(LENGTH(%col%)) AS %col%___avg,
			 MIN(LENGTH(%col%)) AS %col%___minimum,
			 MAX(LENGTH(%col%)) AS %col%___maximum""", # var. character
	"BF": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts""", # fixed binary
	"BV": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts""", # var. binary 
	"I2": """record_count-COUNT(CAST(%col% as BIGINT)) AS %col%___nulls, 
			COUNT(DISTINCT CAST(%col% as BIGINT)) AS %col%___distincts,
			MIN(CAST(%col% as BIGINT)) AS %col%___minimum, 
			MAX(CAST(%col% as BIGINT)) AS %col%___maximum, 
			SUM(CAST(%col% as BIGINT)) AS %col%___sum,
			ROUND(STDDEV_POP(CAST(%col% as BIGINT)), 2) AS %col%___standard_deviation, 
			AVG(CAST(%col% as BIGINT)) AS %col%___mean""", # smallint
	"DA": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts""", # date
	"AT": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts""", # time
	"TS": """record_count-COUNT(%col%) AS %col%___nulls,
			 COUNT(DISTINCT %col%) AS %col%___distincts""" # timestamp
}

# Table data class containing table name and list of it's columns
class Table:
	def __init__(self, name):
		self.name = name
		self.columns = []
		
	def add_column(self, column):
		self.columns.append(column)
		
	def __repr__(self):
		return "Table(name='{}', columns={})".format(self.name, self.columns)

# Column data class containg column name and it's type		
class Column:
	def __init__(self, name, type):
		self.name = name
		self.type = type
		
	def __repr__(self):
		return "Column(name='{}', type='{}')".format(self.name, self.type)
	
# main function	
def main(database_name, table_names, output_fn, debug):
	g_t1 = datetime.now()
	udaExec = teradata.UdaExec()		# create udaExec framework entry point, load configuration from udaexec.ini
	with open(output_fn, 'w' ,newline='') as csvfile:		# open file for output
		output = csv.writer(csvfile)		# create output csv writer 
		output.writerow(["Table Name", "Column Name", "Metric Name", "Metric Value", "Execution time"]) 		# write header row to csv file
		with udaExec.connect(method="${method}", dsn="${dsn}") as session: 		# connect to TeraData instance and save connectin as session
			_tables = {}		# temporary tables list
			for row in session.execute("""SELECT TRIM(TableName) as table_name, TRIM(ColumnName) as column_name, TRIM(ColumnType) as column_type 
										  FROM dbc.columns WHERE DatabaseName = '{database_name}';""".format(database_name=database_name)):
				_tables.setdefault(row.table_name, Table(row.table_name)).add_column(Column(row.column_name, row.column_type)) # retrive all tables and it's columns from database dbc.columns
			
			tables = {}
			if len(table_names) == 0:		# if no table_names given as argument, run calculations on all tables retrived from dbc.columns
				tables = _tables
			else:
				for t in table_names:		# otherwise loop through given names and check if they exists in db, and select only those
					if t not in _tables.keys():
						raise AttributeError("Invalid input table name: '{}' is not one of {}".format(t, _tables.keys()))
					tables[t] = _tables[t] 
			 
			for table in tables.values():		# main loop, processing tables one by one
				print("\nProcessing table: {}".format(table.name))
				if debug: 
					print(table)
				stmnt = "SELECT COUNT(*) as record_count"		# prepare statement for table
				for column in table.columns:		# each column queries are added to single statement for better performance
					try: 
						stmnt += ", " + STATISTICS_QUERY_BY_TYPE[column.type].replace("%col%", column.name)		# queries for statistics are chosen based on column type
					except KeyError as e:
						print("\t\tWarning: Unknown column type: {}".format(e))		# warning is printed if there is no query associated with column type
				stmnt += " FROM {database_name}.".format(database_name=database_name) + table.name + ";"
				 
				print("Created statement.")
				if debug:
					print("Statement: {}".format(stmnt))
				print("Executing... ", end='', flush=True)
				t1 = datetime.now()
				cur = session.execute(stmnt)		#execute statement and calculate time elapsed 
				row = cur.fetchone()
				execution_time = datetime.now() - t1
				print("DONE")
				print("Execution time: {}".format(execution_time))
				
				print("\nWriting results to file: {}".format(output_fn))
				for column in row.columns:		# save results to csv file
					try:
						column_name, metric_name = column.split('___')		# split output column name by `___` which delimeters column name and metric
					except ValueError:
						column_name = '*'
						metric_name = column
					result_row = [table.name, column_name, metric_name, str(row[column]), str(execution_time)]		# create row for csv file. Table Name, Column Name, Metric Name, Metric Value, Execution time
					output.writerow(result_row)		# save row
					if debug:
						print(result_row)
					
	print("Global execution time: {}".format(datetime.now() - g_t1))
		

# program entry point
# it defines and parse arguments and pass these to main function.		
if __name__=="__main__":
	parser = argparse.ArgumentParser(description='TeraDataProfiler v0.1')
	parser.add_argument('-d', '--database', default='vmtest', help='database name')
	parser.add_argument('-t', '--tables', metavar='TABLE_NAME', nargs='*', default=[], help='list of tables to be processed')
	parser.add_argument('-o', '--output', default='output.csv', help='output csv filename')
	parser.add_argument('-v', '--verbose', action='store_true', help='make output verbose')
	args = parser.parse_args()
	main(args.database, args.tables, args.output, args.verbose)
