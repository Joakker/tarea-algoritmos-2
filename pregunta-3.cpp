#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
using namespace std;

vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename);
    int n, m;
    file >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

// Estrategia A
vector<int> vertexCoverA(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> cover;
    
    for (int u = 1; u < n; ++u) {
        if (!visited[u]) {
            for (int v : graph[u]) {
                if (!visited[v]) {
                    cover.push_back(u);
                    cover.push_back(v);
                    visited[u] = visited[v] = true;
                    break;
                }
            }
        }
    }
    return cover;
}

// Estrategia B
vector<int> vertexCoverB(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> cover;
    vector<int> degree(n, 0);
    
    for (int u = 1; u < n; ++u) {
        degree[u] = graph[u].size();
    }
    
    while (true) {
        int maxDegree = -1;
        int v = -1;
        for (int i = 1; i < n; ++i) {
            if (degree[i] > maxDegree) {
                maxDegree = degree[i];
                v = i;
            }
        }
        
        if (maxDegree == 0) break;
        
        cover.push_back(v);
        for (int u : graph[v]) {
            degree[u]--;
            graph[u].erase(remove(graph[u].begin(), graph[u].end(), v), graph[u].end());
        }
        degree[v] = 0;
    }
    
    return cover;
}

// Función para encontrar la solución exacta de Vertex Cover usando backtracking
void exactVertexCoverHelper(const vector<vector<int>>& graph, vector<int>& cover, vector<int>& bestCover, vector<bool>& visited, int edgeCount) {
    int n = graph.size();
    if (edgeCount == 0) {
        if (cover.size() < bestCover.size() || bestCover.empty()) {
            bestCover = cover;
        }
        return;
    }

    for (int u = 1; u < n; ++u) {
        if (!visited[u]) {
            for (int v : graph[u]) {
                if (!visited[v]) {
                    cover.push_back(u);
                    visited[u] = true;
                    for (int w : graph[u]) {
                        if (!visited[w]) {
                            visited[w] = true;
                            edgeCount--;
                        }
                    }
                    exactVertexCoverHelper(graph, cover, bestCover, visited, edgeCount);
                    for (int w : graph[u]) {
                        if (visited[w]) {
                            visited[w] = false;
                            edgeCount++;
                        }
                    }
                    visited[u] = false;
                    cover.pop_back();
                    break;
                }
            }
        }
    }
}

vector<int> exactVertexCover(const vector<vector<int>>& graph) {
    int edgeCount = 0;
    for (const auto& edges : graph) {
        edgeCount += edges.size();
    }
    edgeCount /= 2; // Cada arista se cuenta dos veces

    vector<int> cover;
    vector<int> bestCover;
    vector<bool> visited(graph.size(), false);

    exactVertexCoverHelper(graph, cover, bestCover, visited, edgeCount);

    return bestCover;
}

void evaluate(const string& filename) {
    auto graph = readGraph(filename);
    auto coverA = vertexCoverA(graph);
    auto coverB = vertexCoverB(graph);
    auto exactCover = exactVertexCover(graph);
    
    cout << "Evaluación del grafo: " << filename << endl;
    cout << "Estrategia A: Tamaño de la cobertura = " << coverA.size() << endl;
    cout << "Estrategia B: Tamaño de la cobertura = " << coverB.size() << endl;
    cout << "Solución exacta: Tamaño de la cobertura = " << exactCover.size() << endl;
    
    if (coverA.size() <= 2 * exactCover.size()) {
        cout << "La estrategia A cumple con la 2-aproximación." << endl;
    } else {
        cout << "La estrategia A no cumple con la 2-aproximación." << endl;
    }
}

void evaluateBipartite() {
    vector<vector<int>> bipartiteGraph = {
        {}, {2, 4}, {1, 3}, {2, 5}, {1, 5}, {3, 4}, {7, 8, 9}, {6}, {6, 10}, {6, 11}, {8, 12}, {9, 13}
    };
    
    auto coverA = vertexCoverA(bipartiteGraph);
    auto coverB = vertexCoverB(bipartiteGraph);
    auto exactCover = exactVertexCover(bipartiteGraph);
    
    cout << "Grafo bipartito:" << endl;
    cout << "Estrategia A: Tamaño de la cobertura = " << coverA.size() << endl;
    cout << "Estrategia B: Tamaño de la cobertura = " << coverB.size() << endl;
    cout << "Solución exacta: Tamaño de la cobertura = " << exactCover.size() << endl;
}

int main() {
    evaluate("grafo1.txt");
    evaluate("grafo2.txt");
    evaluateBipartite();
    return 0;
}
