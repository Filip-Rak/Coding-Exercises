#include "IntKit.h"

int sockMerchant(int n, std::vector<int> ar)
{
    // Store all occurances
    const int MAX_ID = 100;
    std::vector<int> freq(MAX_ID, 0);

    // Count sockes per color
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

void dfs_explore(int current, const std::unordered_map<int, std::vector<int>> graph, std::unordered_set<int>& visited)
{
    // Save the node as visited
    visited.insert(current);

    // Further explore other neighbors
    for (int node : graph.at(current))
    {
        if (!visited.contains(node))
            dfs_explore(node, graph, visited);
    }
}

std::unordered_set<int> get_connections(int start_node, const std::unordered_map<int, std::vector<int>> graph)
{
    // Create result set and start recursion
    std::unordered_set<int> visited;
    dfs_explore(start_node, graph, visited);

    return visited;
}

std::unordered_set<int> dfs_reachable_nodes(int start_node, const std::unordered_map<int, std::vector<int>> graph)
{
    std::unordered_set<int> visited;
    std::stack<int> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        visited.insert(current);
        for (int neighbor : graph.at(current))
        {
            if (!visited.contains(neighbor))
                stack.push(neighbor);
        }
    }

    return visited;
}

std::unordered_map<int, std::vector<int>> load_matrix_as_map(const std::string& filename)
{
    std::unordered_map<int, std::vector<int>> graph;
    std::ifstream file(filename);

    if (!file.good())
        throw std::runtime_error("Failed to open file: " + filename);

    int outer_index = 0;
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> connections;
        std::stringstream ss(line);

        int inner_index = 0;
        int buffer;
        while (ss >> buffer)
        {
            if (buffer == 1)
                connections.push_back(inner_index);

            inner_index++;
        }

        graph[outer_index++] = connections;
    }

    file.close();
    return graph;
}

void dfs_connect_to_all_entry()
{
    /* Load The Graph */
    std::cout << "Filename with extension: ";
    std::string filename; std::cin >> filename;

    std::unordered_map<int, std::vector<int>> graph;
    try
    {
        graph = load_matrix_as_map(filename);
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return;
    }

    /* Find & Print all fully valid entry nodes */
    std::cout << "Nodes that can reach all other nodes: ";
    for (int i = 0; i < graph.size(); i++)
    {
        // auto res = get_connections(i, graph);
        auto res = dfs_reachable_nodes(i, graph);
        if (res.size() == graph.size())
            std::cout << i << " ";
    }

    std::cout << "\n";
}

std::vector<int> dfs_find_path(int start_node, int tgt_node, const std::vector<std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    std::unordered_map<int, int> parent;
    std::stack<int> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        if (visited.contains(current))
            continue;

        if (current == tgt_node)
        {
            std::vector<int> path;
            int node = tgt_node;
            
            while (node != start_node)
            {
                path.push_back(node);
                node = parent[node];
            }
            
            path.push_back(start_node);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int child = graph[current].size() - 1; child >= 0; child--)
        {
            if (!visited.contains(child) && graph[current][child] == 1)
            {
                stack.push(child);
                parent[child] = current;
            }
        }
    }

    return {};
}

