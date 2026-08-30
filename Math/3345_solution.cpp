/*
    Approach 2 (Optimized):
    - Compute the product of digits using a helper function.
    - Instead of searching until 100, observe that with the given constraints
      (n <= 100 and t <= 10), the answer is guaranteed to be found within
      the next 10 numbers.
    - Check only the current number and the next 9 candidates.
    - Return the first number whose digit product is divisible by t.

    Time Complexity: O(10 * d)
                     where d is the number of digits (at most 3).
                     This simplifies to O(1).

    Space Complexity: O(1)
*/

class Solution {
public:
    int product_of_digits(int n){
        int prod = 1;
        while(n>0){
            int digit = n%10;
            prod*= digit;
            n /=10;
        }
        return prod;
    }
    int smallestNumber(int n, int t) {
        for(int i = 0;i<10;i++){
            if(product_of_digits(n)%t==0) return n;
            n++;
        }
        return 0;
    }
};

/*
    Approach 1:
    - Create a helper function to compute the product of the digits of a number.
    - Start checking numbers from n.
    - For each number, calculate its digit product.
    - If the product is divisible by t, return the current number.
    - Otherwise, increment n and continue searching until the upper limit (100).

    Time Complexity: O((100 - n + 1) * d)
                     where d is the number of digits (at most 3).
                     Since the constraints are small, this is effectively O(1).

    Space Complexity: O(1)
*/

class Solution {
public:
    int product_of_digits(int n){
        int prod = 1;
        while(n>0){
            int digit = n%10;
            prod*= digit;
            n /=10;
        }
        return prod;
    }
    int smallestNumber(int n, int t) {
        while(n<=100){
            if(product_of_digits(n)%t == 0) return n;
            else n++;
        }
        return 0;
    }
};