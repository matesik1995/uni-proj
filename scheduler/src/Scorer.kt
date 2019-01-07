import kotlin.math.abs

data class Result(val score: Int, val h: Float, val r: Int, val taskIds: List<Int>)

object Scorer {
  fun calculate(schedule: Schedule, deadline: Int): Int {
    var score = 0
    var time = schedule.startTime
    for (task in schedule.tasks) {
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