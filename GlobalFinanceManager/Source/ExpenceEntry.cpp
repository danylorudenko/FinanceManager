#include "..\Include\Entry\ExpenceEntry.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>

ExpenceEntry::ExpenceEntry(ExpenceEntry & anotherEntry) : FinanceEntry(anotherEntry) { }

ExpenceEntry::ExpenceEntry(const std::string & category, float sum, const std::string & description) :
	FinanceEntry(category, sum, description) { }

void ExpenceEntry::EditSum(const float sumNew)
{
	FinanceEntry::EditSum(sumNew);
}

void ExpenceEntry::EditCategory(const std::string & categotyNew)
{
	FinanceEntry::EditCategory(categotyNew);
}

void ExpenceEntry::EditDescription(const std::string & descriptionNew)
{
	FinanceEntry::EditDescription(descriptionNew);
}

void ExpenceEntry::Write(std::ofstream& outFile)
{
	EntryType thisType = EntryType::Expence;
	if (outFile.is_open()) 
	{
		outFile.write(reinterpret_cast<char*>(&thisType), sizeof(decltype(thisType)));
	}
	else
	{
		std::cout << "Failed to write Entry type to the file." << std::endl;
	}

	FinanceEntry::Write(outFile);
}

void ExpenceEntry::Read(std::ifstream& inFile)
{
	
}