bool dfs_find_path_rec(int current_node, int tgt_node, 
    const std::vector<std::vector<int>>& graph, 
    std::unordered_set<int>& visited, 
    std::vector<int>& path)
{
    if (!visited.insert(current_node).second)
        return false;

    path.push_back(current_node);

    if (current_node == tgt_node)
        return true;

    for (int neighbor = 0; neighbor < graph[current_node].size(); neighbor++)
    {
        if (!visited.contains(neighbor) && graph[current_node][neighbor] == 1)
        {
            if (dfs_find_path_rec(neighbor, tgt_node, graph, visited, path))
            {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

std::vector<int> find_path_rec(int start_node, int tgt_node, const std::vector<std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    std::vector<int> path;

    if (dfs_find_path_rec(start_node, tgt_node, graph, visited, path))
        return path;

    return {};
}

void find_path_entry()
{
    std::vector<std::vector<int>> graph =
    {
        {0, 1, 0, 0}, // Node 0 connects to 1 and 2
        {0, 0, 1, 0}, // Node 1 connects to 3
        {0, 0, 0, 1}, // Node 2 connects to 3
        {0, 0, 0, 0}  // Node 3 has no outgoing edges
    };

    auto ret = find_path_rec(0, 3, graph);
    for (auto node : ret)
    {
        std::cout << node << " ";
    }

    std::cout << "\n";
}

std::vector<std::vector<int>> group_graph_components(const std::unordered_map<int, std::vector<int>>& graph)
{
    std::vector<std::vector<int>> groups;
    std::unordered_set<int> visited;

    for (const auto& [entry, _] : graph)
    {
        if (visited.contains(entry))
            continue;

        std::vector<int> group;
        std::stack<int> stack;

        stack.push(entry);
        visited.insert(entry);

        while (!stack.empty())
        {
            int current = stack.top();
            stack.pop();

            group.push_back(current);

            auto it = graph.find(current);
            if (it == graph.end())
                continue;

            for (int neighbor : it->second)
            {
                if (!visited.contains(neighbor))
                {
                    stack.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        groups.push_back(std::move(group));
    }

    return groups;
}

void make_graph_undirected(std::unordered_map<int, std::vector<int>>& graph)
{
    for (auto& [node, neighbors] : graph)
    {
        for (int neighbor : neighbors)
        {
            auto not_found = std::find(neighbors.begin(), neighbors.end(), node) == neighbors.end();
            if (not_found)
                graph[neighbor].push_back(node);
        }
    }
}

void group_components_entry()
{
    std::unordered_map<int, std::vector<int>> graph =
    {
        {0, {}},
        {1, {0}},
        {2, {1}},
        {3, {}},
        {4, {3}},
    };

    make_graph_undirected(graph);

    for (auto group : group_graph_components(graph))
    {
        for (auto member : group)
            std::cout << member << " ";

        std::cout << "\n";
    }
}

bool dfs_has_cycles(const std::unordered_map<int, std::vector<int>>& graph)
{
    std::unordered_set<int> visited;

    for (const auto& [start_node, _] : graph)
    {
        if (visited.contains(start_node))
            continue;

        visited.insert(start_node);

        std::stack<std::pair<int, int>> stack;
        stack.emplace(start_node, -1);

        while (!stack.empty())
        {
            auto [current, parent] = stack.top();
            stack.pop();

            auto it = graph.find(current);
            if (it == graph.end())
                continue;

            for (int neighbor : it->second)
            {
                if (!visited.contains(neighbor))
                {
                    stack.emplace(neighbor, current);
                    visited.insert(neighbor);
                }
                else if (neighbor != parent)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void detect_cycles_entry()
{
    std::unordered_map<int, std::vector<int>> graph =
    {
        {0, {1}},
        {1, {0}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {2, 3}}
    };

   std::cout << dfs_has_cycles(graph) << "\n";
}

LRUCacher::LRUCacher(int capacity)
    : CAPACITY(capacity){}

std::optional<int> LRUCacher::get(int key)
{
    auto it = cache.find(key);
    if (it == cache.end())
        return std::nullopt;

    usage_order.splice(usage_order.begin(), usage_order, it->second);
    return std::make_optional(usage_order.front().second);
}

void LRUCacher::put(int key, int value)
{
    auto cache_iterator = cache.find(key);
    if (cache_iterator == cache.end())
    {
        if (cache.size() == CAPACITY)
        {
            int key_to_delete = usage_order.back().first;
            usage_order.pop_back();
            cache.erase(key_to_delete);
        }

        usage_order.emplace_front(key, value);
        auto usage_iterator = usage_order.begin();
        cache[key] = usage_iterator;
    }
    else
    {
        auto usage_iterator = cache_iterator->second;
        usage_iterator->second = value;

        usage_order.splice(usage_order.begin(), usage_order, usage_iterator);
    }
}

void explore_islands(int i, int j, std::vector<std::vector<int>>& matrix)
{
    // Verify if valid
    if (i < 0 || i >= matrix.size()) return;
    if (j < 0 || j >= matrix[i].size()) return;
    if (matrix[i][j] == 0) return;

    // Mark as visited -> sink.
    matrix[i][j] = 0;

    // Further explore neighbors in 4 directions
    explore_islands(i, j + 1, matrix);
    explore_islands(i + 1, j, matrix);
    explore_islands(i, j - 1, matrix);
    explore_islands(i - 1, j, matrix);
}

int number_of_islands(const std::vector<std::vector<int>>& matrix)
{
    auto matrix_copy(matrix);
    int island_num = 0;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix_copy[i][j] == 1)
            {
                explore_islands(i, j, matrix_copy);
                island_num += 1;
            }
        }
    }

    return island_num;
}

void island_num_entry()
{
    std::vector<std::vector<int>> matrix =
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    std::cout << number_of_islands(matrix);
}

void dfs_flood_fill(int x, int y, int old_color, int new_color, std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& visited)
{
    // Verify if the cell is valid
    if (x < 0 || x >= matrix.size()) return;
    if (y < 0 || y >= matrix[x].size()) return;
    if (visited[x][y]) return;
    if (matrix[x][y] != old_color) return;

    // Add the cell to the list of visited cells
    visited[x][y] = true;

    // Color the cell
    matrix[x][y] = new_color;

    // Explore neighboring cells
    std::vector<std::pair<int, int>> directions =
    {
        {0, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
    };

    for (const auto& [dir_x, dir_y] : directions)
        dfs_flood_fill(x + dir_x, y + dir_y, old_color, new_color, matrix, visited);
}

void flood_cell(int cell_x, int cell_y, int new_color, std::vector<std::vector<int>>& matrix)
{
    if (matrix.size() <= cell_x || matrix[cell_x].size() <= cell_y)
        return;

    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));
    dfs_flood_fill(cell_x, cell_y, matrix[cell_x][cell_y], new_color, matrix, visited);
}

void flood_cell_iterative(int start_x, int start_y, int new_color, std::vector<std::vector<int>>& matrix)
{
    // Validate the starting cell
    if (start_x < 0 || start_x >= matrix.size()) return;
    if (start_y < 0 || start_y >= matrix[start_x].size()) return;

    const int tgt_color = matrix[start_x][start_y];
    const std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));
    std::stack<std::pair<int, int>> stack; // {x, y}
    stack.emplace(start_x, start_y);

    while (!stack.empty())
    {
        auto [current_x, current_y] = stack.top();
        stack.pop();

        // Validate current cell
        if (current_x < 0 || current_x >= matrix.size()) continue;
        if (current_y < 0 || current_y >= matrix[current_x].size()) continue;
        if (visited[current_x][current_y]) continue;
        if (matrix[current_x][current_y] != tgt_color) continue;

        // Mark as visited
        visited[current_x][current_y] = true;

        // Modify the color
        matrix[current_x][current_y] = new_color;

        // Expand towards other directions
        for (auto [dir_x, dir_y] : directions)
            stack.emplace(current_x + dir_x, current_y + dir_y);
    }
}

void flood_cell_entry()
{
    std::vector<std::vector<int>> matrix =
    {
        {1, 1, 0},
        {1, 0, 0},
        {0, 0, 0}
    };

    flood_cell_iterative(0, 2, 7, matrix);

    for (auto row : matrix)
    {
        for (int element : row)
            std::cout << element << " ";

        std::cout << "\n";
    }
}

std::vector<std::pair<int, int>> bfs_shortest_path(int start_x, int start_y, int tgt_x, int tgt_y, const std::vector<std::vector<int>>& grid)
{
    // Validate nodes
    if (start_x < 0 || start_x >= grid.size() ||
        start_y < 0 || start_y >= grid[start_x].size() ||
        tgt_x < 0 || tgt_x >= grid.size() ||
        tgt_y < 0 || tgt_y >= grid[tgt_x].size())
        return {};

    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    std::queue<std::pair<int, int>> queue;

    queue.emplace(start_x, start_y);
    visited[start_x][start_y] = true;

    while (!queue.empty())
    {
        // Retrieve the node
        auto [current_x, current_y] = queue.front();
        queue.pop();

        if (current_x == tgt_x && current_y == tgt_y)
        {
            // Reconstruct the path
            std::vector<std::pair<int, int>> path;
            path.emplace_back(current_x, current_y);

            auto [node_x, node_y] = parent[{current_x, current_y}];
            while (node_x != start_x || node_y != start_y)
            {
                path.emplace_back(node_x, node_y);
                auto [n_x, n_y] = parent[{node_x, node_y}];
                node_x = n_x;
                node_y = n_y;
            }

            path.emplace_back(start_x, start_y);
            std::reverse(path.begin(), path.end());

            return path;
        }
        
        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (auto [dir_x, dir_y] : directions)
        {
            int n_x = current_x + dir_x;
            int n_y = current_y + dir_y;

            // Validate the node
            if (n_x < 0 || n_x >= grid.size()) continue;
            if (n_y < 0 || n_y >= grid[n_x].size()) continue;
            if (visited[n_x][n_y]) continue;
            if (grid[n_x][n_y] != 1) continue;

            queue.emplace(n_x, n_y);
            visited[n_x][n_y] = true;
            parent[{n_x, n_y}] = { current_x, current_y };
        }
    }

    return {};
}

void grid_shortest_path_entry()
{
    std::vector<std::vector<int>> grid =
    {
        {1, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 0}
    };

    auto path = bfs_shortest_path(0, 0, 3, 2, grid);
    for (auto [x, y] : path)
    {
        std::cout << x << " " << y << "\n";
    }
}

int bfs_mins_to_rot(std::vector<std::vector<int>>& matrix)
{
    if (matrix.size() == 0)
        return -1;

    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));
    std::queue<std::pair<int, int>> spread_queue;
    std::queue<std::pair<int, int>> rotting_queue;

    /* Find all rotten oranges */
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == 2)
            {
                spread_queue.emplace(i, j);
                visited[i][j] = true;
            }
        }
    }

    int minutes_passed = 0; // Result

    /* Main loop */
    while (!spread_queue.empty() || !rotting_queue.empty())
    {
        /* Spread the rot to neighbors */
        while (!spread_queue.empty())
        {
            // Retrieve front node
            auto [current_x, current_y] = spread_queue.front();
            spread_queue.pop();

            // Feed rotting queue with neighbor nodes
            std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
            for (auto [dir_x, dir_y] : directions)
            {
                int n_x = current_x + dir_x;
                int n_y = current_y + dir_y;

                // Validate the neighbor
                if (n_x < 0 || n_x >= matrix.size()) continue;
                if (n_y < 0 || n_y >= matrix[n_x].size()) continue;
                if (visited[n_x][n_y]) continue;
                if (matrix[n_x][n_y] != 1) continue;

                // Add to stack & mark as visited
                rotting_queue.emplace(n_x, n_y);
                visited[n_x][n_y] = true;

                // Mark as rotten
                matrix[n_x][n_y] = 2;
            }
        }

        /* Move rotting fruits to spread queue */
        spread_queue = std::move(rotting_queue);

        /* Increase the timer */
        if (!spread_queue.empty())
            minutes_passed += 1;
    }

    // Find if every fruit has rotten
    for (auto row : matrix)
    {
        for (int fruit : row)
            if (fruit == 1)
                return -1;
    }

    return minutes_passed;
}

