#include <sstream>

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

StringVector* FileNames::ConstructFileNames(const Request* request)
{
	StringVector* file_names = new StringVector();

	Month first_month = request->GetFirstEdge().GetMonth();
	Month last_month = request->GetLastEdge().GetMonth();

	int first_year = request->GetFirstEdge().GetYear();
	int last_year = request->GetLastEdge().GetYear();

	// If the the request contains a single year, so we don't need special "circle" of month names
	if (first_year == last_year) {
		// If even the only month is there, so StringVector with single file name will be returned
		if (first_month == last_month) {
			std::string* month_name = new std::string();
			ConstructMonthFileNamePart(first_month, *month_name);

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
				temp_file_name = FileNames::ConstructFileName(month_file_names + i, first_year);
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

std::string* FileNames::ConstructFileName(std::string* month_name, int year)
{
	std::stringstream* string_stream = new std::stringstream;
	*string_stream << year << "_" << month_name->c_str() << ".txt";

	std::string* result_string_p = new std::string(string_stream->str());
	delete string_stream;
	return result_string_p;
}

void FileNames::ConstructMonthFileNamePart(Month month, std::string& dest)
{
	switch (month)
	{
	case Month::Jan:
		dest = jan_file_name;
		break;
	case Month::Feb:
		dest = feb_file_name;
		break;
	case Month::Mar:
		dest = mar_file_name;
		break;
	case Month::Apr:
		dest = apr_file_name;
		break;
	case Month::May:
		dest = may_file_name;
		break;
	case Month::Jun:
		dest = jun_file_name;
		break;
	case Month::Jul:
		dest = jul_file_name;
		break;
	case Month::Aug:
		dest = aug_file_name;
		break;
	case Month::Sep:
		dest = sep_file_name;
		break;
	case Month::Oct:
		dest = oct_file_name;
		break;
	case Month::Nov:
		dest = nov_file_name;
		break;
	case Month::Dec:
		dest = dec_file_name;
		break;
	default:
		dest = "NO_MONTH";
		break;
	}
}

std::string* FileNames::ConstructMonthFileNamePartsBetween(Month first_month, Month last_month, int* names_count)
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
		FileNames::ConstructMonthFileNamePart(MonthConverter::IntToMonth(month_toadd), *iterator_pointer);
		month_toadd++;
		iterator_pointer++;
	}

	return month_file_names;
}

std::string* FileNames::ConstructMonthFileNamePartsFromJan(Month last_month, int* names_count)
{
	return FileNames::ConstructMonthFileNamePartsBetween(Month::Jan, last_month, names_count);
}

std::string* FileNames::ConstructMonthFileNamePartsBeforeDec(Month first_month, int* names_count)
{
	return FileNames::ConstructMonthFileNamePartsBetween(first_month, Month::Dec, names_count);
}