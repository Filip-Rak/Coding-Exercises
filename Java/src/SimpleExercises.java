import javax.swing.*;
import java.util.*;

public class SimpleExercises
{
    public static void entry_simple_input()
    {
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            try
            {
                int buffer = scanner.nextInt();
                System.out.println(buffer);
            }
            catch (Exception e)
            {
                System.out.println("Only numbers are welcome! " + e);
                scanner.next();
            }
        }
    }

    public static void loops_entry()
    {
        Scanner scan = new Scanner(System.in);

        int q = scan.nextInt();
        while (q > 0)
        {
            int a = scan.nextInt();
            int b = scan.nextInt();
            int n = scan.nextInt();

            print_query(a, b, n);
            System.out.print("\n");

            q -= 1;
        }
    }
    /**
     * Generates a mathematical series for each query based on the given parameters.
     * <p>
     * The series is constructed using the formula:
     * (a + 2^0 * b), (a + 2^0 * b + 2^1 * b), ..., (a + 2^0 * b + 2^1 * b + ... + 2^(n-1) * b)
     * <p>
     * For each query containing values of `a`, `b`, and `n`, this function computes and prints
     * a line of `n` space-separated integers representing the series.
     */
    private static void print_query(int a, int b, int n)
    {
        int sum = a + b;
        System.out.print(sum + " ");

        for (int i = 1; i < n; i++)
        {
            sum += (int)(Math.pow(2, i) * b);
            System.out.print(sum + " ");
        }
    }

    public static void frequency_entry()
    {
        Scanner scan = new Scanner(System.in);
        String str = scan.nextLine();

        Map<Character, Integer> res = get_char_frequency(str);
        for (Map.Entry<Character, Integer> entry : res.entrySet())
        {
            String key = entry.getKey().toString().toUpperCase();
            int value = entry.getValue();

            System.out.println(key + "\t" + value);
        }
    }

    private static Map<Character, Integer> get_char_frequency(String str)
    {
        str = str.toLowerCase();

        Map<Character, Integer> freq = new TreeMap<>();
        for (char c : str.toCharArray())
        {
            if (Character.isLetter(c))
                freq.put(c, freq.getOrDefault(c, 0) + 1);
        }

        return freq;
    }

    public static void print_unique()
    {
        Scanner scan = new Scanner(System.in);
        String str = scan.nextLine();
        scan.close();

        Set<Character> unique = new HashSet<>();
        for (char c : str.toCharArray())
        {
            boolean added = unique.add(c);
            if (added)
            {
                System.out.println(c + " ");
            }
        }
    }

    private static boolean isAnagram(String str1, String str2)
    {
        if (str1.length() != str2.length())
            return false;

        char[] chars1 = str1
                .toLowerCase()
                .toCharArray();

        char[] chars2 = str2
                .toLowerCase()
                .toCharArray();


        Map<Character, Integer> freq = new HashMap<>();
        for (int i = 0; i < str1.length(); i++)
        {
            freq.put(chars1[i], freq.getOrDefault(chars1[i], 0) + 1);
            freq.put(chars2[i], freq.getOrDefault(chars2[i], 0) - 1);
        }

        for (Map.Entry<Character, Integer> entry : freq.entrySet())
        {
            if (entry.getValue() != 0)
                return false;
        }

        return true;
    }

    public static void anagrams_entry()
    {
        Scanner scanner = new Scanner(System.in);
        String str1 = scanner.nextLine();
        String str2 = scanner.nextLine();
        scanner.close();

        if (isAnagram(str1, str2))
            System.out.println("Anagrams");
        else
            System.out.println("Not Anagrams");
    }

    private static List<Integer> rot_left(List<Integer> arr, int offset)
    {
        // Normalize the offset
        int n = arr.size();
        offset = ((offset % n) + n) % n;

        // Create new array
        List<Integer> new_arr = new ArrayList<>(n);

        // Offset the old array into new array
        for (int i = 0; i < arr.size(); i++)
        {
            int old_index = (i + offset) % n;
            new_arr.add(arr.get(old_index)); // left-rotate
        }

        return new_arr;
    }

    public static void rotation_entry()
    {
        List<Integer> arr = List.of(1, 2, 3, 4);
        arr = rot_left(arr, 2);

        Iterator<Integer> ite = arr.iterator();
        while(ite.hasNext())
        {
            int num = ite.next();
            System.out.print(num + " ");
        }
    }

    private static Pair<Integer, Integer> two_sum(List<Integer> arr, int target)
    {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < arr.size(); i++)
        {
            int offset = target - arr.get(i);

            Integer query = map.get(offset);
            if (query != null)
            {
                return new Pair<>(i, query);
            }

            map.put(arr.get(i), i);
        }

        return new Pair<>(-1, -1);
    }

    public static void two_sum_entry()
    {
        List<Integer> arr = List.of(1, 4, 2, 6, 7, 3);
        Pair<Integer, Integer> res = two_sum(arr, 9);

        if (res.first == -1)
        {
            System.out.println("Failed two find indices!");
            return;
        }

        System.out.println("Index: " + res.first + ", " + res.second);
        System.out.println("Values: " + arr.get(res.first) + ", " + arr.get(res.second));
    }

    private static Pair<String, Integer> find_longest_unique_substring(String str)
    {
        char[] chars = str.toLowerCase().toCharArray();
        Map<Character, Integer> last_seen_map = new HashMap<>();  // [Character, index]
        int start = 0;
        int max_length = 0;
        int best_start = 0;

        for (int i = 0; i < chars.length; i++)
        {
            // Pick the character
            char c = chars[i];

            // Look if the character is already in the map
            Integer last_seen = last_seen_map.get(c);

            // The character is within the current substring
            if (last_seen != null && last_seen >= start)
            {
                start = last_seen + 1;
            }

            // Add / Update character's position
            last_seen_map.put(c, i);

            // Update maximum length
            if (i - start + 1 > max_length)
            {
                max_length = i - start + 1;
                best_start = start;
            }
        }

        String longest_str = str.substring(best_start, best_start + max_length);
        return new Pair<>(longest_str, max_length);
    }

    public static void substr_entry()
    {
        String str = "abccdefghh";
        Pair<String, Integer> res = find_longest_unique_substring(str);
        System.out.println(res.second + ": " + res.first);
    }

    private static boolean has_duplicates(List<Integer> arr)
    {
        Set<Integer> set = new HashSet<>();
        for (int num : arr)
        {
            boolean added = set.add(num);
            if (!added)
                return true;
        }

        return false;
    }

    public static void duplicates_entry()
    {
        List<Integer> arr = List.of(1, 2, 3, 4);
        System.out.println(has_duplicates(arr));
    }

    private static int get_most_frequent(List<Integer> arr)
    {
        if (arr.isEmpty())
            return -1;

        Map<Integer, Integer> freq = new HashMap<>(); // [data, freq]
        Integer most_frequent = arr.getFirst();
        int max = 1;

        for (int num : arr)
        {
            int new_val = freq.getOrDefault(num, 0) + 1;
            freq.put(num, new_val);

            if (new_val > max)
            {
                max = new_val;
                most_frequent = num;
            }
        }

        return most_frequent;
    }

    public static void most_freq_entry()
    {
        List<Integer> arr = List.of(1, 2, 2, 3, 3, 2);
        System.out.println(get_most_frequent(arr));
    }

    public static void tokenize_split_entry()
    {
        String str = "one 4 12 eight";
        String[] tokens = str.split(" ");

        for (String token : tokens)
            System.out.print(token + " ");
    }

    public static void tokenize_scanner_entry()
    {
        String str = "one 4 12 eight";
        Scanner sc = new Scanner(str);

        List<String> tokens = new ArrayList<>();
        while (sc.hasNext())
        {
            String buffer = sc.next();
            tokens.add(buffer);
        }

        for(String token : tokens)
            System.out.print(token + " ");
    }

    private static boolean is_a_permutation(String str1, String str2)
    {
        if (str1.length() != str2.length())
            return false;

        char[] str1_norm = str1.toLowerCase().toCharArray();
        Arrays.sort(str1_norm);

        char[] str2_norm = str2.toLowerCase().toCharArray();
        Arrays.sort(str2_norm);

        return Arrays.toString(str1_norm).equals(Arrays.toString(str2_norm));
    }

    public static void permutation_entry()
    {
        String str1 = "abbccd";
        String str2 = "bcdabc";

        System.out.println(is_a_permutation(str1, str2));
    }

    private static List<List<String>> group_anagrams(List<String> arr)
    {
        Map<String, List<String>> groups = new HashMap<>();  //[sorted_str, not-sorted entries]

        // Go through all strings
        for (String str : arr)
        {
            // Normalize the string to key
            char[] norm = str.toLowerCase().toCharArray();
            Arrays.sort(norm);
            String key = new String(norm);

            // Find the key, if it does not exist create an arr
            List<String> list = groups.computeIfAbsent(key, _ -> new ArrayList<>());
            list.add(str);
        }

        // Query the array for all results
        return new ArrayList<>(groups.values());
    }

    public static void anagram_groups_entry()
    {
        List<String> arr = List.of("eat", "tea", "tan", "ate", "nat", "bat");

        List<List<String>> groups = group_anagrams(arr);
        groups.sort((a, b) -> b.size() - a.size());

        for (List<String> group : groups)
        {
            for (String str : group)
            {
                System.out.print(str + " ");
            }

            System.out.print("\n");
        }
    }

    private static List<Integer> most_frequent(List<Integer> arr, int k)
    {
        /* Get Frequency */
        // Frequency map [data, count]
        Map<Integer, Integer> freq = new HashMap<>();

        // Count data frequency
        for (int key : arr)
        {
            int new_val = freq.getOrDefault(key, 0) + 1;
            freq.put(key, new_val);
        }

        /* Pick Most Frequent */
        Queue<Map.Entry<Integer, Integer>> heap = new PriorityQueue<>(Comparator.comparingInt(Map.Entry::getValue));
        for (Map.Entry<Integer, Integer> entry : freq.entrySet())
        {
            heap.add(entry);
            if (heap.size() > k)
                heap.poll();
        }

        /* Pack Most Frequent Data */
        List<Integer> res_arr = new ArrayList<>(heap.size());
        while(!heap.isEmpty())
            res_arr.add(heap.poll().getKey());

        return res_arr;
    }

    public static void freq_k_entry()
    {
        List<Integer> arr = List.of(1, 2, 2, 3, 3, 3);
        List<Integer> res = most_frequent(arr, 2);

        for(int num : res)
        {
            System.out.print(num + " ");
        }
    }

    public static void comp_test_entry()
    {
        List<Integer> arr = new ArrayList<>(List.of(1, 4, 5, 2, 3, 6));
        Comparator<Integer> asc = (a, b) -> a - b;
        arr.sort(asc);

        for (int num : arr)
        {
            System.out.print(num + " ");
        }
    }
}
