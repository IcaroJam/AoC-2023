#include <iostream>
#include <fstream>
#include <vector>

void	buildSchemVect(const std::string &str, std::vector<std::string> &vect) {
	std::size_t	i = str.find('\n'), j = 0;

	while ((i != std::string::npos)) {
		std::string tmp = str.substr(j, i - j);
		vect.push_back(tmp);

		j = i + 1;
		i = str.find('\n', j);
	}
}

bool	isSymbol(char c) {
	return (c >= 33 && c <= 45) || c == '/' || (c >= 58 && c <= 64); // From ! to - and : to @
}

size_t	processNumber(const std::vector<std::string> &vect, size_t i, size_t j) {
	while (j > 0 && std::isdigit(vect[i][j - 1]))
		j--;
	return std::atoi(&vect[i].c_str()[j]);
}

// A gear can have at most 6 adjacent numbers. Checking whether the top and bottom rows have 0, 1 or 2 is important.
size_t	processGear(const std::vector<std::string> &vect, size_t i, size_t j) {
	size_t				ret = 1;
	std::vector<size_t>	adjNums;

	// Check all 8 adjacent characters if possible:
	if (i > 0) { // Top row
		if (j < vect[i].size() - 1 && std::isdigit(vect[i - 1][j + 1]) && !std::isdigit(vect[i - 1][j]))
			adjNums.push_back(processNumber(vect, i - 1, j + 1));
		if (std::isdigit(vect[i - 1][j]) && !std::isdigit(vect[i - 1][j - 1]))
			adjNums.push_back(processNumber(vect, i - 1, j));
		if (j > 0 && std::isdigit(vect[i - 1][j - 1]))
			adjNums.push_back(processNumber(vect, i - 1, j - 1));
	}
	if (i < vect.size() - 1) { // Bottom row
		if (j < vect[i].size() - 1 && std::isdigit(vect[i + 1][j + 1]) && !std::isdigit(vect[i + 1][j]))
			adjNums.push_back(processNumber(vect, i + 1, j + 1));
		if (std::isdigit(vect[i + 1][j]) && !std::isdigit(vect[i + 1][j - 1]))
			adjNums.push_back(processNumber(vect, i + 1, j));
		if (j > 0 && std::isdigit(vect[i + 1][j - 1]))
			adjNums.push_back(processNumber(vect, i + 1, j - 1));
	}
	if (j > 0 && std::isdigit(vect[i][j - 1])) // Left
		adjNums.push_back(processNumber(vect, i, j - 1));
	if (j < vect[i].size() - 1 && std::isdigit(vect[i][j + 1])) // Right
		adjNums.push_back(processNumber(vect, i, j + 1));

	if (adjNums.size() < 2)
		return 0;

	std::cout << "Gear found. Nums:" << std::endl;
	for (size_t k = 0; k < adjNums.size(); k++) {
		ret *= adjNums[k];
		std::cout << "\t" << adjNums[k] << std::endl;
	}
	std::cout << "Ratio: " << ret << std::endl << std::endl;
	return ret;
}

size_t	processSchemLine(const std::vector<std::string> &vect, size_t i) {
	size_t	ret = 0;

	for (size_t j = 0; j < vect[i].size(); j++) {
		if (vect[i][j] != '*')
			continue;

		ret += processGear(vect, i, j);
	}
	return ret;
}

size_t	getSchemSum(const std::vector<std::string> &vect) {
	size_t	ret = 0;

	for (size_t i = 0; i < vect.size(); i++)
		ret += processSchemLine(vect, i);
	return ret;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	// Put the whole file into a string:
	std::string					schemStr((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	std::vector<std::string>	schemVect;

	buildSchemVect(schemStr, schemVect);

	size_t	finalSum = getSchemSum(schemVect);
	std::cout << "The sum of all gear ratios is: " << finalSum << std::endl;
}
