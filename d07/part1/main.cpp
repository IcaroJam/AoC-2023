#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

std::map<char, int>	cardVals = {
	{'A', 14},
	{'K', 13},
	{'Q', 12},
	{'J', 11},
	{'T', 10},
	{'9', 9},
	{'8', 8},
	{'7', 7},
	{'6', 6},
	{'5', 5},
	{'4', 4},
	{'3', 3},
	{'2', 2}
};

void	processLine(const std::string &line, std::vector<std::string> *ht) {
	std::map<char, int>	charCount;
	int					i = 0;
	
	while (line[i] && line[i] != ' ') {
		charCount[line[i]]++;
		i++;
	}

	if (charCount.size() == 1) { // All characters are the same
		ht[6].push_back(line);
	} else if (charCount.size() == 2) { // There are only two different characters
		if (charCount.begin()->second == 4 || charCount.begin()->second == 1) // The count for them is 4 and 1
			ht[5].push_back(line);
		else // The count for them is 3 and 2
			ht[4].push_back(line);
	} else if (charCount.size() == 3) { // There are three different characters
		if (charCount.begin()->second == 3 || std::next(charCount.begin(), 1)->second == 3 || std::next(charCount.begin(), 2)->second == 3) // The count for them is 3, 1 and 1
			ht[3].push_back(line);
		else // The count for them is 2, 2 and 1
			ht[2].push_back(line);
	} else if (charCount.size() == 4) { // There are four different characters
		ht[1].push_back(line);
	} else { // All five characters are different
		ht[0].push_back(line);
	}
}

bool highCard(const std::string &a, const std::string &b) {
	int	i = 0;
	
	while (a[i] && a[i] != ' ') {
		if (a[i] != b[i]) {
			return cardVals[a[i]] < cardVals[b[i]];
		}
		i++;
	}
	return true;
}

int getBid(const std::string &line) {
	return std::stoi(line.substr(line.find_first_of(" ") + 1));
}

// Filter out the hands corresponding to the different types by the number of repeated chars in each one, create separate containers for them
// Sort the separate containers by the second ordering rule
// Profit
int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}
	std::string	line;
	int			winTotal = 0;

	std::vector<std::string>	handTypes[7]; // The 7 possible types, from stronger to weakest.

	// Separate lines into groups by their hand type
	while (std::getline(inFile, line)) {
		processLine(line, handTypes);
	}

	// Sort the hands of each type
	for (int i = 0; i < 7; i++) {
		std::sort(handTypes[i].begin(), handTypes[i].end(), highCard);
	}

	// Count points!
	int rank = 1;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < handTypes[i].size(); j++) {
			std::cout << i << ": " << handTypes[i][j] << std::endl;
			winTotal += getBid(handTypes[i][j]) * rank++;
		}
	}

	std::cout << "\nTotal winnings add up to: " << winTotal << std::endl;
}
