 #ifndef __ENTRY_MODIFICATOR_FACTORY_H__
#define __ENTRY_MODIFICATOR_FACTORY_H__

#include <map>

class AEntryModificator;

class EntryModificatorFactory
{
public:
	static AEntryModificator* Construct(std::string& params);

protected:
	static AEntryModificator* ConstructCategoryModificator(std::string& raw_param);
	static AEntryModificator* ConstructSumModificator(std::string& raw_param);
	static AEntryModificator* ConstructDescriptionModificator(std::string& raw_param);

protected:
	using EntryModificatorCreator = AEntryModificator* (*)(std::string&);

	static const std::map<std::string, EntryModificatorCreator> creators_map_;
};

#endif