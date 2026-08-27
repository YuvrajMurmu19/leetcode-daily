/*
LeetCode 3720: Lexicographically Smallest Permutation Greater Than Target
Approach: Greedy + Frequency Array

Idea:
- Store the frequency of each character in s.
- First, try to match target from left to right using available characters.
- If matching fails at index i, we need to make the answer greater than target.
- Move backwards from i to find the rightmost position where we can choose
  a character greater than target[i].
- Choose the smallest possible greater character.
- After increasing that position, append all remaining characters in sorted
  order to get the lexicographically smallest possible answer.
- If target was completely matched, backtrack from the last position because
  an answer equal to target is NOT allowed.

Why greedy works:
- Keep the prefix equal to target for as long as possible.
- Increase the rightmost possible position to make the change as late as
  possible.
- Choose the smallest greater character.
- Sort the remaining characters to minimize the suffix.

Complexity:
Time  : O(26 * n) = O(n)
Space : O(26) = O(1)
*/ 

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        string ans = "";

        vector<int> freq(26,0);
        
        for(char ch:s) freq[ch-'a']++;

        int i = 0;
        while(i<n){
            int ch = target[i];
            if(freq[ch-'a']>0){
                freq[ch-'a']--;
                ans.push_back(ch);
            }else{ 
               break;
            }
            i++;
        }
        if(i==n){
            i--;
            freq[target[i] - 'a']++;
            ans.pop_back();
        }
        //now i have the index where they differ
        while(i>=0){
            char ch = target[i];
            for(int j = ch-'a'+1;j<26;j++){
               if(freq[j]>0){
                ans.push_back('a'+j);

                freq[j]--;

                for(int k = 0;k<26;k++){
                    while(freq[k]>0) {
                        ans.push_back('a'+k);
                        freq[k]--;
                    }
                }
                return ans;

               }

           }
           if (i>0) {
                freq[target[i - 1] - 'a']++;
                ans.pop_back();
            }
            i--;
        }
        return ans;
    }
};

