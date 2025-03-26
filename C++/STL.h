#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>

// You are given N integers. Sort the integers and print the sorted order.
// Store the N integers in a vector. Vectors are sequence containers representing arrays that can change in size.

void load_and_sort()
{
    // Load the amount of numbers and the numbers
    int size;
    std::cin >> size;

    std::vector<int> numbers(size);
    for (int i = 0; i < size; i++)
        std::cin >> numbers[i];

    // Sort the numbers    
    std::sort(numbers.begin(), numbers.end());

    // Print the numbers
    for (int num : numbers)
        std::cout << num << " ";
}

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
void load_and_erase()
{
    int size;
    std::cin >> size;

    std::vector<int> arr(size);
    for (int i = 0; i < size; i++)
        std::cin >> arr[i];

    int q1;
    std::cin >> q1;

    int q2_1;
    std::cin >> q2_1;

    int q2_2;
    std::cin >> q2_2;

    arr.erase(arr.begin() + q1 - 1);
    arr.erase(arr.begin() + q2_1 - 1, arr.begin() + q2_2 - 1);

    std::cout << arr.size() << "\n";

    for (int num : arr)
        std::cout << num << " ";
}

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

void lower_bound()
{
    // Read the input array
    int size;
    std::cin >> size;

    std::vector<int> arr(size);
    for (int i = 0; i < size; i++)
        std::cin >> arr[i];

    // Read the querries
    int querry_num;
    std::cin >> querry_num;

    for (int i = 0; i < querry_num; i++)
    {
        int querry;
        std::cin >> querry;

        auto it = std::lower_bound(arr.begin(), arr.end(), querry);
        if (*it == querry)
        {
            std::cout << "Yes " << (it - arr.begin() + 1) << "\n";
        }
        else
        {
            std::cout << "No " << (it - arr.begin() + 1) << "\n";
        }
    }
}

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
void set_querry()
{
    int querry_number;
    std::cin >> querry_number;

    std::set<int> set;
    for (int i = 0; i < querry_number; i++)
    {
        int y, x;
        std::cin >> y >> x;

        if (y == 1)
        {
            set.insert(x);
        }
        else if (y == 2)
        {
            set.erase(x);
        }
        else
        {
            std::set<int>::iterator it = set.find(x);
            if (it == set.end())
                std::cout << "No\n";
            else
                std::cout << "Yes\n";

        }
    }
}

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
void map_querry()
{
    std::map<std::string, int> map;

    int querry_number;
    std::cin >> querry_number;

    for (int i = 0; i < querry_number; i++)
    {
        int querry_type;
        std::string key;
        std::cin >> querry_type >> key;

        if (querry_type == 1)
        {
            int mark;
            std::cin >> mark;

            map[key] += mark;
        }
        else if (querry_type == 2)
        {
            map.erase(key);
        }
        else
        {
            std::cout << map[key] << "\n";
        }
    }
}

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

std::vector<std::string> tokenize(std::string line)
{
    std::vector<std::string> tokens;
    std::string token = "";

    for (char ch : line)
    {
        if (std::isspace(ch))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (ch == '=' || ch == '<' || ch == '>' || ch == '"' || ch == '/')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }

            if (ch != '"')
                tokens.push_back(std::string(1, ch));
        }
        else
        {
            token += ch;
        }
    }

    if (!token.empty())
        tokens.push_back(token);

    return tokens;
}

std::string to_path(std::vector<std::string> stack)
{
    std::string path;
    for (std::string str : stack)
    {
        path += str;
    }

    return path;
}

void parse_tokens(std::unordered_map<std::string, std::string> &attribute_map, std::vector<std::string> tokens)
{
    static std::vector<std::string> path_stack;

    int i = 0;
    while(i < tokens.size())
    {
        /* Manage Path */
        if (tokens[i] == "<")
        {
            // Close the tag
            if (tokens[i + 1] == "/")
            {
                // Delete last of the tags
                path_stack.erase(path_stack.end() - 1);

                // Delete "." if that was not the only tag
                if (!path_stack.empty())
                    path_stack.erase(path_stack.end() - 1);

                i += 3;
            }
            // Open a tag
            else
            {
                // Add the "." if not empty
                if (!path_stack.empty())
                    path_stack.push_back(".");

                // Add the tag
                path_stack.push_back(tokens[i + 1]);
                i += 2;
            }
        }
        /* Map Keys and Values */
        else if (tokens[i] == "=")
        {
            // Add key and value
            std::string key = tokens[i - 1];
            std::string value = tokens[i + 1];
            std::string path = to_path(path_stack);

            attribute_map[path + "~" + key] = value;
            i += 2;
        }
        else
        {
            i += 1;
        }
    }
}

void parse_attributes_entry()
{
    // Store attributes
    std::unordered_map<std::string, std::string> attribute_map;

    // Read input amounts
    int N, Q;
    std::cin >> N >> Q;
    std::cin.ignore();

    // Read and parse lines
    for (int i = 0; i < N; i++)
    {
        // Read the line
        std::string line;
        std::getline(std::cin, line);

        // Parse the line
        std::vector<std::string> tokens = tokenize(line);
        parse_tokens(attribute_map, tokens);
    }

    // Read and answer querries
    for (int i = 0; i < Q; i++)
    {
        // Read query
        std::string querry;
        std::getline(std::cin, querry);

        // Output value of the attribute
        auto it = attribute_map.find(querry);
        if (it == attribute_map.end())
            std::cout << "Not Found!\n";
        else
            std::cout << it->second << "\n";
    }
}
