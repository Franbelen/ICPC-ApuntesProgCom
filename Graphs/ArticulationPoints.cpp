#include "../Header.cpp"

int disc[100000];
int low[100000];
int visited[100000];
int parent[100000];
int AP[100000];
vector <vector <int> > adj;

int timee = 0;

void DFS(int vertex, int V){
    int child;
    visited[vertex] = true;
    disc[vertex] = low[vertex] = ++timee;
    child = 0;
    rep(i, adj[vertex].size())
    {
        if (visited[adj[vertex][i]] == false){
            child++;
            parent[adj[vertex][i]] = vertex;
            DFS(adj[vertex][i], V);
            low[vertex] = min(low[vertex], low[adj[vertex][i]]);
            if (parent[vertex] == -1 && child > 1){
                AP[vertex] = true;
            }
            if (parent[vertex] != -1 && low[adj[vertex][i]] >= disc[vertex]){
                AP[vertex] = true;
            }
        }
        else if (adj[vertex][i] != parent[vertex]){
            low[vertex] = min(low[vertex], disc[adj[vertex][i]]);
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    while (n != 0 && m !=0){
        timee = 0;
        rep(i, n){
            adj.push_back(vector <int> ());
            disc[i] = 0;
            low[i] = 0;
            visited[i] = false;
            parent[i] = -1;
            AP[i] = false;
        }
        rep(i, m){
            int a, b;
            cin >> a >> b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        DFS(0, n);
        int count = 0;
        rep(i, n){
            if (AP[i]){
                count++;
            }
        }
        cout << count << endl;
        adj.clear();
        cin >> n >> m;
    }
}