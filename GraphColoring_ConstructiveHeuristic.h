#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

class GraphColoring_ConstructiveHeuristic
{
public:
    GraphColoring_ConstructiveHeuristic(int n) : n(n), numDistinctColors(0), executionTime(0), adjList(n), colors(n, -1) {}

    void addEdge(int u, int v)
    {
        if (u >= 0 && u < n && v >= 0 && v < n) // Verificação de limites
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        else
        {
            std::cerr << "Erro: Vértices fora dos limites\n";
        }
    }

    void colorGraph()
    {
        auto start = std::chrono::high_resolution_clock::now(); // Marca o início do tempo

        // Passo 1: Inicializar vetor de cores com -1
        std::fill(colors.begin(), colors.end(), -1);

        // Passo 2: Ordenar vértices em ordem decrescente de grau
        std::vector<int> vertices(n);
        for (int i = 0; i < n; ++i)
            vertices[i] = i;
        std::sort(vertices.begin(), vertices.end(), [&](int a, int b)
                  { return adjList[a].size() > adjList[b].size(); });

        // Passo 3: Colorir cada vértice
        for (int v : vertices)
        {
            std::vector<bool> forbiddenColors(n, false); // Vetor para cores proibidas

            // Passo 3a e 3b: Encontrar cores proibidas dos vizinhos
            for (int u : adjList[v])
            {
                if (colors[u] != -1)
                {
                    forbiddenColors[colors[u]] = true;
                }
            }

            // Passo 3c e 3d: Encontrar a menor cor não proibida
            int color = 0;
            while (color < n && forbiddenColors[color])
            {
                color++;
            }

            // Passo 3e: Atribuir a cor ao vértice
            colors[v] = color;
        }

        // Contar o número de cores distintas usadas
        numDistinctColors = 0;
        for (int color : colors)
        {
            if (color >= numDistinctColors)
            {
                numDistinctColors = color + 1; // Ajusta o número de cores distintas
            }
        }

        auto end = std::chrono::high_resolution_clock::now(); // Marca o final do tempo
        executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Calcula o tempo de execução em milissegundos
        printColors();
    }

    void printColors() const
    {
        for (int i = 0; i < n; ++i)
        {
            std::cout << "Vértice " << i << " -> Cor " << colors[i] << "\n";
        }
        std::cout << "Número de cores diferentes usadas: " << numDistinctColors << "\n";
        std::cout << "Tempo de execução: " << executionTime << " ms\n";
    }

    int getNumDistinctColors() const
    {
        return numDistinctColors;
    }

    long long getExecutionTime() const
    {
        return executionTime;
    }

private:
    int n;                                 // Número de vértices
    int numDistinctColors;                 // Número de cores distintas usadas
    long long executionTime;               // Tempo de execução em milissegundos
    std::vector<std::vector<int>> adjList; // Lista de adjacência
    std::vector<int> colors;               // Vetor de cores atribuídas aos vértices
};
