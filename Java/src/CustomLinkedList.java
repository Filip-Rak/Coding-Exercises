public class CustomLinkedList<T>
{
    /* Types */
    public class Node
    {
        /* Attributes */
        static int active = 0;

        T data;
        Node next;

        /* Constructors & Destructor */
        Node(T data)
        {
            this(data, null);
        }

        Node(T data, Node next)
        {
            this.data = data;
            this.next = next;

            Node.active += 1;
        }
    }

    /* Attributes */
    private Node head = null;
    private int list_size = 0;

    /* Constructors */
    public CustomLinkedList() {}

    /* Public Methods */
    public void push_back(T data)
    {
        Node new_node = new Node(data);

        if (this.head == null)
        {
            this.head = new_node;
            this.list_size += 1;
            return;
        }

        Node tgt = this.head;
        while(tgt.next != null)
        {
            tgt = tgt.next;
        }

        tgt.next = new_node;
        this.list_size += 1;
    }

    public void push_front(T data)
    {
        this.head = new Node(data, this.head);
        this.list_size += 1;
    }

    public Pair<Boolean, T> pop_back()
    {
        if (this.head == null)
            return new Pair<>(false,  null);

        if (this.head.next == null)
        {
            T data = head.data;
            head = null;
            this.list_size -= 1;
            return new Pair<>(true, data);
        }

        Node tgt = this.head;
        Node prev = tgt;
        while(tgt.next != null)
        {
            prev = tgt;
            tgt = tgt.next;
        }

        T data = tgt.data;
        prev.next = null;
        this.list_size -= 1;

        return new Pair<>(true, data);
    }

    public Pair<Boolean, T> pop_front()
    {
        if (this.head == null)
            return new Pair<>(false, null);

        Node to_pop = this.head;
        this.head = this.head.next;
        this.list_size -= 1;

        return new Pair<>(true, to_pop.data);
    }

    public Pair<Boolean, T> pop_at(int target_index)
    {
        if (this.head == null || target_index < 0)
            return new Pair<>(false, null);

        if (target_index == 0)
        {
            Node popped_node = this.head;
            this.head = this.head.next;

            this.list_size -= 1;
            return new Pair<>(true, popped_node.data);
        }

        Node tgt = this.head;
        int index = 1;

        while(tgt != null && index < target_index)
        {
            tgt = tgt.next;
            index += 1;
        }

        if (tgt == null || tgt.next == null)
            return new Pair<>(false, null);

        T data = tgt.next.data;
        tgt.next = tgt.next.next;

        return new Pair<>(true, data);
    }

    public void reverse()
    {
        Node tgt = this.head;
        Node prev = null;

        while(tgt != null)
        {
            Node next = tgt.next;
            tgt.next = prev;

            prev = tgt;
            tgt = next;
        }

        this.head = prev;
    }

    /* Getters */
    public int get_list_size()
    {
        return this.list_size;
    }
}
