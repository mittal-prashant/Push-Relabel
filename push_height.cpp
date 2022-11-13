// Libraries included that has to be used
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int inf = 1000000000;
int n;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int **capacity;
int **flow;
int *height, *excess;

// function to push the flow along the edge
void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;

    // excess at u is decreased by flow sent towards v
    excess[u] -= d;

    // excess at v is increased by flow receieved from u
    excess[v] += d;
}

// function to relabel the vertex
void relabel(int u)
{
    int d = inf;
    for (int i = 0; i < n; i++)
    {
        if (capacity[u][i] - flow[u][i] > 0)
        {
            d = min(d, height[i]);
        }
    }
    if (d < inf)
    {
        // relabeling the vertex height
        height[u] = d + 1;
    }
}

// function to find the maximum height vertex
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

// function to check whether the excess value if positive or not and return the first positive value
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

// function to find the max flow using push_relabel algorithm between vertices s and t ion a given graph
int max_flow(int s, int t)
{
    // intitalize the height of source as n and the excess flow at source to be infinite
    excess[s] = inf;
    height[s] = n;

    for (int i = 0; i < n; i++)
    {
        if (i != s)
        {
            push(s, i);
        }
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
        {
            break;
        }
        max_height = maxmheight();
    }

    // now the maximum flow is the sum of flow sent from source vertex to all of ots neighbouring vertices
    int max_flow = 0;
    for (int i = 0; i < n; i++)
    {
        max_flow += flow[i][t];
    }

    return max_flow;
}

int main()
{
    // taking in the input from various input files
    // freopen("input1.txt", "r", stdin);
    // freopen("input2.txt", "r", stdin);
    // freopen("input3.txt", "r", stdin);
    // freopen("input4.txt", "r", stdin);
    freopen("input5.txt", "r", stdin);
    // freopen("input6.txt", "r", stdin);

    // taking the input for the number of vertices
    scanf("%d", &n);

    // allocating the memory for all the arrays that would be used while running the algorithm
    capacity = (int **)malloc(n * sizeof(int));
    flow = (int **)malloc(n * sizeof(int));
    height = (int *)malloc(n * sizeof(int));
    excess = (int *)malloc(n * sizeof(int));

    // initialize all the values in the arrays
    for (int i = 0; i < n; i++)
    {
        height[i] = 0;
        excess[i] = 0;
        capacity[i] = (int *)malloc(n * sizeof(int));
        flow[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            capacity[i][j] = 0;
            flow[i][j] = 0;
        }
    }

    int m;

    // taking the input for the number of edges
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);

        // intitalize all the capacities of the edges
        capacity[x][y] = c;
        capacity[y][x] = c;
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
