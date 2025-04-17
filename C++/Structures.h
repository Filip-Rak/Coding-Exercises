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