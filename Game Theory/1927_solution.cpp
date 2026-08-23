/*
    Problem: 1927. Sum Game
    Topic: Game Theory / Case Analysis

    Approach:
    Initially, I had no clear idea how to solve this problem.
    I went through the hints and discussion section to understand
    the key observations, and then used multiple dry runs to
    understand all possible cases and edge cases.

    Step 1:
    Calculate the digit sum and number of '?' in both halves.

    Step 2:
    If there are no '?' characters, simply compare the two sums.
    Alice wins if the sums are different.

    Step 3:
    If the total number of '?' is odd, Alice always wins because
    she gets one more turn.

    Step 4:
    If the total number of '?' is even:
        - If the existing sums are equal, Bob wins only when both
          halves contain the same number of '?'.
        - Otherwise, the side with the larger sum is considered.
          We check whether the difference in sums can exactly be
          compensated by Bob's available '?' moves.

    Important Observation:
    When the difference between the two sums is not divisible by 9,
    Alice can always force a win.

    If it is divisible by 9, we compare:
        difference / 9
    with
        difference in the number of '?' / 2

    If they are exactly equal, Bob can balance the sums and win.
    Otherwise, Alice wins.

    Key Learning:
    I initially had no idea how to approach this problem.
    Hints and discussions helped me understand the underlying
    observations, but I still had to do many dry runs and break
    the problem into smaller cases and subcases.

    This problem reinforced an important problem-solving habit:
    Instead of trying to solve a complicated problem all at once,
    break it into smaller, simpler cases and understand each case
    separately.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

class Solution {
public:
    bool solve(int s1,int s2,int q1,int q2){ 
        //function assumes s1>s2
        if(q1>q2 || q1==q2) return true;

        //q1<q2
        int diff = s1-s2;
        if(diff%9==0){
            int rem = q2-q1;
            if(rem/2 == diff/9) return false;

            else return true;
        }
        //not divisible so alice wins always
        return true;
    }
    bool sumGame(string num) {
        int s1 = 0;
        int q1 = 0;
        int n = num.length();
        for(int i = 0;i<n/2;i++){
            if(num[i]=='?') q1++;
            else {
                int number = num[i]-'0';
                s1+=number;
            }
        }
        int s2 =  0;
        int q2 = 0;
        for(int i = n/2;i<n;i++){
            if(num[i]=='?') q2++;
            else {
                int number = num[i]-'0';
                s2+=number;
            }
        }
        if(q1==0 && q2 ==0) return !(s1==s2); //bob wins if both equal

        int Q = q1 + q2;
        if(Q%2==1) {
            //alice always gets one more chance
            return true;
        }
        //else case -- number of ? is even -- 
        
        if(s1==s2) return !(q1==q2);//bob wins

        return s1>s2?solve(s1,s2,q1,q2):solve(s2,s1,q2,q1);
    }
};

