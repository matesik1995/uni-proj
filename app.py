from math import log, ceil
from functools import partial

def o_m(n, m, b):
    """
    Method to calculate complexity of external sort operation
    :param n: data size
    :param m: memory size
    :param b: block size
    :return: number of data transfers from disk to memory
    """
    return n / b * log(n / b, m / b)


def o_n(b, n):
    """
    Method to calculate complexity of network transfers
    :param b: data size
    :param n: number of nodes
    :return: number of data transfers over network
    """
    return b / n * (n - 1)


def calculate_one(data_size, memory_size, number_of_nodes, block_size):
    """
    Metod to calculate summary
    :param data_size:
    :param memory_size:
    :param number_of_nodes:
    :param block_size:
    :return: tuple of values: disk operations, network transfers
    """
    return 2 * o_m(data_size, memory_size, block_size), o_n(data_size, number_of_nodes)


def calculate(full_data_size, memory_size, number_of_nodes, block_size):
    result = [0, 0]
    data_per_node = full_data_size / number_of_nodes
    for i in range(number_of_nodes):
        om, on = calculate_one(data_per_node, memory_size, number_of_nodes, block_size)
        result[0] += om
        result[1] += on
    return result

	
def cluster(name, data_size, node_memory_size, node_number, disk_thru, network_thru, disk_block_size = 4096, debug=False):
    if debug:
        print('-'*100)
        print(name)
    do, nt = calculate(data_size, node_memory_size, node_number, disk_block_size)
	
    dow = (do * disk_block_size) / disk_thru
    ntw = nt / network_thru

    time_disk = dow / node_number
    time_net = ntw / node_number / (node_number - 1)
    time = time_disk + time_net
    if debug:
        print("Summary:")
        print(f"Disk operations:\t {do}\nNetwork transfers:\t {nt}")
        print(f"Disk weighted:\t {dow}\nNetwork weighted:\t {ntw}")
        print(F"Time disk: {time_disk}")
        print(F"Time net: {time_net}")
        print(f"Sum time: {time}")
        print('-'*100)
    return time

def hadoop_cluster():
    time = cluster("Hadoop",
		data_size = 1e+14,  # 100TB
		node_memory_size = 64e+9,  # 64GB
		node_number = 2100,
		disk_block_size = 4096,  # number of bytes per block
		disk_thru = 8e+7,  # 80MBps
		network_thru = 1.25e+9,  # 10Gbps
        debug=True
	)
    return time

def spark_cluster():
    time = cluster("Spark",
		data_size = 1e+14,  # 100TB
		node_memory_size = 244e+9,  # 244GB
		node_number = 207,
		disk_block_size = 4096,  # number of bytes per block
		disk_thru = 3e+9,  # 3GBps
		network_thru = 1.25e+9,  # 10Gbps
        debug=True
	)
    return time

def base_cluster():
	base = partial(cluster, 
        name="Base",
		data_size = 1e+14,  # 100TB
		node_memory_size = 64e+9,  # 64GB
		node_number = 1000,
		disk_block_size = 4096,  # number of bytes per block
		disk_thru = 12e+7,  # 120MBps
		network_thru = 1.25e+9  # 10Gbps
	)
	return base
    

def main():
#    h = hadoop_cluster()
#    s = spark_cluster()
#    print(h)
#    print(s)
#    print(f"Ratio hadoop/spark: {h/s}")
    with open('a.txt', 'w') as f:
        b = base_cluster()
        for i in range(1,10):
            f.write(str(1 * 2 ** i) + '\t' + str(b(node_memory_size=1e+9 * 2 ** i)) + '\n')

if __name__ == "__main__":
    main()