int bfs_mins_to_rot2(std::vector<std::vector<int>>& matrix)
{
    // Make sure the matrix isn't empty
    if (matrix.empty() || matrix[0].empty())
        return -1;

    const int rows = matrix.size();
    const int cols = matrix[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> queue;
    int fresh_oranges = 0;

    // Find all rotting oranges and get the number of fresh ones
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 2)
            {
                queue.emplace(i, j);
                visited[i][j] = true;
            }
               
            if (matrix[i][j] == 1) 
                fresh_oranges += 1;
        }
    }

    const std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    int minutes_passed = 0;
    while (!queue.empty())
    {
        // Save the number of elements in the queue before new oranges are added
        int size = queue.size();
        bool has_rotten = false;

        // Spread rot to new ornages
        for (int i = 0; i < size; i++)
        {
            auto [current_x, current_y] = queue.front();
            queue.pop();

            for (auto [dir_x, dir_y] : directions)
            {
                int n_x = current_x + dir_x;
                int n_y = current_y + dir_y;

                if (n_x < 0 || n_x >= rows) continue;
                if (n_y < 0 || n_y >= cols) continue;
                if (visited[n_x][n_y]) continue;
                if (matrix[n_x][n_y] != 1) continue;

                visited[n_x][n_y] = true;
                matrix[n_x][n_y] = 2;
                queue.emplace(n_x, n_y);
                fresh_oranges -= 1;
                has_rotten = true;
            }
        }

        if (has_rotten)
            minutes_passed += 1;
    }

    return (fresh_oranges > 0) ? -1 : minutes_passed;
}

