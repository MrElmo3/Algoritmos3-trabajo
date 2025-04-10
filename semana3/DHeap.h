#pragma once
#include <vector>
#include <any>

struct Element {
	std::any data;
	float priority;
};

class DHeap {
public:

	std::vector<Element> pairs;
	int d;

	DHeap(
	std::vector<std::any> elements = {}, 
	std::vector<float> priorities = {}, 
	int branchingFactor = 2);

	/**
	 * @brief Verifica que se cumplan las tres invariantes del heap:
	 * 
	 * 1. Cada nodo tiene como máximo `D` hijos. 
	 * (Garantizado por la construcción)
	 * 
	 * 2. El árbol del heap es completo y alineado a la izquierda. 
	 * (También garantizado por la construcción)
	 * 
	 * 3. Cada nodo contiene la mayor prioridad en el subárbol con raíz en ese nodo.
	 * 
	 * @return True si se cumplen todas las invariantes del heap.
	 */
	bool Validate();
	
	/**
	 * @brief Empuja hacia abajo la raíz de un sub-heap hacia sus hojas para restablecer las invariantes del heap.
	 * Si alguno de los hijos del elemento tiene mayor prioridad, se intercambia el elemento actual
	 * con su hijo de mayor prioridad, y se verifica recursivamente el sub-heap que estaba previamente
	 * enraizado en ese hijo.
	 * @param index: El índice de la raíz del sub-heap.
	 */
	void PushDown(int index);

	/**
	 * @brief Eleva un elemento hacia la raíz para restablecer las invariantes del heap.
	 * Si el padre del elemento tiene menor prioridad, se intercambian el elemento actual y su padre,
	 * y se verifica recursivamente la posición anterior.
	 * @param index: El índice del elemento a elevar.
	 */
	void BubbleUp(int index);

	int FirstChild(int index) const;
	int Parent(int index) const;
	int HighestPriorityChild(int index) const;

	void Heapify(std::vector<std::any> elements, std::vector<float> priorities);

	void Insert(std::any element, float priority);

	std::any Top();
	std::any Peek();

	int FirstLeaf() const;
	bool IsEmpty() const;
	int GetSize() const;
};