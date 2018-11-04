import java.io.File
import kotlin.math.abs
import kotlin.math.floor
import kotlin.system.measureTimeMillis

data class Task(val id: Int, val processingTime: Int, val earlyPenalty: Int, val latePenalty: Int) {
  companion object {
    fun fromString(id: Int, string: String): Task {
      val values = string.split(' ')
          .filter { it.isNotEmpty() }
          .map { it.toInt() }
      return Task(id, values[0], values[1], values[2])
    }
  }
}

class Scheduler(
    val id: Int,
    val tasks: List<Task>
) {
  val totalProcessingTime by lazy { tasks.map { it.processingTime }.sum() }

  fun getDeadline(h: Float): Int {
    return floor(totalProcessingTime * h).toInt()
  }

  fun scheduleTasks(): List<Task> {
    return tasks.sortedBy { (it.earlyPenalty - it.latePenalty) * it.processingTime }
  }

  fun getMiddlePoint(tasks: List<Task>): Int {
    val t = tasks.minBy { abs((it.earlyPenalty - it.latePenalty) * it.processingTime) }
    val k = tasks.indexOf(t)
    var s = 0
    for (i in 0 until k) {
      s += tasks[i].processingTime
    }
    return s
  }
}

object Scorer {
  fun calculate(deadline: Int, tasks: List<Task>, startTime: Int = 0): Int {
    var score = 0
    var time = startTime
    for (task in tasks) {
      time += task.processingTime
      score += if (time < deadline) {
        abs(deadline - time) * task.earlyPenalty
      } else {
        abs(deadline - time) * task.latePenalty
      }
    }
    return score
  }
}

fun main(args: Array<String>) {
  if (args[0] == "check") {
    val instanceFileName = args[1]
    val instance = args[2].toInt()
    val resultFileName = args[3]
    val schedulers = loadInstancesFromFile(instanceFileName)
    val s = schedulers[instance-1]
    try {
      val r = loadResultFromFile(resultFileName)
      val tasks = r.taskIds.map { taskId -> s.tasks.find { it.id == taskId }!! }
      val score = Scorer.calculate(s.getDeadline(r.h), tasks, r.r)
      if (score == r.score) {
        println("OK")
      } else {
        println("NOT OK")
      }
    } catch (e: Exception) {
      println("NOT OK")
    }
  } else
  when (args.size){
     1 -> {
      val schedulers = loadInstancesFromFile(args[0])
      val hList = listOf(0.2f, 0.4f, 0.6f, 0.8f)
      for (h in hList) {
        schedulers.forEach {
          lateinit var tasks: List<Task>
          println("Time: ${measureTimeMillis { tasks = it.scheduleTasks() }}")
          val start = if (it.getDeadline(h) - it.getMiddlePoint(tasks) > 0) {
            it.getDeadline(h) - it.getMiddlePoint(tasks)
          } else {
            0
          }
          val score = Scorer.calculate(it.getDeadline(h), tasks, start)
          saveToFile(tasks.size, it.id, h, score, tasks)
        }
      }
    }
    2 -> {
      val schedulers = loadInstancesFromFile(args[0])
      val h = args[1].toFloat()
      schedulers.forEach {
        lateinit var tasks: List<Task>
        println("Time: ${measureTimeMillis { tasks = it.scheduleTasks() }}")
        val start = if (it.getDeadline(h) - it.getMiddlePoint(tasks) > 0) {
          it.getDeadline(h) - it.getMiddlePoint(tasks)
        } else {
          0
        }
        val score = Scorer.calculate(it.getDeadline(h), tasks, start)
        saveToFile(tasks.size, it.id, h, score, tasks)
      }
    }
    3 -> {
      val schedulers = loadInstancesFromFile(args[0])
      val h = args[1].toFloat()
      val s = schedulers[args[2].toInt()-1]
      lateinit var tasks: List<Task>
      println("Time: ${measureTimeMillis { tasks = s.scheduleTasks() }}")
      val start = if (s.getDeadline(h) - s.getMiddlePoint(tasks) > 0) {
        s.getDeadline(h) - s.getMiddlePoint(tasks)
      } else {
        0
      }
      val score = Scorer.calculate(s.getDeadline(h), tasks, start)
      saveToFile(tasks.size, s.id, h, score, tasks)
    }
    else -> println("Bad input arguments. Usage: java -jar scheduler.jar input_file [factor_h] [instance_num]")
  }
}

private fun loadInstancesFromFile(fileName: String): List<Scheduler> {
  val lines = mutableListOf<String>()
  File(fileName).forEachLine { lines.add(it.trim()) }
  val schedulers = mutableListOf<Scheduler>()

  val instances = lines.removeAt(0).toInt()
  for (k in 1..instances) {
    val tasks = mutableListOf<Task>()
    val size = lines.removeAt(0).toInt()
    for (j in 0 until size) {
      tasks.add(Task.fromString(j, lines.removeAt(0)))
    }
    schedulers.add(Scheduler(k, tasks))
  }

  return schedulers
}

data class Result(val score: Int, val h: Float, val r: Int, val taskIds: List<Int>);

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
private fun saveToFile(instanceSize: Int, instanceNumber: Int, h: Float, score: Int, tasks: List<Task>, startTime: Int = 0) {
  val f = File("results/n${instanceSize}k${instanceNumber}h${(h * 10).toInt()}.txt")
  println("Filename: n${instanceSize}k${instanceNumber}h${(h * 10).toInt()}.txt")

  val taskString = tasks.map { it.id }
      .joinToString(" ")
  f.writeText("$score $h $startTime $taskString")
  println("Value: $score $h $startTime $taskString")
}

