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
        throw std::invalid_argument("largest proper divisor is not defined for n=0");
    }
    if (n == 1)
    {
        throw std::invalid_argument("largest proper divisor is not defined for n=1");
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
        std::cout << "result=" << d << std::endl;
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
    std::cin >> n;

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
    std::cin >> new_val;
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
    while (new_val > 1)
    {
        if (new_val % 2 == 0)
        {
            A::func(val); // * 2
            new_val /= 2;
        }
        else if (new_val % 3 == 0)
        {
            B::func(val); // * 3
            new_val /= 3;
        }
        else
        {
            C::func(val); // * 5
            new_val /= 5;
        }
    }        
}

void D::check(int new_val)
{
    update_val(new_val);
    std::cout << "Value = " << val << std::endl << "A's func called " << getA() << " times " << std::endl << "B's func called " << getB() << " times" << std::endl << "C's func called " << getC() << " times" << std::endl;
}

int Computer::compute(int a, int b)
{
    if (a == 0 || b == 0)
        throw std::invalid_argument("one or both of the arguments is equal to 0");

    if (a < 0)
        throw std::invalid_argument("a is below zero");

    if (a % 7 == 0)
        throw std::exception("7");

    std::vector<int> arr(a * b);
    return arr.size();
}

void exception_entry()
{
    std::vector<std::pair<int, int>> args = {
        {0, 2},
        {-1, 2},
        {14, 24},
        {10e3, 10e15}
    };

    for (auto pair : args)
    {
        try
        {
            int result = Computer::compute(pair.first, pair.second);
            std::cout << result << "\n";
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "EXCEPTION: Invalid arg -> " << e.what() << "\n";
        }
        catch (const std::length_error& e)
        {
            std::cout << "EXCEPTION: Length error -> " << e.what() << "\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "EXCEPTION: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cout << "Other exception\n";
        }

    }
}

std::string Dog::sound()
{
    return "woof";
}

std::string Cat::sound()
{
    return "meow";
}

std::string Fish::sound()
{
    return "(...)";
}

void virtual_sound_entry()
{
    Dog a1;
    Cat a2;
    Fish a3;

    std::vector<Animal*> animals = {&a1, &a2, &a3 };

    for (Animal* a : animals)
    {
        std::cout << a->sound() << "\n";
    }
}

void variadic_templates_entry()
{
    print_all("string ", 5.5 , " ", 4, " ", true, " oh god");
}

void variadic_bits_entry()
{
    std::cout << reversed_binary_value1<false, false, true>() << "\n";
    std::cout << reversed_binary_value2(false, false, true) << "\n";
    std::cout << sum(5, 3, 2, 10) << "\n";
}

void set_usage1()
{
    // Load input
    int N, S, P, Q;
    std::cin >> N >> S >> P >> Q;

    // Get the first value
    const long long MOD = 1LL << 31;
    long long recent = S % MOD;

    // Count unique values
    std::unordered_set<long long> unique;
    unique.insert(recent);

    for (int i = 0; i < N; i++)
        recent = (recent * P + Q) % MOD;

    std::cout << unique.size() << "\n";
}

void set_usage2()
{
    // Rand N random numbers
    int N = 10;

    std::unordered_set<int> unique;

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        // Print only non-unique numbers
        int random = (rand() % 10) + 1; // <1, 10>
        
        if (!unique.insert(random).second)
            std::cout << random << " ";
    }

    std::cout << "\n";
}

void count_random_nums()
{
    srand(time(NULL));

    // Rand N random numbers
    int N = 30;
    int min = 1;
    int max = 11; // Not inclusive

    // Rand and save frequency
    std::unordered_map<int, int> frequency;
    for (int i = 0; i < N; i++)
    {
        // Print only non-unique numbers
        int random = (rand() % max) + min;
        frequency[random] += 1;
    }

    for (int i = min; i < max; i++)
    {
        // This will initialize non existent data as 0
        // std::cout << i << ": " << frequency[i] << "\n";

        // This will not
        if (frequency.contains(i))  // .count(i) instead for C++ below 20
            std::cout << i << ": " << frequency[i] << "\n";
        else 
            std::cout << i << ": 0\n";
    }
}

Object::Object(const int id) : obj_id(id)
{
    active += 1;
    std::cout << "Constructor->obj:\t" << obj_id << "\tActive: " << active << "\n";
}

Object::Object(): obj_id(-1) {}

Object::~Object()
{
    active -= 1;
    std::cout << "Destructor->obj:\t" << obj_id << "\tActive: " << active << "\n";
}

void Object::Print(int call_id)
{
    std::cout << "Print->obj:\t" << obj_id << "\tActive: " << active << "\tCall_id: " << call_id << "\n";
}

