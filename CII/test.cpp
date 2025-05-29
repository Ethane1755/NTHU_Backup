#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>

int main() {
	std::string playerName = "Player1";
	int score = 100;

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ofstream output("test.txt", std::ios::app);
	output << playerName << " " << score << " " << std::put_time(&tm, "%Y%m%d %H%M%S") << std::endl;
	output.close();

	return 0;
}