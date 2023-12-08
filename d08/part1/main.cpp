#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

void traverseMap(const std::string &dirs, std::vector<std::string> lookup, std::unordered_map<std::string, std::pair<std::string, std::string>> &hauntMap, int  &n) {
	int			i = 0;
	std::string	curr = "AAA";

	while (curr != "ZZZ") {
		std::cout << n << ": " << curr << std::endl;
		curr = dirs[i] == 'L' ? hauntMap[curr].first : hauntMap[curr].second;
		n++;

		i++;
		if (!dirs[i])
		    i = 0;
	}
	std::cout << n << ": " << curr << std::endl;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	std::string	directions, tmp;
	int			numOSteps = 0;

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
		lookup.push_back(key);
	}

	traverseMap(directions, lookup, hauntMap, numOSteps);

	std::cout << "\nNumber of total steps required is: " << numOSteps << std::endl;
}
