import kotlin.math.abs

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

data class Schedule(val tasks: List<Task>, val startTime: Int)

object SortScheduler {
  fun schedule(instance: Instance): Schedule {
    val sortedTasks = instance.tasks.sortedBy { (it.earlyPenalty - it.latePenalty) * it.processingTime }
    val startTime = getStartTime(sortedTasks, instance.deadline)
    return Schedule(sortedTasks, startTime)
  }

  private fun getStartTime(tasks: List<Task>, deadline: Int) : Int {
    val t = tasks.minBy { abs((it.earlyPenalty - it.latePenalty) * it.processingTime) }
    val k = tasks.indexOf(t)

    var s = 0
    for (i in 0 until k) {
      s += tasks[i].processingTime
    }
    return if (deadline - s > 0) deadline - s else 0
  }
}