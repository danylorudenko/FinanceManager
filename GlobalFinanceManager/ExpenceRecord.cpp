#include "ExpenceRecord.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

ExpenceRecord::ExpenceRecord(const ExpenceRecord & anotherRecord) : FinanceRecord(anotherRecord) { }

ExpenceRecord::ExpenceRecord(const std::string & category, float sum, const std::string & description) :
	FinanceRecord(category, sum, description) { }

void ExpenceRecord::EditSum(const float sumNew)
{
	FinanceRecord::EditSum(sumNew);
}

void ExpenceRecord::EditCategory(const std::string & categotyNew)
{
	FinanceRecord::EditCategory(categotyNew);
}

void ExpenceRecord::EditDescription(const std::string & descriptionNew)
{
	FinanceRecord::EditDescription(descriptionNew);
}

bool ExpenceRecord::Write()
{
	std::ofstream outFile(fileName, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if (outFile.is_open())
	{
		std::cout << "File " << fileName << " was opened for writing." << std::endl;
	}
	else
	{
		std::cout << "Failed to open file " << fileName << " for writing." << std::endl;
		return false;
	}

	outFile.write(reinterpret_cast<char *>(time), sizeof(decltype(*time)));

	outFile.write(reinterpret_cast<char *>(&sum), sizeof(decltype(sum)));

	int writtenSize = category.size();
	outFile.write(reinterpret_cast<char*>(&writtenSize), sizeof(int)); // here I'm writing the size of my string, so i MUST READ IT BEFORE READING THE std::string

	char* tempString = new char[writtenSize];
	stdext::checked_array_iterator<decltype(tempString)> tempCategoryStringBeginIterator(tempString, writtenSize);
	std::copy(category.begin(), category.end(), tempCategoryStringBeginIterator); //here I copy the c-string of the std::string to the char* 
	outFile.write(tempString, writtenSize);					 //to write it to the file
	delete[] tempString;
	
	writtenSize = description.size();
	outFile.write(reinterpret_cast<char*>(&writtenSize), sizeof(int));

	tempString = new char[writtenSize];
	stdext::checked_array_iterator<decltype(tempString)> tempDescriptionStringBeginIterator(tempString, writtenSize);
	std::copy(description.begin(), description.end(), tempDescriptionStringBeginIterator); //same thing for another std::string
	outFile.write(tempString, writtenSize);
	delete[] tempString;

	std::cout << "File was successfully written.\n";

	return true;
}

bool ExpenceRecord::Read()
{
	std::ifstream inFile(fileName, std::ios_base::in | std::ios_base::binary | std::ios_base::beg);
	if (inFile.is_open())
	{
		std::cout << "File " << fileName << " was opened for reading.\n";
	}
	else
	{
		std::cout << "Failder to open " << fileName << " for reading.\n";
		return false;
	}

	char timeHolderBuffer[sizeof(TimeHolder)];
	inFile.read(timeHolderBuffer, sizeof(TimeHolder)); //reading complete buffer for the TimeHolder

	int readingPosition = 0;
	delete time; // deallocating the memory the old TimeHolder
	time = new TimeHolder(timeHolderBuffer, readingPosition); // initializing TimeHolder with buffer. Returns bytes have read by ref(readingPosition)

	char floatBuffer[sizeof(float)];
	inFile.read(floatBuffer, sizeof(float));
	sum = *(reinterpret_cast<float*>(floatBuffer)); // reading float SUM

	int readStringSize;
	const size_t intSize = sizeof(int);
	char intBuffer[intSize];
	inFile.read(intBuffer, intSize);
	readStringSize = *(reinterpret_cast<int*>(intBuffer));

	return true;
}
