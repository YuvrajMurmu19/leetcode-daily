/*
Approach:

* First built the number `x` by removing all zero digits.
* Initially used `pow(10, i)` to place digits and made a second traversal to compute the digit sum.
* Optimized by calculating the digit sum while constructing `x` itself.
* Replaced `pow()` with an integer multiplier (`1, 10, 100, ...`), avoiding floating-point operations.
* This removed the extra traversal and reduced constant overhead.

Time Complexity: O(log₁₀ n)
Space Complexity: O(1)
*/

class Solution {
public:
    long long sumAndMultiply(int n) {
       long long x = 0;
       int multiplier = 1;
       long long sum = 0;
        while(n){
            int digit = n%10;
            n = n/10;

           if(digit!=0){
             x = x + digit*multiplier;
             sum+=digit;
             multiplier*=10;

           }
        }
        return x*sum;

    }
};

class Solution {
public:
    long long sumAndMultiply(int n) {
       long long x = 0;
        int temp = n;
        int it = 0;
        while(temp){
            int digit = temp%10;
            temp = temp/10;

           if(digit!=0){
             x = x + digit*pow(10,it);
             it++;
           }
        }
          
        long long sum = 0;
        temp = x;
         while(temp){
            int digit = temp%10;
            temp = temp/10;

           sum +=  digit;
        }

        return x*sum;

    }
};