#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace nc {
	class FileIO {
	public:
		int static LoadHighScore(const std::string& filename);
		void static WriteScore(const std::string& filename, int NewHighScore);
	};
}