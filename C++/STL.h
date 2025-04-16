#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <map>

// You are given N integers. Sort the integers and print the sorted order.
// Store the N integers in a vector. Vectors are sequence containers representing arrays that can change in size.

void load_and_sort();

/*
 * You are given a vector of N integers.
 *
 * 1. Perform a query that takes a single integer representing a position in the vector.
 *    Erase the element at that position.
 *
 * 2. Perform another query that takes two integers representing a range [start, end).
 *    Erase all elements in the vector that fall within this range.
 *
 * Note: The second query should be performed on the vector after completing the first query.
 */
void load_and_erase();

/*
 * You are given a sorted vector of integers.
 *
 * You will also receive multiple queries. For each query:
 *   - You are given an integer.
 *   - Determine whether this integer exists in the vector.
 *     - If it exists, output the index at which it is found.
 *     - If it does not exist, output the index of the smallest element that is greater than the given number.
 *
 * If there is no such greater element, indicate accordingly.
 */

void lower_bound();

/*
 * You are given Q queries. Each query is of one of the following three types:
 *
 * 1 x : Insert the element x into the set.
 *
 * 2 x : Delete the element x from the set.
 *       (If x is not present in the set, do nothing.)
 *
 * 3 x : Check whether the element x is present in the set.
 *       - If present, print "Yes"
 *       - Otherwise, print "No"
 */
void set_querry();

/*
 * You are helping a teacher manage student marks. Each student can have multiple entries (answer sheets).
 * The teacher will ask you to process Q queries of the following types:
 *
 * 1 X Y : Add marks Y to the student whose name is X.
 *
 * 2 X   : Erase all marks of the student whose name is X.
 *
 * 3 X   : Print the total marks of the student whose name is X.
 *         - If the student has no marks, print 0.
 */
void map_querry();

/*
 * You are given a simplified markup language called HRML.
 * Each element has a start tag and an end tag. Start tags may have attributes in the form:
 *
 * <tag-name attribute1 = "value1" attribute2 = "value2" ...>
 * </tag-name>
 *
 * Tags can be nested. Attributes are referenced using the syntax:
 *   tag1~attribute
 *   tag1.tag2~attribute
 *
 * You are given N lines of HRML source code and Q queries.
 *
 * For each query, print the value of the specified attribute.
 * If the attribute does not exist, print "Not Found!".
 */

std::vector<std::string> tokenize(std::string line);

std::string to_path(std::vector<std::string> stack);

void parse_tokens(std::unordered_map<std::string, std::string>& attribute_map, std::vector<std::string> tokens);

void parse_attributes_entry();


/*
 * Create two classes to compute the area of a rectangle using inheritance.
 *
 * Class: Rectangle
 * - Contains two integer data members: width and height.
 * - Has a method display() that prints width and height separated by a space.
 *
 * Class: RectangleArea (inherits from Rectangle)
 * - Has a method read_input() to take input for width and height.
 * - Overrides the display() method to print the area (width * height) of the rectangle.
 *
 * Input Format:
 * - A single line of input containing two space-separated integers: width and height.
 */

class Rectangle
{
protected:
    int width, height;

public:
    virtual void display();
};

class RectangleArea : public Rectangle
{
public:
    void read_input();

    void display() override;
};

void rect_area();

class Point
{
private:
    /* Attributes */
    int x, y;

public:
    /* Constructor */
    Point(int x, int y);

    /* Public Methods */
    std::string to_string() const;

    /* Operators */
    bool operator == (const Point& other) const;

    bool operator != (const Point& other) const;

    Point operator + (const Point& other) const;

    Point operator - (const Point& other) const;

    Point& operator += (const Point& other);

    Point& operator -= (const Point& other);

    Point operator () (int multi) const;

    Point& operator [] (std::string call);

    Point& operator [] (int def);
};

std::ostream& operator << (std::ostream& out, Point p);

void operators_entry();

/**
 * @brief Selects the maximum number of non-overlapping activities.
 *
 * Reads a list of activities from standard input, where each activity is defined
 * by a start time and a duration. The function calculates the end time for each activity,
 * sorts all activities by end time, and applies a greedy algorithm to select the
 * maximum number of non-overlapping activities that can be scheduled.
 *
 * Input format:
 *  - First line: integer n (number of activities)
 *  - Second line: n integers (start times)
 *  - Third line: n integers (durations)
 *
 * Output:
 *  - A single integer representing the maximum number of non-overlapping activities
 *    that can be attended.
 *
 * Time Complexity: O(n log n) due to sorting.
 */
void activity_selection_entry();

template <class T>
class AddElement
{
    /* Attributes */
    T a;

public:
    /* Methods */
    T add(const T& other)
    {
        return this->a + other;
    }

