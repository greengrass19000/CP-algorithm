// Number of Palindromes (SPOJ)
// https://www.spoj.com/problems/NUMOFPAL/

#include <bits/stdc++.h>
#define N 2005
using namespace std;
 
struct PTNode
{
    int first, length, occurance, child[26], suffix;
    PTNode(int first = 0, int length = 0) : first(first), length(length)
    {
        occurance = suffix = 0;
        for (int i = 0; i < 26; i++) child[i] = 0;
    }
}node[N];
 
int sz, cur, n;
string s;
 
void add(int pos)
{
    int start;
    while (1)
    {
        start = pos - node[cur].length - 1;
        if (start >= 0 && s[start] == s[pos])
            break;
        cur = node[cur].suffix;
    }
 
    int z = s[pos] - 'a';
    if (node[cur].child[z])
    {
        cur = node[cur].child[z];
        node[cur].occurance++;
        return;
    }
    node[++sz] = PTNode(start, node[cur].length + 2);
    node[cur].child[z] = sz;
    if (node[sz].length == 1)
        node[sz].suffix = 2;
    else
    {
        while (1)
        {
            cur = node[cur].suffix;
            int start = pos - node[cur].length - 1;
            if (start >= 0 && s[start] == s[pos])
                break;
        }
        node[sz].suffix = node[cur].child[z];
    }
    node[sz].occurance++;
    cur = sz;
    return;
}
 
void setup()
{
    cin >> s;
    n = s.size();
    sz = cur = 2;
    node[1] = PTNode(0, -1), node[2] = PTNode(0, 0);
    node[1].suffix = node[2].suffix = 1;
}
void solve()
{
    for (int i = 0; i < n; i++)
        add(i);
    int res = 0;
    for (int i = sz; i >= 3; i--)
    {
        node[node[i].suffix].occurance += node[i].occurance;
        res += node[i].occurance;
    }
    cout << res;
}
int main()
{
    //freopen("INP.TXT", "r", stdin);
 
    setup();
    solve();
}
 