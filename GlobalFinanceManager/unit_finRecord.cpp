#include "FinanceRecord.h"
#include "ExpenceRecord.h"
#include "Enums\RecordType.h"
#include <iostream>
#include <iomanip>

int main()
{
	std::string cat("MyCategory");
	std::string descr("MySescription");

	FinanceRecord* record = FinanceRecord::CreateRecord(RecordType::Expence, cat, 100.0f, descr);
	record->Write();
	system("PAUSE");
	return 0;
}