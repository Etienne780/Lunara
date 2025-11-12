#pragma once
#include <string>
#include <CoreLib/FormatUtils.h>

#include "SDLCoreTypes.h"

namespace SDLCore {

	std::string GetError(SDLResult result) {
		std::string msg;
		switch (result)
		{
		case 0:
			msg = "Application closed successfully";
			break;
		case 1:
			msg = "Application SDL3 error!";
			break;
		default:
			msg = "Result '" + FormatUtils::toString(result) + "' is Unknon!";
		}

		return msg;
	}

}