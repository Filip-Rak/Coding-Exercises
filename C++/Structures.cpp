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
    if (heap[index] > heap[parent])
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

    if (left < heap.size() && heap[left] > heap[max])
        max = left;    
    
    if (right < heap.size() && heap[right] > heap[max])
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

void CustomMinStack::push(int val)
{
    main.push(val);
    
    if (min.empty() || val <= min.top())
        min.push(val);
}

void CustomMinStack::pop()
{
    if (main.empty())
        return;

    int top = main.top();
    main.pop();

    if (top == min.top())
        min.pop();
}

std::optional<int> CustomMinStack::get_top() const
{
    if (main.empty())
        return std::nullopt;

    return std::make_optional(main.top());
}

std::optional<int> CustomMinStack::get_min() const
{
    if (min.empty())
        return std::nullopt;

    return std::make_optional(min.top());
}

size_t CustomMinStack::get_min_size()
{
    return min.size();
}

size_t CustomMinStack::get_main_size()
{
    return main.size();
}

void custom_min_stack_entry()
{
    CustomMinStack stack;

    stack.push(1);
    stack.push(-1);
    stack.push(4);
    stack.push(-3);
    stack.push(-2);
    stack.push(-2);
    stack.push(6);

    while (true)
    {
        auto ret = stack.get_top();
        if (ret.has_value())
        {
            auto min = stack.get_min();
            std::string min_str = "no value";
            if (min.has_value())
                min_str = std::to_string(min.value());

            std::cout << "top: " << ret.value() << "\tmin: " << min_str << "\tmin_size: " << stack.get_min_size() 
                << "\tmain size: " << stack.get_main_size() << "\n";

            stack.pop();
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }
}

int CustomStack2::Node::alive = 0;

CustomStack2::Node::Node(int val, Node* next)
    : val(val), next(next) 
{
    Node::alive += 1;
}

CustomStack2::Node::~Node()
{
    Node::alive -= 1;
}

CustomStack2::~CustomStack2()
{
    while (head)
    {
        Node* next = head->next;
        delete head;
        head = head->next;
    }
}

void CustomStack2::push(int val)
{
    Node* new_node = new Node(val, head);
    head = new_node;
    size += 1;
}

std::optional<int> CustomStack2::pop()
{
    if (!head)
        return std::nullopt;

    Node* next = head->next;
    int val = head->val;

    delete head;
    head = next;
    size -= 1;

    return std::make_optional(val);
}

std::optional<int> CustomStack2::top() const
{
    if (!head)
        return std::nullopt;

    return std::make_optional(head->val);
}

int CustomStack2::get_alive() const
{
    return Node::alive;
}

bool CustomStack2::empty() const
{
    return size == 0;
}

size_t CustomStack2::get_size() const
{
    return size;
}

void custom_stack2_test_entry()
{
    CustomStack2 stack;

    stack.push(1);
    stack.push(2);

    stack.pop();
    stack.pop();

    stack.push(3);
    stack.push(4);

    while (true)
    {
        auto ret_top = stack.top();
        auto ret_pop = stack.pop();

        if (ret_pop.has_value())
        {
            std::string top_str = "false";
            if (ret_top.has_value())
                top_str = std::to_string(ret_top.value());

            std::cout << "Pop: " << ret_pop.value() 
                << " Top: " << top_str 
                << " Alive: " << stack.get_alive()
                << "\n";
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }
}

void CustomMaxStack::push(int val)
{
    main.push(val);

    if (max.empty() || val >= max.top().value())
        max.push(val);
}

void CustomMaxStack::pop()
{
    auto pop_main = main.pop();
    if (!pop_main.has_value())
        return;

    if (pop_main.value() == max.top().value())
        max.pop();
}

std::optional<int> CustomMaxStack::get_top() const
{
    return main.top();
}

std::optional<int> CustomMaxStack::get_max() const
{
    return max.top();
}

size_t CustomMaxStack::get_max_size() const
{
    return max.get_size();
}

size_t CustomMaxStack::get_main_size() const
{
    return main.get_size();
}

int CustomMaxStack::get_alive() const
{
    return main.get_alive();
}

void custom_max_stack_entry()
{
    CustomMaxStack stack;

    stack.push(1);
    stack.push(-1);
    stack.push(4);
    stack.push(6);
    stack.push(-3);
    stack.push(-2);
    stack.push(-2);

    while (true)
    {
        auto ret = stack.get_top();
        if (ret.has_value())
        {
            auto min = stack.get_max();
            std::string min_str = "no value";
            if (min.has_value())
                min_str = std::to_string(min.value());

            std::cout << "top: " << ret.value() << "\tmax: " << min_str << "\tmax_size: " << stack.get_max_size()
                << "\tmain size: " << stack.get_main_size() << "\n";

            stack.pop();
        }
        else
        {
            std::cout << "False on return - Stopping.\n";
            break;
        }
    }

    std::cout << "get_alive(): " << stack.get_alive() << "\n";
}

LRUCache::LRUCache(int capacity)
: CAPACITY(capacity){}

void LRUCache::put(int key, int val)
{
    // Check if the key is in the cache
    if (cache.contains(key))
    {
        // Key present -> Update value
        auto it = cache[key];
        it->second = val;

        // Move usage to front
        usage_order.splice(usage_order.begin(), usage_order, it);
    }
    else  // Key not present -> Add it
    {
        if (cache.size() == CAPACITY)
        {
            // Cache is full -> Remove oldest key
            auto last_key = usage_order.back();
            usage_order.pop_back();
            cache.erase(last_key.first);
        }

        // Insert new key
        usage_order.emplace_front(key, val);
        cache[key] = usage_order.begin();
    }
}

std::optional<int> LRUCache::get(int key)
{
    if (!cache.contains(key))
        return std::nullopt;

    auto it = cache[key];
    usage_order.splice(usage_order.begin(), usage_order, it);

    return std::make_optional(it->second);
}

size_t LRUCache::get_usage_order_size() const
{
    return usage_order.size();
}

size_t LRUCache::get_cache_size() const
{
    return cache.size();
}

void LRU_entry() 
{
    LRUCache2 cache(2);

    cache.put(1, 10);  // [1]
    cache.put(2, 20);  // [2, 1]
    std::cout << cache.get(1).value_or(-1) << "\n";  // 10 → [1, 2]
    cache.put(3, 30);  // evicts 2 → [3, 1]
    std::cout << cache.get(2).value_or(-1) << "\n";  // -1
}

LRUCache2::LRUCache2(int capacity)
    : CAPACITY(capacity){}

void LRUCache2::put(int key, int val)
{
    // Check if key is present
    if (cache.contains(key))
    {
        // Update the key and refresh usage order
        auto it = cache[key];
        it->second = val;

        usage_order.splice(usage_order.begin(), usage_order, it);
    }
    else
    {
        // Remove the last used key if the cache is full
        if (cache.size() == CAPACITY)
        {
            int key_to_delete = usage_order.back().first;
            cache.erase(key_to_delete);
            usage_order.pop_back();
        }

        // Insert a new key
        usage_order.emplace_front(key, val);
        auto it = usage_order.begin();
        cache[key] = it;
    }
}

std::optional<int> LRUCache2::get(int key)
{
    if (!cache.contains(key))
        return std::nullopt;

    // Move the usage order to the front
    auto it = cache[key];
    usage_order.splice(usage_order.begin(), usage_order, it);

    return std::make_optional(it->second);
}
