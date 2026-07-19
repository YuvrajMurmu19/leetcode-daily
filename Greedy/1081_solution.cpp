/*
    LeetCode 1081 - Smallest Subsequence of Distinct Characters

    Core Idea:
    ----------
    Build the lexicographically smallest subsequence containing every
    distinct character exactly once.

    Observation:
    ------------
    A larger character should be removed only if:
    1. The current character is smaller.
    2. The larger character appears again later.

    To verify the second condition, store the last occurrence of every
    character before processing the string.

    Approach:
    ---------
    1. Compute the last occurrence of each character.
    2. Maintain a monotonic increasing stack (implemented using the answer string).
    3. Skip characters already present in the subsequence.
    4. While the top character is greater than the current character and
       appears again later, remove it.
    5. Insert the current character into the subsequence.

    Complexity:
    -----------
    Time  : O(n)
    Space : O(1)
*/


class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastOcc(26,-1);
        int n = s.length();
        for(int i = 0;i<n;i++){
            char ch = s[i];
            lastOcc[ch-'a'] = i;
        }

        vector<bool> inSeq(26,false);
        
        string ans;
        for(int i = 0;i<n;i++){
            //process every character
            char ch = s[i];
            if(inSeq[ch-'a']) continue;

            //monotonic wala logic
            //if greater character on top and it does occur later
            //then simply remove it and add current smaller one
            //until a smaller character is found or a last occuring character
            while(!ans.empty() && ans.back()>= ch && lastOcc[ans.back()-'a']>i){
                inSeq[ans.back()-'a'] = false;
               ans.pop_back();
            }
            ans.push_back(ch);
            inSeq[ch-'a'] = true;
        }

       
        return ans;
    }
};