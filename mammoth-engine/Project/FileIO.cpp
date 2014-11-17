#include "FileIO.h"
using namespace Mammoth;


FileIO::FileIO() {
	fileOperationType = FILE_NONE;
	isFileIn = false;
	isFileOut = false;
	currentLine = "";
}


FileIO::~FileIO() {
	if (isFileIn) {
		closeFileIn();
	}
	if (isFileOut) {
		closeFileOut();
	}
}



void FileIO::openFileOut(std::string path) {
	if (fileOperationType == FILE_NONE) {
		fileOperationType = FILE_WRITE;
	}

	if (fileOperationType == FILE_WRITE) {
		fileOut = std::ofstream(path); // create an object using the file name

		if (!fileOut) {
			printf("ERROR: cannot open file %s\n", path);
		}
		else {
			isFileOut = true;
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}



void FileIO::openFileIn(std::string path) {
	if (fileOperationType == FILE_NONE) {
		fileOperationType = FILE_READ;
	}

	if (fileOperationType == FILE_READ) {
		fileIn = std::ifstream(path); // create an object using the file name

		if (!fileIn) {
			printf("ERROR: cannot open file %s\n", path);
		}
		else {
			isFileIn = true;
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}



void FileIO::closeFileOut() {
	if (fileOperationType == FILE_WRITE) {
		if (isFileOut) {
			fileOut.close();
			isFileOut = false;
			fileOperationType = FILE_NONE;
		}
		else {
			printf("ERROR: cannot close file, no file is open.\n");
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}



void FileIO::closeFileIn() {
	if (fileOperationType == FILE_READ) {
		if (isFileIn) {
			fileIn.close();
			isFileIn = false;
			fileOperationType = FILE_NONE;
		}
		else {
			printf("ERROR: cannot close file, no file is open.\n");
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}



void FileIO::write(std::string s) {
	if (fileOperationType == FILE_WRITE) {
		if (isFileOut) {
			fileOut << s;
		}
		else {
			printf("ERROR: cannot write to file, no file is open.\n");
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}



void FileIO::writel(std::string s) {
	if (fileOperationType == FILE_WRITE) {
		if (isFileOut) {
			fileOut << s << std::endl;
		}
		else {
			printf("ERROR: cannot write to file, no file is open.\n");
		}
	}
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
	}
}


bool FileIO::readLine() {
	if (fileOperationType == FILE_READ) {
		if (isFileIn) {
			// If there is a line.
			if (std::getline(fileIn, currentLine)) {
				currentLine += "\n";
				return true;
			} // If we're at the bottom of the file.
			else {
				return false;
			}
		} // If no file is open.
		else {
			printf("ERROR: cannot read file, no file is open.\n");
			return false;
		}
	} // If the file operation is not set to reading at the moment.
	else {
		printf("ERROR: the current file operation type doesn't support this operation.\n");
		return false;
	}
}

std::string FileIO::getLine() {
	return currentLine;
}



bool FileIO::isOutOpen() {
	return isFileOut;
}

bool FileIO::isInOpen() {
	return isFileIn;
}