void rotting_oranges_entry()
{
    std::vector<std::vector<int>> matrix =
    {
        {1,1,1},
        {1,2,1},
        {1,1,1}
    };

    std::cout << bfs_mins_to_rot2(matrix) << "\n";
}

int least_word_transformations(std::string start_word, std::string end_word, std::vector<std::string> words)
{
    std::unordered_set<std::string> word_set(words.begin(), words.end());
    if (words.size() == 0 || !word_set.contains(end_word)) return 0;

    std::queue<std::pair<std::string, int>> queue;

    queue.emplace(start_word, 1);
    word_set.erase(start_word);

    while (!queue.empty())
    {
        auto [current_word, level] = queue.front();
        queue.pop();

        if (current_word == end_word)
        {
            return level;
        }

        for (int i = 0; i < current_word.size(); i++)
        {
            std::string new_word = current_word;
            for (char c = 'a'; c <= 'z'; c++)
            {
                new_word[i] = c;
                if (word_set.contains(new_word))
                {
                    queue.emplace(new_word, level + 1);
                    word_set.erase(new_word);
                }
            }
        }
    }

    return 0;
}

std::optional<std::vector<std::string>> shortest_word_ladder(const std::string& start_word, const std::string& tgt_word, const std::vector<std::string>& words)
{
    if (words.empty()) 
        return std::nullopt;

    std::unordered_set<std::string> word_set(words.begin(), words.end());
    if (!word_set.contains(tgt_word))
        return std::nullopt;

    std::unordered_map<std::string, std::string> parent;
    std::queue<std::string> queue;

    queue.push(start_word);
    word_set.erase(start_word);

    while (!queue.empty())
    {
        std::string current_word = queue.front();
        queue.pop();

        if (current_word == tgt_word)
        {
            std::vector<std::string> path;
            
            std::string word = tgt_word;
            while (word != start_word)
            {
                path.push_back(word);
                word = parent[word];
            }

            path.push_back(start_word);
            std::reverse(path.begin(), path.end());

            return std::make_optional(path);
        }

        for (int i = 0; i < current_word.size(); i++)
        {
            std::string new_word = current_word;
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c == current_word[i]) continue;
                new_word[i] = c;

                if (word_set.contains(new_word))
                {
                    parent[new_word] = current_word;
                    queue.push(new_word);
                    word_set.erase(new_word);
                }
            }
        }
    }

    return std::nullopt;
}

