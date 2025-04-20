#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <optional>
#include <stack>
#include <list>

template <typename T>
class CustomList2
{
    /* Types */
    struct Node
    {
        static int active_nodes;

        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next)
        {
            this->active_nodes += 1;
        }

        ~Node()
        {
            this->active_nodes -= 1;
        }

    };

    /* Attributes */
    Node* head = nullptr;
    int list_size = 0;

public:
    /* Constructor & Destructor */
    CustomList2() {}

    CustomList2(const CustomList2<T>& other)
    {
        Node* tgt = other.head;
        while (tgt)
        {
            this->push_back(tgt->data);
            tgt = tgt->next;
        }
    }

    ~CustomList2()
    {
        this->clear();
    }

    /* Public Methods */
    void push_back(T data)
    {
        this->list_size += 1;
        Node* new_node = new Node(data);

        if (!this->head)
        {
            this->head = new_node;
            return;
        }

        Node* tgt = this->head;
        while (tgt->next)
        {
            tgt = tgt->next;
        }

        tgt->next = new_node;
    }

    void push_front(T data)
    {
        Node* new_node = new Node(data, this->head);
        this->head = new_node;

        this->list_size += 1;
    }

    std::pair<bool, T> pop_back()
    {
        if (!this->head)
            return std::make_pair(false, T());

        Node* to_return = nullptr;
        if (!this->head->next)
        {
            to_return = this->head;
            this->head = nullptr;
        }
        else
        {
            Node* tgt = this->head;
            Node* prev = tgt;

            while (tgt->next)
            {
                prev = tgt;
                tgt = tgt->next;
            }

            to_return = tgt;
            prev->next = nullptr;
        }

        this->list_size -= 1;
        std::pair return_pair = std::make_pair(true, to_return->data);
        delete to_return;

        return return_pair;
    }

    std::pair<bool, T> pop_front()
    {
        if (!this->head)
            return std::make_pair(false, T());

        Node* to_pop = this->head;
        this->head = this->head->next;

        std::pair return_val = std::make_pair(true, to_pop->data);
        this->list_size -= 1;
        delete to_pop;

        return return_val;
    }

    void clear()
    {
        Node* tgt = this->head;
        while (tgt)
        {
            Node* to_delete = tgt;
            tgt = tgt->next;
            delete to_delete;
        }

        this->head = nullptr;
        this->list_size = 0;
    }

    void reverse()
    {
        Node* tgt = this->head;
        Node* prev = nullptr;

        while (tgt)
        {
            Node* next = tgt->next;
            tgt->next = prev;
            prev = tgt;

            tgt = next;
        }

        this->head = prev;
    }
    
    bool contains(T data)
    {
        Node* tgt = this->head;
        while (tgt)
        {
            if (tgt->data == data)
                return true;

            tgt = tgt->next;
        }

        return false;
    }

    bool insert_at(T data, int target_index)
    {
        if (target_index < 0)
            return false;

        if (target_index == 0)
        {
            push_front(data);
            return true;
        }

        if (!this->head)
            return false;

        Node* tgt = this->head;
        int index = 1;

        while (tgt && index < target_index)
        {
            index += 1;
            tgt = tgt->next;
        }

        if (!tgt)
            return false;

        Node* new_node = new Node(data, tgt->next);
        tgt->next = new_node;
        list_size += 1;
        
        return true;
    }

    std::pair<bool, T> pop_at(int target_index)
    {
        if (target_index < 0)
            return std::make_pair(false, T());

        if (target_index == 0)
            return this->pop_front();

        Node* tgt = this->head;
        int index = 1;

        while (tgt && index < target_index)
        {
            index += 1;
            tgt = tgt->next;
        }

        if (!tgt || !tgt->next)
            return std::make_pair(false, T());

        Node* next = tgt->next->next;
        std::pair<bool, T> return_pair = std::make_pair(true, tgt->next->data);

        delete tgt->next;
        tgt->next = next;
        this->list_size -= 1;

        return return_pair;
    }

    std::vector<T> to_vector()
    {
        std::vector<T> arr(this->list_size);

        Node* tgt = this->head;
        int index = 0;

        while (tgt)
        {
            arr[index] = tgt->data;

            tgt = tgt->next;
            index += 1;
        }

        return arr;
    }

    /* Getters */
    int get_size()
    {
        return this->list_size;
    }

    int get_debug_active_nodes()
    {
        return Node::active_nodes;
    }

    /* Operators */
    CustomList2<T>& operator = (const CustomList2<T>& other)
    {
        if (this == &other)
            return *this;

        this->clear();

        Node* tgt = other.head;
        while (tgt)
        {
            this->push_back(tgt->data);
            tgt = tgt->next;
        }

        return *this;
    }
};

