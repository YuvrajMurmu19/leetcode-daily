/*
    LeetCode Daily Challenge - Day 27

    Problem    : Maximum Product of Two Digits
    Difficulty : Easy

    Approach:
    - Traverse the digits of the given number once.
    - Maintain the largest and second-largest digits seen so far.
    - If the current digit is larger than the largest digit,
      update both largest and second-largest.
    - Otherwise, if it is larger than the second-largest,
      update only the second-largest.
    - Return the product of the two largest digits.

    Complexity:
    Time  : O(d), where d is the number of digits.
    Space : O(1)
*/

class Solution {
public:
    int maxProduct(int n) {
        int first = INT_MIN;
        int second = INT_MIN;
        while(n>0){
            int digit = n%10;
            n /=10;
            if(digit>first){
                second = first;
                first = digit;
            }else if(digit<=first && digit>second ) second = digit;
        }
        return first*second;
    }
};