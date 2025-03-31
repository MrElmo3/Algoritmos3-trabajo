#include <assert.h>
#include <vector>
#include <iostream>

int IntegerCubeRootHelper(
	int n,
	int left, 
	int right){
	
	auto cube = [](float n) {return n*n*n;};
	
	// Aserciones para los invariantes
	assert(n >= 1);
	assert(left >= 0);
	assert(left <= right - 1);

	//Aserciones para mantenernos dentro del bucle
	assert(right <= n);
	assert(cube(left) < n);
	assert(cube(right) > n);

	int mid = left + (right-left) / 2;

	if(left + 1 == right) return left;
	if(cube(mid) == n) return mid;

	//En caso que el punto de cruze ya haya pasado 
	//se busca mas hacia la izquierda
	if( cube(mid) < n){
		return IntegerCubeRootHelper(n, mid, right);
	}

	//en caso contrario, mas a la derecha
	return IntegerCubeRootHelper(n, left, mid);

};

int IntegerCubeRoot(int n){
	
	assert(n > 0);
	
	if (n == 1 || n == 2) return 1;

	return IntegerCubeRootHelper(n, 0, n-1);
};


int main(int argc, char const *argv[]) {
	
	assert(IntegerCubeRoot(1) == 1 && "Test 1");
	assert(IntegerCubeRoot(2) == 1 && "Test 2");
	assert(IntegerCubeRoot(4) == 1 && "Test 3");
	assert(IntegerCubeRoot(7) == 1 && "Test 4");
	assert(IntegerCubeRoot(8) == 2 && "Test 5");
	assert(IntegerCubeRoot(20) == 2);
	assert(IntegerCubeRoot(26) == 2);

	for(int i = 27; i < 64; i++){
		assert(IntegerCubeRoot(i) == 3);
	}
	for(int i = 64; i < 125; i++){
		assert(IntegerCubeRoot(i) == 4);
	}
	for(int i = 125; i < 216; i++){
		assert(IntegerCubeRoot(i) == 5);
	}
	for(int i = 216; i < 343; i++){
		assert(IntegerCubeRoot(i) == 6);
	}
	for(int i = 343; i < 512; i++){
		assert(IntegerCubeRoot(i) == 7);
	}

	std::cout<<"¡Felicidades: Todos los tests pasaron! (10 puntos)"<<std::endl;
}