import java.lang.Math.max
import java.util.Random

class Evolution(val schedule: Schedule, val totalProcessingTime: Int, val mutationNumbers: Int = 1) {
  val random = Random()

  fun generateDescendants(descendantsNumber: Int) : List<Schedule> {
    val descendants = mutableListOf<Schedule>()
    for (i in 0..descendantsNumber) {
      val descendant = mutate()
      descendants.add(descendant)
    }
    return descendants
  }

  private fun mutate() : Schedule {
    val mutatedTasks = mutableListOf<Task>()
    mutatedTasks.addAll(schedule.tasks)
    for (i in 0..mutationNumbers) {
      val idx1 = random.nextInt(schedule.tasks.size)
      val idx2 = random.nextInt(schedule.tasks.size)
      val tmpTask = mutatedTasks[idx1]
      mutatedTasks[idx1] = mutatedTasks[idx2]
      mutatedTasks[idx2] = tmpTask
    }

    val timeRange = totalProcessingTime / 4
    val start = max(0, schedule.startTime + random.nextInt(timeRange) - timeRange / 2)

    return Schedule(mutatedTasks, start)
  }
}