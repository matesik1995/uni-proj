import java.io.File

data class Task(val processingTime: Int, val earlyPenalty: Int, val latePenalty: Int) {
  companion object {
    fun fromString(string: String): Task {
      val values = string.split(' ')
          .filter { it.isNotEmpty() }
          .map { it.toInt() }
      return Task(values[0], values[1], values[2])
    }
  }
}

class Scheduler(
    val id: Int,
    val tasks: List<Task>
) {
  val totalProcessingTime by lazy { tasks.map { it.processingTime }.sum() }
}

fun main(args: Array<String>) {
  val schedulers = parseFile(args[0])

  schedulers.forEach { println("k = ${it.id}, ${it.totalProcessingTime}") }

}

private fun parseFile(fileName: String): List<Scheduler> {
  val lines = mutableListOf<String>()
  File(fileName).forEachLine { lines.add(it.trim()) }
  val schedulers = mutableListOf<Scheduler>()

  val instances = lines.removeAt(0).toInt()
  for (k in 1..instances) {
    val tasks = mutableListOf<Task>()
    val size = lines.removeAt(0).toInt()
    for (j in 1..size) {
      tasks.add(Task.fromString(lines.removeAt(0)))
    }
    schedulers.add(Scheduler(k, tasks))
  }

  return schedulers
}