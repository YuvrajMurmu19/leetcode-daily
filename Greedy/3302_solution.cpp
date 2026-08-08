/*
    Approach: Greedy + Suffix DP

    Idea:
    - We need to construct the lexicographically smallest sequence of indices.
    - Therefore, we process word1 from left to right and greedily take the
      earliest possible index.

    Step 1: Build suffix DP
    - dp[j] stores the index in word1 from which word2[j...n2-1] can be
      matched as a subsequence.
    - Traverse both strings from right to left to compute this information.

    Step 2: Greedily construct the answer
    - Traverse word1 and word2 from left to right.
    - If word1[i] == word2[j]:
        * Take index i whenever possible.
        * If the one allowed difference has already been used, take i only
          when the remaining suffix can still be matched.
    - If word1[i] != word2[j]:
        * We can use our one allowed character change.
        * Before using it, check whether word2[j+1...] can still be matched
          using dp.
        * If yes, take i and mark the difference as used.
    - Since we always prefer the earliest valid index, the resulting
      sequence is lexicographically smallest.

    Why Greedy Works:
    - The answer is compared by indices, not by the resulting string.
    - Therefore, choosing a smaller valid index is always better.
    - The suffix DP tells us whether making that greedy choice still allows
      the remaining characters to be matched.

    Time Complexity: O(n + m)
        - O(n + m) to build the suffix DP and construct the answer.

    Space Complexity: O(m)
        - O(m) for the suffix DP array.

    where:
        n = word1.length()
        m = word2.length()
*/

class Solution {
public:
   
    vector<int> validSequence(string word1, string word2) {
        int n1 = word1.size();
        int n2 = word2.size();

        int i = n1-1;
        int j =n2-1;
        
        //form dp array
        //dp[i] = all characters from index i in w2 are present in subseq from max indx dp[i] in w2
        vector<int> dp(n2,-1);
        while(i>=0 && j>=0){
            if(word1[i]==word2[j]){
                dp[j] = i;
                j--;
            }
            i--;
        }

        vector<int> res;
        i = 0,j = 0;
        bool used_diff = false;//for taking 1 different character
        while(i<n1 && j<n2){
            bool match = (word1[i] == word2[j]);
            
            if(match){
                //phle used_diff ho chuka h ya nhi hua h
                if(!used_diff){
                    //koi darr nhi bs include krdo
                     res.push_back(i);
                     j++;
                }else if(used_diff && (j+1==n2 || dp[j+1]>i)){
                    //1 different character used already
                    res.push_back(i);
                    j++;
                }
            }else{
                //match toh nhi kr rha
                //check kro baaki characters aage mil jaenge dp me?
                //ya last me ho?
                if(j+1 == n2 && !used_diff){
                     res.push_back(i);
                     j++;
                }

                else if(!used_diff && dp[j+1]>i){
                    used_diff = true;
                    res.push_back(i);
                    j++;
                }
                
            }
            
            i++;
        }
        if(res.size()<n2) return {};
        
        return res;
    }
};