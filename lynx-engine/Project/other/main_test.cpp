//#include "StringUtils.h"
//#include "FileIO.h"
//#include "LinkedList.h"
//#include "MathUtils.h"
//#include <iostream>
//#include <stdexcept>
//using std::out_of_range;
//using namespace StringUtils;
//static MathUtils math;
//
//void testGetInput() {
//	print("Enter your name: ");
//	printl(getInput());
//}
//
//void testWriteFile() {
//	FileIO io;
//	io.openFileOut("test.txt"); // path of the file, default location is /Project (same as h and cpp files)
//	io.writel("Hey my name is Jake.");
//	io.writel("This is a test print line.");
//	io.writel("This is another line.");
//	io.closeFileOut();
//}
//
//void testReadFile() {
//	FileIO io;
//	io.openFileIn("test.txt");
//	io.readl();
//	io.readl();
//	io.readl();
//	io.closeFileIn();
//}
//
//void testTryCatch() {
//	int arrLength = 5;
//	int arr[] = { 5, 3, 2, 4, 6 };
//
//	try {
//		int index = 6;
//		int v = arr[index];
//		if (index >= arrLength) {
//			throw out_of_range("this is the \"what\" of the exception");
//		}
//		printl(toString(v));
//	}
//	catch (out_of_range oor) {
//		printl("Out of range");
//		cout << oor.what() << endl;
//	}
//	catch (...) {
//		printl("Every other possible exception");
//	}
//}
//
//void testLinkedList() {
//	LinkedList list;
//	list.add(0, 000.1);
//	list.add(1, 111.1);
//	list.add(2, 222.1);
//	list.add(3, 333.1);
//	list.add(4, 444.1);
//	list.outputList();
//	printl("list length: " + toString(list.length));
//}
//
//void init() {
//	//testGetInput();
//	//testWriteFile();
//	//testReadFile();
//	//testTryCatch();
//	//testLinkedList();
//}
//
//int main() {
//	init();
//	
//	// Keep the console window open.
//	std::cin.ignore();
//}
