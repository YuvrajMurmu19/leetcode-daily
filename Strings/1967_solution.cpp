
/*
Problem:
1967. Number of Strings That Appear as Substrings in Word

Difficulty:
Easy

Approach:
-Initially thought about generating every substring of the given word.
-That would require checking each substring against every pattern, leading to unnecessary work.
-Then realized C++'s string::find() directly checks whether a pattern exists inside the word.
-So I simply iterate over all patterns and count those for which find() doesn't return string::npos.

Time Complexity:
O(k x n × m) -- worst case
k -- number of patterns
m -- length of string word
n -- length of string p in patterns
Space Complexity:
O(1)
*/
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
       int ans = 0;
       for(const string& p:patterns){
        if(word.find(p)!=string::npos) ans++;
       }
       return ans;
    }
};