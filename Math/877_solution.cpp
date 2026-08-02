/*
    LeetCode 877. Stone Game
    Difficulty: Medium

    Observation:
    - There are an even number of piles.
    - Alice moves first.
    - Before the game starts, Alice compares:
        1. Sum of stones at even indices.
        2. Sum of stones at odd indices.
    - One of these sums is strictly larger because
      the total number of stones is odd.
    - On her first move, Alice chooses the parity
      (even-indexed or odd-indexed piles) having the
      larger total.
    - From then on, regardless of Bob's moves,
      Alice can always continue taking piles of
      that chosen parity.
    - Therefore, Alice is guaranteed to collect
      the larger sum and always wins.

    Time Complexity : O(1)
    Space Complexity: O(1)
*/

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};