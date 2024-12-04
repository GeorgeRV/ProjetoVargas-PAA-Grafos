#ifndef A2_HEAP_H
#define A2_HEAP_H

#include <vector>
#include <limits.h>  // Para INT_MAX
#include <algorithm> // Para std::swap

typedef int vertex;

class Heap {
public:
    Heap() {}

    // Verifica se o heap está vazio
    bool empty() const {
        return m_heap.empty();
    }

    // Retorna o topo (menor valor)
    std::pair<int, vertex> top() const {
        return m_heap.front(); // O topo do heap é sempre o primeiro elemento
    }

    // Remove o topo
    void pop() {
        if (!empty()) {
            // Troca o topo com o último elemento, depois faz o "descer" (heapify down)
            std::swap(m_heap.front(), m_heap.back());
            m_heap.pop_back();
            heapifyDown(0);
        }
    }

    // Insere ou atualiza um vértice no heap
    void insert_or_update(int cost, vertex v) {
        auto it = findVertex(v);
        if (it != m_heap.end()) {
            // Se o vértice já existe, apenas atualizamos o custo e fazemos "subir" (heapify up)
            it->first = cost;
            heapifyUp(std::distance(m_heap.begin(), it));
        } else {
            // Caso contrário, insere o novo vértice no final e faz "subir"
            m_heap.push_back({cost, v});
            heapifyUp(m_heap.size() - 1);
        }
    }

private:
    // Vetor de pares (custo, vértice)
    std::vector<std::pair<int, vertex>> m_heap;

    // Encontra o índice de um vértice no heap
    typename std::vector<std::pair<int, vertex>>::iterator findVertex(vertex v) {
        return std::find_if(m_heap.begin(), m_heap.end(), [v](const std::pair<int, vertex>& p) {
            return p.second == v;
        });
    }

    // Faz o "subir" (heapify up) no índice indicado para manter a propriedade do heap
    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parentIndex = (index - 1) / 2;
            if (m_heap[index].first < m_heap[parentIndex].first) {
                std::swap(m_heap[index], m_heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // Faz o "descer" (heapify down) no índice indicado para manter a propriedade do heap
    void heapifyDown(size_t index) {
        size_t leftChild, rightChild, smallest;
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            smallest = index;

            if (leftChild < m_heap.size() && m_heap[leftChild].first < m_heap[smallest].first) {
                smallest = leftChild;
            }

            if (rightChild < m_heap.size() && m_heap[rightChild].first < m_heap[smallest].first) {
                smallest = rightChild;
            }

            if (smallest != index) {
                std::swap(m_heap[index], m_heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
};

#endif //A2_HEAP_H

