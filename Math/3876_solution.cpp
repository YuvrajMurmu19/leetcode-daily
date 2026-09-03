// APPROACH:
// 1. Find the minimum element in the array.
// 2. If the minimum element is odd, every element can be made odd:
//    - Odd elements can remain unchanged.
//    - Even elements can subtract the odd minimum -> Even - Odd = Odd.
// 3. If the minimum element is even, an odd element cannot become even:
//    - Odd - Even = Odd.
//    - Therefore, all elements must already be even.
// 4. Hence, if minimum is odd return true; otherwise, return true only if
//    there is no odd element in the array.
//
// TIME: O(n)
// SPACE: O(1)

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mini = *min_element(nums1.begin(),nums1.end());

        if(mini%2==1) return true;
        
        //minimum element was even
        for(int num:nums1){
            if(num%2==1) return false;
        }

        return true;
       
    }
};