template <typename T>
int CustomList2<T>::Node::active_nodes = 0;

void custom_list2_entry();

template <typename T>
class CustomVector
{
    /* Attributes */
    T* arr;
    size_t size;

public:
    /* Constructor & Destructor */
    CustomVector(size_t size = 0)
        : size(size), arr(new T[size])
    {
        for (int i = 0; i < size; i++)
        {
            this->arr[i] = T();
        }
    }

    ~CustomVector()
    {
        delete[] arr;
    }

    /* Public Methods */
    void push_back(T data)
    {
        resize_raw(this->size + 1);
        this->arr[this->size - 1] = data;
    }

    bool insert_at(T data, size_t target_index)
    {
        if (target_index > this->size)
            return false;

        this->resize(this->size + 1);

        // Shift all values back
        for (size_t i = this->size - 1; i > target_index; i--)
        {
            this->arr[i] = std::move(this->arr[i - 1]);
        }

        this->arr[target_index] = data;
        return true;
    }

    bool put(T data, size_t index)
    {
        if (index >= this->size)
            return false;

        this->arr[index] = data;
        return true;
    }

    std::pair<bool, T> get(size_t index)
    {
        if (index >= size)
            return std::make_pair(false, T());

        return std::make_pair(true, arr[index]);
    }

    void resize(size_t new_size)
    {
        size_t old_size = this->size;
        this->resize_raw(new_size);

        for (size_t i = old_size; i < new_size; i++)
            this->arr[i] = T();
    }

    void clear()
    {
        delete[] this->arr;
        this->arr = new T[0];
        this->size = 0;
    }

    bool contains(T data)
    {
        for (size_t i = 0; i < this->size; i++)
        {
            if (data == this->arr[i])
                return true;
        }

        return false;
    }

    /* Opertators */
    T& operator [](size_t index)
    {
        if (index >= this->size)
            throw std::out_of_range("Index out of range");
        
        return this->arr[index];
    }

private:
    /* Private Methods */
    void resize_raw(size_t new_size)
    {
        T* new_arr = new T[new_size];
        for (size_t i = 0; i < this->size && i < new_size; i++)
            new_arr[i] = std::move(this->arr[i]);

        delete[] this->arr;
        this->arr = new_arr;
        this->size = new_size;
    }
};

void custom_vector_entry();

class CustomPriorityQueue
{
    /* Types */
    struct Item
    {
        int value;
        int priority;
        int insertion_order;

        Item(int value, int priority, int insertion_order);
    };

    /* Attributes */
    std::vector<Item> queue;
    const int capacity;
    int insert_order = 0;
    bool is_sorted = true;

public:
    /* Csontructor */
    CustomPriorityQueue(int capacity);

    /* Public Methods */
    void enqueue(int val, int priority);
    void dequeue();
    void print_queue();

    /* Private Methods */
    static bool item_comparator(const Item& a, const Item& b);
};

void cpq_test_entry();

void cpq_input_entry();

template <typename T>
class CustomQueue 
{
    /* Types */
    struct Node
    {
        /* Attributes */
        static int alive;

        T data;
        Node* next;

        /* Constructor & Destrucor */
        Node(T data, Node* next = nullptr)
            : data(data), next(next)
        {
            this->alive += 1;
        }

        ~Node()
        {
            this->alive -= 1;
        }
    };

    /* Attributes */
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    /* Constructor & Destructor */
    CustomQueue(){}

    ~CustomQueue()
    {
        this->clear();
    }

    /* Public Methods */
    void clear()
    {
        Node* tgt = this->head;
        while (tgt)
        {
            Node* to_remove = tgt;
            tgt = tgt->next;

            delete to_remove;
        }

        this->head = nullptr;
        this->tail = nullptr;
    }

    void push(T data)
    {
        Node* new_node = new Node(data);

        if (!this->tail)
        {
            this->head = new_node;
            this->tail = new_node;
            return;
        }

        this->tail->next = new_node;
        this->tail = new_node;
    }

    std::pair<bool, T> pop()
    {
        if (!this->head)
            return std::make_pair(false, T());

        Node* to_pop = this->head;
        this->head = this->head->next;

        T data = to_pop->data;
        delete to_pop;

        if (!this->head)
            this->tail = nullptr;

        return std::make_pair(true, data);
    }

    std::pair<bool, T> front() const
    {
        if (!this->head)
            return std::make_pair(false, T());

        return std::make_pair(true, this->head->data);
    }

    std::pair<bool, T> back() const
    {
        if (!this->tail)
            return std::make_pair(false, T());

        return std::make_pair(true, this->tail->data);
    }

