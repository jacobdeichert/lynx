#pragma once
#include <fstream>
#include <sstream>
#include <iostream>


/**
 * USAGE
 *
 * Reading a file:
	std::string fileText;
	FileIO *fileIn = new FileIO();
	f->openFileIn("file.txt");
	while (f->readLine()) {
		fileText += f->getLine();
	}
	f->closeFileIn();
*/



namespace Mammoth {
	class FileIO {
	private:
		/**
		* The types of file operations.
		* FILE_WRITE will allow an instance of FileIO to write to files.
		* FILE_READ will allow an instance of FileIO to read files.
		*/
		enum FileOperationType { FILE_NONE, FILE_WRITE, FILE_READ };
		/**
		* The specified file operation type will define what functions
		* can be used on the file. This is automatically set once either
		* openFileOut() or openFileIn() are called.
		*/
		FileOperationType fileOperationType;
		std::ofstream fileOut;
		std::ifstream fileIn;
		std::string currentLine;
		bool isFileOut;
		bool isFileIn;
	public:
		FileIO();
		~FileIO();
		void openFileOut(std::string path);
		void openFileIn(std::string path);
		void closeFileOut();
		void closeFileIn();
		void write(std::string s);
		void writel(std::string s);
		bool readLine();
		std::string getLine();
		bool isOutOpen();
		bool isInOpen();
	};
}
