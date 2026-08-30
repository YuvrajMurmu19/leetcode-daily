/*
    LeetCode Daily Challenge - Day 28

    Problem    : 628. Maximum Product of Three Numbers
    Difficulty : Easy

    Approach:
    - Traverse the array once.
    - Maintain the three largest numbers seen so far.
    - Maintain the two smallest numbers seen so far.
    - The maximum product can come from either:
        1. The three largest numbers.
        2. The largest number and the two smallest
           (most negative) numbers.
    - Return the maximum of these two products.

    Complexity:
    Time  : O(n)
    Space : O(1)
*/

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int first = INT_MIN;
        int second = INT_MIN;
        int third = INT_MIN;
        int smallest_first = INT_MAX;
        int smallest_second = INT_MAX;
        for (int num : nums) {
            // if number is positive
            //maintain 3 largest
                if (first <= num) {
                    third = second;
                    second = first;
                    first = num;
                } else if (num < first && num >= second) {
                    third = second;
                    second = num;
                } else if (num > third) {
                    third = num;
                }
          
                // for smallest numbers - may be negative then will come in use
                if (smallest_first >= num) {
                    smallest_second = smallest_first;
                    smallest_first = num;
                } else if (num > smallest_first && num < smallest_second) {
                    smallest_second = num;
                }
            }
        

       
        return max(first * second * third , first * smallest_first * smallest_second);
    }
};
