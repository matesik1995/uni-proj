package put.cs.idss.pmds.bloomfilter

import java.util.*
import kotlin.math.pow

fun main(args: Array<String>) {

    val n = 10_000
    val range = 100_000_000
    val factor = 20.0
    val size = Math.round(factor * n).toInt()

    // optimal k value is ln2 * m/n
    val k = Math.round(Math.log(2.0) * factor).toInt()
//    val k = 5

    val random = Random()

    val bf = BloomFilter(size, k, range)

    val set = HashSet<Int>(n)

    while (set.size < n) {
        set.add(random.nextInt(range))
    }

    for (item in set) {
        bf.add(item)
    }

    var TP = 0
    var FP = 0
    var TN = 0
    var FN = 0

    for (i in 0 until range) {
        val containsBF = bf.contains(i)!!
        val containsHS = set.contains(i)

        if (containsBF && containsHS) {
            TP++
        }
        if (!containsBF && !containsHS) {
            TN++
        }
        if (!containsBF && containsHS) {
            FN++
        }
        if (containsBF && !containsHS) {
            FP++
        }
    }

    println("TP = %6d\tTPR = %.4f".format(TP, TP.toDouble() / n.toDouble()))
    println("TN = %6d\tTNR = %.4f".format(TN, TN.toDouble() / (range - n).toDouble()))
    println("FN = %6d\tFNR = %.4f".format(FN, FN.toDouble() / n.toDouble()))
    println("FP = %6d\tFPR = %.4f".format(FP, FP.toDouble() / (range - n).toDouble()))
    println("Excpected FPR if k optimal: %.4f".format(Math.pow(1.0/2.0, Math.log(2.0) * factor)))
    println("Expected FPR: %.4f".format((1 - Math.E.pow(-k/factor)).pow(k)))
}

class BloomFilter(private val size: Int, k: Int, range: Int) {
    private val bitSet: BitSet = BitSet(size)
    private val hashFunctions: List<HashFunction>

    init {
        val p = getPrimeNumberBiggerThan(range)
        val tempList = mutableListOf<HashFunction>()
        for (i in 1..k) {
            tempList.add(HashFunction(p))
        }
        hashFunctions = tempList
    }

    fun add(key: Int) {
        for (hashFunction in hashFunctions) {
            val bit = hashFunction.hash(key) % size
            bitSet.set(bit)
        }
    }

    fun contains(key: Int): Boolean? {
        for (hashFunction in hashFunctions) {
            val bit = hashFunction.hash(key) % size
            if (!bitSet[bit]) return false
        }
        return true
    }

    class HashFunction(p: Int) {
        private val a: Long
        private val b: Long
        private val p: Long = p.toLong()

        init {
            val random = Random()
            a = (random.nextInt(p - 1) + 1).toLong()
            b = (random.nextInt(p)).toLong()
            println("$a, $b")
        }

        fun hash(x: Int): Int {
            return ((a * x.toLong() + b) % p).toInt()
        }
    }

    private fun getPrimeNumberBiggerThan(init: Int): Int {
        var num = init + 1
        while (!isPrime(num)) num++
        return num
    }

    private fun isPrime(num: Int): Boolean {
        for (i in 2..num / 2) {
            if (num % i == 0) {
                return false
            }
        }
        return true
    }
}
