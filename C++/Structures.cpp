#include "Structures.h"

void custom_list2_entry()
{
    CustomList2<int> list;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    for (int input : inputs)
        list.push_front(input);

    list.reverse();
    std::cout << "list.contains(6): " << list.contains(6) << "\n";
    std::cout << "list.insert_at(20, x): " << list.insert_at(20, 6) << "\n";
    
    auto [success, data] = list.pop_at(0);
    std::cout << "list.pop_at(x) -> Success: " << success << ", Data: " << data << "\n";

    std::cout << "list.to_vector(): ";
    for (int num : list.to_vector())
    {
        std::cout << num << " ";
    }

    CustomList2<int> list2 = list;

    std::cout << "\nlist.pop_front()/list.pop_back(): ";
    // while(list.get_size() > 0)
    while (true)
    {
        auto res = list.pop_front();
        if (res.first)
            std::cout << res.second << ", ";
        else
        {
            std::cout << "Out of elements!";
            break;
        }
    }

    std::cout << "\nlist2.pop_front()/list2.pop_back(): ";
    while (true)
    {
        auto res = list2.pop_front();
        if (res.first)
            std::cout << res.second << ", ";
        else
        {
            std::cout << "Out of elements!";
            break;
        }
    }

    std::cout << "\nlist.contains(6): " << list.contains(6);
    std::cout << "\n\nActive nodes debug: " << list.get_debug_active_nodes() << "\n";
}

void custom_vector_entry()
{
    CustomVector<int> arr;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    arr.push_back(-10);
    arr.push_back(-20);

    try 
    {
        arr[1] = 35;
    }
    catch (std::out_of_range exception)
    {
        std::cout << "Exception: " << exception.what() << "\n";
    }

    std::cout << "arr.contains(): " << arr.contains(35) << "\n";

    // arr.clear();

    for (int input : inputs)
        arr.push_back(input);

    arr.resize(5);
    std::cout << "arr.nsert_at(): " << arr.insert_at(10, 5) << "\n";
    std::cout << "arr.put(): " << arr.put(5, 6) << "\n";

    int index = 0;
    while(true)
    {
        auto ret = arr.get(index++);
        if (ret.first)
            std::cout << "arr[" << index - 1 << "] = " << ret.second << "\n";
        else
            break;
    }
}

CustomPriorityQueue::Item::Item(int value, int priority, int insertion_order)
    : value(value), priority(priority), insertion_order(insertion_order) {}

CustomPriorityQueue::CustomPriorityQueue(int capacity)
    : capacity(capacity) {}

void CustomPriorityQueue::enqueue(int val, int priority)
{
    if (this->queue.size() < this->capacity)
    {
        Item new_item(val, priority, this->insert_order++);
        this->queue.push_back(new_item);
        this->is_sorted = false;
    }
    else if (this->queue.size() == this->capacity)
    {
        auto max =  std::min_element(this->queue.begin(), this->queue.end(), CustomPriorityQueue::item_comparator);
        if (max->priority < priority)
        {
            max->priority = priority;
            max->value = val;
            max->insertion_order = this->insert_order++;

            this->is_sorted = false;
        }
    }
}

void CustomPriorityQueue::dequeue()
{
    if (this->queue.size() == 0)
        return;

    if (!this->is_sorted)
    {
        std::sort(this->queue.begin(), this->queue.end(), CustomPriorityQueue::item_comparator);
        this->is_sorted = true;
    }

    this->queue.pop_back();
}

void CustomPriorityQueue::print_queue()
{
    if (!is_sorted)
    {
        std::sort(this->queue.begin(), this->queue.end(), CustomPriorityQueue::item_comparator);
        this->is_sorted = true;
    }

    for (int i = this->queue.size() - 1; i >= 0; i--)
        std::cout << queue[i].value << " ";
}

bool CustomPriorityQueue::item_comparator(const Item& a, const Item& b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;

    return b.insertion_order < a.insertion_order;
}

void cpq_test_entry()
{
    CustomPriorityQueue queue(5);

    queue.enqueue(1, 1); 
    queue.enqueue(5, 5);    
    queue.enqueue(2, 2);
    queue.enqueue(3, 3);
    queue.enqueue(4, 4);    // 1, 2, 3, 4, 5
    queue.enqueue(6, 6);    // 2, 3, 4, 5, 6
    queue.enqueue(60, 6);   // 3, 4, 5, 60, 6

    queue.dequeue();    // 3, 4, 5, 60
    queue.print_queue();
}