/*
Approach:
My initial idea was to model the board as a graph and solve it using Dijkstra's Algorithm with a max heap. While this correctly computed the maximum score reaching each cell, it became difficult to keep track of the number of maximum-score paths.

If the same cell was reached again with an identical maximum score, it still had to be processed since it could contribute additional optimal paths to future cells. As a result, the same state kept getting pushed into the priority queue, making the bookkeeping increasingly complicated and eventually leading to TLE.

I then explored whether this could be fixed by maintaining a separate 2D count array, but managing the path counts within Dijkstra still felt unnecessarily complex.

After realizing that the problem is fundamentally a Dynamic Programming problem, I switched to a DP approach. I processed the board from the destination back to the start while maintaining two DP tables:
1. maxSum[i][j] -> Maximum score obtainable from that cell.
2. count[i][j]  -> Number of paths achieving that maximum score.

For each cell, I considered the three possible moves, selected the maximum achievable score, and accumulated the counts whenever multiple moves produced the same maximum score.

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/


class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int r = board.size();
        int c = board[0].size();
            int mod = 1e9 + 7;
        vector<vector<int>> maxSum(r, vector<int>(c, -1));
        // 2d vector to store maxsum at that position in board

         vector<vector<int>> directions{{0, 1}, {1, 0}, {1, 1}};

        vector<vector<int>> count(r, vector<int>(c, 0)); // to count how many max sums reach here
        count[r-1][c-1] = 1;
        maxSum[r-1][c-1] =0;

        for(int i = r-1;i>=0;i--){
            for(int j = c-1;j>=0;j--){
                if(board[i][j] == 'X' || (i==r-1 && j==c-1)) continue;
                int currSum = -1;
                int cnt = 0;

                int currCellVal = board[i][j]=='E'? 0 : board[i][j] - '0';
                
                for(auto& dir:directions){
                    int x = i + dir[0];
                    int y = j + dir[1];

                    if(x<r && y<c && maxSum[x][y]!=-1){

                        if(board[x][y]=='X') continue;

                        if(currSum < maxSum[x][y] + currCellVal){
                              currSum = maxSum[x][y] + currCellVal;
                              cnt = count[x][y];
                        }else if(currSum == maxSum[x][y] + currCellVal){
                              cnt = (cnt + count[x][y] )%mod;
                        }
                    }

                    
                }

                if(currSum!=-1){ 
                    maxSum[i][j] = currSum;
                    count[i][j] = cnt;
                }

            }
        }
        if(maxSum[0][0]==-1) return {0,0};
        return {maxSum[0][0],count[0][0]};
    }
};