/*
    LeetCode Daily Challenge - Day 31

    Problem    : 3518. Smallest Palindromic Rearrangement II
    Difficulty : Hard

    Approach:
    - Count the frequency of each character.
    - Store only half the frequency of each
      character since a palindrome is determined
      by its left half.
    - Determine the middle character (if any).
    - Greedily construct the left half of the
      palindrome in lexicographical order.
    - For every position, temporarily place a
      character and count the number of unique
      permutations possible for the remaining
      characters using combinatorics (nCr).
    - If the number of permutations is smaller
      than k, skip them; otherwise, fix the
      current character and continue.
    - Mirror the left half (and append the
      middle character if present) to obtain
      the final palindrome.

    Complexity:
    Time  : O(n)
    Space : O(n)
*/

class Solution {
public:
    typedef long long ll;
    long long nCr(int n,int r,int k){
        r = min(r,n-r);
        long long res = 1;
        for(int i = 1;i<=r;i++){
            res = res * (n-r+i)/i ;
            if(res>=k) return k;
        }
        return res;
    }
    long long getPermutations(int remPos,vector<int>& count,int k){
         ll ways = 1;
         for(int i = 0;i<26;i++){
            ways*= nCr(remPos,count[i],k);
            remPos-=count[i];
            if(ways>=k) return k;
         }
         return ways;
    }
    string smallestPalindrome(string s, int k) {
        int n = s.size();
        vector<int> count(26, 0);
        for (int i = 0; i < n; i++) {
            char ch = s[i];
            count[ch - 'a']++;
        }

        char mid = ' ';
        for (int i = 0; i < 26; i++) {
            if (count[i] % 2 != 0) {
                mid = 'a' + i;
            }
            // take half count
            count[i] = count[i] / 2;
        }

        int totalCount = 0;
        for (int cnt : count) totalCount += cnt;


        ll totalPermutations = getPermutations(n/2,count,k);
        if (k > totalPermutations) return "";

        // now i have to find the left string
        // i have count and i will check each index one by one
        string left(n / 2, ' ');
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < 26; j++) {
                if (count[j] == 0) continue;

                char ch = 'a' + j;
                // just temporarily
                count[j]--;
                int remPos = n/2 - i-1;
                ll ways = getPermutations(remPos,count,k);

                if (ways < k) {
                    k = k - ways; // we checked these many permutations
                    count[j]++;
                } else {
                    // we found it
                    left[i] = ch;
                    totalCount--;
                    break;
                }
            }
        }

        string ans;
        ans += left;

        if (mid != ' ') ans += mid;

        reverse(left.begin(), left.end());

        ans += left; // it is right now

        return ans;
    }
};