    /* Constructor */
    AddElement(T value): a(value){}
};

template <>
class AddElement<char>
{
    /* Attributes */
    char a;
public:
    /* Methods */
    std::string add(const char& other)
    { 
        return std::string { this->a, other };
    }

    /* Constructor */
    AddElement(char str): a(str){}
};

void class_templates_entry();

#define increment(base, addition) base + addition
#define TOTAL 100
#define foreach(container) for(int i = 0; i < container.size(); i++)

void preprocessor_entry();

void iomanip_entry();

class Matrix
{
public:
    /* Attributes */
    std::vector<std::vector<int>> values;

    /* Operators */
    Matrix operator+(const Matrix& other) const;
};

class Person
{
private:
    /* Attributes */
    std::string first_name;
    std::string last_name;

public:
    /* Constructor */
    Person(std::string name, std::string surname) : first_name(name), last_name(surname){}

    /* Getters */
    std::string get_name() const;

    std::string get_surname() const;
};

std::ostream& operator<<(std::ostream& out, const Person& p);

void person_entry();

enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> class Traits;

template <> class Traits<Color>
{
public:
    static std::string name(int color)
    {
        switch (color)
        {
            case 0: return "red"; break;
            case 1: return "green"; break;
            case 2: return "orange"; break;
            default: return "unknown";
        }
    }
};

template<> class Traits<Fruit>
{
public:
    static std::string name(int fruit)
    {
        switch (fruit)
        {
            case 0: return "apple"; break;
            case 1: return "orange"; break;
            case 2: return "pear"; break;
            default: return "unknown";
        }
    }
};

void fruits_and_colors_entry();

int largest_proper_divisor(int n);

void process_input(int n);

int simple_exception_entry();

class HotelRoom
{
private:
    /* Attributes */
    int beds;
    int bathrooms;

public:
    /* Constructor & Destructor */
    HotelRoom(int beds, int bathrooms): beds(beds), bathrooms(bathrooms){}
    virtual ~HotelRoom(){}

    /* Methods */
    virtual int get_price();
};

class HotelApartment : HotelRoom
{
public:
    /* Constructor & Destructor */
    HotelApartment(int beds, int bathrooms): HotelRoom(beds, bathrooms){}
    ~HotelApartment() override {}
    
    /* Methods */
    int get_price() override;
};

void virtual_entry();

class A
{
public:
    A();
private:
    int callA;
    void inc();

protected:
    void func(int& a);
public:
    int getA();
};

class B
{
public:
    B();
private:
    int callB;
    void inc();
protected:
    void func(int& a);
public:
    int getB();
};

class C
{
public:
    C();
private:
    int callC;
    void inc();
protected:
    void func(int& a);
public:
    int getC();
};

/*
    You need to modify the class D and implement the function update_val,
    which sets D's val to new_val by manipulating the value only by calling
    the functions defined in classes A, B, and C.

    It is guaranteed that new_val has only 2, 3, and 5 as its prime factors.
*/

class D : A, B, C
{

    int val;
public:
    //Initially val is 1
    D();

    //Implement this function
    void update_val(int new_val);

    //For Checking Purpose
    void check(int new_val);
};

void static_entry_2();

class Computer 
{
public:
    static int compute(int a, int b);
};

void exception_entry();

class Animal
{
public:
    virtual std::string sound() = 0;
};

class Dog : public Animal
{
public:
    std::string sound() override;
};

class Cat : public Animal
{
public:
    std::string sound() override;
};

class Fish : public Animal
{
public:
    std::string sound() override;
};

void virtual_sound_entry();

template<typename T>
void print(T value) 
{
    std::cout << value << "\n";
}

template<typename T, typename... Rest>
void print(T first, Rest... rest) 
{
    std::cout << first << " ";
    print(rest...);  // recursive unpacking
}

template<typename... Args>
void print_all(Args... args) 
{
    (std::cout << ... << args);
}

void variadic_templates_entry();

template <bool... bits>
int reversed_binary_value1()
{
    int value = 0;
    int multiplier = 1;
    bool values[] = { bits... };

    for (bool bit : values)
    {
        if (bit)
            value += multiplier;

        multiplier *= 2;
    }

    return value;
}

template <typename... Bits>
int reversed_binary_value2(Bits... bits)
{
    int value = 0;
    int multiplier = 1;
    bool arr[] = { bits... };

    for (bool bit : arr)
    {
        if (bit) value += multiplier;
        multiplier *= 2;
    }

    return value;
}

template <typename... Nums>
int sum(Nums... nums)
{
    // Unpack the numbers
    std::vector<int> arr = { nums... };

    // Sum up
    int total_sum = 0;
    for (int number : arr)
    {
        total_sum += number;
    }

    return total_sum;
}

