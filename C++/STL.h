#pragma once

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>

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
    const std::vector<std::vector<int>> values;

    /* Operators */
    Matrix operator+(const Matrix& other) const;
};