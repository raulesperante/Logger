#include <string>
#include "LogLevel.h"

using std::string;
using UndavLogLevel::LogLevel;

string UndavLogLevel::logLevelToString(LogLevel logLevel){
	string level;
	switch(logLevel){
		case OFF: level = "OFF";
			break;
		case FATAL: level = "FATAL";
			break;
		case ERROR: level = "ERROR";
			break;
		case WARN: level = "WARN";
			break;
		case INFO: level = "INFO";
			break;
		case DEBUG: level = "DEBUG";
			break;
		case TRACE: level = "TRACE";
			break;
		case NULO: level = "NULO";
			break;
	}
	return level;
}

enum UndavLogLevel::LogLevel UndavLogLevel::stringToLogLevel(string logLevel){
	if(logLevel == "OFF"){
		return OFF;
	}else if(logLevel == "FATAL"){
		return FATAL;
	}else if(logLevel == "ERROR"){
		return ERROR;
	}else if(logLevel == "WARN"){
		return WARN;
	}else if(logLevel == "INFO"){
		return INFO;
	}else if(logLevel == "DEBUG"){
		return DEBUG;
	}else if(logLevel == "TRACE"){
		return TRACE;
	}else{
		return NULO;
	}
}
