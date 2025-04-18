import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class CustomPriorityQueue2
{
    public static class Item
    {
        /* Attributes */
        int value;
        int priority;
        int insertion_order;

        /* Constructor */
        Item(int val, int priority, int order)
        {
            this.value = val;
            this.priority = priority;
            this.insertion_order = order;
        }
    }

    /* Attributes */
    private final List<Item> queue = new ArrayList<>();
    private final int capacity;
    private int insert_num = 0;
    private Boolean is_sorted = false;

    /* Constructor */
    public CustomPriorityQueue2(int capacity)
    {
        this.capacity = capacity;
    }

    /* Public Methods */
    public void enqueue(int value, int priority)
    {
        if (this.queue.size() < this.capacity)
        {
            Item new_item = new Item(value, priority, this.insert_num++);
            this.queue.add(new_item);
            this.is_sorted = false;
        }
        else if(this.queue.size() == this.capacity)
        {
            Item min = Collections.min(this.queue, this.priorityComparator());

            if (min.priority < priority)
            {
                min.priority = priority;
                min.value = value;
                min.insertion_order = this.insert_num++;
                this.is_sorted = false;
            }
        }
    }

    public void dequeue()
    {
        if(this.queue.isEmpty())
            return;

        if (!this.is_sorted)
            this.sort_queue();

        this.queue.removeLast();
    }

    public void print_state()
    {
        if (!this.is_sorted)
            this.sort_queue();

        for (int i = this.queue.size() - 1; i >= 0; i -= 1)
            System.out.print(this.queue.get(i).value + " ");
    }

    /* Private Methods */
    private void sort_queue()
    {
        this.queue.sort(this.priorityComparator());
        this.is_sorted = true;
    }

    private Comparator<Item> priorityComparator()
    {
        return (a, b) ->
        {
            if (a.priority != b.priority)
                return a.priority - b.priority;

            return b.insertion_order - a.insertion_order;
        };
    }
}
