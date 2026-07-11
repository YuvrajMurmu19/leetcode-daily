/*
========================================
Approach 1: Single DFS (Optimized)
========================================

1. Build the adjacency list of the graph.
2. Perform a DFS for every unvisited connected component.
3. During DFS, compute:
   - Number of nodes in the component.
   - Total edge count (each undirected edge is counted twice).
4. Divide the edge count by 2 to obtain the actual number of edges.
5. A connected component is complete if:
      edges = nodes * (nodes - 1) / 2
6. Count every component satisfying this condition.

Time Complexity: O(V + E)
Space Complexity: O(V)
*/

class Solution {
public:
    pair<int,int> dfs(int curr,vector<vector<int>>& adj,vector<bool>& visited){
        visited[curr] = true;
        int nodes = 1;
        int edges = 0;
        for(int& nbr:adj[curr]){
            if(!visited[nbr]){
                auto [n,edge] = dfs(nbr,adj,visited);
                nodes += n;
                edges += edge;
            }
            edges++;
        }
        
        return {nodes,edges};
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for(auto& edge:edges){
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        //find and store the number of nodes in each component
        vector<bool> visited(n,false);
        int ans = 0;
        for(int i = 0;i<n;i++){
            if(!visited[i]){
                auto [sz,edges] = dfs(i,adj,visited);
                if(edges/2 == sz*(sz-1)/2) ans++;

            }
        }
     
        return ans;
    }
};





/*
========================================
Approach 2: Two DFS Traversals
========================================

1. Build the adjacency list of the graph.
2. Perform a DFS to find the size of every connected component.
3. Traverse each component again using another DFS.
4. For every node, verify that its degree is exactly
      (component_size - 1).
5. If every node satisfies the condition, the component is complete.

Time Complexity: O(V + E)
Space Complexity: O(V)
*/

class Solution {
public:
    int dfs(int curr,vector<vector<int>>& adj,vector<bool>& visited){
        visited[curr] = true;
        int cnt = 0;
        for(int& nbr:adj[curr]){
            if(!visited[nbr]){
                cnt+=dfs(nbr,adj,visited);
            }
        }
        cnt++;
        return cnt;
    }
    bool dfs(int curr,vector<vector<int>>& adj,vector<bool>& visited,int size){
        visited[curr] = true;
        int cnt = 0;
        bool ans = true;
        for(int& nbr:adj[curr]){
            if(!visited[nbr]){
               ans =dfs(nbr,adj,visited,size);
            }
            cnt++;
        }
        if(cnt<size-1) return false;
        return ans;
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for(auto& edge:edges){
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        //find and store the number of nodes in each component
        vector<int> component_size;
        vector<bool> visited(n,false);

        for(int i = 0;i<n;i++){
            if(!visited[i]){
                int sz = dfs(i,adj,visited);
                component_size.push_back(sz);
            }
        }
        fill(visited.begin(),visited.end(),false);
        int ans = 0;
        int it = 0;
        for(int i = 0;i<n;i++){
            if(!visited[i]){
                bool temp = dfs(i,adj,visited,component_size[it]);
                it++;
                if(temp) ans++;
            }
        }
        return ans;
    }
};