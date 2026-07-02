/*
Approach:

1. My first instinct was to solve the problem using a simple BFS on the grid.
   However, I quickly realized that using a normal visited array was incorrect.
   A cell could later be reached with a lower health cost, so marking it visited
   the first time would discard potentially better paths.

2. I then considered a greedy approach where I would always move to the
   neighboring cell with the lower immediate cost. After thinking through a few
   examples, I realized that this could also fail because a path that appears
   more expensive initially may eventually lead to a lower overall cost.

3. The key observation was that instead of tracking whether a cell had been
   visited, I should track the minimum health cost required to reach every cell.
   I maintain a 'price' matrix initialized with infinity. Whenever a better
   (lower-cost) path to a cell is found, I update its cost and push that cell
   back into the queue so the improvement can propagate further.

4. Since the same cell may be inserted into the queue multiple times, stale
   entries are possible. To avoid unnecessary processing, I store the current
   cost along with each queue entry and skip it if a better cost has already
   been recorded in the price matrix.

5. This is essentially a queue-based shortest path (SPFA-like) approach. A
   priority queue (Dijkstra's Algorithm) would provide a better worst-case time
   complexity for this problem since all edge weights are non-negative, but this
   solution demonstrates how the original BFS idea can be gradually refined into
   a correct shortest path algorithm.

Time Complexity: O((m × n)^2) in the worst case.
Space Complexity: O(m × n)

*/

class Solution {
public: 
    bool isSafe(int i ,int j, int m,int n){
        return i>=0 && j>=0 && i<m && j<n;
    }
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        
        vector<vector<int>> price(m,vector<int>(n,INT_MAX));

        //we can store the price in stack along with the pair i,j to ignore costlier entries
        
        queue<pair<pair<int,int>,int>> q;
        q.push({{0,0},grid[0][0]});
        price[0][0] =grid[0][0];

        vector<vector<int>> directions{{0,1},{0,-1},{-1,0},{1,0}};

        while(!q.empty()){
            auto [x,y] = q.front().first;
            int cost = q.front().second;
            q.pop();
            if(price[x][y]< cost) continue; //ignore this stale entry
            for(auto& dir:directions){
                int i = x + dir[0];
                int j = y + dir[1];
               
                if(isSafe(i,j,m,n) && price[x][y]+grid[i][j] < price[i][j] ){
                    //we have found a better way
                    //stack me tbhi jaoge jb better way doge
                    price[i][j] = price[x][y]+grid[i][j];
                    q.push({{i,j},price[i][j]}); 
                }
            }
        }

        return price[m-1][n-1]< health? true : false; 
    }
};