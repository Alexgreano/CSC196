#include "FileIO.h"/*

int nc::FileIO::LoadHighScore(const std::string& filename)
{
	int highscore = -1;
	std::fstream my_file;
	my_file.open(filename, std::ios::in);

	if (my_file) {
		char ch;
		std::string s = " ";

		while (1) {
			my_file >> ch;
			if (my_file.eof()) break;
			s += ch;
		}

		try { highscore = std::stoi(s); }
		catch (...) { std::cerr << "error!\n"; }
	}
}

void nc::FileIO::WriteScore(const std::string& filename, int NewHighScore)
{
}*/
