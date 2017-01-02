#include "..\Include\Record\FinanceRecord.h"
#include "..\Include\Record\ExpenceRecord.h"
#include "..\Include\Enums\RecordType.h"
#include <iostream>
#include <iomanip>

int main()
{
	std::ofstream testOutFile("testExpences.bin", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	
	std::string cat("MyCategory");
	std::string descr("MyDescription");
	
	FinanceRecord* record = FinanceRecord::CreateRecord(RecordType::Expence, cat, 100.0f, descr);
	record->TestDisplay();
	
	record->Write(testOutFile);

	system("PAUSE");
	return 0;
}