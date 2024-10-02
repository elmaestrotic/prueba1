#include <iostream>
#include <vector>
#include <clocale>
#include <windows.h>
#include <limits.h>

const int INF = INT_MAX;  // Definir una constante para representar infinito

class Dijkstra {
public:
    Dijkstra(int n) : distance(n, INF), cost(n, std::vector<int>(n, INF)) {}


    int findMinVertex(int n, const std::vector<bool>& visited) {
        int minDistance = INF;
        int minVertex = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                minVertex = i;
            }
        }

        return minVertex;
    }


    std::vector<int> distance;

    void calc(int n, int source) {
        std::vector<bool> visited(n, false);
        distance[source] = 0;

        for (int i = 0; i < n - 1; ++i) {  // Recorremos n-1 veces
            int u = findMinVertex(n, visited);
            visited[u] = true;

            // Actualizar las distancias a los nodos vecinos de u
            for (int v = 0; v < n; ++v) {
                if (!visited[v] && cost[u][v] != INF && distance[u] != INF &&
                    distance[u] + cost[u][v] < distance[v]) {
                    distance[v] = distance[u] + cost[u][v];
                }
            }
        }
    }

    std::vector<std::vector<int>> cost;
};

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "es_ES.UTF-8");

    int nodes, source;
    std::cout << "Ingrese el número de vértices: ";
    std::cin >> nodes;

    Dijkstra d(nodes);

    std::cout << "Ingrese los pesos de la matriz de costos (0 para no conectado):\n";
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            std::cin >> d.cost[i][j];
            if (d.cost[i][j] == 0 && i != j) {  // No hay auto-lazos
                d.cost[i][j] = INF;
            }
        }
    }

    std::cout << "Ingrese el vértice de origen: ";
    std::cin >> source;

    d.calc(nodes, source);

    std::cout << "Las rutas más cortas desde el vértice " << source << " a los demás vértices son:\n";
    for (int i = 0; i < nodes; ++i) {
        if (i != source) {
            std::cout << "Origen: " << source << "\tDestino: " << i << "\tCosto mínimo: ";
            if (d.distance[i] == INF) {
                std::cout << "Inalcanzable\n";
            } else {
                std::cout << d.distance[i] << "\n";
            }
        }
    }

    return 0;
}


/*
 * 0      3   999   7
3      0    4      2
999  4    0      5
7      2    5      0
 */