/*
    LeetCode 3312 - Sorted GCD Pair Queries

    Core Idea:
    ----------
    Instead of generating all O(n²) pairs, count how many pairs have each
    possible GCD using number theory and answer queries with binary search.

    Steps:
    1. Find the frequency of every number.
    2. For each value i, use a sieve-like traversal to count how many
       elements are divisible by i (countMultiple[i]).
    3. Compute the number of pairs having GCD >= i:
           C(countMultiple[i], 2)
    4. Process from largest to smallest and use inclusion-exclusion to
       subtract pairs already counted for multiples of i, giving the
       number of pairs with exact GCD = i.
    5. Build a prefix sum of exact GCD counts so that prefix[g] represents
       the number of pairs with GCD <= g.
    6. For each query (0-indexed in the sorted GCD pair array), perform
       binary search on the prefix array to find the smallest GCD whose
       cumulative count exceeds the query.

    Time Complexity:
        O(M log M + Q log M)
        M = maximum element in nums
        Q = number of queries

    Space Complexity:
        O(M)
*/

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int n = nums.size();
        int maxi = 1;
        for(int& num:nums){
            maxi = max(maxi,num);
        }
        
        //to find the count of num in nums first 
        vector<int> freq(maxi+1,0);
        for(int& num: nums) freq[num]++;

        //maxi will give me the size
        //now i want the count of elements that are divisible by 'i'
        vector<int> countMultiple(maxi+1,0);
        //right now all count is zero
        //i would have to use sieve
        for(int i = 1;i<=maxi;i++){
            //we have to jump in intevals of i to get multiples of i
            int j = i;
            int cnt = 0;
            while(j<=maxi){
               cnt += freq[j];
               j += i;
            }
            countMultiple[i] = cnt;
        }

        //now get the atleastgcd
        vector<long long> atleast_gcd(maxi+1,0);
        for(int i = 1;i<=maxi;i++){
            long long m = countMultiple[i];
            atleast_gcd[i] = (m*(m-1))/2; //count the pairs with at least gcd i
        }

        //now count the pairs with exact gcd
        vector<long long> exact_gcd(maxi+1,0);
        for(int i = maxi;i>0;i--){
            exact_gcd[i] = atleast_gcd[i];
            int m = maxi/i;
            int j = 2;
            while(j<=m){
                exact_gcd[i] -= exact_gcd[j*i];
                j++;
            }
        }

        //prefix Count array
        vector<int> prefixCount(maxi+1,0);
        for(int i = 1;i<=maxi;i++){
           prefixCount[i] = exact_gcd[i] + prefixCount[i-1];
        }


        vector<int> res;
        for(int query:queries){
           //we will apply binary search to find the count at which it became greater than the query and when it just became greater than query there my answer lies
           int l = 0;
           int r = maxi+1;
           int ans = -1;
           while(l<=r){
             int mid = l+ (r-l)/2;
             int cnt = prefixCount[mid];
             if(cnt>query){
                ans = mid;
                r = mid-1;
             }else{
                  l = mid+1;
             }
           }
           res.push_back(ans);
           
        }
        return res;
    }
};