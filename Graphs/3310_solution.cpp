/*
    Approach: DFS + Reachability Validation

    Idea:
    - Build a directed graph where an edge a -> b means
      method 'a' invokes method 'b'.
    - Perform DFS starting from the buggy method 'k'
      to mark every reachable method as suspicious.
    - After identifying the suspicious group, check whether
      any non-suspicious method invokes a suspicious method.
    - If such an edge exists, the suspicious group cannot
      be removed, so return all methods.
    - Otherwise, return only the non-suspicious methods.

    Time Complexity: O(n + m)
        - O(m) to build the graph.
        - O(n + m) for DFS traversal.
        - O(n + m) to validate incoming edges
          from non-suspicious methods.

    Space Complexity: O(n + m)
        - O(n) for visited and suspicious arrays.
        - O(m) for the adjacency list.
        - O(n) recursion stack in the worst case.
*/

class Solution {
public:
    void bfs(int curr,vector<vector<int>>& adj,vector<bool>& visited,vector<bool>& suspicious){
        queue<int> q;
        q.push(curr);
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(int nbr:adj[node]){
                if(!visited[nbr]){
                    suspicious[nbr] = true;
                    visited[nbr] = true;
                    q.push(nbr);
                }
            }
        }
        return;
    }
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for(auto inv:invocations){
            int a = inv[0];
            int b = inv[1];
            adj[a].push_back(b);//method a invokes method b
        }
        vector<bool> visited(n,false);
        vector<bool> suspicious(n,false);
        suspicious[k] = true;
        visited[k] = true;
        bfs(k,adj,visited,suspicious);
        bool invoked_from_outside = false;

        for(int i = 0;i<n;i++){
            if(!visited[i] ){
                //has not been visited by k
                //it is not suspicious
                //if any of its children are suspicious 
                //then it invokes methods in the suspicious group
                //hence none will be removed
                for(int node:adj[i]){
                    if(suspicious[node]) {
                        invoked_from_outside = true;
                        break;
                    }
                }
                
            }
            if(invoked_from_outside) break;
        }
        if(invoked_from_outside){
            vector<int> ans;
            for(int i = 0;i<n;i++){
                ans.push_back(i);
            }
            return ans;
        }
    
        
        vector<int> ans;
        for(int i = 0;i<n;i++){
            if(!suspicious[i]) ans.push_back(i);
        }

        return ans;
    }
};