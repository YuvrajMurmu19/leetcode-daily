/*
    Approach: Dynamic Programming + Suffix Sum

    Idea:
    - At every state (i, M), the current player can take X piles where:
          1 <= X <= 2 * M

    - Instead of maintaining a separate variable to track whose turn it is,
      define solve(i, M) as the maximum stones the CURRENT player can obtain
      from index i onward.

    - Let suffixSum[i] be the total number of stones from index i to the end.

    - If the current player takes X piles, they get:
          suffixSum[i] - solve(i + X, max(M, X))

      because solve(next state) represents the maximum stones the opponent
      can obtain from the remaining piles.

    - Therefore, try every possible X and maximize the current player's score.

    DP State:
    - dp[i][M] = maximum stones the current player can obtain
                 starting from index i with the current M.

    Recurrence:
        dp[i][M] =
            max(
                suffixSum[i] -
                solve(i + X, max(M, X))
            )

        for 1 <= X <= 2 * M

    Base Case:
    - If i == n, there are no piles left:
          return 0

    Optimization:
    - Suffix sum allows us to calculate the total remaining stones in O(1),
      avoiding an additional loop to calculate the sum of chosen piles.

    Time Complexity:
    - O(n^3)
    - There are O(n^2) states (i, M).
    - For each state, we can try up to O(n) choices of X.

    Space Complexity:
    - O(n^2) for the DP table.
    - O(n) for the suffix sum.
*/

class Solution {
public:
    int dp[101][101];
    int solve(vector<int>& piles, int m,int i,vector<int>& suffixSum){
        if(i==piles.size()) return 0;

        if(dp[i][m] !=-1) return dp[i][m];
        //the current player can choose any path
        int upper_limit_x = 2*m;
        
        //try to maximise my score
        int maxScore = 0;
            for(int x = 1;x<=upper_limit_x;x++){
                if(x+i>piles.size()) break;
                
                int temp_m = max(m,x);
                int score = suffixSum[i] - solve(piles,temp_m,i+x,suffixSum);
                maxScore = max(maxScore,score);
            }
        return dp[i][m] = maxScore;
        
    }
    int stoneGameII(vector<int>& piles) {
        int m = 1;
        int i = 0;
        int n = piles.size();
        vector<int> suffixSum(n,0);
        suffixSum[n-1] = piles[n-1];
        for(int i =  n-2;i>=0;i--){
            suffixSum[i] = piles[i] + suffixSum[i+1];
        }
        memset(dp,-1,sizeof(dp));
        return solve(piles,m,i,suffixSum);
    }
};