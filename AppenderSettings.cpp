#include <string>
#include "AppenderSettings.h"
#include "AppenderType.h"
#include "LogLevel.h"

using std::string;
using ULAppenderSettings::AppenderSettings;
using UndavLogLevel::LogLevel;

struct ULAppenderSettings::AppenderSettings{
	UndavAppenderType::AppenderType appenderType;
	LogLevel logLevel;
	string pathFile;
};

//El atributo pathFile es un string vacio para AppenderConsoleSetting
AppenderSettings* ULAppenderSettings::CreateAppenderConsoleSetting(LogLevel logLevel){
	AppenderSettings* appenderSettings = new AppenderSettings;
	appenderSettings->appenderType = UndavAppenderType::AppenderType::Console;
	appenderSettings->logLevel = logLevel;
	appenderSettings->pathFile = "";
	return appenderSettings;
}

AppenderSettings* ULAppenderSettings::CreateAppenderFileSetting(LogLevel logLevel, string pathFile){
	AppenderSettings* appenderSettings = new AppenderSettings;
	appenderSettings->appenderType = UndavAppenderType::AppenderType::File;
	appenderSettings->logLevel = logLevel;
	appenderSettings->pathFile = pathFile;
	return appenderSettings;
}

LogLevel ULAppenderSettings::GetLogLevel(const AppenderSettings* settings){
	return settings->logLevel;
}

UndavAppenderType::AppenderType ULAppenderSettings::GetAppenderType(const AppenderSettings* settings){
	return settings->appenderType;
}

string ULAppenderSettings::GetPathFile(const AppenderSettings* settings){
	return settings->pathFile;
}

void ULAppenderSettings::Destroy(AppenderSettings* setting){
	delete setting;
}


