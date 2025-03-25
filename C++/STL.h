#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

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