int Object::get_id()
{
    return this->obj_id;
}

int Object::active = 0;

void smart_pointers1()
{
    // Allocate some memory for an array of objects
    int N = 4;
    std::vector<std::unique_ptr<Object>> arr(N);

    // Create pointers and objects
    for (int i = 0; i < N; i++)
    {
        arr[i] = std::make_unique<Object>(i);
    }

    // Shared pointers
    std::shared_ptr<Object> s_ptr = std::make_shared<Object>(20);
    std::shared_ptr<Object> s_ptr2 = s_ptr;
    s_ptr->Print(30);

    {
        std::shared_ptr<Object> s_ptr3 = s_ptr;
        std::cout << "s_ptr.use_count(): " << s_ptr.use_count() << "\n";
    }
    
    std::cout << "s_ptr.use_count(): " << s_ptr.use_count() << "\n";
}

CustomObj::CustomObj(const int id)
    : id(id) {}

CustomObj::CustomObj()
{
    this->id = -1;
}

int CustomObj::get_id() const
{
    return this->id;
}

bool CustomObj::operator==(const CustomObj& other) const
{
    return this->id == other.get_id();
}

void custom_list_entry()
{
    // Declare the list
    CustomList<CustomObj> obj_list;

    // Populate the list
    int N = 5;
    for (int i = 0; i < N; i++)
        obj_list.insert(CustomObj(i));

    // Read the elements from the list
    std::cout << "------ Operator[] ------\n";
    for (int i = 0; i < obj_list.get_number_of_elements(); i++)
    {
        auto res = obj_list[i];
        if (res.first)
            std::cout << "ID: " << res.second.get_id() << "\n";
        else 
            std::cout << "ID: NULL\n";
    }

    // std::cout << "------ remove() ------\n";
    // int id_to_remove = 0;
    // std::cout << "remove(" << id_to_remove << "): " << obj_list.remove(CustomObj(id_to_remove)) << "\n";

    std::cout << "------ reverse_between() ------\n";
    obj_list.reverse_between(0, obj_list.get_number_of_elements());

    std::cout << "------ get_as_vector() ------\n";
    std::vector<CustomObj> obj_vector = obj_list.get_as_vector();
    
    for (const CustomObj& obj : obj_vector)
        std::cout << "ID: " << obj.get_id() << "\n";
}

class PointyObj
{
    int id;

public:
    PointyObj(int id): id(id)
    {
        std::cout << "Object created. ID: " << id << "\n";
    }

    ~PointyObj()
    {
        std::cout << "Object deleted. ID: " << id << "\n";
    }
};

void smart_pointers2()
{
    PointyObj* obj = new PointyObj(1);
    std::shared_ptr<PointyObj> ptr(obj);
}

int hourglass_sum(std::vector<std::vector<int>> arr)
{
    int max = std::numeric_limits<int>::min();

    // The index defines the 'd' portion of the hourglass
    for (int i = 1; i < arr.size() - 1; i++)
    {
        for (int j = 1; j < arr[i].size() - 1; j++)
        {
            int a = arr[i - 1][j - 1];
            int b = arr[i - 1][j];
            int c = arr[i - 1][j + 1];

            int d = arr[i][j];

            int e = arr[i + 1][j - 1];
            int f = arr[i + 1][j];
            int g = arr[i + 1][j + 1];

            int sum = a + b + c + d + e + f + g;
            if (sum > max)
                max = sum;
        }
    }

    return max;
}

void hourglass_entry()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> arr(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cin >> arr[i][j];
    }

    std::cout << hourglass_sum(arr);
}

std::vector<int> rot_left(std::vector<int> arr, int shift)
{
    // Create new vector and normalize shift
    int n = arr.size();
    std::vector<int> new_arr(n);
    int shift_normalized = ((shift % n) + n) % n;  // [0, n-1]

    // Go through each element of the vector
    for (int i = 0; i < n; i++)
    {
        int new_pos = (i - shift_normalized + n) % n;
        new_arr[new_pos] = arr[i];
    }

    return new_arr;
}

void array_rot_entry()
{
    // Load element num and shift
    int element_num, shift;
    std::cin >> element_num >> shift;

    // Load array
    std::vector<int> arr(element_num);
    for (int i = 0; i < element_num; i++)
        std::cin >> arr[i];

    // Rotate array
    arr = rot_left(arr, shift);
    
    // Print result
    for (int element : arr)
        std::cout << element << " ";
}

