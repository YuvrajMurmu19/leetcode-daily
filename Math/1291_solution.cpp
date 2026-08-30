/*
Approach:
- My initial solution checked every number from low to high to see if its digits
  formed a sequential pattern, but it resulted in TLE.
- After trying a few other ideas and understanding the official hint, I realized
  that there are only a fixed number of valid sequential-digit numbers.
- Starting from each digit (1 to 9), I build numbers by appending consecutive
  digits (e.g., 1 -> 12 -> 123 -> 1234).
- Whenever a generated number lies within [low, high], I add it to the answer.
- Finally, I sort the result before returning it.

Time Complexity: O(1)
Space Complexity: O(1) (excluding the output array)
*/

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        vector<int> check{1,2,3,4,5,6,7,8,9};
        int n = check.size();
        for(int i = 0;i<n;i++){
            int num = check[i];
            for(int j = i+1;j<n;j++){
                num = num *10 + check[j];
                if(num>=low && num<=high) ans.push_back(num);
            }
        }
        sort(ans.begin(),ans.end());

        return ans;
    }
};