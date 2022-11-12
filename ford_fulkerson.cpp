// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <chrono>
// #include <time.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
const int INF = 1000000000;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next])
            {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t)
{
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent))
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main()
{
    freopen("input5.txt", "r", stdin);
    cin >> n;
    capacity.assign(n, vector<int>(n, 0));
    adj.resize(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        adj[x].push_back(y);
        adj[y].push_back(x);
        capacity[x][y] = c;
        capacity[y][x] = c;
    }
    clock_t t;
    t = clock();
    printf("%d\n", maxflow(0, n - 1));
    t = clock() - t;
    int time_taken = (((double)t) / CLOCKS_PER_SEC) * 1000000;
    printf("%d\n", (time_taken));
    return 0;
}