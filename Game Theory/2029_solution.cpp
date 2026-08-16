/*
    LeetCode 2029 - Stone Game IX

    Approach: Mathematical Observation / Game Theory

    Key Observation:
    Only the remainder of each stone modulo 3 matters.
    So, count the stones having remainders 0, 1, and 2.

    Remainder 0 is special:
    - Choosing it does not change the current sum % 3.
    - It only consumes a turn, effectively changing the turn order.

    After analyzing the possible game states:

    1. If freq[0] is even:
       Alice wins iff both remainder 1 and remainder 2 stones exist.

    2. If freq[0] is odd:
       Alice wins iff the difference between the number of
       remainder 1 and remainder 2 stones is greater than 2.

    Therefore, the entire game can be decided using only
    the three frequencies.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int n = stones.size();

        int freq[3] = {0};//frequency of remainders
        for(int val:stones){
            freq[val%3]++;
        }

        if(freq[0]%2 ==0) return freq[1]>0 && freq[2]>0;
        else  return abs(freq[1]-freq[2]) > 2;
    }
};