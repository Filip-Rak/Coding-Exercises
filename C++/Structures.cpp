#include "Structures.h"

void custom_list2_entry()
{
    CustomList2<int> list;
    std::vector<int> inputs = { 1, 2, 3, 4, 5, 6 };

    for (int input : inputs)
        list.push_front(input);

    list.reverse();

    // while(list.get_size() > 0)
    while (true)
    {
        auto res = list.pop_back();
        if (res.first)
            std::cout << res.second << " ";
        else
        {
            std::cout << "\nOut of elements!";
            break;
        }
    }

    std::cout << "\nActive nodes debug: " << list.get_debug_active_nodes() << "\n";
}
