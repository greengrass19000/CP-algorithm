///Phß║ím Nguyß╗àn Tu├ín Ho├áng///
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i = a;i <= b;i++)
#define FORN(i,a,b) for(int i = a;i >=b;i--)
#define rep(i,n) for(int i = 0;i < n;i++)
#define pii pair<int,int>
#define F first
#define S second
#define mp make_pair
#define PB push_back
#define Task "manacher"
#define N 100012
#define IOS(); ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

string s;
int LengS;

string Decode(string s)
{
    string t = ".";
    rep(i,s.size())
        t += s[i],t += ".";
    return t;
}
int p[N];
void Manacher(string s)
{
    s = Decode(s);
    LengS = s.size();
    int l = 0,r = 0;
    FOR(i,1,LengS-2)
    {
        int mirror = l*2 - i;
        if(r - i > 0) p[i] = min(r - i,p[mirror]);
        while(i - p[i] > 0 && i + p[i] < LengS - 1 && s[i + 1 + p[i]] == s[i - 1 - p[i]]) p[i]++;
        if(i + p[i] > r)l = i,r = i + p[i];
    }
}

int main()
{
    IOS();
    freopen(Task".inp","r",stdin);
    freopen(Task".out","w",stdout);
    cin >> s;
    Manacher(s);
    return 0;
}
