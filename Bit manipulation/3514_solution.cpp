/*
    LeetCode Daily Challenge - Day 26

    Problem    : 3514. Number of Unique XOR Triplets II
    Difficulty : Medium

    Approach:
    - Any triplet XOR can be written as a ⊕ b ⊕ c = a ⊕ (b ⊕ c).
    - First, compute all distinct XOR values of valid pairs (i <= j).
    - Since nums[i] <= 1500, every XOR value lies in the range [0, 2047].
    - Store these pair XORs in a boolean array of size 2048.
    - XOR each array element with every stored pair XOR to obtain all
      possible triplet XOR values.
    - Count the number of distinct XOR values obtained.

    Complexity:
    Time  : O(n² + 2048 × n)
    Space : O(2048)
*/
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        vector<bool> xor_found(2048,false); //because values are less than 2^11 i.e. --> 0 to 2047
        for(int j = 0;j<n;j++){
            for(int k = j;k<n;k++){
                xor_found[nums[j]^nums[k]] = true;
            }
        }
        vector<bool> ans(2048,false);
        for(int i = 0;i<n;i++){
            ans[nums[i]] = true;
            for(int j = 0;j<2048;j++){

             if(xor_found[j]) ans[nums[i]^j] = true;
         }
        }
        int res = 0;
        for(bool a:ans) a?res++:res;
        
        return res;
    }
};