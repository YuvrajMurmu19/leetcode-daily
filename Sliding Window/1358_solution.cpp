/*
Approach:

1. Initially solved the problem using a brute-force approach by generating
   all possible substrings and checking whether each contained 'a', 'b', and 'c'.
   Once the first valid substring was found for a starting index, all its
   extensions were counted since they would also remain valid.

2. Then explored a sliding window approach using a hash map to track the
   latest occurrence of each character. This reduced unnecessary work but
   made the implementation more complex than needed.

3. Final approach uses a sliding window with a frequency array of size 3.
   Expand the window by moving the right pointer and maintain the frequency
   of 'a', 'b', and 'c'. Whenever the current window contains all three
   characters, every substring extending from the current right pointer to
   the end of the string is also valid. Count all such substrings at once,
   then shrink the window from the left while the condition remains satisfied.

Time Complexity: O(n)
Space Complexity: O(1)
*/

class Solution
{
public:
    int numberOfSubstrings(string s)
    {
        int ans = 0;
        int n = s.length();
        int i = 0;
        int j = 0;
        vector<int> freq(3, 0);
        while (i < n && j < n)
        {
            char temp = s[j];
            freq[temp - 'a']++;
            while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0)
            {
                int len_from_j = n - j;
                ans += len_from_j;
                // remove occ of i;
                freq[s[i] - 'a']--;
                i++;
            }
            j++;
        }
        return ans;
    }
};

// class Solution
// {
// public:
//     bool containsABC(unordered_map<char, int> &found)
//     {
//         for (auto &it : found)
//         {
//             if (it.second == -1)
//                 return false;
//         }
//         return true;
//     }
//     int numberOfSubstrings(string s)
//     {
//         int ans = 0;
//         int n = s.length();
//         int i = 0;
//         int j = 0;
//         unordered_map<char, int> found;
//         found['a'] = -1;
//         found['b'] = -1;
//         found['c'] = -1;
//         while (i < n && j < n)
//         {
//             char temp = s[j];
//             found[temp] = j;
//             while (containsABC(found))
//             {
//                 int len_from_j = n - j;
//                 ans += len_from_j; // remove occ of i;
//                 char x = s[i];
//                 if (found[x] == i)
//                 {
//                     found[x] = -1;
//                 }
//                 i++;
//             }
//             j++;
//         }
//         return ans;
//     }
// };