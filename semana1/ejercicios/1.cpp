#include <assert.h>
#include <vector>
#include <iostream>

int FindCrossoverIndexHelper(
	std::vector<float> x, 
	std::vector<float> y, 
	int left, 
	int right){
	
	// Aserciones para los invariantes
	assert(x.size() == y.size());
	assert(left >= 0);
	assert(left <= right - 1);

	//Aserciones para mantenernos dentro del bucle
	assert(x[left] > y[left]);
	assert(x[right] < y[right]);

	// Caso base
	if(left + 1 == right) return left;

	int mid = left + (right-left) / 2;

	//En caso que el punto de cruze ya haya pasado, se busca mas hacia la izquierda
	if( x[mid] < y[mid]){
		return FindCrossoverIndexHelper(x, y, left, mid);
	}

	//en caso contrario, mas a la derecha
	return FindCrossoverIndexHelper(x, y, mid, right);

};

int FindCrossoverIndex(std::vector<float> x, std::vector<float> y){
	
	assert(x.size() == y.size());
	
	assert(x[0] > y[0]);
	int n = x.size();
	assert(x[n-1] < y[n-1]);

	return FindCrossoverIndexHelper(x, y, 0, n-1);
};


int main(int argc, char const *argv[]) {
	
	int j1 = FindCrossoverIndex(
		{0, 1, 2, 3, 4, 5, 6, 7}, 
		{-2, 0, 4, 5, 6, 7, 8, 9}
	);
	std::cout<<"j1 = "<< j1 <<std::endl;
	assert(j1 == 1);

	int j2 = FindCrossoverIndex(
		{0, 1, 2, 3, 4, 5, 6, 7}, 
		{-2, 0, 4, 4.2, 4.3, 4.5, 8, 9}
	);
	std::cout<<"j2 = "<< j2 <<std::endl;
	assert(j2 == 1 || j2 == 5);

	int j3 = FindCrossoverIndex(
		{0, 1}, 
		{-10, 10}
	);
	std::cout<<"j3 = "<< j3 <<std::endl;
	assert(j3 == 0);

	int j4 = FindCrossoverIndex(
		{0, 1, 2, 3}, 
		{-10, -9, -8, 5}
	);
	std::cout<<"j4 = "<< j4 <<std::endl;
	assert(j4 == 2);

	std::cout<<"¡Felicidades: Todos los tests pasaron! (10 puntos)"<<std::endl;

	/*

	El algoritmo se comporta de la misma forma que una busqueda binaria
	La unica diferencia que se encuentra es en la condicional para
	establecer la recursion

	Por lo que la complejidad temporal del algoritmo viene siendo igual que
	la busqueda binaria; es decir, O(log(n))

	*/
}