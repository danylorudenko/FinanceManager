#include "..\Include\Util\Request\ComplexPredicate\TimeEdgePredicate.h"
#include "..\Include\Managers\ConfigFileManager.h"

void TimeEdgePredicate::AugmentFirstEdgeByConfig(TimeHolder* first_edge)
{
	const ConfigInfo* config_info = ConfigFileManager::GetConfigInfo();

	// if days are out of config edges, set first day from config 
	*first_edge =
		*first_edge < config_info->GetFirstEdge() ?
		config_info->GetFirstEdge() :
		*first_edge;
}