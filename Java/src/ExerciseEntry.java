import java.util.ArrayList;
import java.util.List;

public class ExerciseEntry
{
    public static void priority_queue_entry()
    {
        CustomPriorityQueue pq = new CustomPriorityQueue(4);
        List<Integer> data = List.of(1, 6, -8, -3, -4);
        List<Integer> priorities = List.of(2, 1, 3, 3, 2);

        for (int i = 0; i < data.size(); i++)
        {
            boolean success = pq.enqueue(data.get(i), priorities.get(i));
            if (!success)
                System.out.println("Failed to enqueue: " + data.get(i) + ", " + priorities.get(i));
        }

        pq.dequeue();
        pq.dequeue();
        pq.dequeue();
        pq.enqueue(20, 35);
        pq.dequeue();
        pq.dequeue();
        pq.dequeue();
    }
}
