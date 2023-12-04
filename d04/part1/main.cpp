#include <iostream>
#include <fstream>

std::string	processNumber(const std::string &str, size_t &i) {
	std::string	ret;
	size_t		tmp = i;

	while (std::isdigit(str[tmp]))
		tmp++;
	ret = " " + str.substr(i, tmp - i) + " ";
	i = tmp;
	return ret;
}

int	processLine(const std::string &winningNums, const std::string &cardNums) {
	int	ret = 0;

	std::cout << "Winning numbers found:" << std::endl;
	for (size_t i = 0; i < winningNums.size(); i++) {
		if (!std::isdigit(winningNums[i]))
			continue;

		std::string currNum = processNumber(winningNums, i);

		if (cardNums.find(currNum) != std::string::npos) {
			std::cout << "\t" << currNum << std::endl;
			ret++;
		}
	}
	return ret;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	std::string	line;
	int			points = 0;

	while (std::getline(inFile, line)) {
		size_t		numStart = line.find(':');
		size_t		divisor = line.find('|');
		std::string	winningNums = line.substr(numStart + 2, divisor - numStart - 3);
		std::string	cardNums = " " + line.substr(divisor + 2) + " ";

		std::cout << "Line \'" << line << "': " << std::endl;
		int	numOMatches = processLine(winningNums, cardNums);

		if (numOMatches == 1)
			points += 1;
		else if (numOMatches > 1)
			points += 1 << (numOMatches - 1);
		std::cout << points << " points up till now\n";
	}

	std::cout << "\nThe total number of points is: " << points << std::endl;
}
