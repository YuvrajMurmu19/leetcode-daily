/*
    Approach:
    - Let dp[i] represent the maximum score difference
      (current player - opponent) starting from index i.
    - At every position, the current player can take
      1, 2, or 3 stones.
    - If the current player takes k stones, the opponent
      will play optimally on the remaining stones, so
      the net advantage becomes:
          sum_of_taken_stones - dp[i + k]
    - Compute the best possible score difference by
      taking the maximum among all valid choices.
    - Since each state depends only on the next three
      states, the DP can be optimized from O(n) space
      to O(1) using three variables.
    - If the final score difference is:
        > 0 : Alice wins
        = 0 : Tie
        < 0 : Bob wins

    Time Complexity : O(n)
    Space Complexity: O(1)
*/


class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        int next3 = 0;
        int next2 = 0;
        int next1 = 0;
        for(int i=n-1;i>=0;i--){
            int op2 = -1e9,op3 = -1e9;
            int op1 = stoneValue[i] - next1;
            if(i+1<n) op2 = stoneValue[i] + stoneValue[i+1] - next2;
            if(i+2<n) op3 = stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - next3;

            int temp = max({op1,op2,op3});
            next3 = next2;
            next2 = next1;
            next1 = temp;

        }
         
        
        if(next1>0) return "Alice";
        else if(next1==0) return "Tie";

        return "Bob";
    }
};