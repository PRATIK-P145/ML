#include <iostream>
#include <climits>
#include <vector>
using namespace std;

struct Edge {
    int u, v, w; // from, to, weight
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    
    // Input validation
    if (V <= 0) {
        cout << "Number of vertices must be positive!\n";
        return 1;
    }
    
    cout << "Enter number of edges: ";
    cin >> E;
    
    if (E < 0) {
        cout << "Number of edges cannot be negative!\n";
        return 1;
    }

    vector<Edge> edges(E);
    
    cout << "Enter edges in format: u v w (from to weight)\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        
        // Validate vertex indices
        if (edges[i].u < 0 || edges[i].u >= V || edges[i].v < 0 || edges[i].v >= V) {
            cout << "Error: Vertex index out of bounds! Must be between 0 and " << V-1 << "\n";
            return 1;
        }
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;
    
    if (source < 0 || source >= V) {
        cout << "Error: Source vertex must be between 0 and " << V-1 << "\n";
        return 1;
    }

    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // Relax all edges (V-1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycle
    bool negCycle = false;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            negCycle = true;
            break;
        }
    }

    if (negCycle) {
        cout << "Graph contains a negative weight cycle!\n";
    } else {
        cout << "Shortest distances from source " << source << ":\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX)
                cout << "Vertex " << i << " : Unreachable\n";
            else
                cout << "Vertex " << i << " : " << dist[i] << "\n";
        }
    }

    return 0;
}
