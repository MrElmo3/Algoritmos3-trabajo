#include <iostream>
#include <assert.h>
#include <unordered_map>

//nota: profesor esta implementacion 
//del grafo es mia hecha para un proyecto pasado

/**
 * @brief This struct represents an edge in a graph
 */
struct Edge{
	int from;
	int to;
	int weight;
	Edge* nextEdge;

	Edge();
	Edge(int v1, int v2);
	Edge(int from, int data, int weight);

	~Edge();

};
typedef Edge* pEdge;

/**
 * @brief This struct represents a node in a graph
 */
struct Node{
	int ID;
	int nodeData; //this is for knowing where the player is
	int distanceToRoot;
	bool tempData; //this is for checking algorithm stuff
	pEdge conection;
	Node* nextNode;

public:
	Node();
	Node(int ID);
	Node(int ID, int data);

	~Node();
};
typedef Node* pNode;


/**
 * @brief This class represents a no-directed graph
 */
class Graph{
private:
	pNode head;
	int nodeNumber;

public:

	Graph();
	
	~Graph();
	
	/**
	 * @brief This method inserts a node in the graph
	 * @param ID The ID of the node to insert
	 */
	void InsertNode(int ID);

	/**
	 * @brief This method deletes a node in the graph
	 * @param ID The ID of the node to delete
	 */
	void DeleteNode(int ID);

	/**
	 * @brief This method checks if a node exists in the graph
	 * @param ID The ID of the node to check
	 * @return True if the node exists, false otherwise
	 */
	bool ExistNode(int ID);

	/**
	 * @brief This method inserts an edge in the graph
	 * @param IDx The ID of the first node
	 * @param IDy The ID of the second node
	 */
	void InsertEdge(int IDx, int IDy);

	/**
	 * @brief This method deletes an edge in the graph
	 * @param IDx The ID of the first node
	 * @param IDy The ID of the second node
	 */
	void DeleteEdge(int IDx, int IDy);

	/**
	 * @brief This method searches a node in the graph
	 * @param IDnode The ID of the node to search
	 * @return The node if it exists, nullptr otherwise
	 */
	pNode SearchNodeByID(int IDnode);

	int MaxCycleSize();

private:
	int SearchMaxCycleDFS(
		int currentID, 
		int parentID, 
		int depth, 
		std::unordered_map<int, int>& depthMap);
};

Edge::Edge() {
	nextEdge = nullptr;
	from = 0;
	to = 0;
	weight = 0;
};

Edge::Edge(int v1, int v2) {
	from = v1;
	to = v2;
	weight = 0;
	nextEdge = nullptr;
}

Edge::Edge(int v1, int v2, int weight) : Edge::Edge(v1, v2) {
	weight = weight;
}

Edge::~Edge() {
};

//Node implementation
Node::Node() {
	ID = -1;
	distanceToRoot = -1;
	nodeData = 0;
	nextNode = nullptr;
	conection = nullptr;
	tempData = false;
};

Node::Node(int ID) : Node::Node() {
	this->ID = ID;
};

Node::Node(int ID, int data) : Node::Node(ID) {
	this->nodeData = data;
};

Node::~Node() {
	ID = -1;
	distanceToRoot = -1;
	nodeData = 0;
	tempData = false;
	conection = nullptr;
	nextNode = nullptr;
};

//Graph implementation
Graph::Graph() {
	head = nullptr;
	nodeNumber = 0;
};

Graph::~Graph() {
	pNode graphHead = this->head;

	while (graphHead != nullptr) {
		pNode nodeToDelete = graphHead;
		DeleteNode(nodeToDelete->ID);
		graphHead = graphHead->nextNode;
	}
};

void Graph::InsertNode(int ID) {
	if(SearchNodeByID(ID)) {
		std::cout << "Node already exists" << std::endl;
		return;
	}
	pNode newNode;
	newNode = new Node(ID);

	newNode->nextNode = head;
	head = newNode;

	nodeNumber++;
	std::cout<< "Node inserted with ID: " << ID << std::endl;
};

