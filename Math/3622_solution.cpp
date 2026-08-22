/*
    LeetCode 3622 — Check Divisibility by Digit Sum and Product

    Approach:
    ----------
    We need to check whether n is divisible by:
        digitSum(n) + digitProduct(n)

    I used two helper functions to separately calculate:
    
    1. digitSum(n):
       - Extract each digit using n % 10
       - Add it to the sum
       - Remove the last digit using n /= 10

    2. digitProduct(n):
       - Extract each digit using n % 10
       - Multiply it into the product
       - Remove the last digit using n /= 10

    Finally:
        return n % (sum + product) == 0;

    Example:
        n = 99
        digitSum = 9 + 9 = 18
        digitProduct = 9 * 9 = 81

        sum + product = 18 + 81 = 99

        99 % 99 == 0 -> true

    Time Complexity:
        O(log n)
        We process every digit of n.

    Space Complexity:
        O(1)
        Only a few integer variables are used.

    Topic:
        Mathematics / Digit Manipulation
*/
class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        int sum = 0;
        while(temp>0){
            int digit = temp%10;
            temp/=10;
            sum+=digit;
        }
        
        temp = n;
        int product = 1;
        while(temp>0){
            int digit = temp%10;
            temp/=10;
            product*=digit;
        }

        return n%(sum+product)==0;
    }
};