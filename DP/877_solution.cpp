/*
    LeetCode 877. Stone Game
    Difficulty: Medium

    Approach:
    - Let dp[l][r] represent the maximum score difference
      (current player - opponent) that the current player
      can achieve from the subarray [l...r].
    - If the current player picks the left pile,
      the opponent gains solve(l+1, r), so the net
      advantage becomes:
          piles[l] - solve(l+1, r)
    - Similarly for picking the right pile:
          piles[r] - solve(l, r-1)
    - Choose the option giving the maximum advantage.
    - If the final score difference is positive,
      Alice wins.

    Time Complexity : O(n²)
    Space Complexity: O(n²)
*/

class Solution {
public:
    int dp[501][501];
    int solve(vector<int>& piles,int l,int r){
        if(l==r){
            return piles[l];
        }
        if(dp[l][r]!=-1) return dp[l][r];

        //choose either left or right one
        //the next recursive call would be a different player
        //it will try to minimise the current player score that is why subtraction used
        int left = piles[l] - solve(piles,l+1,r);
        int right = piles[r] -  solve(piles,l,r-1);
        return dp[l][r] = max(left,right);
        
    }
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        memset(dp,-1,sizeof(dp));
        int l = 0;
        int r = n-1;
        return solve(piles,l,r)>=1;
    }
};