    /* Getters */
    int get_alive() const
    {
        return Node::alive;
    }

    bool empty() const
    {
        return !this->head;
    }
};

template <typename T>
int CustomQueue<T>::Node::alive = 0;

void custom_queue_entry();

class CustomStack
{
    /* Types */
    struct Node
    {
        /* Attributes */
        static int active;

        int data;
        Node* next;

        /* Constructor */
        Node(int data, Node* next = nullptr);

        ~Node();
    };

    /* Attributes */
    Node* head = nullptr;

public:
    /* Constructor & Destructor */
    CustomStack();

    ~CustomStack();

    /* Public Methods */
    void push(int data);
    std::optional<int> pop();

    void clear();

    /* Getters */
    int get_alive();
};

void custom_stack_entry();

class CustomMinHeap
{
    /* Attributes */
    std::vector<int> heap;

    /* Private Methods */
    void heapify_up(size_t index);
    void heapify_down(size_t index);

public:
    /* Constructor */
    CustomMinHeap();

    /* Public Methdos */
    void push(int data);
    std::optional<int> pop();

    /* Getters */
    int get_size();
};

void custom_min_heap_entry();

class CustomMaxHeap
{
    /* Attributes */
    std::vector<int> heap;

    /* Private Methods */
    void heapify_up(size_t index);
    void heapify_down(size_t index);

public:
    /* Public Methods */
    void push(int val);
    std::optional<int> pop();
    size_t get_size();
};

void custom_max_heap_entry();

class CustomMinStack
{
    /* Attributes */
    std::stack<int> main;
    std::stack<int> min;

public:
    /* Public Methods */
    void push(int val);
    void pop();

    /* Getters */
    std::optional<int> get_top() const;
    std::optional<int> get_min() const;
    
    size_t get_min_size();
    size_t get_main_size();
};

void custom_min_stack_entry();

class CustomStack2
{
    /* Types */
    struct Node
    {
        /* Attributes */
        static int alive;

        int val;
        Node* next;

        /* Constructor & Destructor */
        Node(int val, Node* next = nullptr);
        ~Node();
    };

    /* Attributes */
    Node* head = nullptr;
    size_t size = 0;

public:
    /* Destructor */
    ~CustomStack2();

    /* Public Methods */
    void push(int val);
    std::optional<int> pop();
    std::optional<int> top() const;

    /* Getters */
    int get_alive() const;
    bool empty() const;
    size_t get_size() const;
};

class CustomMaxStack
{
    /* Attributes */
    CustomStack2 main;
    CustomStack2 max;

public:
    /* Public Methods */
    void push(int val);
    void pop();

    /* Getters */
    std::optional<int> get_top() const;
    std::optional<int> get_max() const;

    size_t get_max_size() const;
    size_t get_main_size() const;
    int get_alive() const;
};

void custom_stack2_test_entry();

void custom_max_stack_entry();

class LRUCache
{
    /* Attributes */
    const int CAPACITY;
    std::list<std::pair<int, int>> usage_order;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache;

public:
    /* Constructor */
    LRUCache(int cpacity);

    /* Public Methods */
    void put(int key, int val);
    std::optional<int> get(int key);

    /* Getters */
    size_t get_usage_order_size() const;
    size_t get_cache_size() const;
};

void LRU_entry();

class LRUCache2
{
    /* Attributes */
    const int CAPACITY;
    std::list<std::pair<int, int>> usage_order;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache;

public:
    /* Constructor */
    LRUCache2(int capacity);

    /* Public Methods */
    void put(int key, int val);
    std::optional<int> get(int key);
};

class CustomHashMap
{
    /* Types */
    struct Item
    {
        /* Attributes */
        std::string key;
        int val;

        /* Csontructor */
        Item(std::string key, int val);
    };

    /* Attributes */
    const int NUM_BUCKETS = 16;
    std::vector<std::list<Item>> buckets;

    /* Private Methods */
    size_t get_index(std::string key) const;

public:
    /* Constructor */
    CustomHashMap();

    /* Public Methods */
    void put(std::string key, int val);
    std::optional<int> get(std::string key);
    void remove(std::string key);
};

void hash_map_entry();

class CustomHashSet
{
    /* Attributes */
    const size_t NUM_BUCKETS = 16;
    std::vector<std::list<std::string>> buckets;

    /* Private Methods */
    size_t get_index(const std::string& key) const;

public:
    /* Constructor */
    CustomHashSet();

    /* Private Methods */
    bool put(const std::string& key);
    bool contains(const std::string& key) const;
    bool remove(const std::string& key);
};

void custom_set_entry();