/*
LeetCode 2996 - Smallest Missing Integer Greater Than Sequential Prefix Sum

Approach 1: Linear Search using find()

Idea:
- Find the longest sequential prefix of the array.
- Calculate the sum of this prefix.
- Starting from the prefix sum, find the smallest integer
  that is missing from nums using find().

Steps:
1. Start with nums[0] as the initial prefix sum.
2. Continue while nums[i] == nums[i-1] + 1.
3. Once the sequence breaks, we have the longest sequential prefix.
4. Starting from maxSum, check each integer using find().
5. Return the first integer that is not present in nums.

Why maxSum > 50 can be returned directly:
- nums[i] <= 50.
- Therefore, any value greater than 50 cannot exist in nums.
- So if maxSum > 50, maxSum itself is the answer.

Time Complexity:
- Finding sequential prefix: O(n)
- Each find(): O(n)
- At most O(n) values are checked
- Overall: O(n^2)

Space Complexity: O(1)
*/

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        int maxSum = 0;
        int temp = nums[0];
        for(int i = 1;i<n;i++){
           if(nums[i]!= nums[i-1]+1){
               maxSum = temp;
               temp = 0;
               break;
            }else{
                temp+= nums[i];
            }
        }
        if(temp!= 0) maxSum = temp;

        if(maxSum>50) return maxSum;

        for(int i = maxSum;i<=51;i++){
            if(find(nums.begin(),nums.end(),i)==nums.end()){
                return i;
            }
        }
        
        return -1;

    }
};

/*
LeetCode 2996 - Smallest Missing Integer Greater Than Sequential Prefix Sum

Approach 2: Using unordered_set

Idea:
- Find the longest sequential prefix and calculate its sum.
- Store all elements of nums in an unordered_set.
- Starting from the prefix sum, find the first integer
  that is not present in the set.

Steps:
1. Find the longest sequential prefix and calculate maxSum.
2. Insert all elements of nums into an unordered_set.
3. Starting from maxSum, check:
      if(s.count(i) == 0)
   then i is the smallest missing integer.
4. Return i.

Why maxSum > 50 can be returned directly:
- nums[i] <= 50.
- Hence any value greater than 50 is guaranteed to be missing.
- Therefore, maxSum is the answer if maxSum > 50.

Time Complexity:
- Finding sequential prefix: O(n)
- Building the set: O(n) average
- Searching for the answer: O(n) average
- Overall: O(n) average

Space Complexity: O(n)
*/

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        int maxSum = 0;
        int temp = nums[0];
        for(int i = 1;i<n;i++){
           if(nums[i]!= nums[i-1]+1){
               maxSum = temp;
               temp = 0;
               break;
            }else{
                temp+= nums[i];
            }
        }
        if(temp!= 0) maxSum = temp;

        if(maxSum>50) return maxSum;

        unordered_set<int> s;
        for(int num:nums){
            s.insert(num);
        }

        for(int i = maxSum;i<=51;i++){
            if(s.count(i) == 0){
                return i;
            }
        }
        
        return -1;

    }
};