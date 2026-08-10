/*
    Approach 1: Recursion + Memoization

    Idea:
    - On each turn, the player can remove any perfect square:
        1, 4, 9, 16, ...
    - Define:
        dp[n] = true  -> current player can win with n stones remaining
        dp[n] = false -> current player loses with n stones remaining

    - For every possible square <= n:
        * Remove the square and move to state (n - square).
        * If the next player loses from that state, then the current
          player can make that move and win.

    - Therefore:
        If there exists a square such that solve(n - square) == false,
        then solve(n) = true.

    Base Case:
    - n <= 0 -> false
      There are no stones left, so the current player has no valid move
      and loses.

    Time Complexity: O(n * sqrt(n))
        - There are O(n) states.
        - For each state, we try O(sqrt(n)) perfect squares.

    Space Complexity: O(n)
        - O(n) memoization array.
        - O(n) maximum recursion stack.
*/

class Solution {
public:
    int dp[100001];
    bool solve(int n){
        //the current player loses the game
        if(n<=0) return false;//because if it's alice chance then she loses and bob wins and if bob's chance then bob loses and alice wins
        if(dp[n] !=-1) return dp[n];
        for(int i = 1;i*i<=n;i++){
            if(!solve(n-i*i)) return dp[n] = true;
        }
        //i could not win
        return dp[n] = false;

    }
    bool winnerSquareGame(int n) {
        memset(dp,-1,sizeof(dp));
      
        return solve(n);
    }
};

/*
    Approach 2: Bottom-Up DP

    Idea:
    - Use the same state definition:
        dp[i] = true  -> current player can win with i stones remaining
        dp[i] = false -> current player loses with i stones remaining

    - Start from smaller states and build the answer for every i from 1 to n.

    - For each i, try removing every perfect square <= i.
    - If there is any move such that:
        dp[i - square] == false

      then the next player loses, so the current player wins:
        dp[i] = true

    - If no such move exists, dp[i] remains false.

    Base Case:
    - dp[0] = false
      With 0 stones, the current player cannot make a move and loses.

    Time Complexity: O(n * sqrt(n))
        - O(n) states.
        - O(sqrt(n)) perfect squares checked for each state.

    Space Complexity: O(n)
        - DP array of size n + 1.
*/
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n+1,false);
        for(int i = 1;i<=n;i++){
            for(int j = 1;j*j<=i;j++){
                if(!dp[i-j*j]){
                    dp[i] = true; 
                    break;
                }
            }
        }
        return dp[n];
    }
};