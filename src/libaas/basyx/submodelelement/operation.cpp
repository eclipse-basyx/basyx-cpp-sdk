#include "operation.h"

namespace basyx {

	bool Operation::invoke(const opVarList_t& inputVars,
		opVarList_t& inoutVars,
		opVarList_t& outputVars)
	{
		return invokable(inputVars, inoutVars, outputVars);
	};


}