#include <bits/stdc++.h>
using namespace std;

void dijkstra(int source, vector<vector<pair<int,int>>> &graph, 
              vector<int> &dist, vector<int> &parent) {
    int V = graph.size();
    dist.assign(V, INT_MAX);
    parent.assign(V, -1);   
    dist[source] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;   // store parent for path
                pq.push({dist[v], v});
            }
        }
    }
}

void printhospitals(vector<int> &dist,vector<int> hospitals)
{
    cout<<"Distance from source to each node:"<<endl;
    for(int h:hospitals)
    {
        if(dist[h]==INT_MAX)
            cout<<"Node not reachable!!\n";
        else
            cout<<"Hospital at node "<<h<<" to distance "<<dist[h]<<"minutes"<<endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of intersections (vertices): ";
    cin >> V;
    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<pair<int,int>>> graph(V);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});   // for directed 
        // graph[v].push_back({u, w}); // for undirected
    }

    int source;
    cout << "Enter ambulance start location (source): ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;
    vector<int> hospitals(H);
    cout << "Enter hospital nodes: ";
    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    vector<int> dist, parent;
    clock_t start=clock();
    dijkstra(source, graph, dist, parent);
    clock_t end=clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Dijkstra's algorithm executed in " << fixed<<setprecision(6)<<time_taken<<" seconds.\n";

    printhospitals(dist,hospitals);
    int minTime = INT_MAX, nearestHospital = -1;
    for (int h : hospitals) {
        if (dist[h] < minTime) {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1) {
        cout << "No hospital reachable.\n";
    } else {
        cout << "Nearest hospital is at node " << nearestHospital 
             << " with travel time " << minTime << " minutes.\n";

        // Simple path reconstruction using stack
        cout << "Path: ";
        int curr = nearestHospital;
        stack<int> s;
        while (curr != -1) {
            s.push(curr);
            curr = parent[curr];
        }
        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << "\n";
    }

    return 0;
}

// Enter number of intersections (vertices): 4
// Enter number of roads (edges): 5
// Enter edges (u v w):
// 0 1 4
// 0 2 1
// 2 1 2
// 1 3 1
// 2 3 5
// Enter ambulance start location (source): 0
// Enter number of hospitals: 2
// Enter hospital nodes: 1 3