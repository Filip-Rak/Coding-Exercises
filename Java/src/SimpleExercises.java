import java.net.URI;
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

    class Pair<T, U>
    {
        /* Attributes */
        T first;
        U second;

        /* Constructor */
        Pair(T first, U second)
        {
            this.first = first;
            this.second = second;
        }
    }
}
