#include "DHeap.h"
#include <stdexcept>
#include <assert.h>
#include <limits>

DHeap::DHeap(
	std::vector<std::any> elements, 
	std::vector<float> priorities, 
	int branchingFactor) {

	if (elements.size() != priorities.size()) {
		std::string error = 
			"La longitud de la lista de elementos (" + 
			std::to_string(elements.size()) + ")" +
			" debe coincidir con la longitud de la lista de prioridades (" + 
			std::to_string(priorities.size()) + ")";
		throw std::invalid_argument(error);
	}


	if(branchingFactor < 2) {
		std::string error = 
			"El factor de ramificación (" + 
			std::to_string(branchingFactor) + 
			") debe ser mayor que 1.";
		throw std::invalid_argument(error);
	}

	d = branchingFactor;

	if (elements.size() > 0) {
		Heapify(elements, priorities);
	}
}

bool DHeap::Validate() {
	int currentIndex = 0;
	int firstLeaf =  FirstLeaf();
	
	while ( currentIndex < firstLeaf ) {
		
		float currentPriority = pairs[currentIndex].priority;
		int firstChild = FirstChild(currentIndex);
		int lastChild = std::min(firstChild + d, GetSize());

		for (size_t i = firstChild; i < lastChild; i++) {
			if (currentPriority < pairs[i].priority) return false;
		}
		currentIndex++;
	}
	return true;
}

void DHeap::PushDown(int index) {
	
	assert(0 <= index && index < pairs.size());

	Element inputPair = pairs[index];
	float inputPriority = inputPair.priority;
	int currentIndex = index;
	int firstLeaf = FirstLeaf();

	while ( currentIndex < firstLeaf ) {
		
		int highestChildIndex = HighestPriorityChild(currentIndex);
		assert (highestChildIndex != -1);

		if(pairs[highestChildIndex].priority <= inputPriority) {
			break;
		}

		pairs[currentIndex] = pairs[highestChildIndex];
		currentIndex = highestChildIndex;
	}

	pairs[currentIndex] = inputPair;
}

void DHeap::BubbleUp(int index) {
	
	assert(0 <= index && index < pairs.size());

	Element inputPair = pairs[index];
	float inputPriority = inputPair.priority;
	int currentIndex = index;

	while (currentIndex > 0) {
		int parentIndex = Parent(currentIndex);
		assert (parentIndex != -1);

		if(pairs[parentIndex].priority >= inputPriority) {
			break;
		}

		pairs[currentIndex] = pairs[parentIndex];
		currentIndex = parentIndex;
	}

	pairs[currentIndex] = inputPair;
}

int DHeap::FirstChild(int index) const {
	return d * index + 1;
}

int DHeap::Parent(int index) const {
	if (index == 0) {
		return -1;
	}
	return (index - 1) / d;
}

int DHeap::HighestPriorityChild(int index) const {
	int firstIndex = FirstChild(index);
	int lastIndex = std::min(firstIndex + d, GetSize());

	if (firstIndex >= GetSize()) {
		return -1;
	}

	float highestPriority = -1 * std::numeric_limits<float>::infinity();
	int indexResult = firstIndex;
	for (size_t i = firstIndex; i < lastIndex; i++) {
		if (pairs[i].priority > highestPriority) {
			highestPriority = pairs[i].priority;
			indexResult = i;
		}
	}
	return indexResult;
}

void DHeap::Heapify(std::vector<std::any> elements, std::vector<float> priorities) {
	
	assert(elements.size() == priorities.size());

	pairs.resize(elements.size());	
	for (size_t i = 0; i < elements.size(); i++) {
		pairs[i].data = elements[i];
		pairs[i].priority = priorities[i];
	}

	int lastInnerNode = FirstLeaf() -1;
	for (int i = lastInnerNode; i >= 0; i--) {
		PushDown(i);
	}
}

void DHeap::Insert(std::any element, float priority) {
	Element newElement;
	newElement.data = element;
	newElement.priority = priority;

	pairs.push_back(newElement);
	BubbleUp(GetSize() - 1);
}

std::any DHeap::Top() {
	if (IsEmpty()) {
		throw std::out_of_range("Heap is empty.");
	}
	Element topElement = pairs[0];
	pairs[0] = pairs.back();
	pairs.pop_back();
	if(GetSize() > 1) PushDown(0);
	return topElement.data;
}

std::any DHeap::Peek() {
	if (IsEmpty()) {
		throw std::out_of_range("Heap is empty.");
	}
	return pairs[0].data;
}

int DHeap::FirstLeaf() const {
	return (GetSize() - 2) / d + 1;
}

bool DHeap::IsEmpty() const {
	return pairs.empty();
}

int DHeap::GetSize() const {
	return pairs.size();
}

