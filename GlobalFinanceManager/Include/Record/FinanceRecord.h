#ifndef __FINANCE_RECORD__
#define __FINANCE_RECORD__

#include <string>
#include <fstream>
#include "..\..\Include\Record\Time\TimeHolder.h"
#include "..\..\Include\Enums\RecordType.h"

class FinanceRecord
{
public:
	static FinanceRecord* CreateRecord(const RecordType type, const std::string& category, const float sum, const std::string& description);
	virtual void EditCategory(const std::string& categoryNew);
	virtual void EditSum(const float newSum);
	virtual void EditDescription(const std::string& newDescription);

	virtual void TestDisplay() const;

	virtual void Write(std::ofstream& outFile) = 0;
	virtual void Read(std::ifstream& inFile) = 0;
	~FinanceRecord();

protected:
	static const int categoryLimit;
	static const int descriptionLimit;
	static const int totalRecordLength;
	
	FinanceRecord(const std::string& category, float sum, const std::string& description);
	static void WriteString(std::ofstream& outFile, std::string str, int limit);

	TimeHolder* time = nullptr;
	float sum;
	std::string category;
	std::string description;
};

#endif