/*
    LeetCode 3090 - Maximum Length Substring With Two Occurrences

    Approach: Two Pointers / Sliding Window

    Maintain a window [i, j] where every character appears at most twice.
    Expand the window by moving j and update the character frequency.
    If any character appears more than twice, move i forward until the
    window becomes valid again.

    Since both pointers only move forward, each character is processed
    at most twice.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.length();
        int maxLen = 0;
        int i = 0;
        int j = 0;
        vector<int> freq(26,0);
        while(j<n && i<n){
            freq[s[j]-'a']++;
            while(i<n && freq[s[j]-'a']>2){
                freq[s[i]-'a']--;
                i++;
            }
            maxLen = max(maxLen,j-i+1);
            j++;
        }
        return maxLen;
    }
};