bool is_permutation(std::string str1, std::string str2)
{
    // Discard strings of different lengths
    if (str1.length() != str2.length())
        return false;

    // Create a frequency map
    std::unordered_map<char, int> frequency;

    // Characters within one stirng add frequency, the other reduces
    for (char c : str1)
        frequency[c] += 1;

    for (char c : str2)
        frequency[c] -= 1;

    // If every letter's frequency is at 0 then string are permutable
    for (auto& [character, count] : frequency)
    {
        if (count != 0)
            return false;
    }

    return true;
}

void permutable_entry()
{
    std::string str1, str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());
    str2.erase(std::remove(str2.begin(), str2.end(), ' '), str2.end());

    std::cout << is_permutation(str1, str2);
}

bool is_rot(std::string str1, std::string str2)
{
    if (str1.length() != str2.length())
        return false;

    std::string str_conc = str1 + str1;
    int index = str_conc.find(str2);

    return index != std::string::npos;
}

void is_rot_entry()
{
    std::string str1, str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());
    str2.erase(std::remove(str2.begin(), str2.end(), ' '), str2.end());

    std::cout << is_rot(str1, str2);
}

int longest_substr_length(std::string str)
{
    // Offset all index related calculaitons by 1 in order to avoid
    // correlaction with map's initialization of 0
    const int INDEX_OFFSET = 1;

    std::unordered_map<char, int> last_seen;
    int max_length = 0;
    int start = 0;

    for (int i = 0; i < str.size(); i += 1)
    {
        char character = str[i];

        if (last_seen[character] >= start + INDEX_OFFSET)
            start = last_seen[character] + 1;
        
        last_seen[character] = i + INDEX_OFFSET;
        max_length = std::max(max_length, i - start + 1);
    }

    return max_length;
}

void substr_entry()
{
    std::string str;
    std::getline(std::cin, str);

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    std::cout << longest_substr_length(str) << "\n";
}

std::pair<int, int> find_two_elements_to_sum(std::vector<int> arr, int tgt)
{
    std::unordered_map<int, int> seen;

    for (int i = 0; i < arr.size(); i++)
    {
        int diff = tgt - arr[i];
        if (seen.contains(diff))
            return std::make_pair(seen[diff], i);

        seen[arr[i]] = i;
    }

    return std::make_pair(-1, -1);
}

std::ostream& operator << (std::ostream& out, const std::pair<int, int>& pair)
{
    out << pair.first << " " << pair.second;
    return out;
}

void twosum_entry()
{
    int n, tgt;
    std::cin >> n >> tgt;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    std::cout << find_two_elements_to_sum(arr, tgt) << "\n";
}

bool has_duplicates(std::vector<int> arr)
{
    std::unordered_set<int> unique;

    for (int num : arr)
    {
        // Add num to arr and check if it was present
        bool is_unique = unique.insert(num).second;

        if (!is_unique)
            return true;
    }

    return false;
}

void duplicate_entry()
{
    std::vector<int> arr = { 1, 2, 3, 4 };
    std::cout << has_duplicates(arr) << "\n";
}

void reverse_in_place(std::string& str)
{
    for (int i = 0; i < str.size() / 2; i++)
        std::swap(str[i], str[str.size() - 1 - i]);
}

