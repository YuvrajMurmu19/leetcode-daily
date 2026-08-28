// Approach:

// Compute the required GCD-related values.
// Store them in an array.
// Sort the array.
// Use two pointers (left and right) to process pairs from both ends.
// Compute the GCD for each pair and accumulate the answer.

// Time Complexity: O(n log n)

// Sorting dominates the overall complexity.

// Space Complexity: O(n)

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        int mxi = nums[0];
        vector<int> prefixGcd(n);

        for(int i = 0;i<n;i++){
            mxi = max(nums[i],mxi);
            prefixGcd[i] = gcd(nums[i],mxi);
        }

        sort(prefixGcd.begin(),prefixGcd.end());

        int l = 0;
        int r = n-1;

        long long sum = 0;

        while(l<r){
            int temp = gcd(prefixGcd[l],prefixGcd[r]);
            sum += temp;
            l++;
            r--;
        }

        return sum;
    }
};