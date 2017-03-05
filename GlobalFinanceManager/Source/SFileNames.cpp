#include "..\Include\Util\SFileNames.h"
#include "..\Include\Time\MonthConverter.h"

#include <sstream>

const char* SFileNames::jan_file_name = "JAN";
const char* SFileNames::feb_file_name = "FEB";
const char* SFileNames::mar_file_name = "MAR";
const char* SFileNames::apr_file_name = "APR";
const char* SFileNames::may_file_name = "MAY";
const char* SFileNames::jun_file_name = "JUN";
const char* SFileNames::jul_file_name = "JUL";
const char* SFileNames::aug_file_name = "AUG";
const char* SFileNames::sep_file_name = "SEP";
const char* SFileNames::oct_file_name = "OCT";
const char* SFileNames::nov_file_name = "NOV";
const char* SFileNames::dec_file_name = "DEC";

StringVector* SFileNames::ConstructFileNames(const Request& request)
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
			std::string *month_name = ConstructMonthFileNamePart(first_month);
			std::string* file_name = ConstructFileName(month_name, first_year);
			file_names->push_back(*file_name);

			delete month_name;
			delete file_name;
		}
		// Multiple months in the single year
		else {
			int names_count;
			std::string* month_file_names = ConstructMonthFileNamePartsBetween(first_month, last_month, &names_count);

			std::string* temp_file_name = nullptr;
			for (int i = 0; i < names_count; i++) {
				temp_file_name = SFileNames::ConstructFileName(month_file_names + i, first_year);
				file_names->push_back(*temp_file_name);

				delete temp_file_name;
			}

			delete[] month_file_names;
		}
	}
	// Many years, many months
	else {
		int years_count = (last_year - first_year) + 1;

		int first_year_month_count;
		std::string* first_year_months = ConstructMonthFileNamePartsBeforeDec(first_month, &first_year_month_count);

		int last_year_month_count;
		std::string* last_year_months = ConstructMonthFileNamePartsFromJan(last_month, &last_year_month_count);

		std::string* file_name_temp = nullptr;

		for (int i = 0; i < first_year_month_count; i++) {
			file_name_temp = ConstructFileName(first_year_months + i, first_year);
			file_names->push_back(*file_name_temp);

			delete file_name_temp;
		}

		// If there are more than 2 years
		if (years_count > 2) {
			int all_month_count;
			std::string* all_month_names = ConstructMonthFileNamePartsBetween(Month::Jan, Month::Dec, &all_month_count);

			// Years between first and last year
			int middle_years_count = years_count - 2;
			for (int i = 0; i < middle_years_count; i++)
			{
				int target_year = first_year + i + 1;
				for (int j = 0; j < all_month_count; j++) {
					file_name_temp = ConstructFileName(all_month_names + j, target_year);
					file_names->push_back(*file_name_temp);
					delete file_name_temp;
				}
			}

			delete[] all_month_names;
		}

		for (int i = 0; i < last_year_month_count; i++) {
			file_name_temp = ConstructFileName(last_year_months + i, last_year);
			file_names->push_back(*file_name_temp);

			delete file_name_temp;
		}

		delete[] first_year_months;
		delete[] last_year_months;
	}

	return file_names;
}

std::string* SFileNames::ConstructFileName(std::string* month_name, int year)
{
	std::stringstream* string_stream = new std::stringstream;
	*string_stream << year << "_" << month_name->c_str() << ".txt";

	std::string* result_string_p = new std::string(string_stream->str());
	delete string_stream;
	return result_string_p;
}

std::string* SFileNames::ConstructMonthFileNamePart(Month month)
{
	switch (month)
	{
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
	default:
		return new std::string("NO_MONTH");
	}
}

std::string* SFileNames::ConstructMonthFileNamePartsBetween(Month first_month, Month last_month, int* names_count)
{
	int first_month_int = MonthConverter::MonthToInt(first_month);
	int last_month_int = MonthConverter::MonthToInt(last_month);

	// Jan - Jan == 0, for example, but need 1
	*names_count = (last_month_int - first_month_int) + 1;
	std::string* month_file_names = new std::string[*names_count];

	// Temporary variables to be incremented in the loop
	int month_toadd = first_month_int;
	std::string* iterator_pointer = month_file_names;

	// This loop is incrementing temporary pointer and month value safely,
	// because it uses names_count as a limiter
	for (int i = 0; i < *names_count; i++) {
		iterator_pointer = SFileNames::ConstructMonthFileNamePart(MonthConverter::IntToMonth(month_toadd));
		month_toadd++;
		iterator_pointer++;
	}

	return month_file_names;
}

std::string* SFileNames::ConstructMonthFileNamePartsFromJan(Month last_month, int* names_count)
{
	return SFileNames::ConstructMonthFileNamePartsBetween(Month::Jan, last_month, names_count);
}

std::string* SFileNames::ConstructMonthFileNamePartsBeforeDec(Month first_month, int* names_count)
{
	return SFileNames::ConstructMonthFileNamePartsBetween(first_month, Month::Dec, names_count);
}