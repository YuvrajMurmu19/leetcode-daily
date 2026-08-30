/*
Approach 1: Calculate deletion cost for min and max separately.

1. Find the indices of the minimum and maximum elements.
   - i = index of minimum
   - j = index of maximum

2. For each element, it can be removed from either:
   - Front  -> index + 1 deletions
   - Back   -> n - index deletions

   So:
   min_del_i = minimum deletions needed to remove the minimum alone
   min_del_j = minimum deletions needed to remove the maximum alone

3. We have three possible ways to remove both:
   - Remove the minimum first, then remove the maximum.
   - Remove the maximum first, then remove the minimum.
   - Remove both from the same side / remove the segment containing both.

4. dist = abs(i - j) represents the number of deletions needed
   to remove one element from the middle after removing the required
   elements from one side.

5. Take the minimum possible combination.

Time Complexity: O(n)
Space Complexity: O(1)
*/

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int i = 0; //min element
        int j = 0; //max element
        
        int n =  nums.size();
        for(int k = 0;k<n;k++){
            if(nums[i]>nums[k]) i = k;
            else if(nums[j]<nums[k]) j = k;
        }
        int min_del_i = min(i-0+1,n-i);
        int min_del_j = min(j-0+1,n-j);
        int dist = abs(j-i);

        if(min_del_i>min_del_j){
            return min_del_j + min(min_del_i,dist);
        }else if(min_del_i<min_del_j){
            return min_del_i + min(min_del_j,dist);
        }

        return min_del_j + min(min_del_j,dist);
    }
};


/*
Approach 2: Consider the 3 possible ways to remove both elements.

Let:
    l = min(index of minimum, index of maximum)
    r = max(index of minimum, index of maximum)

There are only 3 possibilities:

1. Remove both from the FRONT:
   We need to remove everything up to r.
   Cost = r + 1

2. Remove both from the BACK:
   We need to remove everything from l to the end.
   Cost = n - l

3. Remove one from the FRONT and the other from the BACK:
   - Remove elements up to l from the front -> l + 1
   - Remove elements from r to the end -> n - r
   Cost = (l + 1) + (n - r)

Therefore, the answer is simply the minimum of these 3 cases.

Time Complexity: O(n)
Space Complexity: O(1)

This approach is simpler because it directly models all possible
ways of deleting the minimum and maximum.
*/

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int i = 0; //min element
        int j = 0; //max element
        
        int n =  nums.size();
        for(int k = 0;k<n;k++){
            if(nums[i]>nums[k]) i = k;
            else if(nums[j]<nums[k]) j = k;
        }
        int l = min(i,j);
        int r = max(i,j);
        int case1 = r+1;
        int case2 = n-l;
        int case3 = n-r + l+1;

        return min({case1,case2,case3});
    }
};