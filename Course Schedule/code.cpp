/*
Author: Palash Kamble
Solution on leetcode: 
  Runtime: 12 ms, faster than 99.81% of cpp submissions for Course Schedule
  Memory Usage: 15 MB, less than 32.73% of cpp submissions for Course Schedule
*/
#include <bits/stdc++.h>
using namespace std;

class Solution{
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> recVisited;
public:
    void addEdge(int u,int v){
        adj[u].push_back(v);
    }
    
    bool checkCycle(int u,vector<bool> &visited,vector<bool> &recVisited){
        stack<int> st;
        st.push(u);
        
        while (!st.empty()){
            u = st.top();
            
            if (!visited[u]){
                visited[u] = true;
                recVisited[u] = true;
            }
            bool isAnyChildrenNotVisited = false;
            for (auto v=adj[u].begin(); v!=adj[u].end(); v++){
                if (recVisited[*v]){
                    return true;
                }
                if (!visited[*v]){
                    isAnyChildrenNotVisited = true;
                    st.push(*v);
                    break;
                }
            }
            if (!isAnyChildrenNotVisited){
                st.pop();
                recVisited[u] = false;
            }
        }
        return false;
    }
    
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites){
        adj.resize(numCourses);
        visited.resize(numCourses);
        recVisited.resize(numCourses);
        
        for (auto x : prerequisites){
            addEdge(x[0], x[1]);
        }
        
        for (int i=0;i<numCourses;i++){
            if (!visited[i]){
                if(checkCycle(i,visited,recVisited)){
                    return false;
                }
            }
        }
        return true;
    }
    
};
