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
