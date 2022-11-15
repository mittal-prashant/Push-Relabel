// Libraries included that has to be used
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int inf = 1000000000;
int n;

// function for minimum of a and b
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// structure for any node in queue
typedef struct Queue
{
    int value;
    Queue *next;
} Queue;

// array for storing the flow capacity of an edge in a graph
int **capacity;
int **flow;
int *height, *seen, *excess;

// represent the front end of the queue and the rear end of the queue
Queue *front = NULL, *rear = NULL;

// function to check whether the queue is empty or not
int isEmpty()
{
    if (front == NULL)
    {
        return 1;
    }
    return 0;
}

// function to create a new node in the queue
Queue *new_node(int item)
{
    Queue *temp = (Queue *)malloc(sizeof(Queue));

    temp->value = item;
    temp->next = NULL;

    return temp;
}

// function to add the value in queue at the rear end
void enqueue(int item)
{
    Queue *temp = new_node(item);
    if (isEmpty())
    {
        front = temp;
        rear = temp;
        return;
    }

    // moving the rear pointer one step forward since value is added at rear end
    rear->next = temp;
    rear = rear->next;
}

// function to pop the value from the front end of the queue
int dequeue()
{
    if (isEmpty())
    {
        // if queue is empty return minimum value of integer
        return INT_MIN;
    }

    int item = front->value;
    front = front->next;
    return item;
}

// function to get the value at the front of queue without deleting it
int front_value()
{
    if (isEmpty())
    {
        // if queue is empty return minimum value of integer
        return INT_MIN;
    }
    return front->value;
}

// function to push the flow along the edge
void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]); // pushing the flow from u to v
    flow[u][v] += d;
    flow[v][u] -= d;

    // excess at u is decreased by flow sent towards v
    excess[u] -= d;

    // excess at v is increased by flow receieved from u
    excess[v] += d;
    if (d && excess[v] == d)
    {
        enqueue(v);
    }
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

// function to implement the discharge in the algorithm
void discharge(int u)
{
    while (excess[u] > 0)
    {
        if (seen[u] < n)
        {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
            {
                // if condition is satisfied the flow is pushed towards in edge (u,v)
                push(u, v);
            }
            else
            {
                seen[u]++;
            }
        }
        else
        {
            // relabel the vertex u if seen[u] >= n and set seen[u] = 0
            relabel(u);
            seen[u] = 0;
        }
    }
}

// function to find the max flow using push relabel algorithm between vertices s and t ion a given graph
int max_flow(int s, int t)
{
    // intitalize the height of source as n and the excess flow at source to be infinite
    height[s] = n;
    excess[s] = inf;

    for (int i = 0; i < n; i++)
    {
        if (i != s)
        {
            // push the flow from source to all of its neighbours
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
    // freopen("input5.txt", "r", stdin);

    // taking the input for the number of vertices
    n = 10000;

    // allocating the memory for all the arrays that would be used while running the algorithm
    capacity = (int **)malloc(n * sizeof(int));
    flow = (int **)malloc(n * sizeof(int));
    height = (int *)malloc(n * sizeof(int));
    seen = (int *)malloc(n * sizeof(int));
    excess = (int *)malloc(n * sizeof(int));

    // initialize all the values in the arrays
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

    for (int x = 0; x < n; x++)
    {
        for (int y = x; y < n; y++)
        {
            capacity[x][y] = x + y + 1;
            capacity[y][x] = x + y + 1;
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