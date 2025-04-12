import java.util.Scanner;

public class SimpleExercises
{
    public static void entry_simple_input(){
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNext())
        {
            try{
                int buffer = scanner.nextInt();
                System.out.println(buffer);
            }
            catch (Exception e) {
                System.out.println("Only numbers are welcome! " + e);
                scanner.next();
            }
        }
    }
}
