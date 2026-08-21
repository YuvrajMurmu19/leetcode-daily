/*
    Problem: 3116. Kth Smallest Amount With Single Denomination Combination

    Approach:
    Binary Search on Answer + Inclusion-Exclusion + LCM + Bitmasking

    Thought Process:
    - k can be as large as 2 * 10^9, so generating all possible amounts
      directly is not possible.
    - The kth smallest amount must lie between:
          low  = minimum coin
          high = minimum coin * k
    - Therefore, we can Binary Search for the answer.
    - For every mid, we need to find how many distinct amounts are <= mid.
    - Each coin produces multiples of that coin, so we need to count numbers
      divisible by at least one coin.
    - Some numbers are divisible by multiple coins and would be counted more
      than once.
    - This leads to the Inclusion-Exclusion Principle.
    - For every subset of coins, we calculate its LCM.
    - The number of multiples of this LCM <= mid is:
          mid / LCM
    - Odd-sized subsets are added and even-sized subsets are subtracted.
    - Initially, generating every subset seemed difficult. I took help and
      learned that Bitmasking can represent and enumerate all subsets.
    - For n coins, masks from 1 to (1 << n) - 1 represent all non-empty subsets.

    Bitmasking:
    - Bit i is set -> coins[i] is included in the current subset.
    - bits = number of selected coins.
    - If bits is odd:
          add mid / LCM
      Otherwise:
          subtract mid / LCM

    Binary Search Condition:
    - count(mid) >= k means there are at least k valid amounts <= mid.
      Therefore, mid can be the answer, so search the left half.
    - Otherwise, we need a larger value.

    Time Complexity:
        O(2^n * n * log(min(coins) * k))

    Space Complexity:
        O(1)

    Key Concepts:
    - Binary Search on Answer
    - Inclusion-Exclusion Principle
    - LCM
    - Bitmasking
*/

class Solution {
public:
    typedef long long ll;
    ll count(ll x,vector<int>& coins){
        //count function gives the number of distinct elements less than or equal to x
        ll cnt = 0;
        int n = coins.size();
        for(int mask = 1;mask<(1<<n);mask++){
            int bits = 0;
            ll total_lcm = 1;
            for(int i = 0;i<n;i++){
                if(mask & (1<<i)){
                    bits++;
                    total_lcm = lcm((ll)coins[i],total_lcm);
                }
            }
            if(bits%2==0){
                cnt -= (x/total_lcm);
            }else{
                cnt += (x/total_lcm);
            }
        }
        return cnt;
    }
    long long findKthSmallest(vector<int>& coins, int k) {
        ll low = 1LL*(*min_element(coins.begin(),coins.end()));
        ll high = low*k;//max kth element possible
        
        ll ans = 0;
        while(low<=high){
            ll mid = low + (high-low)/2;
            if(k<=count(mid,coins)){
                ans = mid;
                high = mid-1;
            }else{
                low = mid+1;
            }
        }

        return ans;

    }
};
