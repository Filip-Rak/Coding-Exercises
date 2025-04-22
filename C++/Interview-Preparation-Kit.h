#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stack>

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


int sockMerchant(int n, std::vector<int> ar);

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
int countingValleys(int steps, std::string path);

/*
 * Problem: Jumping on the Clouds
 *
 * There is a new mobile game that starts with consecutively numbered clouds.
 * Some of the clouds are thunderheads (represented by 1), and others are
 * cumulus clouds (represented by 0).
 *
 * The player can jump from the current cloud to a cloud that is either
 * 1 or 2 positions ahead, but only if the target cloud is a cumulus cloud (0).
 * The player must avoid thunderheads.
 *
 * Goal:
 * Determine the minimum number of jumps needed to reach the last cloud
 * starting from the first one. It is guaranteed that it is always
 * possible to win the game.
 *
 * Input:
 * - An array of integers where each element is either 0 (safe) or 1 (must be avoided)
 */
int jumpingOnClouds(std::vector<int> c);


/*
 * Problem: Repeated String
 *
 * There is a string, s, consisting of lowercase English letters that is
 * repeated infinitely many times.
 *
 * Given an integer, n, determine the number of letter 'a's in the first
 * n characters of the infinitely repeated string.
 *
 * Input:
 * - A string 's' (to be infinitely repeated)
 * - An integer 'n' representing the number of characters to consider
 *
 * Output:
 * - The total count of letter 'a' in the first 'n' characters of the infinite string
 */

long repeatedString(std::string s, long n);

std::vector<int> tokenize(const std::string& str);

bool process_line(const std::string& line, int current_light, std::unordered_map<int, bool>& map);

void problem_entry();

void rot_left(const std::vector<int>& arr, int k);

void reverse3_rot_left_entry();

bool valid_parentheses(const std::string& line);

void valid_parentheses_entry();