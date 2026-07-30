/*
    LeetCode Daily Challenge - Day 32

    Problem    : 3014. Minimum Number of Pushes to Type Word I
    Difficulty : Easy

    Approach 1 (Simulation):
    - There are 8 available keys (2–9).
    - To minimise pushes, assign the first
      8 characters to the first position
      on each key (1 push each).
    - The next 8 characters require
      2 pushes each, and so on.
    - Process the characters in groups of 8,
      adding (currentPushes × groupSize)
      to the answer.
    - Continue until all characters have
      been assigned.

    Complexity:
    Time  : O(n)
    Space : O(1)



    Approach 2 (Mathematical):
    - Observe that every complete group of
      8 characters contributes the same
      number of pushes.
    - Let x be the number of push levels
      required and rem be the remaining
      characters in the last group.
    - Compute the contribution of all
      complete groups using the formula:
          4 * x * (x - 1)
    - Add the contribution of the remaining
      characters:
          rem * x
    - Return the total pushes directly,
      without any iteration.

    Complexity:
    Time  : O(1)
    Space : O(1)
*/

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int i = 1;
        if(n<8) return n;
        int ans = 0;
        while(n>0){
            ans+= i*min(8,n);
            i++; //then next characters will be in next position at each keys
            //8 characters have been taken
            n -= 8;
        }
        return ans;
    }
};

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int x = n/8 +1;
        int rem = n%8;
        int ans = (4*x*(x-1)) + (rem*x);
        return ans;
    }
};