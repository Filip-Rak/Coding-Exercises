#include "Interview-Preparation-Kit.h"

int sockMerchant(int n, std::vector<int> ar)
{
    // Store all occurances
    const int MAX_ID = 100;
    std::vector<int> freq(MAX_ID, 0);

    // Map all numbers to vector
    for (int i = 0; i < n; i++)
    {
        freq[ar[i] - 1] += 1;
    }

    // Count all pairs
    int count = 0;
    for (int f : freq)
    {
        count += f / 2; // Divide as integers
    }

    return count;
}

int countingValleys(int steps, std::string path)
{
    // Tracking parameters
    int level = 0;
    int valleys = 0;

    // Go through entire path
    for (char step : path)
    {
        // The step is down
        if (step == 'D')
        {
            level -= 1;
        }
        // The step is up
        else if (step == 'U')
        {
            level += 1;
            if (level == 0)
            {
                valleys += 1;
            }
        }
    }

    return valleys;
}

int jumpingOnClouds(std::vector<int> c)
{
    int jumps = 0;
    int total_distance = 0;
    int length = c.size();

    while (total_distance < length - 1)
    {
        if (total_distance < length - 2 && c[total_distance + 2] == 0)
            total_distance += 2;
        else
            total_distance += 1;

        jumps += 1;
    }

    return jumps;
}

long repeatedString(std::string s, long n)
{
    // Find the numbers of a's in the substring
    long sub_count = 0;
    for (char c : s)
    {
        if (c == 'a')
            sub_count += 1;
    }

    // Calculate how many times the subs string will FULLY fit in the infinite
    long full_inserts = n / s.size(); // Integer division
    long total_count = full_inserts * sub_count;
    long characters_left = n - full_inserts * s.size();

    // Go through the last substring that did not fully fit
    // and count the last 'a' characters
    for (long i = 0; i < characters_left; i++)
    {
        if (s[i] == 'a')
            total_count += 1;
    }

    return total_count;
}

std::vector<int> tokenize(const std::string& str)
{
    std::vector<int> tokens;
    std::stringstream ss(str);

    int buffer;
    while (ss >> buffer)
        tokens.push_back(buffer);

    return tokens;
}

bool process_line(const std::string& line, int current_light, std::unordered_map<int, bool>& map)
{
    bool color = false;
    if (map.contains(current_light))
        color = map[current_light];

    auto lights = tokenize(line);
    for (int light : lights)
    {
        if (map.contains(light) && light != !color)
        {
            return false;
        }

        map[light] = !color;
    }

    return true;
}

void problem_entry()
{
    std::unordered_map<int, bool> map;
    std::string line;
    int current_light = 0;

    while (std::getline(std::cin, line))
    {
        if (!process_line(line, current_light, map))
        {
            std::cout << "False\n";
            return;
        }

        current_light += 1;
    }

    std::cout << "True\n";
}

void rot_left(std::vector<int>& arr, int k)
{
    if (arr.empty())
        return;

    int size = arr.size();
    int norm_k = ((k % size) + size) % size;

    std::reverse(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.begin() + k);
    std::reverse(arr.begin() + k, arr.end());
}

void reverse3_rot_left_entry()
{
    std::vector<int> arr = { 1, 2, 3, 4, 5, 6 };
    rot_left(arr, 3);

    for (auto num : arr)
        std::cout << num << " ";

    std::cout << "\n";
}