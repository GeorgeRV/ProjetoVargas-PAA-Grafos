#ifndef A2_DATA_H
#define A2_DATA_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <locale>
#include "graph.h"

struct Node {
    int id;
    std::string region;
    std::string type;
};

struct Edge {
    int source;
    int target;
    int length;
    int speed_limit;
    int cost;
};

struct Region{
    int start;
    int size;
    std::string id;
};

// Função genérica para ler CSV e retornar um vetor de strings
std::vector<std::vector<std::string>> lerCSV(const std::string& caminhoArquivo) {
    std::vector<std::vector<std::string>> dados;
    std::ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << std::endl;
        return dados;
    }

    std::string linha;
    // Lê o cabeçalho e ignora
    std::getline(arquivo, linha);

    // Lê as linhas seguintes
    while (std::getline(arquivo, linha)) {
        std::vector<std::string> linhaDados;
        std::stringstream ss(linha);
        std::string valor;

        // Divide a linha nas colunas
        while (std::getline(ss, valor, ',')) {
            linhaDados.push_back(valor);
        }
        dados.push_back(linhaDados);
    }

    arquivo.close();
    return dados;
}

// Função para carregar nós
std::vector<Node> carregarNodes(const std::string& caminhoArquivo) {
    std::vector<Node> nodes;
    auto dados = lerCSV(caminhoArquivo);

    for (const auto& linha : dados) {
        if (linha.size() == 3) { // Certifica que há duas colunas
            Node node;
            node.id = std::stoi(linha[0]);
            node.region = linha[1];
            node.type = linha[2];
            nodes.push_back(node);
        }
    }

    return nodes;
}

// Função para carregar arestas
std::vector<Edge> carregarEdges(const std::string& caminhoArquivo) {
    std::vector<Edge> edges;
    auto dados = lerCSV(caminhoArquivo);

    for (const auto& linha : dados) {
        if (linha.size() == 5) { // Certifica que há quatro colunas
            Edge edge;
            edge.source = std::stoi(linha[0]);
            edge.target = std::stoi(linha[1]);
            edge.length = std::stoi(linha[2]);
            edge.speed_limit = std::stoi(linha[3]);
            edge.cost = std::stoi(linha[4]);
            edges.push_back(edge);
        }
    }

    return edges;
}

// Função para carregar arestas
std::vector<Region> carregarRegions(const std::string& caminhoArquivo) {
    std::vector<Region> regions;
    auto dados = lerCSV(caminhoArquivo);

    for (const auto& linha : dados) {
        if (linha.size() == 3) { // Certifica que há quatro colunas
            Region region;
            region.start = std::stoi(linha[0]);
            region.size = std::stoi(linha[1]);
            region.id = linha[2];
            regions.push_back(region);
        }
    }

    return regions;
}

std::string verificarCaminho(const std::string& arquivo) {
    // Verifica se o arquivo existe no diretório atual
    if (std::filesystem::exists(arquivo)) {
        return arquivo;
    }
    // Caminho relativo alternativo (um nível acima)
    std::string caminhoAlternativo = "../" + arquivo;
    if (std::filesystem::exists(caminhoAlternativo)) {
        return caminhoAlternativo;
    }
    // Retorna vazio se nenhum dos caminhos for válido
    return "";
}

int readData() {
    // Caminhos dos arquivos CSV
    std::string nodesPath = verificarCaminho("nodes.csv");
    std::string edgesPath = verificarCaminho("edges.csv");
    std::string regionsPath = verificarCaminho("regions.csv");

    // Carrega os dados
    std::vector<Node> nodes = carregarNodes(nodesPath);
    std::vector<Edge> edges = carregarEdges(edgesPath);
    std::vector<Region> regions = carregarRegions(regionsPath);

    GraphCity G(42);

    for (const auto& edge : edges) {
        G.addEdge(edge.source,
                  edge.target,
                  edge.cost,
                  edge.length,
                  edge.speed_limit);
        G.addEdge(edge.target,
                  edge.source,
                  edge.cost,
                  edge.length,
                  edge.speed_limit);
    }

    for (const auto& region : regions) {
        G.addRegion(region.id,
                    region.start,
                    region.size);
    }


    G.defineSubwayLine();

    auto start = std::chrono::high_resolution_clock::now();
    G.defineSubwayLine();
    auto end = std::chrono::high_resolution_clock::now();

    G.printSubwayLine();

    std::chrono::duration<double> duration = end - start;

    // Exibindo o tempo em segundos
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;


    return 0;
}




#endif //A2_DATA_H
