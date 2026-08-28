/*
    LeetCode 3718 - Smallest Missing Multiple of K

    Approach:
    - Sort the array so that the multiples of k can be checked in order.
    - `it` represents the multiplier of k that we are currently looking for.
      So, the current required multiple is `it * k`.
    - Traverse the sorted array:
        - If num == it * k, this multiple exists in the array,
          so move to the next multiple by incrementing `it`.
        - Otherwise, ignore the current number.
    - After the traversal, `it * k` is the smallest positive multiple
      of k that is missing from the array.

    Example:
        nums = [8,2,3,4,6], k = 2

        Sorted: [2,3,4,6,8]

        Check multiples:
        2  -> present
        4  -> present
        6  -> present
        8  -> present
        10 -> missing

        Answer = 10

    Complexity:
        Time  : O(n log n)  -> sorting
        Space : O(1) extra space (ignoring sorting implementation)

    Key Idea:
        We only care about the positive multiples of k.
        By checking them in increasing order, the first one we don't
        encounter is automatically the smallest missing multiple.
*/


class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int it = 1;
        for(int num:nums){
            if(num == it*k)it++;
        }

        return it*k;
    }
};