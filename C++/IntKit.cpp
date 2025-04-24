#include "IntKit.h"

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

bool valid_parentheses(const std::string& line)
{
    std::unordered_map<char, char> brackets =
    {
        {'}', '{'},
        {']', '['},
        {')', '('},
    };

    std::stack<char> opened;
    for (char c : line)
    {
        if (brackets.contains(c))
        {
            if (!opened.empty() && opened.top() == brackets[c])
                opened.pop();
            else
                return false;
        }
        else
        {
            opened.push(c);
        }
    }

    return opened.empty();
}

void valid_parentheses_entry()
{
    std::unordered_map<std::string, bool> tests =
    {
        {"{[()]}", true},
        {"{[(]}", false},
        {"{[)]}", false},
        {"{}()[]", true},
        {"{{{{{{([])}}}}}}", true},
        {"", true},
        {"]", false},
        {"[", false},
    };

    int passed = 0;
    for (const auto& [test, expected_res] : tests)
    {
        if (expected_res == valid_parentheses(test))
            passed += 1;
        else
            std::cout << "Failed for: " << test << "\n";
    }

    std::cout << "Passed " << passed << " out of " << tests.size() << " tests\n";
}

std::vector<int> dfs_visit_order(int start, const std::unordered_map<int, std::vector<int>>& graph)
{
    std::vector<int> order;
    std::unordered_set<int> visited;
    std::stack<int> stack;
    stack.push(start);

    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();

        if (visited.contains(node))
            continue;

        visited.insert(node);
        order.push_back(node);

        auto children = graph.at(node);
        for (auto it = children.rbegin(); it != children.rend(); it += 1)
            stack.push(*it);
    }

    return order;
}

void dfs_vo_entry()
{
    std::unordered_map<int, std::vector<int>> graph = {
        {0, {1, 2}},
        {1, {3}},
        {2, {}},
        {3, {}}
    };

    for (auto node : dfs_visit_order(0, graph))
        std::cout << node << " ";

    std::cout << "\n";
}

bool dfs_is_reachable(int start, int target, const std::unordered_map<int, std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    std::stack<int> stack;
    stack.push(start);

    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();

        if (visited.contains(node))
            continue;

        if (node == target)
            return true;

        auto neighbours = graph.at(node);
        for (int neighbor : neighbours)
        {
            if (!visited.contains(neighbor))
                stack.push(neighbor);
        }
    }

    return false;
}

bool dfs_is_reachable_recursive(int current, int tgt, 
                                const std::unordered_map<int, std::vector<int>>& graph,
                                std::unordered_set<int>& visited)
{
    if (current = tgt)
        return true;

    visited.insert(current);

    for (int neighbor : graph.at(current))
    {
        if (!visited.contains(neighbor))
        {
            if (dfs_is_reachable_recursive(current, tgt, graph, visited))
                return true;
        }
    }

    return false;
}

bool dfs_rec_path(int current, int tgt, 
    const std::unordered_map<int, std::vector<int>>& graph, 
    std::unordered_set<int>& visited, 
    std::vector<int>& path)
{
    path.push_back(current);
    visited.insert(current);

    if (current == tgt)
        return true;

    for (int neighbor : graph.at(current))
    {
        if (!visited.contains(neighbor))
        {
            if (dfs_rec_path(neighbor, tgt, graph, visited, path))
                return true;
        }
    }

    path.pop_back();
    return false;
}

std::vector<int> dfs_find_path(int start, int tgt, 
    const std::unordered_map<int, 
    std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    std::vector<int> path;

    if (dfs_rec_path(start, tgt, graph, visited, path))
        return path;

    return {};
}

void dfs_entry()
{
    std::unordered_map<int, std::vector<int>> graph = {
        {0, {1, 2}},
        {1, {3}},
        {2, {}},
        {3, {4}},
        {4, {}},
    };

    std::cout << "Iterative: " << dfs_is_reachable(0, 4, graph) << "\n";

    std::unordered_set<int> visited;
    std::cout << "Recursive: " << dfs_is_reachable_recursive(0, 4, graph, visited) << "\n";

    std::cout << "\n/* Find the Path */\n";
    for (int node : dfs_find_path(0, 4, graph))
        std::cout << node << " ";

    std::cout << "\n";
}

void dfs_explore(int current, const std::vector<std::vector<int>>& graph, std::unordered_set<int>& visited)
{
    // Save the node as visited
    visited.insert(current);

    // Further explore other neighbors
    for (int node = 0; node < graph[current].size(); node++)
    {
        if (!visited.contains(node) && graph[current][node] == 1)
            dfs_explore(node, graph, visited);
    }
}

// Wrapper for the recursive function
std::unordered_set<int> get_connections(int start_node, const std::vector<std::vector<int>>& graph)
{
    // Create result set and start recursion
    std::unordered_set<int> visited;
    dfs_explore(start_node, graph, visited);

    return visited;
}

std::vector<std::vector<int>> load_graph_verts(const std::string& filename)
{
    std::vector<std::vector<int>> graph;
    std::ifstream file(filename);

    if (!file.good())
        throw std::runtime_error("Failed to open file: " + filename);

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> connections;
        std::stringstream ss(line);

        int buffer;
        while (ss >> buffer)
            connections.push_back(buffer);

        graph.push_back(connections);
    }

    file.close();
    return graph;
}

void dfs_connect_to_all_entry()
{
    /* Load The Graph */
    std::cout << "Filename (including extension): ";
    std::string filename; std::cin >> filename;

    std::vector<std::vector<int>> graph;
    try
    {
        graph = load_graph_verts(filename);
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return;
    }

    /* Find & Print all fully valid entry nodes */
    std::cout << "Nodes with connections to every other node: ";
    for (int i = 0; i < graph.size(); i++)
    {
        auto res = get_connections(i, graph);
        if (res.size() == graph.size())
            std::cout << i << " ";
    }

    std::cout << "\n";
}

