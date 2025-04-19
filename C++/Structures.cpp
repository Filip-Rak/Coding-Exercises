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

void cpq_input_entry()
{
    int N;
    std::cin >> N;
    CustomPriorityQueue queue(N);
    std::cin.ignore();

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);

        std::string op;
        ss >> op;

        if (op == "enqueue")
        {
            int val, priority;
            ss >> val >> priority;

            queue.enqueue(val, priority);
        }
        else if (op == "dequeue")
        {
            queue.dequeue();
        }
        else
        {
            queue.print_queue();
            break;
        }

    }
}

void custom_queue_entry()
{
    CustomQueue<int> queue;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    for (auto input : inputs)
        queue.push(input);

    queue.clear();

    for (int i = inputs.size() - 1; i >= 0; i--)
        queue.push(inputs[i]);

    {
        auto [f_success, f_data] = queue.front();
        std::cout << "queue.first(): " << f_success << " " << f_data << "\n";
        auto [b_success, b_data] = queue.back();
        std::cout << "queue.back(): " << b_success << " " << b_data << "\n";
    }

    while (true)
    {
        auto ret = queue.pop();
        if (ret.first)
        {
            std::cout << ret.second << " ";
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }

    {
        auto [f_success, f_data] = queue.front();
        std::cout << "queue.first(): " << f_success << " " << f_data << "\n";
        auto [b_success, b_data] = queue.back();
        std::cout << "queue.back(): " << b_success << " " << b_data << "\n";
    }

    std::cout << "\nDEBUG:\n";
    std::cout << "queue.get_alive(): " << queue.get_alive() << "\n";
    std::cout << "queue.empty(): " << queue.empty() << "\n";
}

int CustomStack::Node::active = 0;

CustomStack::Node::Node(int data, Node* next)
    : data(data), next(next) 
{
    this->active += 1;
}

CustomStack::Node::~Node()
{
    this->active -= 1;
}

CustomStack::CustomStack(){}

CustomStack::~CustomStack()
{
    this->clear();
}

void CustomStack::push(int data)
{
    Node* new_node = new Node(data, this->head);
    this->head = new_node;
}

std::optional<int> CustomStack::pop()
{
    if (!this->head)
        return std::nullopt;

    Node* next = this->head->next;
    int data = this->head->data;
    
    delete this->head;
    this->head = next;

    return std::make_optional(data);
}

void CustomStack::clear()
{
    while (this->head)
    {
        Node* next = this->head->next;
        delete this->head;

        this->head = next;
    }
}

int CustomStack::get_alive()
{
    return Node::active;
}

void custom_stack_entry()
{
    CustomStack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.clear();

    stack.push(3);
    stack.push(2);
    stack.push(1);

    while (true)
    {
        auto ret = stack.pop();
        if (ret.has_value())
        {
            std::cout << ret.value() << ", ";
        }
        else
        {
            std::cout << "False on return - Stopping.";
            break;
        }
    }

    std::cout << "\n\nDEBUG:\n";
    std::cout << "stack.get_alive(): " << stack.get_alive() << "\n";
}

void CustomMinHeap::heapify_up(size_t index)
{
    if (index == 0)
        return;

    int parent = (index - 1) / 2;
    if (heap[index] < heap[parent])
    {
        std::swap(heap[index], heap[parent]);
        heapify_up(parent);
    }
}

void CustomMinHeap::heapify_down(size_t index)
{
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;
    size_t smallest = index;

    if (left < heap.size() && heap[left] < heap[smallest])
        smallest = left;    
    
    if (right < heap.size() && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index)
    {
        std::swap(heap[smallest], heap[index]);
        heapify_down(smallest);
    }
}

CustomMinHeap::CustomMinHeap(){}

void CustomMinHeap::push(int data)
{
    heap.push_back(data);
    heapify_up(heap.size() - 1);
}

std::optional<int> CustomMinHeap::pop()
{
    if (heap.empty())
        return std::nullopt;

    int root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);

    return root;
}

int CustomMinHeap::get_size()
{
    return heap.size();
}

void custom_min_heap_entry()
{
    CustomMinHeap heap;

    heap.push(-1);
    heap.push(10);
    heap.push(-15);
    heap.push(8);

    while (true)
    {
        auto ret = heap.pop();
        if (ret.has_value())
        {
            std::cout << ret.value() << " ";
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }

    std::cout << "\nDEBUG:\n";
    std::cout << "heap.get_size(): " << heap.get_size() << "\n";
}

void CustomMaxHeap::heapify_up(size_t index)
{
    if (index == 0)
        return;

    size_t parent = (index - 1) / 2;
    if (heap[parent] < heap[index])
    {
        std::swap(heap[parent], heap[index]);
        heapify_up(parent);
    }
}

void CustomMaxHeap::heapify_down(size_t index)
{
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;
    size_t max = index;

    if (left < heap.size() && heap[max] < heap[left])
        max = left;    
    
    if (right < heap.size() && heap[max] < heap[right])
        max = right;

    if (max != index)
    {
        std::swap(heap[max], heap[index]);
        heapify_down(max);
    }
}

void CustomMaxHeap::push(int val)
{
    heap.push_back(val);
    heapify_up(heap.size() - 1);
}

std::optional<int> CustomMaxHeap::pop()
{
    if (heap.empty())
        return std::nullopt;

    int root_data = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);

    return std::make_optional(root_data);
}

size_t CustomMaxHeap::get_size()
{
    return heap.size();
}

void custom_max_heap_entry()
{
    CustomMaxHeap heap;
    
    heap.push(6);
    heap.push(-2);
    heap.push(8);
    heap.push(4);

    while (true)
    {
        auto ret = heap.pop();
        if (ret.has_value())
        {
            std::cout << ret.value() << " ";
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }

    std::cout << "\nDEBUG:\n";
    std::cout << "heap.get_size(): " << heap.get_size() << "\n";
}
