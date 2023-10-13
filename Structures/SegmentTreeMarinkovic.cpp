#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Node
{
    ll v, lzv = 0;
    bool lz = false;
    Node() : v(0) {}
    Node(ll x) : v(x) {}
    Node(const Node &a, const Node &b) : v(a.v + b.v) {}
    Node(ll x, ll i, ll j, const Node &b)
    {
        v = b.v + (j - i + 1) * x;
    }
};

// 0 - indexed / inclusive - inclusive
template <class node>
struct STL
{
    vector<node> st; ll n;

    void build(ll u, ll i, ll j, vector<node> &arr)
    {
        if (i == j) { st[u] = arr[i]; return; }
        ll m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        build(l, i, m, arr), build(r, m + 1, j, arr);
        st[u] = node(st[l], st[r]);
    }
    void push(ll u, ll i, ll j, ll x)
    {
        st[u] = node(x, i, j, st[u]);
        if (i == j) return;
        st[u * 2 + 1].lz = true, st[u * 2 + 1].lzv += x;
        st[u * 2 + 2].lz = true, st[u * 2 + 2].lzv += x;
    }
    node query(ll a, ll b, ll u, ll i, ll j)
    {
        if (j < a || b < i) return node();
        ll m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        if (st[u].lz) push(u, i, j, st[u].lzv);
        if (a <= i && j <= b) return st[u];
        return node(query(a, b, l, i, m), query(a, b, r, m + 1, j));
    }
    void update(ll a, ll b, ll v, ll u, ll i, ll j)
    {
        if (st[u].lz) push(u, i, j, st[u].lzv);
        if (j < a || b < i) return;
        ll m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        if (a <= i && j <= b) { push(u, i, j, v); return; }
        update(a, b, v, l, i, m); update(a, b, v, r, m + 1, j);
        st[u] = node(st[l], st[r]);
    }

    STL(vector<node> &v, ll N) : n(N), st(N * 4 + 5) { build(0, 0, n - 1, v);}
    node query(ll a, ll b) { return query(a, b, 0, 0, n - 1); }
    void update(ll a, ll b, ll v) { update(a, b, v, 0, 0, n - 1);}
};



int main(){
    ll n, q;
    cin >> n >> q;
    vector<ll> v;
    for (ll i = 0; i < n; i++){
        ll r;
        cin >> r;
        v.push_back(r);
    }
    vector<Node> _v;
    for(ll i = 0; i < n; i++){
        _v.push_back(v[i]);
    }
    STL<Node> st(_v, n);
    for (ll i = 0; i < q; i++){
        ll r;
        cin >> r;
        if (r == 2){
            ll a;
            cin >> a;
            cout << st.query(a - 1, a - 1).v << endl;
        } else {
            ll a, b, u;
            cin >> a >> b >> u;
            st.update(a-1, b-1, u);
        }
    }
}