#include "../Header.cpp"

int V,E;
int w,v,u;

class UnionFind { // OOP style
    private: vi p, rank, setSize; // vi p is the key part
    int numSets;
    public:
        UnionFind(int N) {
            p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
            rank.assign(N, 0); // optional speedup
            setSize.assign(N, 1); // optional feature
            numSets = N; // optional feature
        }
        int findSet(int i) 
        { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) 
        { return findSet(i) == findSet(j); }

        void unionSet(int i, int j) 
        {
            if (isSameSet(i, j)) return; //i and j in same set
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) swap(x, y); 
            // keep x ’shorter’ than y
            p[x] = y; // set x under y
            if (rank[x] == rank[y]) ++rank[y]; //optional speedup
            setSize[y] += setSize[x]; // combine set sizes at y
            --numSets; // a union reduces numSets
        }
        // optional
        int numDisjointSets() { return numSets; } 
        int sizeOfSet(int i) { return setSize[findSet(i)]; } 
    };
int main()
{
    cin >> V >> E;
    
    vector< pair<int, ii> > Edgelist;
    for(int i = 0; i< E; i++){
        cin >> u >> v >> w;
        Edgelist.push_back(make_pair(w,ii(u,v)));
    }
sort(Edgelist.begin(),Edgelist.end());// sort de built in de pair 

int mst_cost = 0, num_taken = 0; // No edge has been taken
UnionFind UF(V); // all V are disjoint sets

for (auto &[w, e] : Edgelist) { 
    u = e.first -1 ; v = e.second -1;
    
    if (UF.isSameSet(u, v)) continue; // already in the same CC
    mst_cost += w;
    UF.unionSet(u, v); // link them
    ++num_taken; // 1 more edge is taken
    if (num_taken == V-1) break; 
}

cout << mst_cost << '\n';
}