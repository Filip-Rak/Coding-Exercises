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

    /* Getters */
    int get_size()
    {
        return this->list_size;
    }

    int get_debug_active_nodes()
    {
        return Node::active_nodes;
    }
};

template <typename T>
int CustomList2<T>::Node::active_nodes = 0;

void custom_list2_entry();