//Deletes a node with the ID given
void Graph::DeleteNode(int ID) {
	pNode nodeToDelete = SearchNodeByID(ID);

	if(nodeToDelete == nullptr) {
		std::cout << "Node does not exist" << std::endl;
		return;
	}
	
	//Delete edges related to this node
	while(nodeToDelete->conection != nullptr) {
		DeleteEdge(nodeToDelete->ID, nodeToDelete->conection->to);
	}	

	//deleting the node
	pNode graphHead = head;

	if (graphHead->ID == ID) {
		head = head->nextNode;
		nodeToDelete->~Node();
		return;
	}

	while (head->nextNode != nodeToDelete) {
		head = head->nextNode;
	}

	head->nextNode = nodeToDelete->nextNode;
	nodeToDelete->~Node();
};

//Checks if a node with the ID given exists
bool Graph::ExistNode(int ID) {
	if(nodeNumber == 0) return false;
	if(ID < 0) return false;
	if(SearchNodeByID(ID)) return true;
	return false;
};

//Searches for a node with the ID given
pNode Graph::SearchNodeByID(int IDnode) {
	pNode graphHead;
	graphHead = head;

	while (graphHead != nullptr) {
		if (graphHead->ID == IDnode)
			return graphHead;
		graphHead = graphHead->nextNode;
	}

	return nullptr;

};

//Inserts an edge between two nodes with the IDs given
void Graph::InsertEdge(int IDx, int IDy) {

	if (IDx < 0 || IDy < 0) {
		std::cout << "Invalid ID" << std::endl;
		return;
	}

	if (IDx == IDy) {
		std::cout << "Can't insert an edge between the same node" << std::endl;
		return;
	}

	if (nodeNumber <= 1) {
		std::cout << "graph is empty or only have 1 Node" << std::endl;
		return;
	}

	pEdge newEdge;
	pEdge edgeHead;
	pNode nodeX = SearchNodeByID(IDx);
	pNode nodeY = SearchNodeByID(IDy);

	if (nodeX == nullptr || nodeY == nullptr) {
		std::cout << "one or both nodes do not exist in trying to insert Edge (" << IDx << ", " << IDy << ")" << std::endl;
		return;
	}

	//Cheking for X
	edgeHead = nodeX->conection;
	while (edgeHead != nullptr) {
		if (edgeHead->to == IDy) {
			std::cout << "the Edge already exists" << std::endl;
			return;
		}
		edgeHead = edgeHead->nextEdge;
	};
	//Inserting for X
	newEdge = new Edge(IDx, IDy);
	newEdge->nextEdge = nodeX->conection;
	nodeX->conection = newEdge;

	//Cheking for Y
	edgeHead = nodeY->conection;
	while (edgeHead != nullptr) {
		if (edgeHead->to == IDx) {
			std::cout << "the Edge already exists" << std::endl;
			return;
		}
		edgeHead = edgeHead->nextEdge;
	};
	//Inserting for Y
	newEdge = new Edge(IDy, IDx);
	newEdge->nextEdge = nodeY->conection;
	nodeY->conection = newEdge;

	//Setting the distance to root
	if (nodeX->distanceToRoot == -1) { nodeX->distanceToRoot = nodeY->distanceToRoot + 1; }
	if (nodeY->distanceToRoot == -1) { nodeY->distanceToRoot = nodeX->distanceToRoot + 1; }
};

