/*
Approach:

The key observation comes from the statement that we can visit the same
road and the same city multiple times.

This means we are not restricted to following a single simple path from
city 1 to city n. Once both cities belong to the same connected component,
we are free to traverse any road within that component before reaching the
destination.

Therefore, the minimum possible score is simply the minimum edge weight
present in the connected component containing city 1.

Algorithm:

1. Build the adjacency list.
2. Perform a BFS starting from city 1.
3. Traverse every reachable node.
4. For every edge encountered, update the answer with the minimum edge
   weight seen so far.
5. Return the minimum edge weight.

Time Complexity: O(V + E)
Space Complexity: O(V + E)
*/

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // since i can visit the same road multiple times and can visit cities
        // btw 1 and n multiple times hence the minimum possible score will be
        // the edge containing the minimum edge weight when 1 and n are
        // connected
        // so i will explore all edges in the graph from 1 to n

        vector<vector<pair<int, int>>> adj(n+1);

        for (auto& road : roads) {
            int a = road[0];
            int b = road[1];
            int dist = road[2];
            // road is bidirectional

            adj[a].push_back({b, dist});
            adj[b].push_back({a, dist});
        }

        vector<bool> visited(n+1,false);

        queue<int> q;
        q.push(1);
        visited[1] = true;

        int ans = INT_MAX;
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for(auto& nbr:adj[node]){
                int next = nbr.first;
                int dist = nbr.second;
                ans = min(ans,dist);
                if(!visited[next]){
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        return ans;
    }
};