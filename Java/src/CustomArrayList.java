public class CustomArrayList<T>
{
    /* Attributes */
    private T[] arr;
    private int size = 0;
    private int capacity;

    /* Constructors */
    public CustomArrayList(int capacity)
    {
        this.capacity = capacity;
        this.arr = (T[]) new Object[this.capacity];
    }

    /* Public Methods */
    public Boolean put (T data)
    {
        return this.put(data, this.size);
    }

    public Boolean put(T data, int index)
    {
        if (index == this.capacity)
            this.smart_resize(true);
        else if (index > this.capacity || index < 0)
            return false;

        if (index >= this.size)
            this.size += 1;

        arr[index] = data;
        return true;
    }

    public Boolean insert_at(T data, int index)
    {
        if (index < 0 || index > this.size)
            return false;

        if (this.capacity < this.size + 1)
            this.smart_resize(true);

        this.size += 1;
        for (int i = this.size - 1; i > index; i--)
            this.arr[i] = this.arr[i - 1];

        this.arr[index] = data;
        return true;
    }

    public Pair<Boolean, T> get(int index)
    {
        if (index < 0 || index >= size)
            return new Pair<>(false, null);

        return new Pair<>(true, this.arr[index]);
    }

    public Pair<Boolean, T> pop(int index)
    {
        if (index < 0 || index >= this.size)
            return new Pair<>(false, null);

        T data = this.arr[index];

        for (int i = index; i < this.size - 1; i++)
            this.arr[i] = this.arr[i + 1];

        this.size -= 1;
        this.smart_resize(false);

        return new Pair<>(true, data);
    }

    /* Getter */
    int get_size()
    {
        return this.size;
    }

    int get_capacity()
    {
        return this.capacity;
    }

    /* Private Methods */
    private void smart_resize(Boolean increase)
    {
        if (increase)
            this.resize_raw(this.capacity * 2);
        else
        {
            if (this.size < this.capacity / 2)
                this.resize_raw(this.size);
        }
    }

    private void resize_raw(int new_capacity)
    {
        T[] new_arr = (T[]) new Object[new_capacity];
        for (int i = 0; i < this.size && i < new_capacity; i += 1)
            new_arr[i] = this.arr[i];

        this.capacity = new_capacity;
        this.size = Math.min(this.capacity, this.size);
        this.arr = new_arr;
    }
}
