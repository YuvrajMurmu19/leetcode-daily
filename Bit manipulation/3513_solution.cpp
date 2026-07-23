/*
    LeetCode Daily Challenge - Day 25

    Problem  : 3513. Number of Unique XOR Triplets I
    Difficulty : Medium

    Approach:
    - Since nums is a permutation of [1...n], every number in this range is already obtainable.
    - For n >= 3, XOR of 1, 2, and 3 gives 0, so 0 is also achievable.
    - Let k be the number of bits required to represent n.
    - Every value from 0 to (2^k - 1) can be generated using XOR.
    - Therefore, the number of unique XOR values is simply 2^k.

    Complexity:
    Time  : O(log n)
    Space : O(1)

    Takeaway:
    A few observations about XOR and bit representation reduce the entire
    problem to a constant-time mathematical solution.
*/
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if(n<=2) return n;
        //any range greater than this will have 1 2 3 and we can surely get 0 
        //min value 0
        //have to find k i.e. number of bits in larget integer
        int k = 0;
        while(n>0){
            n>>=1;
            k++;
        }
        return 1<<k;

    }
};