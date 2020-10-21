void add(string s, int id)
{
    int p = 1;
    for (auto c : s)
    {
        int ch = c - 'a';
        if (trie[p][ch] == 0)
            trie[p][ch] = ++numNode;
        p = trie[p][ch];
    }
    pos[id] = p;
}
void buildAho()
{
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        FOR(i, 0, 25)
            if (trie[u][i])
            {
                int v = trie[u][i];
                int tmp = kmp[u];
                while (tmp != 0 && trie[tmp][i] == 0)
                    tmp = kmp[tmp];
                if (tmp == 0)
                    kmp[v] = 1;
                else
                    kmp[v] = trie[tmp][i];
                q.push(v);
            }
    }
}
void buildGraph()
{
    FOR(i, 2, numNode)
        g[kmp[i]].PB(i);
}