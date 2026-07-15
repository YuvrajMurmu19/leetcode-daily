/*
==========================================
LeetCode POTD - GCD of Odd and Even Sums
==========================================

Thought Process:

1. Instead of generating the first n odd and even numbers,
   derive their mathematical formulas.

   • Sum of first n even numbers = n * (n + 1)
   • Sum of first n odd numbers  = n²

2. The problem then becomes:

      gcd(n * (n + 1), n²)

3. Factor out the common 'n':

      = n * gcd(n + 1, n)

4. Since consecutive integers are always coprime,

      gcd(n + 1, n) = 1

   Therefore,

      gcd(n * (n + 1), n²) = n

Key Insight:
The GCD computation itself is unnecessary after simplifying the expression.

Complexity:
• Initial approach : O(log n)   // Using gcd()
• Optimized approach: O(1)      // Simply return n
*/

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        return n;
    }
};


class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sumEven = n*(n+1);
        int sumOdd = n*n;
        return gcd(sumEven,sumOdd);
    }
};