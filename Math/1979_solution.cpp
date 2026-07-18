/*
    LeetCode 1979 - Find Greatest Common Divisor of Array

    Core Idea:
    ----------
    The GCD of the entire array is equal to the GCD of its
    smallest and largest elements.

    Steps:
    1. Traverse the array to find the minimum and maximum values.
    2. Compute their GCD using the Euclidean Algorithm.
    3. Return the result.

    Euclidean Algorithm:
        gcd(a, b) = gcd(b % a, a)
        Repeat until a becomes 0.

    Time Complexity:
        O(N + log(min(a, b)))
        N = size of the array
        log(min(a, b)) = time taken by the Euclidean Algorithm

    Space Complexity:
        O(log(min(a, b)))   // Recursive calls
        O(1)                // If implemented iteratively
*/

class Solution {
public:
    int gcd(int a,int b){
        if(a==0) return b;

        return gcd(b%a,a);
    }
    int findGCD(vector<int>& nums) {
        int mini = INT_MAX;
        int maxi = INT_MIN;

        for(int& num:nums){
            mini = min(mini,num);
            maxi = max(maxi,num);
        }

        return gcd(mini,maxi);
    }
};