#include "..\Include\Record\FinanceRecord.h"
#include "..\Include\Record\ExpenceRecord.h"
#include "..\Include\Enums\RecordType.h"
#include <iostream>
#include <iomanip>

int main()
{
	std::string cat("MyCategory");
	std::string descr("MySescription");

	FinanceRecord* record = FinanceRecord::CreateRecord(RecordType::Expence, cat, 100.0f, descr);
	record->TestDisplay();

	record->Write();

	system("PAUSE");
	return 0;
}