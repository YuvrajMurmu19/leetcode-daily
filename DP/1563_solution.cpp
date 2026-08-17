// LeetCode 1563. Stone Game V
// Approach: Prefix Sum + Recursion + Memoization
//
// dp[s][e] = maximum score Alice can obtain from subarray [s...e].
//
// For every possible partition i:
// left = sum(s...i), right = sum(i+1...e)
//
// If left > right:
//     Bob removes left -> Alice gets right + solve(i+1, e)
//
// If left < right:
//     Bob removes right -> Alice gets left + solve(s, i)
//
// If left == right:
//     Alice can choose which side to discard ->
//     left + max(solve(s, i), solve(i+1, e))
//
// Try all partitions and take the maximum score.
//
// Prefix sum gives O(1) range-sum queries.
// Memoization avoids recalculating the same subproblems.
//
// T.C: O(n^3)
// S.C: O(n^2)

class Solution {
public:
    vector<int> prefixSum;
    int dp[501][501];
    int solve(vector<int>& stoneValue,int s,int e){
        if(s==e) return 0;
        if(dp[s][e]!=0) return dp[s][e];

        int max_minScore = 0;
        //try all partitions
        for(int i = s;i<e;i++){
            //partition at i
            //s---i => in l
            //i+1....e => in r
            int l = prefixSum[i] - (s-1>=0?prefixSum[s-1]:0);
            int r = prefixSum[e] - prefixSum[i];
            int minScore;
            if(l>r){
                //chose r
                minScore= r + solve(stoneValue,i+1,e);
            }else if(l<r){
                minScore = l + solve(stoneValue,s,i);
            }else{
                //take maximum from both future scores
                //because when two rows are equal bob lets alice decide which row will be thrown away
                minScore = l + max(solve(stoneValue,s,i),solve(stoneValue,i+1,e));
            }
            if(minScore>max_minScore){
                max_minScore = minScore;
            }
        }
        int alice_score = max_minScore;
        
        return dp[s][e] = alice_score;
    }
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        prefixSum.assign(n,0);
        prefixSum[0] = stoneValue[0];
        for(int i = 1;i<n;i++){
            prefixSum[i] = stoneValue[i] + prefixSum[i-1];
        }
        memset(dp,0,sizeof(dp));
        // for(int i = 0;i<n;i++){
        //     dp[i][i] = stoneValue[i];
        // }
        if(n==1) return 0;
        return solve(stoneValue,0,n-1);
    }
};