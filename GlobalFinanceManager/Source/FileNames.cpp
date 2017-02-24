#include "..\Include\Util\FileNames.h"
#include "..\Include\Time\MonthConverter.h"

const char* FileNames::jan_file_name = "JAN";
const char* FileNames::feb_file_name = "FEB";
const char* FileNames::mar_file_name = "MAR";
const char* FileNames::apr_file_name = "APR";
const char* FileNames::may_file_name = "MAY";
const char* FileNames::jun_file_name = "JUN";
const char* FileNames::jul_file_name = "JUL";
const char* FileNames::aug_file_name = "AUG";
const char* FileNames::sep_file_name = "SEP";
const char* FileNames::oct_file_name = "OCT";
const char* FileNames::nov_file_name = "NOV";
const char* FileNames::dec_file_name = "DEC";

StringVector* FileNames::ConstructFileNames(const Request& request)
{
	StringVector* file_names = new StringVector();

	Month first_month = request.GetFirstEdge().GetMonth();
	Month last_month = request.GetLastEdge().GetMonth();

	int first_year = request.GetFirstEdge().GetYear();
	int last_year = request.GetLastEdge().GetYear();

	// If the the request contains a single year, so we don't need special "circle" of month names
	if (first_year == last_year) {
		// If even the only month is there, so StringVector with single file name will be returned
		if (first_month == last_month) {
			std::string *month_name = ConstructMonthFileName(first_month);

			file_names->push_back(*month_name + std::to_string(first_year));

			delete month_name;

			return file_names;
		}
		// Multiple months in the single year
		else {

		}
	}
	// Many years, many months
	else {

	}

	
}

std::string* FileNames::ConstructMonthFileName(Month month)
{
	switch (month)
	{
	case Month::NO_MONTH:
		return new std::string("NO_MONTH");
	case Month::Jan:
		return new std::string(jan_file_name);
	case Month::Feb:
		return new std::string(feb_file_name);
	case Month::Mar:
		return new std::string(mar_file_name);
	case Month::Apr:
		return new std::string(apr_file_name);
	case Month::May:
		return new std::string(may_file_name);
	case Month::Jun:
		return new std::string(jun_file_name);
	case Month::Jul:
		return new std::string(jul_file_name);
	case Month::Aug:
		return new std::string(aug_file_name);
	case Month::Sep:
		return new std::string(sep_file_name);
	case Month::Oct:
		return new std::string(oct_file_name);
	case Month::Nov:
		return new std::string(nov_file_name);
	case Month::Dec:
		return new std::string(dec_file_name);
	}
}

std::string* ConstructMonthFileNamesFromJan(Month last_month, int* names_count)
{
	int first_month_int = MonthConverter::MonthToInt(Month::Jan);
	int last_month_int = MonthConverter::MonthToInt(last_month);

	*names_count = last_month_int - first_month_int;
	std::string* month_file_names = new std::string[*names_count];

	for (int i = 0; i < *names_count; i++) {
		month_file_names + i = FileNames::ConstructMonthFileName(MonthConverter::IntToMonth(first_month_int));
	}
}