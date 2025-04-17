#pragma once

#include <vector>
#include <iostream>

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

    bool insert_at(T data, int target_index)
    {
        if (target_index < 0 || target_index > this->size)
            return false;

        this->resize(this->size + 1);

        // Shift all values back
        for (int i = this->size - 1; i > target_index; i--)
        {
            this->arr[i] = std::move(this->arr[i - 1]);
        }

        this->arr[target_index] = data;
        return true;
    }

    std::pair<bool, T> get(size_t index)
    {
        if (index < 0 || index >= size)
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

private:
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