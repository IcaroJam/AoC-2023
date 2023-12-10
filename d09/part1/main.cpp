#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

size_t getLinePrediction(const std::string &line) {
	std::vector<int>	vect;
	std::stack<int>		stk;

	/* std::cout << line << std::endl; */

	// Build the initial vector from the line:
	int	start, tmp = 0;
	do {
		vect.push_back(std::atoi(&line.c_str()[tmp]));
		tmp = line.find(" ", tmp + 1);
	} while (tmp != std::string::npos);

	// The stack will hold all the last numbers, since the prediction equals their sum.
	stk.push(vect.back());

	// Create the diffs and push their last value until all diffs are zero:
	bool	notAllZeros = true;
	while (notAllZeros) {
		notAllZeros = false;
		// Get the diff:
		for (int i = 0; i < vect.size() - 1; i++) {
			vect[i] = vect[i + 1] - vect[i];
			/* std::cout << vect[i] << " "; */
			notAllZeros |= vect[i];
		}
		/* std::cout << std::endl; */
		vect.pop_back();
		stk.push(vect.back());
	}

	size_t	ret = 0;
	while (stk.size()) {
		ret += stk.top();
		/* std::cout << ret << std::endl; */
		stk.pop();
	}

	return ret;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}

	size_t		sum = 0;
	std::string	line;

	while (std::getline(inFile, line)) {
		sum += getLinePrediction(line);
	}

	std::cout << "\nThe sum of all extrapolated values is: " << sum << std::endl;
}
