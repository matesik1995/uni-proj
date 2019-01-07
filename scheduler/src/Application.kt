import java.io.File
import java.time.Instant
import java.util.regex.Pattern
import kotlin.math.floor
import kotlin.system.exitProcess

const val TIME_LIMIT_IN_MILLISECONDS = 60 * 1000

data class Instance(val id: Int, val tasks: List<Task>, val h: Float) {
  val totalProcessingTime by lazy { tasks.map { it.processingTime }.sum() }
  val deadline by lazy { floor(totalProcessingTime * h).toInt() }
}

fun main(args: Array<String>) {
  if (args[0] == "check") {
    val instanceFileName = args[1]
    val resultFileName = args[2]

    val pattern = Pattern.compile("\\d+")
    val matcher = pattern.matcher(resultFileName)
    val numberList = mutableListOf<Int>()
    while(matcher.find())
      numberList.add(matcher.group().toInt())
    if (numberList.size != 3) {
      println("Bad input arguments. Usage: java -jar scheduler.jar check instance_filename results_filename")
      exitProcess(1)
    }
    val instanceNum = numberList[1]
    val hList = listOf(numberList[2]/10f)

    val instances = loadInstancesFromFile(instanceFileName, hList)
    val instance = instances[instanceNum-1]
    try {
      val r = loadResultFromFile(resultFileName)
      val tasks = r.taskIds.map { taskId -> instance.tasks.find { it.id == taskId }!! }
      val schedule = Schedule(tasks, r.r)
      val score = Scorer.calculate(schedule, instance.deadline)
      if (score == r.score) {
        println("OK")
      } else {
        println("NOT OK")
      }
    } catch (e: Exception) {
      println("MORE NOT OK")
    }
  } else {
    val hList: List<Float>
    var instanceNum: Int? = null
    when (args.size){
      1 -> {
        hList = listOf(0.2f, 0.4f, 0.6f, 0.8f)
      }
      2 -> {
        hList = listOf(args[1].toFloat())
      }
      3 -> {
        hList = listOf(args[1].toFloat())
        instanceNum = args[2].toInt() - 1
      }
      else -> {
        println("Bad input arguments. Usage: java -jar scheduler.jar input_file [factor_h] [instance_num]")
        exitProcess(1)
      }
    }
    val instances = loadInstancesFromFile(args[0], hList)

    // JIT Warm up:
    println("Warm up - start")
    val warmUpInstances = listOf(
        Instance(999, instances[0].tasks, 1f),
        Instance(999, instances[1].tasks, 0.5f),
        Instance(999, instances[2].tasks, 0f)
    )
    warmUpInstances.forEach { doCalculation(it) }
    println("Warm up - end")

    // Proper calculations
    if (instanceNum == null) {
      instances.forEach {
        val result = doCalculation(it)
        saveToFile(it, result)
      }
    } else {
      val result = doCalculation(instances[instanceNum])
      saveToFile(instances[instanceNum], result)
    }
  }
}

private fun doCalculation(instance: Instance) : Result {
  val initSchedule = SortScheduler.schedule(instance)
  var score = Scorer.calculate(initSchedule, instance.deadline)
  var schedule = initSchedule
  val startTime = Instant.now().toEpochMilli()
  val endTime = startTime + TIME_LIMIT_IN_MILLISECONDS
  var lastUpgradeTime = 0L
  while (Instant.now().toEpochMilli() < endTime) {
    val evolution = Evolution(schedule, instance.totalProcessingTime, 1)
    val descendants = evolution.generateDescendants(20)
    for (descendant in descendants) {
      val newScore = Scorer.calculate(descendant, instance.deadline)
      if (newScore < score) {
        lastUpgradeTime = Instant.now().toEpochMilli() - startTime
//        println("Better score $newScore (${newScore-score}) after $lastUpgradeTime ms")
        score = newScore
        schedule = descendant
      }
    }
  }
  println("$score\t\t\tLast upgrade time: $lastUpgradeTime")
  return Result(score, instance.h, schedule.startTime, schedule.tasks.map { it.id })
}

private fun loadInstancesFromFile(fileName: String, hList: List<Float>): List<Instance> {
  val lines = mutableListOf<String>()
  File(fileName).forEachLine { lines.add(it.trim()) }
  val instances = mutableListOf<Instance>()

  val instancesCount = lines.removeAt(0).toInt()
  for (k in 1..instancesCount) {
    val tasks = mutableListOf<Task>()
    val size = lines.removeAt(0).toInt()
    for (j in 0 until size) {
      tasks.add(Task.fromString(j, lines.removeAt(0)))
    }
    hList.forEach { instances.add(Instance(k, tasks, it)) }
  }

  return instances
}

private fun loadResultFromFile(fileName: String): Result {
  val lines = mutableListOf<String>()
  File(fileName).forEachLine { lines.add(it.trim()) }
  val values = lines[0].split(' ')
  val taskIds = mutableListOf<Int>()
  for (i: Int in 3 until values.size) {
    taskIds.add(values[i].toInt())
  }
  return Result(values[0].toInt(), values[1].toFloat(), values[2].toInt(), taskIds)
}

/**
 * Format danych wyjściowych:
 *  - nazwa pliku: n[rozmiar_instancji]k[numer_instancji]h[wartosc_wsp*10].txt
 *    np: n10k2h2.txt
 *  - format danych: Fcelu WspolczynikH, CzasRozpoczeciaR, ids...
 *    np: 123 0.2 15 2, 5, 3, 1, 7, 6, 4
 */

private fun saveToFile(instance: Instance, result: Result) {
  val f = File("results/n${instance.tasks.size}k${instance.id}h${(instance.h * 10).toInt()}.txt")
  val taskString = result.taskIds.joinToString(" ")
  f.writeText("${result.score} ${instance.h} ${result.r} $taskString")

//  println("Filename: n${instance.tasks.size}k${instance.id}h${(instance.h * 10).toInt()}.txt")
//  println("Value: $score ${instance.h} ${schedule.startTime} $taskString")
}
