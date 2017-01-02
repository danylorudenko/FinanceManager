#include "..\Include\Record\ExpenceRecord.h"
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

void ExpenceRecord::Write(std::ofstream& outFile)
{
	RecordType thisType = RecordType::Expence;
	if (outFile.is_open()) 
	{
		outFile.write(reinterpret_cast<char*>(&thisType), sizeof(decltype(thisType)));
	}
	else
	{
		std::cout << "Failed to write record type to the file." << std::endl;
	}

	FinanceRecord::Write(outFile);
}

void ExpenceRecord::Read(std::ifstream& inFile)
{
	
}
