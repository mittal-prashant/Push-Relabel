#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int inf = 1000000000;
int n;

typedef struct Queue
{
    int value;
    Queue *next;
} Queue;

int **capacity;
int **flow;
int *height, *seen, *excess;
Queue *front = NULL, *rear = NULL;

int isEmpty()
{
    if (front == NULL)
    {
        return 1;
    }
    return 0;
}

Queue *new_node(int item)
{
    Queue *temp = (Queue *)malloc(sizeof(Queue));
    temp->value = item;
    temp->next = NULL;
    return temp;
}

void enqueue(int item)
{
    Queue *temp = new_node(item);
    if (isEmpty())
    {
        front = temp;
        rear = temp;
        return;
    }
    rear->next = temp;
    rear = rear->next;
}

int dequeue()
{
    if (isEmpty())
    {
        return INT_MIN;
    }
    int item = front->value;
    front = front->next;
    return item;
}

int front_value()
{
    if (isEmpty())
    {
        return INT_MIN;
    }
    return front->value;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
    {
        enqueue(v);
    }
}

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
        height[u] = d + 1;
    }
}

void discharge(int u)
{
    while (excess[u] > 0)
    {
        if (seen[u] < n)
        {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
            {
                push(u, v);
            }
            else
            {
                seen[u]++;
            }
        }
        else
        {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t)
{
    height[s] = n;
    excess[s] = inf;
    for (int i = 0; i < n; i++)
    {
        if (i != s)
        {
            push(s, i);
        }
    }
    while (!isEmpty())
    {
        int u = front_value();
        int f = dequeue();
        if (u != s && u != t)
        {
            discharge(u);
        }
    }
    int max_flow = 0;
    for (int i = 0; i < n; i++)
    {
        max_flow += flow[i][t];
    }
    return max_flow;
}

int main()
{
    freopen("input5.txt", "r", stdin);
    scanf("%d", &n);
    capacity = (int **)malloc(n * sizeof(int));
    flow = (int **)malloc(n * sizeof(int));
    height = (int *)malloc(n * sizeof(int));
    seen = (int *)malloc(n * sizeof(int));
    excess = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        height[i] = 0;
        seen[i] = 0;
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
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        capacity[x][y] = c;
        capacity[y][x] = c;
    }
    clock_t t;
    t = clock();
    printf("%d\n", max_flow(0, n - 1));
    t = clock() - t;
    int time_taken = (((double)t) / CLOCKS_PER_SEC) * 1000000;
    printf("%d\n", (time_taken));
    return 0;
}