void variadic_bits_entry();

/*
You are given four integers: N, S, P, Q. You will use them in order to create
the sequence a with the following pseudo-code:

    a[0] = S (modulo 2^31)
    for i = 1 to N - 1
        a[i] = a[i - 1] * P + Q (modulo 2^31)

Your task is to calculate the number of distinct integers in the sequence a.

Input Format:
Four space-separated integers on a single line: N, S, P, and Q respectively.

Output Format:
A single integer that denotes the number of distinct integers in the sequence a.
*/
void set_usage1();

void set_usage2();

void count_random_nums();

class Object
{
private:
    /* Attributes */
    static int active;
    const int obj_id;

public:
    /* Constructor & Destructor */
    Object(const int id);

    Object();

    ~Object();

    void Print(int call_id);
    int get_id();
};

void smart_pointers1();

class CustomObj
{
private:
    int id;
public:
    CustomObj(const int id);
    CustomObj();

    int get_id() const;

    bool operator == (const CustomObj& other) const;
};

template <class T>
class CustomList
{
private:
    /* Definitions */
    struct Node 
    {
        T data;
        Node* next = nullptr;

        /* Constructor */
        Node(T data): data(data){}
    };

    /* Attributes */
    Node* head = nullptr;
    int element_number = 0;

public:
    /* Constructors */
    CustomList(){}

    /* Destructors */
    ~CustomList()
    {
        Node* tgt = this->head;

        while (tgt)
        {
            Node* buffer = tgt;
            tgt = tgt->next;

            delete buffer;
        }
    }

