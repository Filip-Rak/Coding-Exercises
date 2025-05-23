﻿#include "Structures.h"

void remove_duplicates_entry()
{
    CustomList2<std::string> list;
    // std::vector<int> inputs = { 1, 1, 1, 2, 3, 4, 4, 5, 6, 6, 7, 8, 9, 9, 10 };
    std::vector<std::string> inputs = { "one", "one", "two", "two", "two", "three", "four", "five", "fifth" };

    for (auto input : inputs)
        list.push_back(input);

    list.remove_duplicates_keep_order();

    for (auto entry : list.to_vector())
        std::cout << entry << "\n";

    std::cout << "\nTracked size: " << list.get_size() << "\n";
    std::cout << "True size: " << list.get_debug_active_nodes() << "\n";
}

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
    LRUCache3 cache(2);

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

CustomHashMap::Item::Item(std::string key, int val)
    : key(key), val(val) {}

size_t CustomHashMap::get_index(std::string key) const
{
    std::hash<std::string> hasher;
    return hasher(key) % NUM_BUCKETS;
}

CustomHashMap::CustomHashMap()
    : buckets(NUM_BUCKETS){}

void CustomHashMap::put(std::string key, int val)
{
    size_t index = get_index(key);

    // If the key is already in the map
    for (Item& item : buckets[index])
    {
        if (key == item.key)
        {
            item.val = val;
            return;
        }
    }

    // There is no key in the map
    Item new_item(key, val);
    buckets[index].push_back(new_item);
}

std::optional<int> CustomHashMap::get(std::string key)
{
    size_t index = get_index(key);
    for (const Item& item : buckets[index])
    {
        if (item.key == key)
            return std::make_optional(item.val);
    }

    return std::nullopt;
}

void CustomHashMap::remove(std::string key)
{
    size_t index = get_index(key);
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++)
    {
        if (it->key == key)
        {
            buckets[index].erase(it);
            return;
        }
    }
}

void hash_map_entry()
{
    const int KEYS = 100;
    CustomHashMap map;

    for (int i = 0; i < KEYS; i++)
    {
        std::string key = std::to_string(i);
        map.put(key, i);
    }

    map.remove("70");
    map.remove("30");
    map.remove("12");
    map.remove("4");

    int not_found = 0;
    for (int i = 0; i < KEYS; i++)
    {
        std::string key = std::to_string(i);
        
        auto ret = map.get(key);
        if (ret.has_value())
        {
            std::cout << "Key: " << key << " val: " << ret.value() << "\n";
        }
        else
        {
            std::cout << "VAL NOT FOUND FOR: " << key << "\n";
            not_found += 1;
        }
    }

    std::cout << "\nNot found: " << not_found << "\n";
}

size_t CustomHashSet::get_index(const std::string& key) const
{
    std::hash<std::string> hasher;
    return hasher(key) % NUM_BUCKETS;
}

CustomHashSet::CustomHashSet()
    : buckets(NUM_BUCKETS){}

bool CustomHashSet::put(const std::string& key)
{
    size_t index = get_index(key);
    for (const auto& bucket_key : buckets[index])
    {
        if (bucket_key == key)
            return false;
    }

    buckets[index].push_back(key);
    return true;
}

bool CustomHashSet::contains(const std::string& key) const
{
    size_t index = get_index(key);
    for (const auto& bucket_key : buckets[index])
    {
        if (bucket_key == key)
            return true;
    }

    return false;
}

bool CustomHashSet::remove(const std::string& key)
{
    size_t index = get_index(key);
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++)
    {
        if (*it == key)
        {
            buckets[index].erase(it);
            return true;
        }
    }

    return false;
}

void custom_set_entry()
{
    const int NUM_KEYS = 10000;
    std::vector<std::string> keys(NUM_KEYS);

    for (int i = 0; i < NUM_KEYS; i++)
        keys[i] = std::to_string(i);

    CustomHashSet set;
    
    int check = 0;
    for (const auto& key : keys)
    {
        if (set.put(key))
            check += 1;
    }

    std::cout << "First insertion: " << check << "\n";

    check = 0;
    for (const auto& key : keys)
    {
        if (set.contains(key))
            check += 1;
    }

    std::cout << "Contains: " << check << "\n";

    check = 0;
    for (const auto& key : keys)
    {
        if (set.put(key))
            check += 1;
    }

    std::cout << "Second insertion: " << check << "\n";

    check = 0;
    for (const auto& key : keys)
    {
        if (set.remove(key))
            check += 1;
    }

    std::cout << "Removal: " << check << "\n";

    check = 0;
    for (const auto& key : keys)
    {
        if (set.put(key))
            check += 1;
    }

    std::cout << "Second insertion: " << check << "\n";
}

