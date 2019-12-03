from math import log


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


def hadoop_cluster():
    print('-'*100)
    print("Hadoop")
    data_size = 1e+14  # 100TB
    node_memory_size = 64e+9  # 64GB
    node_number = 2100
    disk_block_size = 512  # number of bytes per block

    disk_thru = 8e+7  # 80Mbps
    network_thru = 1e+10  # 10Gbps

    do, nt = calculate(data_size, node_memory_size, node_number, disk_block_size)

    dow = (do * disk_block_size) / disk_thru
    ntw = nt / network_thru

    time_disk = dow
    time_net = ntw
    time = time_disk + time_net

    print("Summary:")
    print(f"Disk operations:\t {do}\nNetwork transfers:\t {nt}")
    print(f"Disk weighted:\t {dow}\nNetwork weighted:\t {ntw}")
    print(F"Time disk: {time_disk}")
    print(F"Time net: {time_net}")
    print(f"Sum time: {time}")
    print('-'*100)
    return time


def spark_cluster():
    print('-'*100)
    print("Spark")
    data_size = 1e+14  # 100TB
    node_memory_size = 244e+9  # 244GB
    node_number = 207
    disk_block_size = 512_000  # number of bytes per block

    disk_thru = 5e+8  # 500Mbps
    network_thru = 1e+10  # 10Gbps

    do, nt = calculate(data_size, node_memory_size, node_number, disk_block_size)

    dow = (do * disk_block_size) / disk_thru
    ntw = nt / network_thru

    time_disk = dow
    time_net = ntw
    time = time_disk + time_net

    print("Summary:")
    print(f"Disk operations: {do}\nNetwork transfers: {nt}")
    print(f"Disk weighted: {dow}\nNetwork weighted: {ntw}")
    print(F"Time disk: {time_disk}")
    print(F"Time net: {time_net}")
    print(f"Sum time: {time}")
    print('-'*100)
    return time


def main():
    h = hadoop_cluster()
    s = spark_cluster()
    print(h)
    print(s)
    print(f"Ratio hadoop/spark: {h/s}")


if __name__ == "__main__":
    main()
