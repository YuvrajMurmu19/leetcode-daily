// Approach-2: Observation / Case Analysis
// T.C : O(n)
// S.C : O(1)
//
// Case 1: k == 1
// Each element forms its own subarray.
// Therefore, an element is almost missing iff its frequency in nums is 1.
// Return the largest such element.
//
// Case 2: k == n
// There is only one subarray: the entire array.
// Hence, every distinct element appears in exactly one subarray.
// Return the maximum element.
//
// Case 3: 1 < k < n
// Every index from 1 to n-2 belongs to at least two size-k subarrays.
// Therefore, an element can be almost missing only if it occurs at
// nums[0] or nums[n-1].
// Its total frequency must also be exactly 1.
//
// Check nums[0] and nums[n-1] and return the larger valid one.
//
// Note:
// We use freq[] to check whether the boundary element occurs only once.

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        
        int l = nums[0];
        int r = nums[n-1];
        int maxi = *max_element(nums.begin(),nums.end());
           
        int freq[51];
        for(int num:nums) freq[num]++;

        if(k==1){
            //all elements are part of length 1 subarray
            //the maximum element with frequency 1
            for(int i = 50;i>=0;i--) {
                if(freq[i]==1) return i;
            }
        }else if(k==n){
            //the max element with multiple frequency is still the part of same subarray i.e. the whole array 
            return maxi;
        }
        //1<k<n
        //all elements from 1<i<n-1 are part of more than one subarray
        //only the l and r may occur once
        //but they can also occur in 1<i<n-1 range 
        //so check their frequency
        //first try to take max but if not possible then minimum
        else if(freq[max(l,r)]==1) return max(l,r);
        else if(freq[min(l,r)] == 1) return min(l,r);

        return -1;
    }
};


// Approach-1: Brute Force
// T.C : O(n * k)
// S.C : O(1)
//
// For every subarray of size k:
// - Use a boolean array to ensure duplicate elements inside the same
//   subarray are counted only once.
// - Increment freq[x] if x is present in that subarray.
//
// Finally, traverse from 50 to 0 and return the largest number
// that appears in exactly one size-k subarray.
//
// Important:
// An element appearing multiple times in the SAME subarray is counted
// only once. We count the number of DIFFERENT subarrays containing x.

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int freq[51];
        int n = nums.size();

        for(int i = 0;i+k<=n;i++){
            int j = i;
            bool done[51] = {false};
            while(j<i+k){
                if(!done[nums[j]]) {
                    freq[nums[j]]++;
                    done[nums[j]] = true;
                }
                j++;
            }
        }
        for(int i = 50;i>=0;i--){
            if(freq[i]==1) return i;
        }
        return -1;
    }
};