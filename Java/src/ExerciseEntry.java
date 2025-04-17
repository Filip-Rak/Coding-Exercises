import java.util.List;
import java.util.Set;

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

    public static void linked_list_entry()
    {
        CustomLinkedList<Integer> list = new CustomLinkedList<>();
        List<Integer> inputs = List.of(1, 2, 3, 4, 5, 6);

        for (int input : inputs)
            list.push_back(input);

        // list.reverse();
        Pair<Boolean, Integer> ret_val = list.pop_at(1);
        System.out.println("list.pop_at(): " + ret_val.first + " " + ret_val.second);

        System.out.print("list.pop_back(): ");
        while(true)
        {
            Pair<Boolean, Integer> res = list.pop_front();
            if (res.first)
            {
                System.out.print(res.second + " ");
            }
            else
            {
                System.out.println("\nlist.pop_back(): False on return - stopped");
                break;
            }
        }

        System.out.println("\nDebug:\nlist.get_list_size(): " + list.get_list_size());
    }
}
