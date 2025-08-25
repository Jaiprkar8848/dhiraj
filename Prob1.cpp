#include<bits/stdc++.h>
using namespace std;

#ifdef VARM
void generateGraph(int N, vector<pair<int,int>>&edges){
    srand(time(NULL));
    int minm = 2*N;
    int maxm = (N*(N-1))/2;
    int M = minm + rand()%(maxm-minm+1);

    set<pair<int,int>> st;
    int i=0;
    while(i<M){
        int u = rand()%N;
        int v = rand()%N;
        if(u!=v && st.find({u,v})==st.end() && st.find({v,u})==st.end()){
            st.insert({u,v});
            edges.push_back({u,v});
            i++;
        }
    }
}
#endif

#ifdef VARN
void generateGraph(int N, vector<pair<int,int>>&edges){
    srand(time(NULL));
    cout<<N<<endl;
    int M = 2*N;
    #ifdef nlogn
    M = log10(N);
    #endif
    #ifdef nsqrtn
    M = N*sqrt(N);
    #endif
    #ifdef nc2
    M = N*(N-1)/2;
    #endif

    set<pair<int,int>> st;
    int i=0;
    while(i<M){
        int u = rand()%N;
        int v = rand()%N;
        if(u!=v && st.find({u,v})==st.end() && st.find({v,u})==st.end()){
            st.insert({u,v});
            edges.push_back({u,v});
            i++;
        }
    }
}
#endif

#ifdef DFS
void dfs(vector<vector<int>>&adj){
    int n = adj.size();
    vector<int> visited(n,0);
    stack<int> st;
    st.push(0);
    while(!st.empty()){
        int node = st.top();
        st.pop();
        visited[node] = 1;
        for(auto adjNode : adj[node]){
            if(visited[adjNode]==0){
                st.push(adjNode);
            }
        }
    }
}
#endif
#ifdef BFS
void bfs(vector<vector<int>>&adj){
    int n = adj.size();
    vector<int> visited(n,0);
    queue<int> q;
    q.push(0);
    visited[0]=1;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto adjNode: adj[node]){
            if(visited[adjNode]==0){
                visited[adjNode] = 1;
                q.push(adjNode);
            }
        }
    }
}
#endif
#ifdef REC_DFS
void recDFS(int node, vector<int>&visited, vector<vector<int>>&adj){
    visited[node] = 1;
    for(auto adjNode : adj[node]){
        if(visited[adjNode]==0){
            recDFS(adjNode, visited, adj);
        }
    }
}
#endif 

int main(int argc, char *argv[]){
    if(argc<2){
        cout<<"Invalid number of arguments in the main file!"<<endl;
        return 0;
    }
    int N = atoi(argv[1]);
    vector<pair<int,int>> edges;
    
    //generates random graph
    generateGraph(N,edges);

    //creates adj matrix for undirected unweighted graph
    vector<vector<int>>adj(N);
    for(int i=0;i<edges.size();i++){
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> visited(N,0);

    #ifdef BFS 
    bfs(adj);
    #endif
    #ifdef DFS
    dfs(adj);
    #endif
    #ifdef REC_DFS
    recDFS(0,visited,adj);
    #endif
    return 0;
}