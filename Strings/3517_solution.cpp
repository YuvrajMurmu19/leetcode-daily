/*
    LeetCode Daily Challenge - Day 30

    Problem    : 3517. Smallest Palindromic Rearrangement I
    Difficulty : Medium

    Approach:
    - Count the frequency of each character.
    - If a character has an odd frequency,
      place one occurrence at the centre.
    - Pre-allocate the answer string.
    - Fill the remaining characters from
      the centre towards both ends using
      two pointers.
    - Process characters in lexicographical
      order to obtain the smallest palindrome.

    Complexity:
    Time  : O(n)
    Space : O(n)
*/

class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26,0);
        for(char ch:s){
            count[ch-'a']++;
        }
        int n = s.length();
        string ans(n,' ');
        int left = n/2-1;
        int right =n/2;
        if(n%2!=0){

            right = n/2 + 1;
            for(int i =0;i<26;i++){
            if(count[i]%2!=0){
                count[i]--;
                char ch = 'a' + i;
                int idx = n/2;
                ans[idx] = ch;
                break;
            }
            }
        }

        for(int i = 25;i>=0;i--){
            if(count[i]==0) continue;

            //extract character
            char ch = 'a' + i;
            while(count[i]!=0){
                count[i]-=2;
                ans[left--] = ch;
                ans[right++] = ch;
            }
        }
        return ans;
    }
};