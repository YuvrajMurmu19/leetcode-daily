/*
Approach:
- Instead of generating all subsequences explicitly, store only the current GCDs
  of the two subsequences.
- DP state: dp[gcd1][gcd2] = number of ways to obtain a pair of subsequences
  whose current GCDs are gcd1 and gcd2.
- Initialize dp[0][0] = 1, where GCD 0 represents an empty subsequence.
- For every number, there are three possible transitions:
    1. Add it to the first subsequence  -> (gcd(gcd1, num), gcd2)
    2. Add it to the second subsequence -> (gcd1, gcd(gcd2, num))
    3. Skip it                          -> (gcd1, gcd2)
- Update a temporary DP table for each element to avoid using updated states
  in the same iteration.
- After processing all numbers, sum the counts of all states where
  gcd1 == gcd2 and gcd1 > 0 (excluding the case where both subsequences are empty).

Time Complexity: O(N × M² × log M)
    N = size of nums
    M = 200 (maximum possible GCD value)

Space Complexity: O(M²)
*/

class Solution {
public:
    int gcd(int a,int b){
        if(a==0) return b;
        if(b==0) return a;

        return gcd(b%a,a);
    }
    
    int subsequencePairCount(vector<int>& nums) {
        int mod = 1e9+7;
        int n = nums.size();
        vector<vector<int>> gcd_count(201,vector<int>(201,0));
        gcd_count[0][0] = 1;
        for(int num:nums){
            vector<vector<int>> temp_gcd_count(201,vector<int>(201,0));

            for(int i = 0;i<201;i++){
                for(int j = 0;j<201;j++){
                    if(gcd_count[i][j]!=0){
                        int count = gcd_count[i][j];
                        //3 choices
                        //take in seq1
                        temp_gcd_count[gcd(i,num)][j] = (temp_gcd_count[gcd(i,num)][j] + count)%mod;

                        //take in seq2
                        temp_gcd_count[i][gcd(j,num)] = (temp_gcd_count[i][gcd(j,num)] + count)%mod;

                        //none
                        temp_gcd_count[i][j] = (temp_gcd_count[i][j] + count)%mod;
                    }
                }
            }
            gcd_count = temp_gcd_count;
        }

        int ans = 0;
        for(int i = 1;i<201;i++){
                for(int j = 1;j<201;j++){
                    if(i==j){
                        ans =( ans + gcd_count[i][j])%mod;
                    }
                }
        }
        return ans;
        
    }
};