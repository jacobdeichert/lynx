#include "FileIO.h"
#include "Logger.h"
using namespace lynx;


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
		fileOut = std::ofstream(path);

		if (!fileOut) {
			Log::error("FileIO> cannot open file: " + path);
		}
		else {
			isFileOut = true;
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
	}
}


void FileIO::openFileIn(std::string path) {
	if (fileOperationType == FILE_NONE) {
		fileOperationType = FILE_READ;
	}

	if (fileOperationType == FILE_READ) {
		fileIn = std::ifstream(path);

		if (!fileIn) {
			Log::error("FileIO> cannot open file: " + path);
		}
		else {
			isFileIn = true;
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
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
			Log::error("FileIO> cannot close file because no file is open");
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
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
			Log::error("FileIO> cannot close file because no file is open");
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
	}
}


void FileIO::write(std::string s) {
	if (fileOperationType == FILE_WRITE) {
		if (isFileOut) {
			fileOut << s;
		}
		else {
			Log::error("FileIO> cannot write to file because no file is open");
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
	}
}


void FileIO::writeLine(std::string s) {
	if (fileOperationType == FILE_WRITE) {
		if (isFileOut) {
			fileOut << s << std::endl;
		}
		else {
			Log::error("FileIO> cannot write to file because no file is open");
		}
	}
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
	}
}


bool FileIO::readLine() {
	// If the file operation is in read mode.
	if (fileOperationType == FILE_READ) {
		// If file is open.
		if (isFileIn) {
			// If there is a line.
			if (std::getline(fileIn, currentLine)) {
				currentLine += "\n";
				return true;
			} // Else we're at the bottom of the file.
			else {
				return false;
			}
		} // Else no file is open.
		else {
			Log::error("FileIO> cannot read file because no file is open");
			return false;
		}
	} // Else the file operation is not set to read mode at the moment.
	else {
		Log::error("FileIO> the current file operation type doesn't support this operation");
		return false;
	}
}


std::string FileIO::getLine() {
	return currentLine;
}


std::string FileIO::getEntireFile() {
	std::string fileContents = "";
	while (readLine()) {
		fileContents += getLine();
	}
	return fileContents;
}


bool FileIO::isOutOpen() {
	return isFileOut;
}


bool FileIO::isInOpen() {
	return isFileIn;
}

