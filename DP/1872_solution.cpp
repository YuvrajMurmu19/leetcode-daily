/*
LeetCode 1872 - Stone Game VIII
Topic: Dynamic Programming / Game Theory / Prefix Sum

Approach:
- Alice and Bob play optimally, so we focus on the SCORE DIFFERENCE.
- Let solve(i) = maximum score difference the current player can achieve
  starting from index i.
- Precompute prefix sums because when we take the first k stones,
  their total value is prefixSum[k].

At every state, we have two choices:

1. Take:
   Take the current prefix sum and then the opponent gets their
   optimal score difference.
   
   take = prefixSum[i] - solve(i + 1)

2. Skip:
   Don't take the current prefix and move to the next state.
   
   skip = solve(i + 1)

Therefore:

solve(i) = max(take, skip)

Why subtraction?
- solve(i + 1) represents the opponent's best possible score difference
  from the next state.
- Since we are calculating the difference from the current player's
  perspective, we subtract the opponent's result.

Base Case:
- When i == n, there are no more moves, so the score difference is 0.

Optimization:
- Use memoization so each state is calculated only once.

Complexity:
- Time: O(n)
- Space: O(n)

Key Game Theory Pattern:
    Current player's score - Opponent's best score

This "my score - opponent's optimal result" pattern is very common
in two-player optimal game DP problems.
*/

class Solution {
public:
    vector<int> prefixSum;
    int n;
    vector<int> dp;
    int solve(int i){
        if(i==n){
            return 0;
        }
        if(dp[i]!=INT_MIN) return dp[i];
        
        int take = INT_MIN;
        int skip = INT_MIN; 
        //take upto this stone
        take = prefixSum[i] - solve(i+1);
        //skip this stone -- means take upto a higher number of stones
        if(i!=n-1) skip = solve(i+1);
        return dp[i] = max(take,skip);
    }
    int stoneGameVIII(vector<int>& stones) {
        n = stones.size();
        prefixSum.assign(n,0);
        prefixSum[0] = stones[0];
        for(int i =1;i<n;i++ ){
            prefixSum[i] = stones[i] + prefixSum[i-1];
        }
        dp.assign(n,INT_MIN);
        return solve(1);
    }
};

