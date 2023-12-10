#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

ssize_t getLinePrediction(const std::string &line) {
	std::vector<int>	vect;
	std::stack<int>		stk;

	std::cout << line << std::endl;

	// Build the initial vector from the line:
	int	tmp = 0;
	do {
		vect.push_back(std::atoi(&line.c_str()[tmp]));
		tmp = line.find(" ", tmp + 1);
	} while (tmp != std::string::npos);

	// The stack will hold all the first numbers, since the prediction equals their sum.
	stk.push(vect.front());

	// Create the diffs and push their first value until all diffs are zero:
	bool	notAllZeros = true;
	while (notAllZeros) {
		notAllZeros = false;
		// Get the diff:
		for (int i = vect.size() - 1; i; i--) {
			vect[i] = vect[i] - vect[i - 1];
			notAllZeros |= vect[i];
		}

		vect.erase(vect.begin());
		stk.push(vect.front());

		for (int i = 0; i < vect.size(); i++)
		    std::cout << vect[i] << (i != vect.size() - 1 ? " " : "\n");
	}

	// Get the value!
	ssize_t	ret = 0;
	while (stk.size()) {
		ret = stk.top() - ret;
		stk.pop();
	}

	std::cout << "For this line: " << ret << std::endl;

	return ret;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}

	ssize_t		sum = 0;
	std::string	line;

	while (std::getline(inFile, line)) {
		sum += getLinePrediction(line);
	}

	std::cout << "\nThe sum of all extrapolated values is: " << sum << std::endl;
}
