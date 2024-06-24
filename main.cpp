#include <iostream>
#include <map>
#include <numeric>

#include "myallocator.h"

#define CONTAINER_SIZE 10

using namespace std;

template <typename Map>
void fillFactorial(Map &map, int size) {
	map[0] = 1;
	for (int i = 1; i < size; ++i) {
		map[i] = map[i - 1] * i;
	}
}

template <typename Map>
void printMap(const Map &map) {
	for (auto [key, value] : map) {
		cout << key << " " << value << "\n";
	}
}

void testStdMapWithStdAlloc() {
	map<int, int> map;
	fillFactorial(map, CONTAINER_SIZE);
	printMap(map);
}

void testStdMapWithMyAlloc() {
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int> > > map(MyAllocator<std::pair<const int, int>>(10));
	fillFactorial(map, CONTAINER_SIZE);
	printMap(map);
}

void testStdMapWithScalableMyAlloc() {
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int> > > map;
	fillFactorial(map, CONTAINER_SIZE);
	printMap(map);
}

int main() {
	try {
		testStdMapWithStdAlloc();
		testStdMapWithMyAlloc();
		testStdMapWithScalableMyAlloc();
	} catch(const exception &e) {
		cerr << e.what() << endl;
	}

	return 0;
}