void word_ladder_entry()
{
    std::string start_word = "cold";
    std::string end_word = "warm";

    std::vector<std::string> words = {
        "cold", "cord", "card", "ward", "warm", "worm", "word",
        "sold", "told", "bold", "bald", "gold", "goad", "load", "loan",
        "loon", "look", "book", "back", "pack", "puck", "luck", "duck",
        "suck", "sock", "sick", "pick", "pock", "dock", "dork", "dark",
        "lark", "bark", "barn", "born", "corn", "porn", "form", "farm",
        "harm", "harp", "hard", "card", "care", "cane", "lane", "lame",
        "came", "camp", "lamp"
    };


    // std::cout << least_word_transformations(start_word, end_word, word_list);

    auto ret = shortest_word_ladder(start_word, end_word, words);
    if (ret.has_value())
    {
        for (auto word : ret.value())
            std::cout << word << " ";
    }
    else
        std::cout << "No value on return";


    std::cout << "\n";
}

std::optional<int> number_of_lock_moves(const std::string& target_lock, const std::vector<std::string>& deadends)
{
    const std::string START = "0000";
    const std::vector<int> DIRECTIONS = { 1, -1 };
    const int RANGE = 10;

    std::unordered_set<std::string> visited(deadends.begin(), deadends.end());

    if (visited.contains(START))
        return std::nullopt;

    std::queue<std::pair<std::string, int>> queue; // [current, level]
    queue.emplace(START, 0);
    visited.insert(START);

    while (!queue.empty())
    {
        auto [current_lock, level] = queue.front();
        queue.pop();

        if (current_lock == target_lock)
        {
            return std::make_optional(level);
        }

        for (int i = 0; i < current_lock.size(); i++)
        {
            std::string new_lock = current_lock;
            int current_digit = new_lock[i] - char('0');

            for (int direction : DIRECTIONS)
            {
                int new_digit = ((current_digit + direction) % RANGE + RANGE) % RANGE;
                new_lock[i] = new_digit + char('0');

                if (!visited.contains(new_lock))
                {
                    visited.insert(new_lock);
                    queue.emplace(new_lock, level + 1);
                }
            }
        }
    }

    return std::nullopt;
}

