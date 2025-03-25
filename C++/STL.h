#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>

// You are given N integers. Sort the integers and print the sorted order.
// Store the N integers in a vector. Vectors are sequence containers representing arrays that can change in size.

int load_and_sort()
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
int load_and_erase()
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

int lower_bound()
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
int set_querry()
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
int map_querry()
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
