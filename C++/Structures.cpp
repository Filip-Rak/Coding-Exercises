#include "Structures.h"

void custom_list2_entry()
{
    CustomList2<int> list;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    for (int input : inputs)
        list.push_front(input);

    list.reverse();
    std::cout << "list.contains(6): " << list.contains(6) << "\n";
    std::cout << "list.insert_at(20, x): " << list.insert_at(20, 6) << "\n";
    
    auto [success, data] = list.pop_at(0);
    std::cout << "list.pop_at(x) -> Success: " << success << ", Data: " << data << "\n";

    std::cout << "list.to_vector(): ";
    for (int num : list.to_vector())
    {
        std::cout << num << " ";
    }

    CustomList2<int> list2 = list;

    std::cout << "\nlist.pop_front()/list.pop_back(): ";
    // while(list.get_size() > 0)
    while (true)
    {
        auto res = list.pop_front();
        if (res.first)
            std::cout << res.second << ", ";
        else
        {
            std::cout << "Out of elements!";
            break;
        }
    }

    std::cout << "\nlist2.pop_front()/list2.pop_back(): ";
    while (true)
    {
        auto res = list2.pop_front();
        if (res.first)
            std::cout << res.second << ", ";
        else
        {
            std::cout << "Out of elements!";
            break;
        }
    }

    std::cout << "\nlist.contains(6): " << list.contains(6);
    std::cout << "\n\nActive nodes debug: " << list.get_debug_active_nodes() << "\n";
}

void custom_vector_entry()
{
    CustomVector<int> arr;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    arr.push_back(-10);
    arr.push_back(-20);

    try 
    {
        arr[1] = 35;
    }
    catch (std::out_of_range exception)
    {
        std::cout << "Exception: " << exception.what() << "\n";
    }

    std::cout << "arr.contains(): " << arr.contains(35) << "\n";

    // arr.clear();

    for (int input : inputs)
        arr.push_back(input);

    arr.resize(5);
    std::cout << "arr.nsert_at(): " << arr.insert_at(10, 5) << "\n";
    std::cout << "arr.put(): " << arr.put(5, 6) << "\n";

    int index = 0;
    while(true)
    {
        auto ret = arr.get(index++);
        if (ret.first)
            std::cout << "arr[" << index - 1 << "] = " << ret.second << "\n";
        else
            break;
    }
}