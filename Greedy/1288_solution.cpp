/*
    Initial Idea:
    - Compare every interval with all remaining intervals.
    - Mark covered intervals using a boolean array.
    - Works correctly but takes O(n²) time.

    Optimization:
    - After noticing the Sorting tag, I revisited the problem.
    - Sort the intervals and process them from left to right.
    - Since start points are already ordered, only the end point
      needs to be tracked.
    - If the current interval's end is <= the previous maximum end,
      it is covered.
    - Otherwise, update the active interval.

    Time Complexity: O(n log n)
    Space Complexity: O(1) (excluding sort)

*/

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        int totalRemoved = 0;

        sort(intervals.begin(), intervals.end());

        int i = 0;
        int x = intervals[i][0];//no need to worry about x as x is always smaller due to sorting
        int y = intervals[i][1];

        int j = 1;

        while(i<n && j<n){
           //a is guaranteed to be greater or equal to x
           int a = intervals[j][0];
           //so we need to worry about the end limit y
           //unless edge case encountered
           int b = intervals[j][1];

           if(y>=b){
             totalRemoved++;
           }else{
            // y < b
            //now switch
            //edge case
            //i ne sbko remove krdiya lekin j wala abb contain kr rha h i ko
            //i ko remove krdo
            if(x==a) totalRemoved++;

            i = j;
            x = intervals[i][0];
            y = intervals[i][1];
           }
             j++;
        }

        return n - totalRemoved;
    }
};



// class Solution {
// public:
//     int removeCoveredIntervals(vector<vector<int>>& intervals) {
//          int n = intervals.size();
//          int totalRemoved = 0;
//          vector<bool> removed(n,false);
//          for(int i = 0;i<n;i++){
//             if(removed[i]) continue;
//             int x = intervals[i][0];
//             int y = intervals[i][1];
//             for(int j = i+1;j<n;j++){

//                 if(removed[j]) continue;

//                   int a = intervals[j][0];
//                   int b = intervals[j][1];

//                   if(x<=a && y>=b){
//                      totalRemoved++;
//                      removed[j] = true;
//                   }else if(a<=x && b>=y){
//                     totalRemoved++;
//                     removed[i] = true;
//                     break; //because the original element is removed;
//                   }
//             }
//          }

//          return n-totalRemoved;
//     }
// };