    /* Public Methods */
    void insert(const T& data)
    {
        Node* new_node = new Node(data);
        this->element_number += 1;

        if (!head)
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

    bool remove(const T& data)
    {
        bool found = false;

        Node* node_to_remove = nullptr;
        if (this->head->data == data)
        {
            node_to_remove = this->head;
            this->head = this->head->next;
            found = true;
        }

        if (!found)
        {
            Node* tgt = this->head;
            while (tgt->next)
            {
                if (tgt->next->data == data)
                {
                    node_to_remove = tgt->next;
                    tgt->next = node_to_remove->next;
                    found = true;
                    break;
                }

                tgt = tgt->next;
            }
        }
        
        if (found)
        {
            delete node_to_remove;
            this->element_number -= 1;
        }
        
        return found;
    }

    /* Operators */
    std::pair<bool, T> operator [] (int tgt_index) const
    {
        int offset = 0;
        Node* tgt = this->head;
        while (tgt)
        {
            if (offset == tgt_index)
                return std::make_pair(true, tgt->data);
         
            offset += 1;
            tgt = tgt->next;
        }

        return std::make_pair(false, T{});
    }

    /* Getters & Setters */
    int get_number_of_elements() const
    {
        return this->element_number;
    }

    std::vector<T> get_as_vector() const
    {
        std::vector<T> result(this->element_number);

        Node* tgt = this->head;
        int i = 0;
        while (tgt)
        {
            result[i++] = tgt->data;
            tgt = tgt->next;
        }

        return result;
    }

    void reverse_order()
    {
        Node* prev = nullptr;
        Node* curr = this->head;

        while (curr)
        {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        this->head = prev;
    }

    void reverse_between(int begin, int end)
    {
        if (begin >= end || !head)
            return;

        Node dummy(-1);
        dummy.next = head;
        Node* pre = &dummy;

        // Move pre to node before 'begin'
        for (int i = 0; i < begin; ++i)
        {
            if (!pre) return;
            pre = pre->next;
        }

        Node* start = pre->next;
        Node* curr = start->next;

        // Reverse sublist
        for (int i = 0; i < end - begin; ++i)
        {
            if (!curr) break;

            start->next = curr->next;
            curr->next = pre->next;
            pre->next = curr;
            curr = start->next;
        }

        head = dummy.next;
    }


private:
    /* Private Methods */
};

void custom_list_entry();

void smart_pointers2();

int hourglass_sum(std::vector<std::vector<int>> arr);

void hourglass_entry();

std::vector<int> rot_left(std::vector<int> a, int d);

void array_rot_entry();

bool is_permutation(std::string str1, std::string str2);

void permutable_entry();

bool is_rot(std::string str1, std::string str2);

void is_rot_entry();

int longest_substr_length(std::string str);

void substr_entry();

std::pair<int, int> find_two_elements_to_sum(std::vector<int> arr, int tgt);

void twosum_entry();

bool has_duplicates(std::vector<int> arr);

void duplicate_entry();

void reverse_in_place(std::string& str);

void reverse_entry();

std::unordered_map<char, int> get_character_frequency(std::string str);

void freq_entry();

std::unordered_map<std::string, std::vector<std::string>> group_anagrams(std::vector<std::string> arr);

void anagrams_entry();

bool custom_comparator(const std::pair<int, int>& a, const std::pair<int, int>& b);

void custom_sort_entry();

/* 
* Returns frequency data about string's characters
* @param std::string
* @returns std::tuple<char, int, int> = (most frequent char, it's frequency, number of distinct characters)
*/
std::tuple<char, int, int> get_frequency(std::string str);

void tuple_entry();

int longest_substr_of_unique_characters(std::string arr);

void longest_substr_entry2();

std::vector<int> rot_arr_left(std::vector<int> arr, int shift);

void rot_arr_entry2();

bool check_magazine(std::vector<std::string> magazine, std::vector<std::string> note);

void check_magazine_entry();

/*
* Check if two strings have a common substring.
*/
bool two_strings(std::string str1, std::string str2);

void subs_entry();

/**
 * Given a string, this function counts the number of unordered pairs of
 * substrings that are anagrams of each other.
 *
 * Two substrings are considered anagrammatic pairs if they contain the
 * same characters in any order. Substrings must be of the same length
 * and can overlap. The function counts all such unordered pairs.
 *
 * Example:
 * Input: "mom"
 * Substrings: "m", "o", "m", "mo", "om", "mom"
 * Anagrammatic pairs: ["m", "m"], ["mo", "om"]
 * Output: 2
 *
 * @param str The input string to analyze.
 * @return The number of unordered anagrammatic pairs of substrings in s.
 */
int sherlock_anagrams(std::string str);

void sherlock_entry();

/**
 * Processes a list of frequency-related queries on a multiset of integers.
 *
 * There are three types of queries:
 * 1 x — Insert integer x into the data structure.
 * 2 y — Delete one occurrence of integer y, if present.
 * 3 z — Check if any integer is present whose frequency is exactly z.
 *       Append 1 to the result if found, else 0.
 *
 * The function uses two hash maps:
 * - One to track the frequency of each integer.
 * - One to track how many integers have a given frequency.
 *
 * @param queries A vector of (operation, value) pairs representing the queries.
 * @return A vector of results for type 3 queries (0 or 1).
 */
std::vector<int> freq_query(std::vector<std::pair<int, int>> queries);

void query_entry();

class PriorityQueue
{
    /* Structs */
    struct Item
    {
        /* Attributes */
        int data;
        int priority;
        int insertion_order;

        /* Consatructor */
        Item(int data, int priority, int insertion_order);

        /* Operators */
        bool operator<(const Item& other);

        static bool comp_items(const Item& a, const Item& b);
    };

    /* Attributes */
    std::vector<Item> queue;
    int capacity;
    int order_counter = 0;
    bool is_sorted = true;

public:
    /* Constructor & Destructor */
    PriorityQueue(int capacity);
    ~PriorityQueue(){}
    
    /* Public Methods */
    void enqueue(int data, int priority);
    void dequeue();
    void print();
};

void pq_entry();

class PriorityQueue2
{
    /* Types */
    struct Item
    {
        /* Attributes */
        int data;
        int priority;

        /* Csontructors */
        Item(int data, int priority);

        Item(const Item& item);

        /* Static Methods */
        static bool comp(const Item& a, const Item& b);
    };

    /* Attributes */
    std::vector<Item> queue;
    const int CAPACITY;
    bool is_sorted = true;

public:
    /* Constructor */
    PriorityQueue2(int capacity);

    /* Public Methods */
    bool enqueue(int data, int priority);
    std::pair<bool, Item> dequeue();
};

void pq2_entry();

std::vector<int> most_frequent_elements(std::vector<int> arr, int k);
void most_frequent_elements_entry();

std::vector<int> biggest_elements1(std::vector<int> arr, int k);
std::vector<int> biggest_elements2(std::vector<int> arr, int k);
void k_biggest_el_entry();

void comp_test_entry();

template <typename T>
class CustomList2
{
    /* Types */
    struct Node
    {
        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    /* Attributes */
    Node* head = nullptr;
    int size = 0;

public:
    /* Constructor */
    CustomList2() {}

    /* Public Methods */
    void push_back(T data)
    {
        this->size += 1;
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

    std::pair<bool, T> pop_back()
    {
        if (!this->head)
            return std::make_pair(false, T());

        Node* tgt = this->head;
        Node* prev = tgt;
        while (tgt->next)
        {
            prev = tgt;
            tgt = tgt->next;
        }

        Node* to_return = tgt;
        prev->next = nullptr;
        this->size -= 1;

        return std::make_pair(true, to_return->data);
    }

    int get_size()
    {
        return this->size;
    }
};

void custom_list2_entry();