void open_the_lock_entry()
{
    std::vector<std::string> deadends = {
        "8887","8889","8878","8898","8788","8988","7888","9888"
    };
    std::string target = "8888";

    auto ret = number_of_lock_moves(target, deadends);
    if (ret.has_value())
        std::cout << ret.value() << "\n";
    else
        std::cout << "Combination unattainable\n";
}

std::string compress_string(const std::string& str)
{
    if (str.empty())
        return "";
    
    std::string result;
    char prev = str[0];
    int count = 1;

    for (int i = 1; i < str.size(); i++)
    {
        if (str[i] == prev)
        {
            count += 1;
        }
        else
        {
            result += prev + std::to_string(count);
            prev = str[i];
            count = 1;
        }
    }

    result += prev + std::to_string(count);

    return result;
}

void compress_string_entry()
{
    std::string str = "aabcccccaaa";
    std::cout << compress_string(str) << "\n";
}

std::string rot_str(const std::string& str, int left)
{
    int size = str.size();
    int norm_left = (left % size + size) % size;
    std::string result = str;

    for (int i = 0; i < size; i++)
    {
        int new_index = ((i - norm_left) % size + size) % size;
        result[new_index] = str[i];
    }

    return result;
}

bool is_str_a_rot(const std::string& str1, const std::string& str2)
{
    if (str1.size() != str2.size() || str1.size() == 0 || str1 == str2)
        return false;

    std::string total = str1 + str1;
    return (total.find(str2) != std::string::npos);
}

void is_a_rot_entry()
{
    std::string str1 = "string";
    std::string str2 = rot_str(str1, 0);

    std::cout << is_str_a_rot(str1, str2);
}

std::string longest_distinct_subs(const std::string str)
{
    if (str.empty())
        return "";

    std::unordered_map<char, int> last_seen;
    int max_start = 0, max_length = 0;
    int start = 0;

    int end;
    for (end = 0; end < str.size(); end++)
    {
        char c = str[end];
        if (last_seen.contains(c) && last_seen[c] >= start)
        {
            int length = end - start;
            if (length > max_length)
            {
                max_start = start;
                max_length = length;
            }

            start = last_seen[c] + 1;
        }

        last_seen[c] = end;
    }

    int length = end - start;
    if (length > max_length)
    {
        max_start = start;
        max_length = length;
    }

    return str.substr(max_start, max_length);
}

void longest_distinct_sub_entry()
{
    std::string str("abccbad");
    std::cout << longest_distinct_subs(str) << "\n";
}

std::vector<std::string> distinct_subs_k(const std::string& str, int k)
{
    int size = str.size();
    if (size <= 0 || k <= 0)
        return {};

    const int offset = 1;
    std::unordered_map<char, int> last_seen;
    std::unordered_set<std::string> result_set;
    std::vector<std::string> results;

    int start = 0;
    for (int end = 0; end < size; end++)
    {
        char c = str[end];
        int last_index = last_seen[c] - offset;
        if (last_index >= start)
            start = last_index + 1;

        last_seen[c] = end + offset;

        int length = end - start + 1;
        if (length == k)
        {
            std::string substr = str.substr(start, k);
            bool inserted = result_set.insert(substr).second;

            if (inserted) results.push_back(substr);

            start += 1;
        }
    }

    return results;
}

void distinct_subs_k_entry()
{
    std::string str = "awaglknagawunagwkwagl";
    int k = 4;

    auto ret = distinct_subs_k(str, k);
    for (auto str : ret)
        std::cout << str << "\n";

    std::cout << "Count: " << ret.size() << "\n";
}

