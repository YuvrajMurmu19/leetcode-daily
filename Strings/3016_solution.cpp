/*
    LeetCode Daily Challenge - Day 33

    Problem    : 3016. Minimum Number of Pushes to Type Word II
    Difficulty : Medium

    Approach:
    - Count the frequency of every
      character in the given word.
    - Since letters can be remapped freely,
      assign the lowest push costs to the
      most frequently occurring characters.
    - Sort the frequency array in
      descending order.
    - There are 8 available keys (2–9):
        * First 8 frequencies cost 1 push.
        * Next 8 frequencies cost 2 pushes.
        * Remaining frequencies cost
          3 pushes, and so on.
    - Multiply each frequency by its
      assigned push cost and accumulate
      the total answer.

    Complexity:
    Time  : O(n + 26 log 26) ≈ O(n)
    Space : O(1)
*/

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        vector<int> count(26,0);
        for(char ch:word) count[ch-'a']++;

        sort(count.rbegin(),count.rend());

        int pushes = 0;
        for(int i = 0;i<26;i++){
            if(count[i]==0) break;

            pushes += (count[i]*(i/8 + 1));
        }
        return pushes;
    }
};