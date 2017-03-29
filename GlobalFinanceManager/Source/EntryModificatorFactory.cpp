#include <iostream>

#include "..\Include\Util\CommandParametersExtractor.h"
#include "..\Include\Util\Request\RequestFactory.h"
#include "..\Include\Entry\EntryModificator\CategoryModificator.h"
#include "..\Include\Entry\EntryModificator\SumModificator.h"
#include "..\Include\Entry\EntryModificator\DescriptionModificator.h"
#include "..\Include\Entry\EntryModificator\EntryModificatorFactory.h"

const std::map<std::string, EntryModificatorFactory::EntryModificatorCreator> EntryModificatorFactory::creators_map_ =
{
	{ RequestFactory::category_argument_prefix_,	EntryModificatorFactory::ConstructCategoryModificator },
	{ RequestFactory::sum_argument_prefix_,			EntryModificatorFactory::ConstructSumModificator },
	{ RequestFactory::description_argument_prefix_, EntryModificatorFactory::ConstructDescriptionModificator }
};

AEntryModificator* EntryModificatorFactory::Construct(std::string& params)
{
	AEntryModificator* modificator = nullptr;
	CommandParametersExtractor* params_extractor = new CommandParametersExtractor(params);

	const int arguments_count = static_cast<const int>(params_extractor->ArgumentsCount());
	for (int i = 0; i < arguments_count; ++i) {
		try {
			const std::string& param_prefix = params_extractor->GetPrefix(i);
			const std::string& param_content = params_extractor->TryGetArgument(param_prefix);

			EntryModificatorCreator modificator_creator = creators_map_.at(param_prefix);
			if (modificator == nullptr) {
				modificator = modificator_creator(std::string(param_content));
			}
			else {
				modificator->Decorate(modificator_creator(params));
			}
		}
		catch (std::out_of_range e) {
			std::cout << e.what() << std::endl;
		}
	}

	delete params_extractor;
	return modificator;
}

AEntryModificator* EntryModificatorFactory::ConstructCategoryModificator(std::string& raw_param)
{
	return new CategoryModificator(raw_param);
}

AEntryModificator* EntryModificatorFactory::ConstructDescriptionModificator(std::string& raw_param)
{
	return new DescriptionModificator(raw_param);
}

AEntryModificator* EntryModificatorFactory::ConstructSumModificator(std::string& raw_param)
{
	return new SumModificator(raw_param);
}