#include <iostream>
#include <string>
#include "Logger.h"

using std::string;
using namespace ULLogger;
using std::cout;
using std::endl;
using namespace UndavLogLevel;

void TestLogger(Logger* logger);

int main() {
	string settings = "<logger dateTimeFormat=\"YYMD_Hms\">\n\t<appender type=\"console\" logLevel=\"INFO\"/>\n\t<appender type=\"file\" logLevel=\"DEBUG\" path=\"logFile1.log\"/>\n</logger>";
	cout<<settings<<endl;
	Logger* logger1 = BuildLogger(settings);
	Logger* logger2 = BuildLoggerFromConfigFile("config.txt");
	cout<<endl<<"Prueba BuildLogger"<<endl;
	TestLogger(logger1);
	cout<<endl<<"Prueba BuildLoggerFromConfigFile"<<endl;
	TestLogger(logger2);
}

void TestLogger(Logger* logger){

	LogFatalMessage(logger, "Log 1 ");
	LogErrorMessage(logger, "Log 2 ");
	LogWarningMessage(logger, "Log 3 ");
	LogDebugMessage(logger, "Log 4 ");
	LogTraceMessage(logger, "Log 5 ");
	LogInfoMessage(logger, "Log 6 ");
}

