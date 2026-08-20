// Approach: Simulation
// Maintain two arrays and follow the given distribution rules.
// nums[0] -> arr1, nums[1] -> arr2.
// For each remaining element:
//   - If the last element of arr1 is greater than arr2, add to arr1.
//   - Otherwise, add to arr2.
// Finally, concatenate arr2 to arr1.
//
// Time Complexity: O(n)
// Space Complexity: O(n)

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr1;
        vector<int> arr2;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        
        for(int i =2 ;i<n;i++){
            if(arr1.back()>arr2.back()){
                arr1.push_back(nums[i]);
            }else arr2.push_back(nums[i]);
        }

        arr1.insert(arr1.end(),arr2.begin(),arr2.end());

        return arr1;

    }
};