
/*
    LeetCode 2904 - Shortest and Lexicographically Smallest Beautiful String

    Approach: Sliding Window / Two Pointers

    A beautiful substring must contain exactly k '1's.

    Idea:
    - Maintain a window [i, j] and count the number of '1's in it.
    - Expand j to include new characters.
    - Once the window contains at least k ones, shrink it from the
      left to find the shortest possible valid window.
    - Whenever cnt == k:
        1. If the current window is shorter, update the answer.
        2. If the length is the same, compare both substrings
           lexicographically and keep the smaller one.

    Why does shrinking work?
    - Once the window has k ones, removing characters from the left
      can only make the window shorter.
    - We keep shrinking until removing another '1' would make the
      number of ones less than k.
    - Therefore, we consider the shortest valid window ending at j.

    Lexicographical condition:
    - If two beautiful substrings have the same minimum length,
      the lexicographically smaller one is the required answer.
    - Since '0' < '1', normal string comparison gives the required
      lexicographical ordering.

    Edge Case:
    - If no substring contains exactly k ones, return "".

    Complexity:
    - Sliding window: O(n)
    - Lexicographical comparisons: O(n) per comparison in the worst case.
    - Overall: O(n^2) worst case.
    - Extra space: O(1), excluding temporary substrings.

    Key Takeaway:
    This problem is a good application of the Sliding Window technique
    combined with lexicographical comparison for tie-breaking.
*/
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        string ans = s;
        int n = s.length();
        int i = 0;
        int j = 0;
        int cnt = 0;
        int len = n+1;

        while (i < n && j < n) {

            if (s[j] == '1')
                cnt++;

            while (i < n && cnt >= k) {
                 if(cnt == k) {
                    if(j-i+1<len){
                        ans = s.substr(i,j-i+1);
                    len = j-i+1;
                    }
                    else if(j-i+1==len){
                        ans = min(s.substr(i,j - i + 1),ans);
                        len = min(len, j - i + 1);
                    }
                 }
                if (s[i] == '1')
                    cnt--;
                i++;
            }

            j++;
        }

        if(len == n+1){
            len = 0;
            ans = "";
        }//nothing found

        return ans;
    }
};