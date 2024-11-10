#include <iostream>
#include <fstream>
#include "InstanceReader.h"
#include "GraphColoring_ConstructiveHeuristic.h"

int main() {
    // Lista de arquivos de entrada e saída
    std::vector<std::string> inputFiles;
    std::vector<std::string> outputFiles;

    for (int i = 1; i <= 12; i++) {
        inputFiles.push_back("../Instances/Instance" + std::to_string(i) + "_450_LEI.txt");
        outputFiles.push_back("../Results/output" + std::to_string(i) + "_450_LEI.txt");
    }
    for (int i = 1; i <= 5; i++) {
        inputFiles.push_back("../Instances/Instance" + std::to_string(i) + "_MYC.txt");
        outputFiles.push_back("../Results/output" + std::to_string(i) + "_MYC.txt");
    }
    for (int i = 1; i <= 14; i++) {
        inputFiles.push_back("../Instances/Instance" + std::to_string(i) + "_REG.col");
        outputFiles.push_back("../Results/output" + std::to_string(i) + "_REG.txt");
    }
    for (int i = 1; i <= 10; i++) {
        inputFiles.push_back("../Instances/Instance" + std::to_string(i) + "_SGB.txt");
        outputFiles.push_back("../Results/output" + std::to_string(i) + "_SGB.txt");
    }

    // Processa cada arquivo
    for (size_t i = 0; i < inputFiles.size(); ++i) {
        const std::string& inputFilename = inputFiles[i];
        const std::string& outputFilename = outputFiles[i];

        // Ler o arquivo e carregar o grafo
        InstanceReader reader(inputFilename);
        int numVertices = reader.getNumVertices();
        const auto& edges = reader.getEdges();

        // Inicializar o grafo com o número de vértices
        GraphColoring_ConstructiveHeuristic graph(numVertices);

        // Adicionar as arestas ao grafo
        for (const auto& edge : edges) {
            graph.addEdge(edge[0], edge[1]);
        }

        // Executar o algoritmo de coloração
        graph.colorGraph();

        // Salvar o número de cores e o tempo de execução em um arquivo de saída
        std::ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
            outputFile << "Número de cores diferentes usadas: " << graph.getNumDistinctColors() << "\n";
            outputFile << "Tempo de execução: " << graph.getExecutionTime() << " ms\n";
            outputFile.close();
            std::cout << "Resultados salvos em " << outputFilename << "\n";
        } else {
            std::cerr << "Erro ao abrir o arquivo de saída " << outputFilename << ".\n";
        }
    }

    return 0;
}
