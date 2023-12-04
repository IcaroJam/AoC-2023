#include <iostream>
#include <fstream>
#include <map>

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

	for (size_t i = 0; i < winningNums.size(); i++) {
		if (!std::isdigit(winningNums[i]))
			continue;

		std::string currNum = processNumber(winningNums, i);

		if (cardNums.find(currNum) != std::string::npos)
			ret++;
	}
	return ret;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	std::map<int, int>	cards;
	std::string			line;

	while (std::getline(inFile, line)) {
		size_t		numStart = line.find(':');
		size_t		divisor = line.find('|');
		size_t		currCard = std::stoi(line.substr(5, numStart - 5));
		std::string	winningNums = line.substr(numStart + 2, divisor - numStart - 3);
		std::string	cardNums = " " + line.substr(divisor + 2) + " ";

		cards[currCard]++;

		std::cout << "\nLine \'" << line << "': " << std::endl;
		int	numOMatches = processLine(winningNums, cardNums);
		std::cout << "\tNumber of winning numbers found: " << numOMatches << std::endl;

		while (numOMatches) // Add as many copies of the following cards as there are copies of the current card.
			cards[currCard + numOMatches--] += cards[currCard];
	}

	int	totalNumOCards = 0;
	for (std::map<int, int>::iterator it = cards.begin(); it != cards.end(); ++it) {
		totalNumOCards += it->second;
		std::cout << "Card " << it->first << ": " << it->second << " copies\n";
	}

	std::cout << "\nThe total number of cards is: " << totalNumOCards << std::endl;
}
