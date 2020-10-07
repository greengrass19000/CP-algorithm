#include <bits/stdc++.h>
#define maxn 200005
#define Y first
#define X second
#define maxC 1000000000
#define MOD 1000000007
#define pii pair <int, int>
#define mp make_pair
#define PB push_back
#define Task "closestpair"
#define ll long long
using namespace std;
int n;
pii a[maxn];
set <pii> S;

bool cmp(pii x, pii y) {
    return (x.X < y.X || (x.X == y.X && x.Y < y.Y));
}

double dist(pii x, pii y) {
    double oX = y.X - x.X;
    double oY = y.Y - x.Y;
    return sqrt(oX * oX + oY * oY);
}

double calc(pii a[], int n) {
    sort(a, a+n, cmp);
    S.insert(a[0]);
    int left = 0;
    double ans = maxC * 1.0;
    for(int i=1 ; i<n ; ++i) {
        int px = a[i].X;
        int py = a[i].Y;
        while(a[left].X < px - ans) S.erase(a[left++]);
        for(set <pii> :: iterator it = S.lower_bound(mp(1.0 * py-ans, 1.0 * px - ans)) ; it != S.end() && it->Y < ans + py ; ++it)
            ans = min(ans, dist(*it, a[i]));
        S.insert(a[i]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(Task".inp", "r", stdin);
    freopen(Task".out", "w", stdout);
    cin >> n;
    for(int i=0 ; i<n ; ++i) cin >> a[i].X >> a[i].Y;
    cout << fixed << setprecision(6) << calc(a, n);
    return 0;
}