int CustomDequeue::Node::debug_alive = 0;

CustomDequeue::Node::Node(int val, Node* next, Node* prev)
    : val(val), next(next), prev(prev)
{
    Node::debug_alive += 1;
}

CustomDequeue::Node::~Node()
{
    Node::debug_alive -= 1;
}

CustomDequeue::~CustomDequeue()
{
    while (head)
    {
        Node* next = head->next;
        delete head;

        head = next;
    }
}

void CustomDequeue::push_front(int val)
{
    if (!head)
    {
        Node* new_node = new Node(val);
        head = tail = new_node;
        return;
    }

    Node* new_node = new Node(val, head);
    head->prev = new_node;

    head = new_node;
}

void CustomDequeue::push_back(int val)
{
    if (!tail)
    {
        Node* new_node = new Node(val);
        tail = head = new_node;
        return;
    }

    Node* new_node = new Node(val, nullptr, tail);
    tail->next = new_node;

    tail = new_node;
}

void CustomDequeue::pop_front()
{
    if (!head)
        return;

    if (head == tail)
    {
        delete head;

        head = nullptr;
        tail = nullptr;

        return;
    }

    Node* to_delete = head;
    head = head->next;
    head->prev = nullptr;

    delete to_delete;
}

void CustomDequeue::pop_back()
{
    if (!tail)
        return;

    if (tail == head)
    {
        delete tail;

        tail = nullptr;
        head = nullptr;

        return;
    }

    Node* to_delete = tail;
    tail = tail->prev;
    head->next = nullptr;

    delete to_delete;
}

std::optional<int> CustomDequeue::front() const
{
    if (!head)
        return std::nullopt;

    return std::make_optional(head->val);
}

std::optional<int> CustomDequeue::back() const
{
    if (!tail)
        return std::nullopt;

    return std::make_optional(tail->val);
}

int CustomDequeue::get_alive()
{
    return Node::debug_alive;
}

void dequeue_entry()
{
    CustomDequeue dequeue;

    dequeue.push_front(1);
    dequeue.push_back(2);
    dequeue.pop_front();

    std::cout << dequeue.front().value_or(-1) << "\n";
    std::cout << dequeue.back().value_or(-1) << "\n";

    dequeue.pop_back();

    std::cout << dequeue.front().value_or(-1) << "\n";
    std::cout << dequeue.back().value_or(-1) << "\n";

    dequeue.push_back(4);

    std::cout << dequeue.front().value_or(-1) << "\n";
    std::cout << dequeue.back().value_or(-1) << "\n";
    std::cout << dequeue.get_alive() << "\n";
}

CustomPriorityQueue2::Node::Node(int val, int priority, int insertion_order)
    : val(val), priority(priority), insertion_order(insertion_order){}

bool CustomPriorityQueue2::Node::node_comparator(const Node& a, const Node& b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;

    return a.insertion_order > b.insertion_order;
}

CustomPriorityQueue2::CustomPriorityQueue2(size_t capacity)
    : CAPACITY(capacity){}

void CustomPriorityQueue2::enqueue(int val, int priority)
{
    if (queue.size() == CAPACITY)
    {
        auto min = std::min_element(queue.begin(), queue.end(), Node::node_comparator);
        if (min->priority < priority)
        {
            min->val = val;
            min->priority = priority;
            min->insertion_order = insertion_order++;

            is_sorted = false;
        }
    }
    else
    {
        Node new_node(val, priority, insertion_order++);
        queue.push_back(new_node);
        is_sorted = false;
    }
}

void CustomPriorityQueue2::dequeue()
{
    if (queue.empty())
        return;

    if (!is_sorted)
    {
        std::sort(queue.begin(), queue.end(), Node::node_comparator);
        is_sorted = true;
    }

    queue.pop_back();
}

void CustomPriorityQueue2::print_queue()
{
    if (!is_sorted)
    {
        std::sort(queue.begin(), queue.end(), Node::node_comparator);
        is_sorted = true;
    }

    for (auto it = queue.rbegin(); it != queue.rend(); it++)
        std::cout << it->val << " " << it->priority << "\n";
}

