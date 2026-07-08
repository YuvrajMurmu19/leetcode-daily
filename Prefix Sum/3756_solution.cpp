/*
Approach:
- Precompute prefix arrays:
  1. prefixSum      -> Sum of digits up to each index.
  2. prefixX        -> Concatenated non-zero digits modulo 1e9+7.
  3. countNonZero   -> Number of non-zero digits up to each index.
  4. power10        -> Powers of 10 modulo 1e9+7.

- For each query [l, r]:
  * Compute the sum of digits using prefixSum.
  * Find the number of non-zero digits in the range.
  * Remove the contribution of the prefix before l from prefixX using
    power10 and the non-zero digit count.
  * Multiply the resulting concatenated number with the digit sum.

Time Complexity: O(n + q)
  - O(n) preprocessing
  - O(1) per query

Space Complexity: O(n)
*/


class Solution {
public:
    typedef long long ll;
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        ll mod = 1e9 + 7;
        int n = s.size();

        vector<ll> prefixSum(n);
        vector<ll> prefixX(n);
        vector<ll> power10(n+1);
        
        vector<int> countNonZero(n,0);

        for(int i = 0;i<n;i++){
            int digit = s[i] - '0';
           
            if(i==0){
                if(digit!= 0) {
                    countNonZero[0] = 1;
                 }
                prefixSum[0] = digit;
                prefixX[0] = digit;
                power10[0] = 1;
            }else{
                 if(digit!= 0) {
                     countNonZero[i] = countNonZero[i-1] + 1;
                     prefixX[i] =( (prefixX[i-1] * 10)%mod + digit )%mod;
                 }else{
                     countNonZero[i] = countNonZero[i-1];
                     prefixX[i] =prefixX[i-1];
                 }
                prefixSum[i] = (prefixSum[i-1] +digit )%mod;
               
                power10[i] =( power10[i-1]*10 )%mod; //should we add mod here?
            }
        }
        n = queries.size();
        vector<int> ans;
        for(auto& query:queries){
            int l = query[0];
            int r = query[1];

            ll sum_to_be_subtracted = (l==0)? 0 : prefixSum[l-1];
 
            //because of modulo large numbers can become smaller 
            // and this difference can be negative
           
            ll sum =( prefixSum[r] - sum_to_be_subtracted + mod)%mod;
            
            int digits_btw_range = countNonZero[r]-((l==0)? 0 : countNonZero[l-1]);
            ll prefixX_to_be_subtracted = (( (l==0)?0:prefixX[l-1] ) * power10[digits_btw_range])%mod;
            //similar mod calculation here
            ll x = (prefixX[r] -prefixX_to_be_subtracted + mod)%mod ;
            ans.push_back((sum*x)%mod);
        }
        return ans;
    }
};