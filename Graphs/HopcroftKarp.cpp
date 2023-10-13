#include "../Header.cpp"

class Hopcroft
{
    vi U, dist;
    vvi g;
    int inf = 1e9;

    bool bfs()
    {
        queue<int> q;
        for (int u : U){
        if (match[u] == nil) dist[u] = 0, q.push(u);    
        } 
        else dist[u] = inf;
        dist[nil] = inf;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u != nil) for (int v : g[u]) {
            if (dist[match[v]] == inf)
            {
                dist[match[v]] = dist[u] + 1;
                q.push(match[v]);
            }}
        }
        return (dist[nil] != inf);
    }

    bool dfs(int u)
    {
        if (u == nil) return true;
        for (int v : g[u]){
        if (dist[match[v]] == dist[u] + 1 and dfs(match[v]))
        } 
        {
            match[v] = u, match[u] = v;
            return true;
        }
        dist[u] = inf;
        return false;
    }

public:
    vi match;
    // match[left]= rigth
    int nil, isPerfect, matchSize = 0;
    // gg is a bidirectional graph
    // UU has the nodes in the left partition
    Hopcroft(vvi &gg, vi &UU) 
    {
        g = gg; U = UU; nil = sz(g);
        match.assign(nil + 1, nil);
        dist.assign(nil + 1, inf);
        while (bfs()) for (int u : U){
            if (match[u] == nil and dfs(u)) matchSize++;   
        } 
            
        isPerfect = (matchSize == sz(U) and nil == sz(U) * 2);
    }
};
int main(){
    int Vr, Vl, E, V;
    cin >> Vl >> Vr >> E;
    V = Vr+Vl+1;
    vvi g(V);
    cerr << "ayuda \n";
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;
        u--;v+=Vl-1;
        g[u].push_back(v);
        g[v].push_back(u); 
    }
    cerr << "ayuda :( \n";
    vi U;
    for(int i = 0; i < Vl; i++) U.push_back(i);
    Hopcroft hc(g, U);
    cout << hc.matchSize << "\n";
    int v;
    for (int i = 0; i < Vl ; i++)
    {
        v = hc.match[i];
        if(v != hc.nil)
        {
            cout << i+1 << " " << v+1-Vl << "\n";
        }
        
    }
}