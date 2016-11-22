#include "ExpenceRecord.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

char * fileName = "ExpencesTest.bin";

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
		std::cout << "File " << fileName << " was opened." << std::endl;
	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
		return false;
	}

	outFile.write(reinterpret_cast<char *>(time), sizeof(decltype(*time)));
	outFile.write("\0", sizeof(char));

	outFile.write(reinterpret_cast<char *>(&sum), sizeof(decltype(sum)));
	outFile.write("\0", sizeof(char));

	int writtenSize = category.size();
	char* tempString = new char[writtenSize];
	stdext::checked_array_iterator<decltype(tempString)> tempStringBeginIterator(tempString, writtenSize);
	std::copy(category.begin(), category.end(), tempStringBeginIterator); //here I copy the c-string of the std::string to the char* 
	outFile.write(tempString, writtenSize);					 //to write it to the file
	outFile.write("\0", sizeof(char)); // this is a marker tells when the string is over
	delete[] tempString;
	
	writtenSize = description.size();
	tempString = new char[writtenSize];
	stdext::checked_array_iterator<decltype(tempString)> tempStringBeginIterator2(tempString, writtenSize);
	std::copy(description.begin(), description.end(), tempStringBeginIterator2); //same thing for another std::string
	outFile.write(tempString, writtenSize);
	outFile.write("\0", sizeof(char));
	delete[] tempString;

	std::cout << "File was written.\n";

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

	size_t bufferSize = sizeof(TimeHolder);
	char* buffer = new char[bufferSize];
	inFile.read(buffer, bufferSize); //reading complete buffer for the TimeHolder

	delete time;
	time = new TimeHolder(buffer); // initializing TimeHolder with buffer;
	delete[] buffer;

	buffer = new char[sizeof(float)];
	inFile.read(buffer, sizeof(float));
	sum = *(reinterpret_cast<float*>(buffer)); // reading float SUM


	return true;
}
