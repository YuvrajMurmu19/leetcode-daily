/*
Approach: Frequency Array + Greedy + Backtracking

1. Count the frequency of each character.
2. A palindrome is possible only if at most one character has an odd frequency.
3. Since the answer is a palindrome, construct only its left half.
   - half_freq[i] = freq[i] / 2
   - The odd-frequency character becomes the middle character.
4. Try to match the left half with the first half of target.
5. If the complete left half matches, construct the palindrome and check
   whether it is strictly greater than target.
6. Otherwise, backtrack from the right side:
   - Remove the last chosen character.
   - Find the smallest available character greater than target[i].
   - Once found, fill the remaining characters in sorted order.
   - Mirror the left half to construct the palindrome.
7. Return the first valid palindrome, which is the lexicographically smallest.

Key Idea:
Only the left half needs to be decided because the right half of a
palindrome is completely determined by reversing the left half.

Time: O(26 * n) = O(n)
Space: O(26) = O(1)
*/

class Solution {
public:
    bool palindromePossible(vector<int>& freq){
        bool f1 = false;
        for(int f:freq){
            if(f%2==1){
               if(f1) return false;
               else f1 = true;
            }
        }
        return true;
    }
    string solve(vector<int> freq,string& t,string& mid){
        string ans = "";
        int n = t.length();
        int i = 0;
        while(i<n/2){
            if(freq[t[i]-'a']>0){
                freq[t[i]-'a']--;
                ans.push_back(t[i]);
                i++;
            }else break;
        }
        
        
        if(i==n/2){
            string reversed(ans.rbegin(),ans.rend());
            string temp = ans + mid+reversed;
            if(temp>t) return temp;
            i--;
            // freq[ans.back()-'a']++;
            // ans.pop_back();
        }

        while(i>=0){
            if (i < ans.length()) {
            freq[ans.back() - 'a']++;
            ans.pop_back();
            }
            bool isGreater = false;
            string x= ans;
            for(int j = t[i]-'a'+1;j<26;j++){
                if(freq[j]>0){
                    ans.push_back(j+'a');
                    freq[j]--;
                    isGreater = true;
                    break;
                }
            }
            if(isGreater){
                for(int k = 0;k<26;k++){
                        while(freq[k]>0){
                            freq[k]--;
                            ans.push_back(k+'a');
                        }
                }
                string r(ans.rbegin(),ans.rend());
                string temp = ans + mid + r;
                if(temp>t) return temp;
            }
            ans = x;
            i--;
        }

        return "";
    }
    string lexPalindromicPermutation(string s, string target) {
        vector<int> freq(26,0);

        for(char ch:s){
            int idx = ch-'a';
            freq[idx]++;
        }

        if(!palindromePossible(freq)) return "";

        int n = s.length();
        
        vector<int> half_freq(26,0);
        string mid = "";
        for(int i = 0;i<26;i++){
            if(freq[i]%2==1){
                mid = 'a'+ i;
            }
            half_freq[i] = freq[i]/2;
        }
        int sz = n/2;
        string ans = solve(half_freq,target,mid);
        
        return ans;
    }
};