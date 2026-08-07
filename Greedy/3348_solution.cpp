
/*
    LeetCode 3348: Smallest Divisible Digit Product II
    Difficulty: Hard

    Approach: Prime Factorization + Greedy Construction

    Key Observation:
    - Every digit from 1 to 9 can only contribute the prime factors:
      2, 3, 5, and 7.
    - Therefore, if t contains any prime factor other than
      2, 3, 5, or 7, no answer is possible.

    Step 1: Check whether t is achievable
    - Remove all factors of 2, 3, 5, and 7 from t.
    - If anything remains, return "-1".

    Step 2: Track remaining requirements
    - remainingFactor[i] represents the part of t that is still
      required after using the first i digits of num.
    - For every digit:
        remaining = remaining / gcd(remaining, digit)
      This removes the prime factors already provided by that digit.

    Step 3: Check num itself
    - If remainingFactor[n] == 1, num is already a valid answer.

    Step 4: Construct the smallest larger number
    - Start from the rightmost possible position and move left.
    - Try replacing the current digit with the smallest larger digit.
    - Calculate the factors still required after choosing that digit.
    - Fill the remaining positions with the smallest possible
      digits whose product provides all required factors.
    - The first valid construction is the smallest number >= num.

    Helper: freeSlotsFiller()
    - Factor the required value using digits 9 down to 2.
    - This gives the minimum number of digits needed to satisfy
      the required prime factors.
    - Remaining positions are filled with '1'.
    - Reverse the result to obtain the smallest possible number.

    Why greedy works:
    - We try changing the rightmost possible position first.
    - At each position, we try digits in increasing order.
    - Once a valid suffix can be constructed, it gives the
      lexicographically smallest number of that length.

    Time Complexity: O(n)
        - We scan the string a constant number of times.
        - Only digits 2 to 9 are checked in the construction.

    Space Complexity: O(n)
        - remainingFactor array and temporary strings.
*/


class Solution {
public:
    typedef long long ll;
    string freeSlotsFiller(ll required,int length){
        string str;

        for(int digit = 9;digit>=2;digit--){
           while(required%digit == 0){
            str.push_back(digit+'0');
            required/=digit;
           }
        }

        while(str.length()<length) str.push_back('1');

        reverse(begin(str),end(str));
        return str;
    }
    string smallestNumber(string num, long long t) {
        int n =  num.length();
        vector<int> prime_factors = {2,3,5,7};
        ll rem = t;
        for(int factor:prime_factors){
            while(rem%factor==0) {
                rem/=factor;
            }
        }
        //its factor is greater than 9
        //since the product of digits of nums will always be
        //of 1 to 9
        //no product will ever be divisible by t
        if(rem!=1) return "-1";

        //precompute remainig factors for i digits 
        vector<ll> remainingFactor(n+1,t);
        //remainingFactor[i] -- remainingFactor when i digits are taken from the start
        for(int i = 0;i<n;i++){
            int digit = num[i]-'0';
            
            //if the current digit is zero then changing starts from here
            if(digit==0) break;

            remainingFactor[i+1] = remainingFactor[i]/gcd(remainingFactor[i],(ll)digit);
        }
        if(remainingFactor[n] == 1){
            //meaning that when all of the length is taken then factor is 1 that is completely divisible by t
            return num;
        }

        //find first occurence of zero
        int zeroPos = num.find('0');
        int zeroIdx = n-1;
        if(zeroPos!=-1) zeroIdx = zeroPos;

        for(int i = zeroIdx;i>=0;i--){
            ll required = remainingFactor[i];
            int freeSlots = n-1-i;

            for(int digit = (num[i]-'0')+1;digit<=9;digit++){
                ll furtherRequired = required/gcd(required,digit);
                string requiredNumber = freeSlotsFiller(furtherRequired,freeSlots);

                if(requiredNumber.length() == freeSlots){
                    return num.substr(0,i) + char(digit + '0') + requiredNumber;
                }
            }
        }


        return freeSlotsFiller(t,n+1);;
    }
};