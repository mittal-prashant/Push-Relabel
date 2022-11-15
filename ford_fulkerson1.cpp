#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;
int n;

// vector for storing the capacity of edges and adj list for storing the graph
vector<vector<int>> capacity;
vector<vector<int>> adj;

// bfs function to find a new flow in the edited graph
int bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, inf});

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
                {
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

// function to find the max flow using ford fulkersion algorithm between vertices s and t ion a given graph
int max_flow(int s, int t)
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
    // taking in the input from various input files
    // freopen("input1.txt", "r", stdin);
    // freopen("input2.txt", "r", stdin);
    // freopen("input3.txt", "r", stdin);
    // freopen("input4.txt", "r", stdin);
    // freopen("input5.txt", "r", stdin);

    // taking the input for the number of vertices
    n = 10000;

    // initialising the arrays for storing the capacities and the edges
    capacity.assign(n, vector<int>(n, 0));
    adj.resize(n);

    for (int x = 0; x < n; x++)
    {
        for (int y = x; y < n; y++)
        {
            capacity[x][y] = x + y + 1;
            capacity[y][x] = x + y + 1;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    // calculating the time taken by the algorithm to run on the given graph
    clock_t t;
    t = clock();

    // finding and printing the maximum flow between source vertex s and sink vertex t
    printf("%d\n", max_flow(0, n - 1));

    t = clock() - t;
    int time_taken = (((double)t) / CLOCKS_PER_SEC) * 1000000;

    // printing the time taken by the algorithm
    printf("%d\n", (time_taken));

    return 0;
}