int min_num_of_jumps(std::vector<int> arr)
{
    const int size = arr.size();
    int jumps = 0;
    int index = 0;

    for (int i = 0; i < size - 1; i++)
    {
        if (i + 2 < size)
        {
            if (arr[i + 2] != 1)
                i += 1;
        }
        
        jumps += 1;
    }

    return jumps;
}

void cloud_jumper_entry()
{
    std::vector<int> arr = { 0, 1, 0, 0, 0, 1, 0 };
    std::cout << min_num_of_jumps(arr) << "\n";
}

bool custom_greater_comp(int a, int b)
{
    return a > b;
}

void comparators_entry()
{
    auto comp = [](int a, int b) { return a > b; };

    std::vector<int> arr1 = { 1, 3, 2, 5, 4 };
    std::sort(arr1.begin(), arr1.end(), comp);

    for (int num : arr1)
        std::cout << num << " ";

    std::cout << "\n";

    int arr2[] = { 1, 3, 2, 5, 4 };
    // std::sort(std::begin(arr2), std::end(arr2), comp);
    std::sort(std::begin(arr2), std::end(arr2), std::less<int>());

    for (int num : arr2)
        std::cout << num << " ";

    std::cout << "\n";

    // std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);
    std::priority_queue<int, std::vector<int>, std::less<int>> pq;

    for (int num : arr1)
        pq.push(num);

    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }

    std::cout << "\n";
}

std::string longest_unique_substr(const std::string& str)
{
    std::unordered_map<char, int> last_seen;
    int max_start = 0, max_length = 0;
    int start = 0;

    for (int end = 0; end < str.size(); end++)
    {
        char c = str[end];

        if (last_seen.contains(c) && last_seen[c] >= start)
        {
            int length = end - start;
            if (length > max_length)
            {
                max_length = length;
                max_start = start;
            }

            start = last_seen[c] + 1;
        }

        last_seen[c] = end;
    }

    int length = str.size() - start;
    if (length > max_length)
    {
        max_length = length;
        max_start = start;
    }

    return str.substr(max_start, max_length);
}

void lus_entry()
{
    std::string str = "abccdfgc";
    std::cout << longest_unique_substr(str) << "\n";
}

std::vector<std::vector<int>> generate_all_subsets(const std::vector<int>& arr)
{
    std::vector<std::vector<int>> result;
    std::unordered_set<std::string> seen;

    std::vector<int> nums(arr);
    std::sort(nums.begin(), nums.end());

    std::stack<std::pair<int, std::vector<int>>> stack;
    stack.push({0, {}});

    while (!stack.empty())
    {
        auto [index, subset] = stack.top();
        stack.pop();

        if (index <= nums.size())
        {
            std::string key;
            for (int num : subset)
                key += std::to_string(num) + ";";

            bool inserted = seen.insert(key).second;
            if (inserted) result.push_back(subset);
        }

        if (index < nums.size())
        {
            // Exclude value under current index
            stack.push({index + 1, subset});

            // Include value under current index
            std::vector<int> included(subset);
            included.push_back(nums[index]);
            stack.push({index + 1, included});
        }
    }

    return result;
}

void generate_subsets_entry()
{
    std::vector<int> arr = { 1, 2, 2, 2 };
    
    auto ret = generate_all_subsets(arr);
    auto comp = [](const std::vector<int>& a, const std::vector<int>& b) 
        { 
            if (a.size() == b.size())
            {
                for (int i = 0; i < a.size(); i++)
                {
                    if (a[i] < b[i])
                        return true;

                    else if (a[i] > b[i])
                        return false;
                }
            }

            return a.size() > b.size(); 
        };

    std::sort(ret.begin(), ret.end(), comp);

    for (auto set : ret)
    {
        std::cout << "Set: ";
        for (auto num : set)
            std::cout << num << " ";

        std::cout << "\n";
    }

    std::cout << "\n";
}

