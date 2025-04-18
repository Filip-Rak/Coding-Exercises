import java.util.List;
import java.util.PriorityQueue;
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

    public static void custom_array_list_entry()
    {
        CustomArrayList<Integer> arr = new CustomArrayList<>(4);
        List<Integer> inputs = List.of(1, 2, 3, 4, 5, 6);

        for (int input : inputs)
            arr.put(input);

        arr.put(10, 0);
        arr.insert_at(20, 2);
        arr.insert_at(30, 4);
        arr.insert_at(40, 6);

        System.out.print("arr.pop(): ");
        for (int i = 0; i < 3; i++)
        {
            Pair<Boolean, Integer> ret = arr.pop(0);
            if (ret.first)
            {
                System.out.print(ret.second + ", ");
            }
            else
            {
                System.out.print("False on return - Stopping");
                break;
            }

        }

        System.out.print("\narr.get(): ");
        int index = 0;
        while(true)
        {
            Pair<Boolean, Integer> ret = arr.get(index);
            if (ret.first)
            {
                System.out.print(ret.second + ", ");
                index += 1;
            }
            else
            {
                System.out.print("False on return - Stopping.\n");
                break;
            }
        }

        System.out.println("\nDEBUG:");
        System.out.println("arr.get_size(): " + arr.get_size());
        System.out.println("arr.get_capacity(): " + arr.get_capacity());
    }

    public static void pq_entry2()
    {
        CustomPriorityQueue2 queue = new CustomPriorityQueue2(4);

        queue.enqueue(3, 3);
        queue.enqueue(1, 1);
        queue.enqueue(4, 4);
        queue.enqueue(2, 2);    // 4, 3, 2, 1

        queue.dequeue();    // 3, 2, 1
        queue.enqueue(5, 5);    // 5, 3, 2, 1
        queue.enqueue(6, 6);    // 6, 5, 3, 2
        queue.enqueue(1, 1);    // 6, 5, 3, 2
        queue.dequeue();  // 5, 3, 2
        queue.dequeue();  // 3, 2
        queue.enqueue(30, 3);
        queue.dequeue();

        queue.print_state();
    }
}