//Deletes an edge between two nodes with the IDs given
void Graph::DeleteEdge(int IDx, int IDy) {
	pEdge edgeToDelete;
	pEdge edgeHead;
	pNode nodeX = SearchNodeByID(IDx);
	pNode nodeY = SearchNodeByID(IDy);

	if (nodeNumber <= 1) {
		std::cout << "graph is empty or only have 1 Node" << std::endl;
		return;
	}

	if (!SearchNodeByID(IDx) || !SearchNodeByID(IDy)) {
		std::cout << "one or both nodes do not exist in trying to delete Edge (" << IDx << ", " << IDy << ")" << std::endl;
		return;
	}

	if (IDx == IDy) {
		std::cout << "Can't delete an edge between the same node" << std::endl;
		return;
	}

	//Deleting for X
	edgeHead = nodeX->conection;
	if (edgeHead->to == IDy) {
		nodeX->conection = edgeHead->nextEdge;
		edgeHead->~Edge();
	}
	else {
		while (edgeHead->nextEdge->to != IDy) {
			edgeHead = edgeHead->nextEdge;
		}
		edgeToDelete = edgeHead->nextEdge;
		edgeHead->nextEdge = edgeToDelete->nextEdge;
		edgeToDelete->~Edge();
	}

	//Deleting for Y
	edgeHead = nodeY->conection;
	if (edgeHead->to == IDx) {
		nodeY->conection = edgeHead->nextEdge;
		edgeHead->~Edge();
	}
	else {
		while (edgeHead->nextEdge->to != IDx) {
			edgeHead = edgeHead->nextEdge;
		}
		edgeToDelete = edgeHead->nextEdge;
		edgeHead->nextEdge = edgeToDelete->nextEdge;
		edgeToDelete->~Edge();
	}
};

int Graph::MaxCycleSize() {
	// Reiniciar los datos temporales de cada nodo
	pNode graphHead = head;
	while (graphHead != nullptr) {
		graphHead->tempData = false;
		graphHead = graphHead->nextNode;
	}

	int maxCycleSize = 0;
	graphHead = head;
	while (graphHead != nullptr) {
		if (graphHead->tempData == false) {
			std::unordered_map<int, int> depthMap;
			maxCycleSize = std::max(
				maxCycleSize, 
				SearchMaxCycleDFS(graphHead->ID, -1, 0, depthMap));
		}
		graphHead = graphHead->nextNode;
	}

	return maxCycleSize;
}

// Retorna el tamaño máximo de un ciclo encontrado desde este nodo
int Graph::SearchMaxCycleDFS(
	int currentID, 
	int parentID, 
	int depth, 
	std::unordered_map<int, int>& depthMap) {
	
	pNode currentNode = SearchNodeByID(currentID);
	currentNode->tempData = true;
	depthMap[currentID] = depth;

	int maxCycleSize = 0;
	pEdge edge = currentNode->conection;

	while (edge != nullptr) {
		int neighborID = edge->to;

		if (depthMap.find(neighborID) == depthMap.end()) {
			maxCycleSize = std::max(
				maxCycleSize,
				SearchMaxCycleDFS(neighborID, currentID, depth + 1, depthMap));
		}
		else if (neighborID != parentID) {
			// Encontramos un ciclo: calcular su tamaño
			int cycleSize = depth - depthMap[neighborID] + 1;
			maxCycleSize = std::max(maxCycleSize, cycleSize);
		}

		edge = edge->nextEdge;
	}

	depthMap.erase(currentID);
	return maxCycleSize;
}

int main(int argc, char const *argv[]) {
	std::string _;
	
	int testNumber;

	std::cout<<"Number of tests: ";
	std::getline(std::cin, _);
	testNumber = std::stoi(_);
	std::fflush(stdin);

	assert(testNumber > 0);

	for (int i = 0; i < testNumber; i++) {
		
		int nodeNumber;

		std::cout<<"Number of nodes: ";
		std::getline(std::cin, _);
		nodeNumber = std::stoi(_);
		std::fflush(stdin);

		assert (nodeNumber > 3);

		//base graph definition

		Graph graph = Graph();
		graph.InsertNode(0);
		graph.InsertNode(1);
		graph.InsertNode(2);

		graph.InsertEdge(0 , 1);
		graph.InsertEdge(0 , 2);
		graph.InsertEdge(1 , 2);

		for(int j = 3; j < nodeNumber; j++) {
			graph.InsertNode(j);
			int indexA;
			int indexB;

			std::cout<<"Connections: ";
			std::getline(std::cin, _, ' ');
			indexA = std::stoi(_);
			std::getline(std::cin, _);
			indexB = std::stoi(_);

			graph.InsertEdge(j, indexA - 1);
			graph.InsertEdge(j, indexB - 1);
		}

		int result = graph.MaxCycleSize();

		std::cout<<"Caso #"<<i + 1<<": "<<result<<std::endl;

	}
	
	return 0;
}
