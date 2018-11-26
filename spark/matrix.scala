val M = sc.
	textFile("/home/matesik/tmp/M.txt").
	map(line => {
		val t = line.split(" ");
		(t(0).trim.toInt, t(1).trim.toInt, t(2).trim.toDouble)
	}).
	map { case(i, j, a) => (j, ("M", i, a)) }

val N = sc.
	textFile("/home/matesik/tmp/N.txt").
	map(line => {
		val t = line.split(" ");
		(t(0).trim.toInt, t(1).trim.toInt, t(2).trim.toDouble)
	}).
	map { case(j, k, b) => (j, ("N", k, b)) }

val result = M.join(N).
	map { case(k, (a, b)) => {
		if (a._1 == "M") {
			((a._2, b._2), a._3*b._3)
		} else {
			((b._2, a._2), a._3*b._3)
		}
	} }.
	reduceByKey(_ + _).
	sortByKey().
	collect
	
result.foreach { case((i,k), v) => println(s"$i $k\t$v") }
