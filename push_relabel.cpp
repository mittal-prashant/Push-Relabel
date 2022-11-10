#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
// #include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
const int inf = 1000000000;
const int n = 10000;
// int n = 4;

// A structure to represent a queue
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int *array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue *createQueue(unsigned capacity)
{
    struct Queue *queue = (struct Queue *)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(
        queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue *queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue *queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    // printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(struct Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue
int rear(struct Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}
// vector<vector<int>> capacity, flow;
// vector<int> height, excess, seen;
// queue<int> excess_vertices;
int min(int a, int b)
{
    return (a < b) ? a : b;
}
int capacity[n][n];
int flow[n][n];
int height[n], seen[n], excess[n];
struct Queue *excess_vertices = createQueue(1000);
void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        enqueue(excess_vertices, v);
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

void discharge(int u)
{
    while (excess[u] > 0)
    {
        if (seen[u] < n)
        {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
                push(u, v);
            else
                seen[u]++;
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
    // height.assign(n, 0);
    height[s] = n;
    // flow.assign(n, vector<int>(n, 0));
    // excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++)
    {
        if (i != s)
            push(s, i);
    }
    // seen.assign(n, 0);

    while (!isEmpty(excess_vertices))
    {
        int u = front(excess_vertices);
        int f = dequeue(excess_vertices);
        if (u != s && u != t)
            discharge(u);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}

int main()
{
    // n = 4;
    // capacity.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            capacity[i][j] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            capacity[i][j] = i + j;
        }
    }
    // clock_t tStart = clock();
    auto start = high_resolution_clock::now();
    printf("%d\n", max_flow(0, 99));
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printf("%d", duration.count());
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}