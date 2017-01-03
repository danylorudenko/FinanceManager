#include <iostream>
#include <exception>
#include "..\Include\Entry\FinanceEntry.h"
#include "..\Include\Entry\ExpenceEntry.h"
#include "..\Include\Entry\IncomeEntry.h"

const char FinanceEntry::recordStringTerminator = '\0';


FinanceEntry* FinanceEntry::CreateEntry(const EntryType type, const std::string& category, float sum, const std::string& description = "")
{
	switch (type)
	{
	case EntryType::Expence:
		return new ExpenceEntry(category, sum, description);
		break;
	case EntryType::Income:
		return new IncomeEntry(category, sum, description);
		break;
	default:
		throw new std::invalid_argument("Invalid type of Entry");
	}
}

FinanceEntry::FinanceEntry(const std::string& newCategory, float newSum, const std::string& newDescription) :
	category(newCategory), sum(newSum), description(newDescription)
{
	time = TimeHolder();
}

void FinanceEntry::EditCategory(const std::string& newCategory)
{
	category = newCategory;
}

void FinanceEntry::EditDescription(const std::string& newDescription)
{
	description = newDescription;
}

void FinanceEntry::TestDisplay() const
{
	std::cout << time.GetTimeString() << std::endl
		<< "Sum: " << sum << std::endl
		<< category << std::endl
		<< description << std::endl;
}

void FinanceEntry::EditSum(const float newSum)
{
	sum = newSum;
}

void FinanceEntry::Write(std::ofstream& outFile) 
{
	if (outFile.is_open())
	{
		std::cout << "File " << " was opened for writing." << std::endl;
	}
	else
	{
		std::cout << "Failed to open file for writing." << std::endl;
		return;
	}

	
	std::cout << "File was successfully written.\n";
}

void FinanceEntry::Read(std::ifstream& inFile)
{
	if (inFile.is_open())
	{
		std::cout << "File was opened for reading.\n";
	}
	else
	{
		std::cout << "Failder to open for reading.\n";
	}

}

void FinanceEntry::WriteString(std::ofstream& outFile, std::string str, int limit) 
{
	int counter = 0;
	int stringSize = str.size();

	while (counter < limit && counter < stringSize) {
		outFile.write(reinterpret_cast<char*>(&str[counter]), sizeof(char));
		counter++;
	}

	// If unused space left, write null-characters
	char* nullChar = new char('\0');
	while (counter < limit) {
		outFile.write(nullChar, sizeof(decltype(nullChar)));
		counter++;
	}
	delete nullChar;
}