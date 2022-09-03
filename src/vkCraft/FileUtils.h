#pragma once

#include <stdexcept>
#include <vector>
#include <fstream>

/**
 * Utils to read and write data to files.
 */
class FileUtils
{
public:
	/**
	 * Read file to a char vector.
	 */
	static std::vector<char> readFile(const std::string& filename);
};