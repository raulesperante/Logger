#ifndef APPENDERTYPE_H_
#define APPENDERTYPE_H_
#include <string>
using std::string;


namespace UndavAppenderType{
	enum AppenderType { Console, File };
	string appenderTypeToString(AppenderType appenderType);
}


#endif
