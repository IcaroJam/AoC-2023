#include <iostream>
#include <fstream>
#include <vector>

// Since the maze is a perfect, linear loop, we can just do a whole loop and divide it's length by 2:
int loopMap(std::vector<std::string> &map, int sX, int sY) {
	int	x = sX, y = sY;
	int	preX = sX, preY = sY;
	int	loopLen = 1;

	// We first need to find a direction to follow.
	if (y > 0 && (map[y - 1][x] == '|' || map[y - 1][x] == '7' || map[y - 1][x] == 'F'))
		y--;
	else if (x < map[y].size() - 1 && (map[y][x + 1] == '-' || map[y][x + 1] == '7' || map[y][x + 1] == 'J'))
		x++;
	else if (y < map.size() - 1 && (map[y + 1][x] == '|' || map[y + 1][x] == 'L' || map[y + 1][x] == 'J'))
		y++;
	else if (x > 0 && (map[y][x - 1] == '-' || map[y][x - 1] == 'L' || map[y][x - 1] == 'F'))
		x--;

	while (!(x == sX && y == sY)) {
		switch (map[y][x]) {
			case '|':
				if (preY < y) {
					preY = y;
					y++;
				} else {
					preY = y;
					y--;
				}
				break;
			case '-':
				if (preX < x) {
					preX = x;
					x++;
				} else {
					preX = x;
					x--;
				}
				break;
			case 'L':
				if (preY < y) {
					preY = y;
					x++;
				} else {
					preX = x;
					y--;
				}
				break;
			case 'J':
				if (preY < y) {
					preY = y;
					x--;
				} else {
					preX = x;
					y--;
				}
				break;
			case '7':
				if (preX < x) {
					preX = x;
					y++;
				} else {
					preY = y;
					x--;
				}
				break;
			case 'F':
				if (preX > x) {
					preX = x;
					y++;
				} else {
					preY = y;
					x++;
				}
				break;
		}

		loopLen++;
	}
	
	return loopLen;
}

int main() {
	std::ifstream	inFile("../input.txt");
	if (inFile.fail()) {
		std::cerr << "Failed to open input file :(" << std::endl;
		return 1;
	}

	int							dist = 0;
	int							sX, sY;
	std::string					line;
	std::vector<std::string>	map;

	// Build the map and get the starting position:
	while (std::getline(inFile, line)) {
		int	tmpos = line.find("S");
		if (tmpos != std::string::npos) {
			sX = tmpos;
			sY = map.size();
		}
		map.push_back(line);
	}

	dist = loopMap(map, sX, sY);

    for (int i = 0; i < map.size(); i++)
		std::cout << map[i] << std::endl;

    std::cout << "Pos: (" << sX << ", " << sY << ")\n";

	std::cout << "\nThe furthest point is " << dist / 2 << " tiles away!" << std::endl;
}
