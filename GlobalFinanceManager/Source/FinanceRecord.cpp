#include <iostream>
#include <exception>
#include "..\Include\Record\FinanceRecord.h"
#include "..\Include\Record\ExpenceRecord.h"
#include "..\Include\Record\IncomeRecord.h"

const char* FinanceRecord::fileName = "ExpencesTest.bin";
const unsigned char FinanceRecord::stringSeparator = static_cast<unsigned char>(234); // greek OMEGA character

FinanceRecord* FinanceRecord::CreateRecord(const RecordType type, const std::string& category, float sum, const std::string& description = "")
{
	switch (type)
	{
	case RecordType::Expence:
		return new ExpenceRecord(category, sum, description);
		break;
	case RecordType::Income:
		return new IncomeRecord(category, sum, description);
		break;
	default:
		throw new std::invalid_argument("Invalid type of record");
	}
}

FinanceRecord::FinanceRecord(const std::string& newCategory, float newSum, const std::string& newDescription) :
	category(newCategory), sum(newSum), description(newDescription)
{
	time = new TimeHolder;
}

FinanceRecord::FinanceRecord(const FinanceRecord & anotherRecord)
{
	time = new TimeHolder(*anotherRecord.time);
	sum = anotherRecord.sum;
	category = anotherRecord.category;
	description = anotherRecord.description;
}

FinanceRecord::~FinanceRecord()
{
	delete time;
}

void FinanceRecord::EditCategory(const std::string& newCategory)
{
	category = newCategory;
}

void FinanceRecord::EditDescription(const std::string& newDescription)
{
	description = newDescription;
}

void FinanceRecord::TestDisplay() const
{
	std::cout << time->GetTimeString() << std::endl
		<< "Sum: " << sum << std::endl
		<< category << std::endl
		<< description << std::endl;
}

void FinanceRecord::EditSum(const float newSum)
{
	sum = newSum;
}
