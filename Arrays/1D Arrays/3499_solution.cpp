/*
    Approach:
    - Traverse the string and process it block by block.
    - For every contiguous block of '1's, count the total number of active sections.
    - Keep track of the lengths of the zero block immediately before and after each one block.
    - If both neighbouring zero blocks exist, trading the current one block allows them to merge,
      giving a gain equal to the sum of their lengths.
    - Compute this gain for every valid one block and return the original number of active
      sections plus the maximum gain.

    T.C. : O(n)
    S.C. : O(1)
*/
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.length();

        int numOfOnes = 0;
        int maxGain = 0;
        int leftZero = 0;
        int rightZero= 0;
       
        int i = 0;
        while(i<n) {
            leftZero = rightZero;
            while(i<n && s[i] == '0'){
                leftZero++;
                i++;
            }

            while(i<n && s[i]=='1'){
                numOfOnes++;
                i++;
            }

            rightZero = 0;
            while(i<n && s[i]=='0'){
                rightZero++;
                i++;
            }

            if(leftZero!=0 && rightZero!=0){
                int gain = leftZero + rightZero;
                maxGain = max(maxGain,gain);
            }
            
        }
        return numOfOnes + maxGain;
    }
};
