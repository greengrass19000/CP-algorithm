#include<bits/stdc++.h>
#define rep(i, a, b) for(int i=(a) ; i<=(b) ; ++i)
#define pii pair<int,int >
#define F first
#define S second
#define PB push_back
#define mp make_pair
#define Task ""
using namespace std;
const int N=10005;
int Q, n, par[N][20], h[N], child[N], topo[N], cnt, chain, fchain[N], ofchain[N], b[N], it[N*6];
vector <pii > g[N], e;
 
void setup() {
    rep(i, 0, n) {
        g[i].clear();
        fchain[i]=ofchain[i]=child[i]=0;
    }
    e.clear();
    cnt=0;
    chain=1;
    cin >> n;
    rep(i, 1, n-1) {
        int u, v, ts;
        cin >> u >> v >> ts;
        g[u].PB(mp(v, ts));
        g[v].PB(mp(u, ts));
        e.PB(mp(u, v));
    }
}
 
void build(int l, int r, int node) {
    if(l==r) {
        it[node]=b[l];
        return;
    }
    int mid=(r+l)>>1;
    build(l, mid, node*2);
    build(mid+1, r, node*2+1);
    it[node]=max(it[node*2], it[node*2+1]);
}
 
void update(int l, int r, int node, int u, int ts) {
    if(r<u||u<l) return;
    if(l==r) {
        it[node]=ts;
        return;
    }
    int mid=(r+l)>>1;
    update(l, mid, node*2, u, ts);
    update(mid+1, r, node*2+1, u, ts);
    it[node]=max(it[node*2], it[node*2+1]);
}
 
int get(int l, int r, int node, int u, int v) {
    if(r<u||v<l) return 0;
    if(u<=l&&r<=v) return it[node];
    int mid=(r+l)>>1;
    int m1=get(l, mid, node*2, u, v);
    int m2=get(mid+1, r, node*2+1, u, v);
    return max(m1, m2);
}
 
void HLD(int u, int ts) {
    if(fchain[chain]==0) fchain[chain]=u;
    ofchain[u]=chain;
    int maxchild=-1;
    topo[u]=++cnt;
    b[cnt]=ts;
    int w=0;
    for(int i=0 ; i<g[u].size() ; ++i) {
        pii P=g[u][i];
        int v=P.F;
        if(v==par[u][0]) continue;
        if(maxchild==-1||child[maxchild]<child[v]) {
            maxchild=v;
            w=P.S;
        }
    }
    if(maxchild!=-1) HLD(maxchild, w);
    for(int i=0 ; i<g[u].size() ; ++i) {
        pii P=g[u][i];
        int v=P.F;
        if(v==par[u][0]) continue;
        if(v!=maxchild) {
            ++chain;
            HLD(v, P.S);
        }
    }
}
 
void DFS(int u) {
    child[u]=1;
    for(int i=0 ; i<g[u].size() ; ++i) {
        pii P=g[u][i];
        int v=P.F, ts=P.S;
        if(v==par[u][0]) continue;
        par[v][0]=u;
        h[v]=h[u]+1;
        rep(i, 1, 14) {
            par[v][i]=par[par[v][i-1]][i-1];
        }
        DFS(v);
        child[u]+=child[v];
    }
}
 
int tinh(int u, int v) {
    int maxx=0;
    while(1) {
        if(ofchain[u]==ofchain[v]) {
            maxx=max(maxx, get(2, n, 1, topo[v], topo[u]));
            break;
        }
        int id=ofchain[u];
        int head=fchain[id];
        maxx=max(maxx, get(2, n, 1, topo[head], topo[u]));
        u=par[head][0];
    }
    return maxx;
}
 
void change() {
    int tt, ts;
    cin >> tt >> ts;
    --tt;
    int u=e[tt].F, v=e[tt].S;
    int vex=(par[u][0]==v?u:v);
    update(2, n, 1, topo[vex], ts);
}
 
int LCA(int u, int v) {
    if(h[u]<h[v]) swap(u, v);
    int delta=h[u]-h[v];
    rep(i, 0, 14) {
        if((delta>>i)&1) u=par[u][i];
    }
    if(u==v) return u;
    for(int i=14 ; i>=0 ; --i) {
        if(par[u][i]!=par[v][i]) {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[u][0];
}
 
int up(int u, int leng) {
    rep(i, 0, 14) {
        if((leng>>i)&1) u=par[u][i];
    }
    return u;
}
 
void query() {
    int u, v;
    cin >> u >> v;
    int maxx=0;
    int cha=LCA(u, v);
    if(h[u]>h[cha]) {
        int dinh=up(u, h[u]-h[cha]-1);
        maxx=max(maxx, tinh(u, dinh));
    }
    if(h[v]>h[cha]) {
        int dinh=up(v, h[v]-h[cha]-1);
        maxx=max(maxx, tinh(v, dinh));
    }
    cout << maxx << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("test.inp", "r", stdin);
    //freopen("mine.out", "w", stdout);
    cin >> Q;
    while(Q--) {
        setup();
        DFS(1);
        HLD(1, 0);
        build(2, n, 1);
        while(1) {
            string t;
            cin >> t;
            if(t=="DONE") break;
            else if(t=="QUERY") query();
            else change();
        }
    }
    return 0;
}