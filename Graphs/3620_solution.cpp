/*
Approach:

1. My first idea was to solve the problem using DFS.

   Since the graph is a Directed Acyclic Graph (DAG), I assumed that a
   visited array wasn't necessary because there are no cycles. During DFS,
   I tracked the total path cost and the minimum edge weight (bottleneck)
   along the current path, updating the answer whenever I reached the
   destination within the budget.

2. Although correct, this approach was inefficient. A DAG can still have
   an exponential number of distinct paths, so DFS ends up exploring almost
   every valid path, resulting in exponential time complexity.

3. I then realized that the problem has a monotonic property, making it
   suitable for Binary Search on the answer.

   Instead of directly finding the maximum bottleneck value, I binary search
   on a candidate value 'mid', treating it as the minimum edge weight that
   every edge in the chosen path must satisfy.

4. For each 'mid':
   - Ignore all edges with weight < mid.
   - Run Dijkstra's Algorithm on the remaining graph.
   - If the shortest path from node 0 to node n-1 has total cost <= k,
     then 'mid' is feasible, so we try a larger value.
   - Otherwise, we reduce the search space.

5. This transforms the original optimization problem into a sequence of
   shortest-path feasibility checks, giving an efficient solution.

Time Complexity:
- Dijkstra: O(E log V)
- Binary Search: O(log W), where W is the range of edge weights.
- Overall: O(E log V * log W)

Space Complexity:
O(V + E)
*/

class Solution {
public:
    bool valid_dijkstra(vector<vector<pair<int,int>>>& adj,vector<bool>& online, long long k,int mid){
        //i just have to check whether a path exists or not using the given minimum edge weight of mid

        priority_queue<pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>> > pq; // i am declaring a min heap**

        pq.push({0,0});
        int n = online.size();
        vector<long long> total_dist(n,LLONG_MAX);
        total_dist[0] = 0;
        while(!pq.empty()){
            auto [d,node] =pq.top();
            pq.pop();

            if(node == n-1) return true;

            //remove stale entries
            if(d>total_dist[node]) continue;

            for(auto& nbr:adj[node]){
                int next = nbr.first;
                int w = nbr.second;
                //we wont consider the edge weight less than the given weight 'mid'
                if(w<mid || !online[next]) continue;
                long long temp = (long long) d + w;
                if(temp <= k && temp<total_dist[next]){
                    total_dist[next] = temp;
                    pq.push({temp,next});
                }

            }
        }
        return false;

    }
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        vector<vector<pair<int,int>>> adj(n);
        int low = INT_MAX;
        int high = INT_MIN;

        for(auto& edge:edges){
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            low = min(w,low);
            high = max(w,high);
            //u -> v
            adj[u].push_back({v,w});
        }
        int ans = -1;
        while(low<=high){
            int mid = low + (high - low)/2;

            if(valid_dijkstra(adj,online,k,mid)){
               ans = mid;
               low = mid+1;
            }else{
                high = mid-1;
            }
        }

        return ans;
    }
};