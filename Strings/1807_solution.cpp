/*
    Approach:
    ---------
    1. Store all key-value pairs from `knowledge` in an unordered_map.
       This allows average O(1) lookup for each key.

    2. Traverse the string using index `i`.

    3. If s[i] == '(':
       - Move past '('.
       - Find the corresponding ')' using another pointer `j`.
       - Extract the key using:
             s.substr(i, j - i)
       - Search for the key in the hashmap.
       - If the key exists, append its value to the answer.
       - Otherwise, append '?'.
       - Move `i` directly after ')'.

    4. If s[i] != '(':
       - It is a normal character, so directly append it to the answer.

    Why this works:
    ---------------
    Every bracket pair is independent and there are no nested brackets.
    Therefore, whenever we encounter '(', we can directly find the next ')',
    evaluate the key, and skip the entire bracket pair.

    Time Complexity:
    ----------------
    O(N + K)
    - N = length of string `s`
    - K = total size of `knowledge`
    - Each character is processed a constant number of times.
    - Hashmap lookup is O(1) on average.

    Space Complexity:
    -----------------
    O(K)
    - Hashmap stores all key-value pairs.
    - `ans` requires O(N) output space.

    Key Idea:
    ---------
    Hashmap + Two-Pointer/String Traversal
*/

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> val;

        for (vector<string> t : knowledge) {
            string key = t[0];
            string value = t[1];

            val[key] = value;
        }

        int n = s.length();
        int i = 0;

        string ans;
        while (i < n) {
            if(s[i]=='('){
                i++;
                int j = i;
                while(s[j]!=')'){
                    j++;
                }
                
                string key = s.substr(i,j-i);
                auto v = val.find(key);

                if(v!=val.end()) ans.append(val[key]);
                else ans.push_back('?');

                i = j+ 1;
            }
            else{
               ans.push_back(s[i]);
               i++;
            }
        }

        return ans;
    }
};