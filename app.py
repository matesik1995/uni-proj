from math import ceil, log

class Counter:
	disk = 0
	network = 0
	
	def __iadd__(self, other):
		self.disk += other.disk
		self.network += other.network
		return self


class Node:
	def __init__(self, id, memory, buffer, cluster_size):
		self.id = id
		self.memory = memory
		self.buffer = buffer
		self.cluster_size = cluster_size
		self.counter = Counter()
		
	
	def execute(self):
		# override this method to provide different algorithm statistics
		
		# imitate external sort
		external_sort = 2 * self.buffer * ( 1 + ceil(log(ceil(self.buffer/self.memory), self.memory - 1)))
		
		# imitate sending data - worst case scenario
		communication = ceil(self.buffer / self.cluster_size * (self.cluster_size - 1))
		
		self.counter.disk += external_sort * 2
		self.counter.network += communication
		 




def main():
	n = 100
	mem = 8e+9 # 8GB
	data = 1e+14 # 100TB
	
	data_per_node = data / n
	
	nodes = [Node(i, mem, data_per_node, n) for i in range(n)]
	
	for node in nodes:
		print(f"Node[{node.id}].execute()")
		node.execute()
		
	counter = Counter()
	for node in nodes:
		counter += node.counter
	
	print(f"Disk: {counter.disk}")
	print(f"Network: {counter.network}")
	
	
if __name__=="__main__":
	main()