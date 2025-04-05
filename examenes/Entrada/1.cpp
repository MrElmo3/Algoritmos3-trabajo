#include <iostream>
#include <assert.h>
#include <vector>
#include <limits>

struct PersonPreference {
	int A;
	int B;
	int C;

	PersonPreference(int _a, int _b, int _c){

		assert(_a >= 0);
		assert(_b >= 0);
		assert(_c >= 0);

		assert(_a <= 10000);
		assert(_b <= 10000);
		assert(_c <= 10000);

		assert(_a + _b + _c <= 10000);

		this->A = _a;
		this->B = _b;
		this->C = _c;
	};
};

int MaxPeopleParty(std::vector<PersonPreference> persons);

int MaxPeoplePartyHelper(
	int maxPeople, 
	std::vector<int> bebrage, 
	std::vector<PersonPreference> nextPersons);

int main(int argc, char const *argv[]) {
	std::string _;
	
	int testNumber;

	std::cout<<"Number of tests: ";
	std::getline(std::cin, _);
	testNumber = std::stoi(_);
	std::fflush(stdin);

	assert(testNumber > 0);

	for (int i = 0; i < testNumber; i++) {
		
		auto personList = std::vector<PersonPreference>();
		int personNumber;

		std::cout<<"Number of persons: ";
		std::getline(std::cin, _);
		personNumber = std::stoi(_);
		std::fflush(stdin);

		assert (personNumber > 0);

		for(int j = 0; j < personNumber; j++) {
			int _a;
			int _b;
			int _c;
			
			std::cout<<"Person data: ";
			std::getline(std::cin, _, ' ');
			_a = std::stoi(_);
			std::getline(std::cin, _, ' ');
			_b = std::stoi(_);
			std::getline(std::cin, _);
			_c = std::stoi(_);
			std::fflush(stdin);

			auto person = PersonPreference(_a, _b, _c);
			personList.push_back(person);
		}

		int result = MaxPeopleParty(personList);

		std::cout<<"Caso #"<<i + 1<<": "<<result<<std::endl;

	}
	
	return 0;
}

int MaxPeopleParty(std::vector<PersonPreference> persons) {
	std::vector<int> bebrage = {0, 0, 0};
	int maxPeople = 0;

	return MaxPeoplePartyHelper(maxPeople, bebrage, persons);
}

int MaxPeoplePartyHelper(
	int maxPeople, 
	std::vector<int> bebrage, 
	std::vector<PersonPreference> nextPersons){

	if(nextPersons.size() == 0) return maxPeople;

	std::vector<int> newBebrage = bebrage;

	newBebrage[0] = std::max(bebrage[0], nextPersons[0].A);
	newBebrage[1] = std::max(bebrage[1], nextPersons[0].B);
	newBebrage[2] = std::max(bebrage[2], nextPersons[0].C);

	if(newBebrage[0] + newBebrage[1] + newBebrage[2] > 10000) return maxPeople;
	
	std::vector<PersonPreference> auxPersonList = nextPersons;

	auxPersonList.erase(auxPersonList.begin());

	MaxPeoplePartyHelper(maxPeople + 1, newBebrage, auxPersonList);
	
	return std::max(
		MaxPeoplePartyHelper(maxPeople + 1, newBebrage, auxPersonList),
		MaxPeoplePartyHelper(maxPeople, bebrage, auxPersonList)
	);

}
