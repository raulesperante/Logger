#include "AppenderType.h"
#include <string>
using std::string;

string UndavAppenderType::appenderTypeToString(AppenderType appenderType){
	string type;
	switch(appenderType){
		case UndavAppenderType::AppenderType::Console: type = "console";
			break;
		case UndavAppenderType::AppenderType::File: type = "file";
			break;
	}
	return type;
}
