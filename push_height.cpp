#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
const int inf = 1000000000;
const int n = 4;

int min(int a, int b)
{
    return (a < b) ? a : b;
}
int capacity[n][n];
int flow[n][n];
int height[n], excess[n];

void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

void relabel(int u)
{
    int d = inf;
    for (int i = 0; i < n; i++)
    {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

// vector<int> find_max_height_vertices(int s, int t) {
//     vector<int> max_height;
//     for (int i = 0; i < n; i++) {
//         if (i != s && i != t && excess[i] > 0) {
//             if (!max_height.empty() && height[i] > height[max_height[0]])
//                 max_height.clear();
//             if (max_height.empty() || height[i] == height[max_height[0]])
//                 max_height.push_back(i);
//         }
//     }
//     return max_height;
// }

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int maxmheight()
{
    int maxm = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if (excess[i] > 0)
        {
            maxm = max(maxm, height[i]);
        }
    }
    return maxm;
}

int checkexcess()
{
    for (int i = 1; i < n - 1; i++)
    {
        if (excess[i] > 0)
        {
            return excess[i];
        }
    }
    return 0;
}
int max_flow(int s, int t)
{
    for (int i = 0; i < n; i++)
    {
        height[i] = 0;
        excess[i] = 0;
    }
    excess[s] = inf;
    height[s] = n;
    for (int i = 0; i < n; i++)
    {
        if (i != s)
            push(s, i);
    }
    int max_height = maxmheight();

    int f = checkexcess();
    while (true)
    {
        for (int i = 1; i < n - 1; i++)
        {
            if (height[i] == max_height && excess[i] > 0)
            {
                bool pushed = false;
                for (int j = 0; j < n && excess[i]; j++)
                {
                    if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1)
                    {
                        push(i, j);
                        pushed = true;
                    }
                }
                if (!pushed)
                {
                    relabel(i);
                    break;
                }
            }
        }
        f = checkexcess();
        if (f == 0)
            break;
        // printf("%d\n", f);
        max_height = maxmheight();
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}

int main()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            capacity[i][j] = 0;
            flow[i][j] = 0;
        }
    }

    capacity[0][1] = 3;
    capacity[0][2] = 1;
    capacity[1][3] = 1;
    capacity[2][3] = 3;
    capacity[1][2] = 3;
    printf("max-flow for this graph is: %d\n", max_flow(0, 3));
    return 0;
}