import scala.util.Random

val groups = Map(0->(0, 1), 1->(1, 1), 2->(2, 2), 3->(3, 3), 4->(4, 3), 5->(5, 2), 6->(6, 1))

val n = 1000000

val random = Random

val data = sc.parallelize(for (i <- 1 to n) yield {
	val g = random.nextInt(7); 
	val (mu, sigma) = groups(g); 
	(g, mu + sigma*random.nextGaussian())
})

val resultsForGroups = data.
	map(t => (t._1, (1, t._2, t._2*t._2))).
	reduceByKey((acc, n) => (acc._1 + n._1, acc._2 + n._2, acc._3 + n._3)).
	cache()

resultsForGroups.
	map { case(k, t) => (k, t._1, t._2/t._1, ((t._3 - (t._2*t._2)/t._1)/t._1)) }.
	foreach { case(k, n, av, va) => println(s"Group: $k - Count: $n, avarage: $av, variance: $va") }
	
val result = resultsForGroups.
	map { case(k, t) => t }.
	reduce((acc, n) => (acc._1 + n._1, acc._2 + n._2, acc._3 + n._3))
	
val (n, av, va) = (result._1, result._2/result._1, (result._3 - (result._2*result._2)/result._1)/result._1)
println(s"All - Count: $n, avarage: $av, variance: $va")
