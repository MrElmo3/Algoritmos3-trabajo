#include <chrono>
#include <iostream>

using namespace std::chrono;

int dataList[] = {100, 1000, 5000, 10000, 50000};


double orderTimeStimation(
	double dataSize, 
	double assignationTime, 
	double comparationTime) {

	return (assignationTime * dataSize + dataSize*(dataSize-1)/2 * (assignationTime + comparationTime));

};

int main(int argc, char const *argv[]) {

	auto start1 = high_resolution_clock::now();

	int patata = 5;

	auto stop1 = high_resolution_clock::now();

	const double assignationTime = duration_cast<microseconds>(stop1 - start1).count();

	std::cout<< assignationTime << std::endl;

	auto start2 = high_resolution_clock::now();

	if (5>2){}

	auto stop2 = high_resolution_clock::now();

	const double comparationTime = duration_cast<microseconds>(stop2 - start2).count();
	
	for(int i = 0; i< 5; i++){
		float time = orderTimeStimation(dataList[i], 0.00001, 0.000001);
		std::cout<< time <<std::endl;
	}

	return 0;
}



