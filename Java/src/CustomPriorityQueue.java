import java.util.*;

public class CustomPriorityQueue
{
    /* Types */
    public static class Item implements Comparable<Item>
    {
        /* Attributes */
        int data;
        int priority;

        /* Constructor */
        public Item(int data, int priority)
        {
            this.data = data;
            this.priority = priority;
        }

        /* Interfaces */
        @Override
        public int compareTo(Item o)
        {
            return (this.priority - o.priority);
        }
    }

    /* Attributes */
    private final ArrayList<Item> queue = new ArrayList<>();
    private boolean is_sorted = false;
    private final int CAPACITY;

    /* Constructor & Destructor */
    public CustomPriorityQueue(int capacity)
    {
        this.CAPACITY = capacity;
    }

    /* Public Methods */
    public boolean enqueue(int data, int priority)
    {
        if (queue.size() >= this.CAPACITY)
            return false;

        Item new_item = new Item(data, priority);
        queue.addLast(new_item);
        this.is_sorted = false;

        return true;
    }

    public void dequeue()
    {
        if (queue.isEmpty())
            return;

        if (!is_sorted)
        {
            Collections.sort(queue);
            this.is_sorted = true;
        }

        Item max_priority = queue.getLast();
        queue.removeLast();

        System.out.println("Removed Item: ("
                + max_priority.data + ", "
                + max_priority.priority + ")");
    }
}