void reverse_entry()
{
    std::string str;
    std::getline(std::cin, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    reverse_in_place(str);

    std::cout << str << "\n";
}

std::unordered_map<char, int> get_character_frequency(std::string str)
{
    std::unordered_map<char, int> frequency;

    for (char c : str)
        frequency[c] += 1;

    return frequency;
}

std::ostream& operator << (std::ostream& out, const std::unordered_map<char, int>& map)
{
    for (const auto& [key, value] : map)
        out << key << " " << value << "\n";

    return out;
}

void freq_entry()
{
    std::string str;
    std::getline(std::cin, str);

    std::cout << get_character_frequency(str) << "\n";
}

std::unordered_map<std::string, std::vector<std::string>> group_anagrams(std::vector<std::string> arr)
{
    std::unordered_map<std::string, std::vector<std::string>> groups;

    for (const std::string& str : arr)
    {
        std::string sorted = str;
        std::sort(sorted.begin(), sorted.end());

        groups[sorted].push_back(str);
    }

    return groups;
}

// Example input: eat tea tan ate nat bat
void anagrams_entry()
{
    // Load line
    std::vector<std::string> strs;

    std::string line;
    std::getline(std::cin, line);

    // Tokenize
    std::stringstream ss(line);
    std::string token;

    while (ss >> token)
    {
        strs.push_back(token);
    }

    // Group & Print
    auto groups = group_anagrams(strs);
    for (const auto& [key, arr] : groups)
    {
        for (const std::string& str : arr)
        {
            std::cout << str << " ";
        }

        std::cout << "\n";
    }
}

bool custom_comparator(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    if (a.first == b.first)
    {
        return a.second > b.second;
    }

    return a.first < b.first;
}

void custom_sort_entry()
{
    std::vector<std::pair<int, int>> arr = { {1, 47}, {5, 2}, {3, 2}, {3, 50}, {6, 70} };
    std::sort(arr.begin(), arr.end(), custom_comparator);

    for (const auto& [first, second] : arr)
    {
        std::cout << first << " " << second << "\n";
    }
}

std::tuple<char, int, int> get_frequency(std::string str)
{
    // Map characters to their frequency
    std::unordered_map<char, int> frequency;

    // Find most frequent character
    int max_freq = 0;
    char max_freq_char = '\0';

    for (char c : str)
    {
        frequency[c] += 1;

        if (frequency[c] > max_freq)
        {
            max_freq = frequency[c];
            max_freq_char = c;
        }
    }

    return std::tuple<char, int, int>(max_freq_char, max_freq, frequency.size());
}

void tuple_entry()
{
    std::string str;
    std::getline(std::cin, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    auto [ch, count, unique] = get_frequency(str);
    std::cout << "Most common character: " << ch << "\n";
    std::cout << "It's frequency: " << count << "\n";
    std::cout << "Total number of distinct characters: " << unique << "\n";
}

int longest_substr_of_unique_characters(std::string str)
{
    std::unordered_map<char, int> last_seen;
    int start = 0;
    int max_length = 0;

    for (int i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        // Check if the character ch, of index higher than start is present in the macp
        if (last_seen.count(ch) && last_seen[ch] >= start)
        {
            start = last_seen[ch] + 1;
        }

        // Add the character to the map / update it's index
        last_seen[ch] = i;

        // Update max_length
        max_length = std::max(max_length, i - start + 1);
    }

    return max_length;
}

void longest_substr_entry2()
{
    std::string str;
    std::getline(std::cin, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    std::cout << longest_substr_of_unique_characters(str);
}

std::vector<int> rot_arr_left(std::vector<int> arr, int shift)
{
    int size = arr.size();
    int n_shift = ((shift % size) + size) % size;   // Normalize to: [0, size - 1]

    std::vector<int> new_arr(size);

    for (int i = 0; i < size; i++)
    {
        int new_pos = (i - n_shift + size) % size;
        new_arr[new_pos] = arr[i];
    }

    return new_arr;
}

void rot_arr_entry2()
{
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    auto rotated = rot_arr_left(arr, -3);

    for (int num : rotated)
        std::cout << num << " ";

}

// Problem: Given a list of words from a magazine and a list of words in a ransom note,
// determine if the note can be constructed using whole words from the magazine.
// Each word in the magazine can only be used once.
// The function returns true if the note can be formed, false otherwise.
bool check_magazine(std::vector<std::string> magazine, std::vector<std::string> note)
{
    std::unordered_map<std::string, int> words;

    for (const std::string& word : magazine)
        words[word] += 1;

    for (const std::string& word : note)
    {
        if (--words[word] < 0)
            return false;
    }

    return true;
}

void check_magazine_entry()
{
    std::vector<std::string> magazine = { "give", "me", "one", "grand", "today", "night" };
    std::vector<std::string> note = { "give", "one", "grand", "today" };

    std::cout << check_magazine(magazine, note) << "\n";
}

bool two_strings(std::string str1, std::string str2)
{
    std::unordered_set<char> chars(str1.begin(), str1.end());

    for (char ch : str2)
    {
        if (chars.contains(ch))
            return true;
    }

    return false;
}

void subs_entry()
{
    std::string str1 = "abc";
    std::string str2 = "bfg";

    std::cout << two_strings(str1, str2);
}

int sherlock_anagrams(std::string str)
{
    // Sum the total number of pairs
    int total_pairs = 0;

    // Go through all substring lengths [1, s.size()] outside of last.
    for (int w_length = 1; w_length < str.length(); w_length += 1)
    {
        // Create substrings
        std::unordered_map<std::string, int> freq;
        for (int i = 0; i < str.length() - w_length + 1; i++)
        {
            // Create, sort & count up the substring
            std::string sub = str.substr(i, w_length);
            std::sort(sub.begin(), sub.end());
            freq[sub] += 1;
        }

        // Find the number of pairs
        for (const auto& [_, count] : freq)
        {
            if (count > 1)
                total_pairs += (count * (count - 1)) / 2;
        }
    }

    return total_pairs;
}

void sherlock_entry()
{
    std::string str("mom");
    std::cout << sherlock_anagrams(str) << "\n";
}
