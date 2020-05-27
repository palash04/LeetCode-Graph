#include <bits/stdc++.h>
using namespace std;

#define inf INT_MAX

class Solution {
    int V;
    vector<vector<pair<int,int>>> adj;
public:
    void addEdge(int u,int v,int wt){
        adj[u].push_back(make_pair(v, wt));
    }
    
    int shortest(int src){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0,src});
        vector<int> dist(V,inf);
        dist[src] = 0;
        
        while (!pq.empty()){
            int u = pq.top().second;
            pq.pop();
            for (auto V : adj[u]){
                int v = V.first;
                int u_v_weight = V.second;
                if (dist[v] > dist[u] + u_v_weight){
                    dist[v] = dist[u] + u_v_weight;
                    pq.push({dist[v],v});
                }
            }
        }
        int maxTimeTaken = INT_MIN;
        
        for (int i=1;i<V;i++){
            if (dist[i] == inf){
                return -1;
            }
            if (dist[i] > maxTimeTaken){
                maxTimeTaken = dist[i];
            }
        }
        return maxTimeTaken;
    }
    
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        
        V = N+1;
        adj.resize(V);
        
        for (auto time : times){
            addEdge(time[0], time[1], time[2]);
        }
        return shortest(K);
    }
};
