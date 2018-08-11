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
	static std::vector<char> readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("vkCraft: Failed to open file");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();

		return buffer;
	}
};