std::vector<std::string> generate_all_permutations(const std::string& str)
{
    std::vector<std::string> result;
    std::unordered_set<std::string> visited;
    std::stack<std::pair<std::string, std::string>> stack; // [current, remainder]
    stack.emplace("", str);

    while (!stack.empty())
    {
        auto [current, remainder] = stack.top();
        stack.pop();

        if (remainder.empty())
        {
            bool inserted = visited.insert(current).second;
            if (inserted) result.push_back(current);
        }

        for (size_t i = 0; i < remainder.size(); i++)
        {
            std::string new_current = current + remainder[i];
            std::string new_remainder = remainder;
            new_remainder.erase(i, 1);

            stack.emplace(new_current, new_remainder);
        }
    }

    return result;
}

void generate_permutations_entry()
{
    std::string str = "abc";

    for (std::string entry : generate_all_permutations(str))
    {
        std::cout << entry << "\n";
    }
}

std::vector<std::vector<int>> generate_all_permutations(const std::vector<int>& arr)
{
    if (arr.empty())
        return {};

    std::unordered_set<std::string> visited;
    std::vector<std::vector<int>> result;
    std::stack<std::pair<std::string, std::string>> stack; // [current, remainder]

    const char DELIMITER = ' ';
    std::string initial_remainder;
    for (int num : arr)
        initial_remainder += std::to_string(num) + DELIMITER;

    stack.push({ "", initial_remainder });

    while (!stack.empty())
    {
        auto [current, remainder] = stack.top();
        stack.pop();

        if (current.size() == arr.size() * 2)
        {
            // Retrieve the array
            std::vector<int> local_result(arr.size());
            std::stringstream ss(current);

            int index = 0;
            int buffer;
            while (ss >> buffer)
                local_result[index++] = buffer;

            result.push_back(std::move(local_result));
            continue;
        }

        for (int i = 0; i < remainder.size(); i++)
        {
            if (remainder[i] == DELIMITER) continue;

            std::string next_current = current + DELIMITER + remainder[i];
            bool unique = visited.insert(next_current).second;
            if (!unique) continue;

            std::string next_remainder = remainder;
            next_remainder.erase(i, 1);
            stack.push({ next_current, next_remainder });
        }
    }

    return result;
}

void generate_all_vector_perms_entry()
{
    std::vector<int> arr = { 1, 2, 3 };
    for (auto sub_vec : generate_all_permutations(arr))
    {
        for (int num : sub_vec)
            std::cout << num << " ";

        std::cout << "\n";
    }
}

std::vector<std::string> generate_all_valid_parentheses(int n)
{
    struct Args
    {
        std::string string;
        int open_remaining;
        int close_remaining;
    };

    std::vector<std::string> result;
    std::stack<Args> stack;
    stack.emplace("", n, n);

    while (!stack.empty())
    {
        Args current = stack.top();
        stack.pop();

        if (current.open_remaining == 0 && current.close_remaining == 0)
        {
            result.push_back(current.string);
            continue;
        }

        if (current.open_remaining > 0)
        {
            Args new_args = { current.string + "(", current.open_remaining - 1, current.close_remaining };
            stack.push(new_args);
        }

        if (current.close_remaining > current.open_remaining)
        {
            Args new_args = { current.string + ")", current.open_remaining, current.close_remaining - 1 };
            stack.push(new_args);
        }
    }

    return result;
}

void gen_valid_per_entry()
{
    for (std::string gen : generate_all_valid_parentheses(3))
    {
        std::cout << gen << "\n";
    }
}

std::vector<std::vector<int>> generate_all_subsets2(std::vector<int> arr)
{
    if (arr.empty())
        return {};

    std::unordered_set<std::string> unique;
    std::vector<std::vector<int>> results;
    std::stack<std::pair<int, std::vector<int>>> stack; // [index, subset]

    std::sort(arr.begin(), arr.end());
    stack.push({ 0, {} });

    while (!stack.empty())
    {
        auto [current_index, current_subset] = stack.top();
        stack.pop();

        if (current_index <= arr.size())
        {
            std::string str;
            for (int num : current_subset)
                str += std::to_string(num) + ";";

            bool inserted = unique.insert(str).second;
            if (inserted) results.push_back(current_subset);
        }

        if (current_index < arr.size())
        {
            // Include current index
            std::vector<int> next_subset(current_subset);
            next_subset.push_back(arr[current_index]);
            stack.emplace(current_index + 1, next_subset);

            // Exclude current index
            stack.emplace(current_index + 1, current_subset);
        }
    }

    return results;
}
