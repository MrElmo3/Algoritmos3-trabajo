#include <iostream>
#include <assert.h>
#include <vector>

struct SkipList {
private:
	float probability = 0.5;
	int numberElements;
	int numberLevels = 0;
	
	std::vector<std::vector<int>> Levels;

	SkipList(int numberElements, float probability){
		this->numberElements = numberElements;
		this->probability = probability;
	}
	
	void InitializeList(){
	
		
	}
};

int main(int argc, char const *argv[]) {
	
	return 0;
}
