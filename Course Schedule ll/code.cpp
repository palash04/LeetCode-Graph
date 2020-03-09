#include <bits/stdc++.h>
using namespace std;

class Solution{
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> recVisited;
    vector<int> indegree;
public:
    void addEdge(int u,int v){
        adj[u].push_back(v);
    }
    
    bool checkCycle(int u){
        stack<int> st;
        st.push(u);
        
        while (!st.empty()){
            u = st.top();
            if (!visited[u]){
                visited[u] = true;
                recVisited[u] = true;
            }
            bool isAnyNodeLeft = false;
            for (auto v=adj[u].begin(); v!=adj[u].end(); v++){
                if ( recVisited[*v]){
                    return true;
                }
                if (!visited[*v]){
                    isAnyNodeLeft = true;
                    st.push(*v);
                    break;
                }
            }
            if (!isAnyNodeLeft){
                st.pop();
                recVisited[u] = false;
            }
        }
        return false;
    }
    
    void topoOrder(vector<int> &res){
        vector<int> v;
        for (int i=0;i<indegree.size();i++){
            if (!indegree[i]){
                v.push_back(i);
            }
        }
        
        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<>> pq;
        for (auto x : v) pq.push({0,x});
        
        while (!pq.empty()){
            int u = pq.top().second;
            pq.pop();
            res.push_back(u);
            for (auto v=adj[u].begin(); v!=adj[u].end(); v++){
                indegree[*v]--;
                if (indegree[*v] == 0) {
                    pq.push({indegree[*v],*v});
                }
            }
        }
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        adj.resize(numCourses);
        visited.resize(numCourses,false);
        recVisited.resize(numCourses,false);
        indegree.resize(numCourses,0);
        for (int i=0;i<prerequisites.size();i++){
            int u = prerequisites[i][1];
            int v = prerequisites[i][0];
            if (u == v) continue;
            indegree[v]++;
            addEdge(u, v);
        }
        
        for (int i=0;i<numCourses;i++){
            if (!visited[i]){
                if (checkCycle(i)){
                    //cout << "Cycle exists\n";
                    return res;
                }
            }
        }
        
        topoOrder(res);
        //cout << "Cycle does not exists\n";
        return res;
    }
};