void custom_pq_entry()
{
    size_t N;
    std::cin >> N;
    std::cin.ignore();

    CustomPriorityQueue2 queue(N);

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
            break;
        }
    }

    queue.print_queue();
}

LRUCache3::LRUCache3(size_t capacity)
    : CAPACITY(capacity) {}

void LRUCache3::put(int key, int value)
{
    if (cache.contains(key))
    {
        auto it = cache[key];
        it->second = value;

        usage_order.splice(usage_order.begin(), usage_order, it);
        return;
    }

    if (cache.size() == CAPACITY)
    {
        const auto& last_used = usage_order.back();
        cache.erase(last_used.first);
        usage_order.pop_back();
    }

    usage_order.emplace_front(key, value);
    cache[key] = usage_order.begin();
}

std::optional<int> LRUCache3::get(int key)
{
    if (!cache.contains(key))
        return std::nullopt;

    auto it = cache[key];
    usage_order.splice(usage_order.begin(), usage_order, it);

    return std::make_optional(it->second);
}

CustomHashMap2::Node::Node(std::string key, int val)
    : key(key), value(val){}

size_t CustomHashMap2::get_index(std::string key)
{
    std::hash<std::string> hasher;
    return hasher(key) % NUM_BUCKETS;
}

CustomHashMap2::CustomHashMap2()
    : buckets(NUM_BUCKETS){}

void CustomHashMap2::put(std::string key, int value)
{
    size_t index = get_index(key);
    for (Node& node : buckets[index])
    {
        if (node.key == key)
        {
            node.value = value;
            return;
        }
    }

    buckets[index].emplace_back(key, value);
}

std::optional<int> CustomHashMap2::get(std::string key)
{
    size_t index = get_index(key);
    for (Node node : buckets[index])
    {
        if (node.key == key)
            return std::make_optional(node.value);
    }

    return std::nullopt;
}

bool CustomHashMap2::remove(std::string key)
{
    size_t index = get_index(key);
    for (auto it = buckets[index].begin(); it != buckets[index].end(); it++)
    {
        if (it->key == key)
        {
            buckets[index].erase(it);
            return true;
        }
    }

    return false;
}

void chm_entry()
{
    const int NUM_KEYS = 100;
    std::vector<std::string> keys(NUM_KEYS);
    CustomHashMap2 map;
    
    // Convert to string
    for (int i = 0; i < NUM_KEYS; i++)
        keys[i] = std::to_string(i);

    // Input keys and coresponding nums
    for (int i = 0; i < NUM_KEYS; i++)
        map.put(keys[i], i);

    // Check if the keys are present
    int check = 0;
    for (int i = 0; i < NUM_KEYS; i++)
    {
        auto ret = map.get(keys[i]);

        if (ret.value_or(-1) == i)
            check += 1;
    }

    std::cout << "1st. get: " << check << "\n";
    
    // Change vals to (int)key * 2
    for (int i = 0; i < NUM_KEYS; i++)
    {
        map.put(keys[i], i * 2);
    }

    // Check validity of vals
    check = 0;
    for (int i = 0; i < NUM_KEYS; i++)
    {
        auto ret = map.get(keys[i]);

        if (ret.value_or(-1) == i * 2)
            check += 1;
    }

    std::cout << "2nd. get: " << check << "\n";

    // Remove vals
    check = 0;
    for (int i = 0; i < NUM_KEYS; i++)
    {
        if (map.remove(keys[i]))
            check += 1;
    }

    std::cout << "remove: " << check << "\n";

    // Second insert
    for (int i = 0; i < NUM_KEYS; i++)
        map.put(keys[i], i * 3);

    // Check validity of vals
    check = 0;
    for (int i = 0; i < NUM_KEYS; i++)
    {
        auto ret = map.get(keys[i]);

        if (ret.value_or(-1) == i * 3)
            check += 1;
    }

    std::cout << "2nd. get: " << check << "\n";
}

void MinHeap2::heapify_up(size_t index)
{
    if (index == 0)
        return;

    size_t parent = (index - 1) / 2;
    if (heap[index] < heap[parent])
    {
        std::swap(heap[index], heap[parent]);
        heapify_up(parent);
    }
}

void MinHeap2::heapify_down(size_t index)
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

void MinHeap2::push(int value)
{
    heap.push_back(value);
    heapify_up(heap.size() - 1);
}

bool MinHeap2::pop()
{
    if (heap.empty())
        return false;

    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);
    return true;
}

