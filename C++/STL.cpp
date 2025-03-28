#include "STL.h"

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

void parse_tokens(std::unordered_map<std::string, std::string>& attribute_map, std::vector<std::string> tokens)
{
    static std::vector<std::string> path_stack;

    int i = 0;
    while (i < tokens.size())
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

void rect_area()
{
    /*
     * Declare a RectangleArea object
     */
    RectangleArea r_area;

    /*
     * Read the width and height
     */
    r_area.read_input();

    /*
     * Print the width and height
     */
    r_area.Rectangle::display();

    /*
     * Print the area
     */
    r_area.display();
}

void Rectangle::display()
{
    std::cout << width << " " << height << "\n";
}

void RectangleArea::read_input()
{
    std::cin >> width >> height;
}

void RectangleArea::display()
{
    std::cout << width * height << "\n";
}

Point::Point(int x, int y)
    : x(x), y(y) {}

std::string Point::to_string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

bool Point::operator==(const Point& other) const
{
    return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other) const
{
    return !(*this == other);
}

Point Point::operator+(const Point& other) const
{
    int new_x = this->x + other.x;
    int new_y = this->y + other.y;

    return Point(new_x, new_y);
}

Point Point::operator-(const Point& other) const
{
    int new_x = this->x - other.x;
    int new_y = this->y - other.y;

    return Point(new_x, new_y);
}

Point& Point::operator+=(const Point& other)
{
    *this = *this + other;
    return *this;
}

Point& Point::operator-=(const Point& other)
{
    *this = *this - other;
    return *this;
}

Point Point::operator()(int multi) const
{
    int new_x = this->x * multi;
    int new_y = this->y * multi;

    return Point(new_x, new_y);
}

Point& Point::operator[](std::string call)
{
    if (call == "clear")
    {
        this->x = 0;
        this->y = 0;
    }

    return *this;
}

Point& Point::operator[](int def)
{
    this->x = def;
    this->y = def;

    return *this;
}

std::ostream& operator<<(std::ostream& out, Point p)
{
    out << p.to_string();
    return out;
}

void operators_entry()
{
    const Point p1(10, 20);
    Point p2(1, 2);

    /*std::cout
        << (p1 != p2) << "\n"
        << p1 << "\n"
        << p2 << "\n";*/

    Point p3 = p2;
    p3 += p1;
    // std::cout << "P3: " << p3 << "\n";

    // std::cout << p3(5) << "\n";

    std::cout << p3 << "\n";
    p3[3];
    std::cout << p3;
}

void activity_selection_entry()
{
    // Querry amount of data
    int n = 0; std::cin >> n;

    // Allocate memory
    // (end_time, start_time)
    std::vector<std::pair<int, int>> data(n);

    // Load data
    for (int i = 0; i < n; i++)
        std::cin >> data[i].second;

    for (int i = 0; i < n; i++)
    {
        // Get end time from duration and save it
        int duration; std::cin >> duration;
        data[i].first = data[i].second + duration;
    }

    // Sort by end time
    std::sort(data.begin(), data.end());

    // Count the maximum number of available events
    int count = 0;
    int last_end = 0;

    for (const auto& pair : data)
    {
        if (pair.second >= last_end)
        {
            count += 1;
            last_end = pair.first;
        }
    }

    std::cout << count << "\n";
}

void class_templates_entry()
{
    // Add floats
    AddElement<float> float_adder(2.5);
    std::cout << "<float> " << float_adder.add(1.2) << "\n";

    // Add ints
    AddElement<int> int_adder(5);
    std::cout << "<int> " << int_adder.add(3) << "\n";

    // Add string
    AddElement<std::string> string_adder("1 + 1 = ");
    std::cout << "<std::string> " << string_adder.add("2") << "\n";

    // Add char
    AddElement<char> char_adder('C');
    std::cout << "<char> " << char_adder.add('#') << "\n";
}

void preprocessor_entry()
{
    std::vector<int> arr(TOTAL);
    for (int i = 0; i < TOTAL; i = increment(i, 1))
    {
        arr[i] = i;
    }

    foreach(arr)
    {
        std::cout << arr[i] << "\n";
    }
}

void iomanip_entry()
{
    std::cout << std::setiosflags(std::ios::uppercase);
    std::cout << std::setw(0xf) << std::internal;

    float A = 100.345;
    float B = 2006.008;
    float C = 2331.41592653498;

        std::cout
            << std::setw(3)
            << std::hex
            << std::showbase
            << std::nouppercase;
        std::cout << (long)A << "\n";

        std::cout
            << std::setprecision(2)
            << std::fixed
            << std::setw(15)
            << std::showpos
            << std::right
            << std::setfill('_')
            << B << "\n";

        std::cout
            << std::setprecision(9)
            << std::scientific
            << std::noshowpos
            << std::uppercase
            << C << "\n";

    }

std::ostream& operator<<(std::ostream& out, const Person& p)
{
    out << "name = " << p.get_name() << ", surname = " << p.get_surname();
    return out;
}

void person_entry()
{
    Person p1("Rafaelo", "Zoblotni");
    std::cout << p1 << "\n";
}

void fruits_and_colors_entry()
{
    int t = 0; std::cin >> t;

    for (int i = 0; i != t; ++i)
    {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        std::cout << Traits<Color>::name(index1) << " ";
        std::cout << Traits<Fruit>::name(index2) << "\n";
    }
}

int largest_proper_divisor(int n)
{
    if (n == 0)
    {
        throw invalid_argument("largest proper divisor is not defined for n=0");
    }
    if (n == 1)
    {
        throw invalid_argument("largest proper divisor is not defined for n=1");
    }
    for (int i = n / 2; i >= 1; --i)
    {
        if (n % i == 0) {
            return i;
        }
    }
    return -1; // will never happen
}

void process_input(int n)
{
    try
    {
        int d = largest_proper_divisor(n);
        cout << "result=" << d << endl;
    }
    catch (std::invalid_argument exc)
    {
        std::cout << exc.what() << "\n";
    }

    std::cout << "returning control flow to caller\n";
}

int simple_exception_entry()
{
    int n;
    cin >> n;

    process_input(n);

    return 0;
}

void virtual_entry()
{
    HotelRoom r1(1, 2);
    HotelApartment r2(1, 2);

    std::cout << r1.get_price() << "\n";
    std::cout << r2.get_price() << "\n";
}

void static_entry_2()
{
    D d;
    int new_val;
    cin >> new_val;
    d.check(new_val);
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix new_matrix;
    for (int i = 0; i < values.size(); i++)
    {
        std::vector<int> inner;
        for (int j = 0; j < values[i].size(); j++)
        {
            float val = this->values[i][j] + other.values[i][j];
            inner.push_back(val);
        }

        new_matrix.values.push_back(inner);
    }

    return new_matrix;
}

std::string Person::get_name() const
{
    return this->first_name;
}

std::string Person::get_surname() const
{
    return this->last_name;
}

int HotelApartment::get_price()
{
    return HotelRoom::get_price() + 100;
}

int HotelRoom::get_price()
{
    return beds * 50 + bathrooms * 100;
}

A::A()
{
    callA = 0;
}

void A::inc()
{
    callA++;
}

void A::func(int& a)
{
    a = a * 2;
    inc();
}

int A::getA()
{
    return callA;
}

B::B()
{
    callB = 0;
}

void B::inc()
{
    callB++;
}

void B::func(int& a)
{
    a = a * 3;
    inc();
}

int B::getB()
{
    return callB;
}

C::C()
{
    callC = 0;
}

void C::inc()
{
    callC++;
}

void C::func(int& a)
{
    a = a * 5;
    inc();
}

int C::getC()
{
    return callC;
}

D::D()
{
    val = 1;
}

void D::update_val(int new_val)
{
    int x2 = 0, x3 = 0, x5 = 0;

    while (new_val > 1)
    {
        if (new_val % 2 == 0)
        {
            x2 += 1;
            new_val /= 2;
        }
        else if (new_val % 3 == 0)
        {
            x3 += 1;
            new_val /= 3;
        }
        else
        {
            x5 += 1;
            new_val /= 5;
        }
    }

    for (int i = 0; i < x2; i++)
        A::func(val); // * 2
    for (int i = 0; i < x3; i++)
        B::func(val); // * 3
    for (int i = 0; i < x5; i++)
        C::func(val); // * 5
}

void D::check(int new_val)
{
    update_val(new_val);
    cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
}
