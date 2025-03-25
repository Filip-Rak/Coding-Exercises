#include <iostream>
#include <vector>

/*
 * Problem: Sales by Match
 *
 * There is a large pile of socks that must be paired by color.
 * Given an array of integers representing the color of each sock,
 * determine how many pairs of socks with matching colors there are.
 *
 * Constraints:
 * - 1 <= n <= 100
 */


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

/*
 * Problem: Counting Valleys
 *
 * An avid hiker keeps meticulous records of their hikes. During the last hike
 * that took exactly 'steps' steps, for every step it was noted if it was an
 * uphill ('U') or a downhill ('D') step.
 *
 * Hikes always start and end at sea level, and each step up or down represents
 * a 1-unit change in altitude. We define the following terms:
 *
 * - A mountain is a sequence of consecutive steps above sea level, starting
 *   with a step up from sea level and ending with a step down to sea level.
 *
 * - A valley is a sequence of consecutive steps below sea level, starting
 *   with a step down from sea level and ending with a step up to sea level.
 *
 * Task:
 * Given the sequence of up and down steps during a hike, find and return
 * the number of valleys walked through.
 */
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

int main()
{
	std::cout << "Hello World!\n";
}
