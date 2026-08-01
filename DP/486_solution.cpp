/*
    LeetCode Daily Challenge - Day 34

    Problem    : 486. Predict the Winner
    Difficulty : Medium

    Approach (DP - Score Difference):
    - Instead of tracking the individual
      scores of both players, track the
      maximum score difference
      (current player - opponent).
    - Let dp[l][r] represent the maximum
      score difference the current player
      can achieve from subarray [l...r].
    - If the current player picks the
      left element, the opponent becomes
      the current player for the remaining
      subarray, so the resulting
      difference is:
          nums[l] - dp[l + 1][r]
    - Similarly, picking the right
      element gives:
          nums[r] - dp[l][r - 1]
    - Choose the better of the two
      options since the current player
      always plays optimally.
    - If the final score difference is
      non-negative, Player 1 can win
      (or tie), so return true.

    Complexity:
    Time  : O(n²)
    Space : O(n²)
*/

class Solution {
public:
    int maxDiff(vector<int>& nums, int n, int l, int r,int (&dp)[21][21]) {
        if(l>r)  return 0;
        if(l==r){
            return nums[l];
        }
        if(dp[l][r]!=-1e9) return dp[l][r];
        int left = nums[l] - maxDiff(nums,n,l+1,r,dp);
        int right = nums[r] - maxDiff(nums,n,l,r-1,dp);
        return dp[l][r] = max(left,right);
    }
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        int l = 0;
        int r = n - 1;
        int dp[21][21];
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                dp[i][j] = -1e9;
            }
        }
        int ans = maxDiff(nums, n, l, r,dp);
        return ans>=0;
    }
};