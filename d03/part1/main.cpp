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

size_t	processNumber(const std::vector<std::string> &vect, size_t i, size_t &j) {
	size_t	currNum = std::atoi(&vect[i].c_str()[j]);
	bool	symbolFound = false;

	while (!symbolFound && std::isdigit(vect[i][j])) {
		// Check all 8 adjacent characters if possible:
		if (i > 0) { // Top row
			if (j > 0 && isSymbol(vect[i - 1][j - 1]))
				symbolFound = true;
			if (isSymbol(vect[i - 1][j]))
				symbolFound = true;
			if (j < vect[i].size() - 1 && isSymbol(vect[i - 1][j + 1]))
				symbolFound = true;
		}
		if (i < vect.size() - 1) { // Bottom row
			if (j > 0 && isSymbol(vect[i + 1][j - 1]))
				symbolFound = true;
			if (isSymbol(vect[i + 1][j]))
				symbolFound = true;
			if (j < vect[i].size() - 1 && isSymbol(vect[i + 1][j + 1]))
				symbolFound = true;
		}
		if (j > 0 && isSymbol(vect[i][j - 1])) // Left
			symbolFound = true;
		if (j < vect[i].size() - 1 && isSymbol(vect[i][j + 1])) // Right
			symbolFound = true;

		j++;
	}
	if (symbolFound) {
		while (std::isdigit(vect[i][j]))
			j++;
		return currNum;
	}
	return 0;
}

size_t	processSchemLine(const std::vector<std::string> &vect, size_t i) {
	size_t	ret = 0;

	for (size_t j = 0; j < vect[i].size(); j++) {
		if (!std::isdigit(vect[i][j]))
			continue;

		size_t A = processNumber(vect, i, j);
		if (A)
			std::cout << "Number found: " << A << std::endl;
		ret += A;
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

	std::cout << "The sum of part numbers is: " << getSchemSum(schemVect) << std::endl;
}
