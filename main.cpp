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

int main() {
	try {
		map<int, int> map1;
		fillFactorial(map1, CONTAINER_SIZE);

		std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int> > > map2(MyAllocator<std::pair<const int, int>>(10));
		fillFactorial(map2, CONTAINER_SIZE);

		cout << "Default: \n ";
		printMap(map1);

		cout << "Custom: \n";
		printMap(map2);
		cout << endl;

	} catch(const exception &e) {
		cerr << e.what() << endl;
	}

	return 0;
}