std::optional<int> MinHeap2::get_min() const
{
    if (heap.empty())
        return std::nullopt;

    return std::make_optional(heap.front());
}

void mh2_test_entry()
{
    MinHeap2 heap;

    heap.push(3);
    heap.push(-1);
    heap.push(-2);
    heap.push(6);
    heap.push(-4);

    heap.pop();

    std::cout << heap.get_min().value_or(-42);
}

int Dequeue::Node::alive = 0;

Dequeue::Node::Node(int val, Node* next, Node* prev)
    : value(val), next(next), prev(prev)
{
    Node::alive += 1;
}

Dequeue::Node::~Node() 
{
    Node::alive -= 1;
};

Dequeue::~Dequeue()
{
    clear();
}

void Dequeue::push_front(int val)
{
    if (!head)
    {
        head = tail = new Node(val);
        return;
    }

    Node* new_node = new Node(val, head);
    head->prev = new_node;
    head = new_node;
}

void Dequeue::push_back(int val)
{
    if (!tail)
    {
        tail = head = new Node(val);
        return;
    }
    
    Node* new_node = new Node(val, nullptr, tail);
    tail->next = new_node;
    tail = new_node;
}

std::optional<int> Dequeue::front() const
{
    if (!head)
        return std::nullopt;

    return std::make_optional(head->value);
}

std::optional<int> Dequeue::back() const
{
    if (!tail)
        return std::nullopt;

    return std::make_optional(tail->value);
}

Dequeue Dequeue::get_reversed() const
{
    Dequeue dequeue;

    Node* tgt = head;
    while (tgt)
    {
        dequeue.push_front(tgt->value);
        tgt = tgt->next;
    }

    return dequeue;
}

std::optional<int> Dequeue::get_middle_val() const
{
    if (!head)
        return std::nullopt;

    Node* slow_pointer = this->head;
    Node* fast_pointer = this->head;

    while (fast_pointer && fast_pointer->next)
    {
        slow_pointer = slow_pointer->next;
        fast_pointer = fast_pointer->next->next;
    }

    return std::make_optional(slow_pointer->value);
}

void Dequeue::pop_front()
{
    if (!head)
        return;

    Node* to_delete = head;
    head = head->next;
    delete to_delete;

    if (!head)
        tail = nullptr;
    else
        head->prev = nullptr;
}

void Dequeue::pop_back()
{
    if (!tail)
        return;

    Node* to_delete = tail;
    tail = tail->prev;
    delete to_delete;

    if (!tail)
        head = nullptr;
    else
        tail->next = nullptr;
}

void Dequeue::clear()
{
    while (head)
    {
        Node* to_delete = head;
        head = head->next;

        delete to_delete;
    }

    tail = nullptr;
}

void Dequeue::reverse()
{
    Node* tgt = this->head;
    Node* prev = nullptr;

    while (tgt)
    {
        Node* next = tgt->next;
        tgt->next = prev;
        tgt->prev = next;
        prev = tgt;

        tgt = next;
    }

    this->tail = this->head;
    this->head = prev;
}

void dequeue_entry2()
{
    Dequeue queue;

    int start = 1, range = 5;
    for (int i = start; i < start + range; i++)
        queue.push_back(i);

    Dequeue new_queue = queue.get_reversed();

    auto ret = new_queue.front();
    while (ret.has_value())
    {
        std::cout << ret.value() << "\n";

        new_queue.pop_front();
        ret = new_queue.front();
    }

    std::cout << "\n";
}

void list_reversal_entry()
{
    CustomList2<int> single_list;
    Dequeue double_list;

    // Feed with example data
    int start = 1, range = 5;
    for (int i = start; i < start + range; i++)
    {
        single_list.push_back(i);
        double_list.push_back(i);
    }

    // Reverse
    single_list.reverse();
    double_list.reverse();

    // Print result
    std::cout << "Single list: ";

    auto sl_ret = single_list.pop_front();
    while (sl_ret.first)
    {
        std::cout << sl_ret.second << " ";
        sl_ret = single_list.pop_front();
    }

    std::cout << "\nDouble list: ";

    auto dl_ret = double_list.front();
    while (dl_ret.has_value())
    {
        std::cout << dl_ret.value() << " ";

        double_list.pop_front();
        dl_ret = double_list.front();
    }

    std::cout << "\n";
}

void get_mid_list_element_entry()
{
    Dequeue list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    std::cout << list.get_middle_val().value_or(-1) << "\n";
}
