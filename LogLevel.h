#ifndef LOGLEVEL_H_
#define LOGLEVEL_H_
#include <string>
using std::string;


namespace UndavLogLevel{
	enum LogLevel{ OFF, FATAL,	ERROR, WARN, INFO, DEBUG, TRACE, NULO };
	string logLevelToString(LogLevel logLevel);
	enum LogLevel stringToLogLevel(string logLevel);

}

#endif
