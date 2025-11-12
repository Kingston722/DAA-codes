#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<int> path; // partial path (sequence of cities visited)
    vector<bool> visited;
    int level; // number of cities visited so far
    int cost;  // actual cost so far
    int bound; // estimated lower bound of total cost

    bool operator>(const Node &other) const
    {
        return bound > other.bound; // min-heap based on bound
    }
};

int N;                    // number of cities
vector<vector<int>> dist; // distance matrix
int bestCost = INT_MAX;
vector<int> bestPath;

// Function to compute lower bound (LB) for a node
int calculateBound(const Node &node)
{
    int bound = node.cost;

    // For each unvisited city, add the minimum incoming edge
    for (int i = 0; i < N; i++)
    {
        if (!node.visited[i])
        {
            int minEdge = INT_MAX;
            for (int j = 0; j < N; j++)
            {
                if (i != j && (!node.visited[j] || j == 0))
                {
                    minEdge = min(minEdge, dist[i][j]);
                }
            }
            if (minEdge != INT_MAX)
                bound += minEdge;
        }
    }

    return bound;
}

void tspLCBB(int start)
{
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Initial node (starting city)
    Node root;
    root.path = {start};
    root.visited.assign(N, false);
    root.visited[start] = true;
    root.level = 1;
    root.cost = 0;
    root.bound = calculateBound(root);

    pq.push(root);

    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        // Prune if bound is already worse than best
        if (curr.bound >= bestCost)
            continue;

        // If all cities visited, close the tour
        if (curr.level == N)
        {
            int finalCost = curr.cost + dist[curr.path.back()][start];
            if (finalCost < bestCost)
            {
                bestCost = finalCost;
                bestPath = curr.path;
            }
            continue;
        }

        // Branch: try next unvisited cities
        for (int next = 0; next < N; next++)
        {
            if (!curr.visited[next])
            {
                Node child;
                child.path = curr.path;
                child.path.push_back(next);
                child.visited = curr.visited;
                child.visited[next] = true;
                child.level = curr.level + 1;
                child.cost = curr.cost + dist[curr.path.back()][next];
                child.bound = calculateBound(child);

                if (child.bound < bestCost) // explore promising paths
                    pq.push(child);
            }
        }
    }
}

int main()
{
    cout << "Enter number of cities: ";
    cin >> N;

    dist.assign(N, vector<int>(N));
    cout << "Enter distance matrix:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> dist[i][j];

    int start = 0;
    cout << "\nStarting from city: " << start << "\n";
    tspLCBB(start);

    cout << "\nOptimal Route: ";
    for (int city : bestPath)
        cout << city << " -> ";
    cout << bestPath[0] << "\n";

    cout << "Minimum Cost: " << bestCost << "\n";
    return 0;
}

// Enter number of cities: 4
// Enter distance matrix:
// 0 10 15 20
// 10 0 35 25
// 15 35 0 30
// 20 25 30 0

// Starting from city: 0

// Optimal Route: 0 -> 1 -> 3 -> 2 -> 0
// Minimum Cost: 80
