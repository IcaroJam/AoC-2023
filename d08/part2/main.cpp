#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <numeric>

void traverseMap(const std::string &dirs, std::vector<std::string> lookup, std::unordered_map<std::string, std::pair<std::string, std::string>> &hauntMap, size_t &numOSteps) {
	int	i;
	int	n;
	std::vector<size_t>	turns;

	for (int j = 0; j < lookup.size(); j++) {
		i = n = 0;
		while (lookup[j][2] != 'Z') {
			lookup[j] = dirs[i] == 'L' ? hauntMap[lookup[j]].first : hauntMap[lookup[j]].second;

			n++;

			i++;
			if (!dirs[i])
				i = 0;
		}
		turns.push_back(n);
	}

	for (int j = 0; j < turns.size(); j++)
		std::cout << turns[j] << std::endl;

	for (int j = 0; j < turns.size() - 1; j++)
		turns[j + 1] = std::lcm(turns[j], turns[j + 1]);
	numOSteps = turns.back();
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	std::string	directions, tmp;
	size_t		numOSteps = 0;

	std::getline(inFile, directions);

	std::vector<std::string>												lookup;
	std::unordered_map<std::string, std::pair<std::string, std::string>>	hauntMap;

	// Fill the map with everything needed:
	std::getline(inFile, tmp); // Skip the empty line
	while (std::getline(inFile, tmp)) {
		std::string	key = tmp.substr(0, tmp.find_first_of(" "));
		std::string	L = tmp.substr(tmp.find_first_of("(") + 1, 3);
		std::string	R = tmp.substr(tmp.find_first_of(",") + 2, 3);

		hauntMap[key] = {L, R};

		// We'll store here all the starting points:
		if (key[2] == 'A')
			lookup.push_back(key);
	}

	traverseMap(directions, lookup, hauntMap, numOSteps);

	std::cout << "\nNumber of total steps required is: " << numOSteps << std::endl;
}
