#include "LoggerSettings.h"
#include "DateTime.h"
#include "AppenderSettings.h"
#include "AppenderType.h"
#include "LogLevel.h"
#include "ColectionSettings.h"
#include "FormatString.h"
#include <cstring>


using std::string;
using ULLoggerSettings::LoggerSettings;
using ULDateTime::DateTimeFormat;
using ULAppenderSettings::AppenderSettings;

struct ULLoggerSettings::LoggerSettings{
	ULDateTime::DateTimeFormat formato;
	UndavColectionSettings::ColectionSettings* colectionSetting;
};

/*
 * Precondicion: Ninguna
 * Postcondicion: Devuelve una instancia valida de un setting de logger
 * que tiene asociado un @dateTimeFormat
 */
LoggerSettings* ULLoggerSettings::Create(DateTimeFormat dateTimeFormat){
	LoggerSettings* settings = new LoggerSettings;
	settings->formato = dateTimeFormat;
	settings->colectionSetting = UndavColectionSettings::Create();
	return settings;

}

/*
 * Precondicion: @setting y @appenderSetting son instancias validas
 * Postcondicion: Agrega a @setting un @appenderSetting
 */
void ULLoggerSettings::AddAppenderSetting(LoggerSettings* setting,
										  AppenderSettings* appenderSetting)
{
	UndavColectionSettings::Add(setting->colectionSetting, appenderSetting);

}

string strAppender(string type, string logLevel){
	string nuevoString = "\n<appender type=\""+type+"\""+" logLevel=\""+logLevel+"\""+"/>";
	return nuevoString;
}

string strHeader(string format){
	string nuevoString = "<logger dateTimeFormat=\""+format+"\""+"/>";
	return nuevoString;
}

enum DateTimeFormat ULLoggerSettings::getDateTime(const LoggerSettings* setting){
	return setting->formato;
}

/*
 * Precondicion: @setting es una instancia valida
 * Postcondicion: Devuelve una representacion XML de @setting donde
 * - Hay un tag llamado [logger] que tiene un atributo  [dateTimeFormat] con el valor asociado de dateTimeFormat de @setting
 * - Por cada cada appender setting hay un tag llamado [appender] con los atributos [logLevel] y [type] que tienen como valor el log level y el type del appender
 * - Los tag [appender] son hijos de el tag [logger]
 */
string ULLoggerSettings::ToXml(const LoggerSettings* setting){
	string format = ULDateTime::PrintFormat(setting->formato);
	string header = strHeader(format);
	string storeAppeders = "";
	UndavColectionSettings::IteratorUndav::Iterator* iteradorBag = UndavColectionSettings::IteratorUndav::Create(setting->colectionSetting);
	while(!UndavColectionSettings::IteratorUndav::IsEnd(iteradorBag)){
		AppenderSettings* appender = (AppenderSettings*)UndavColectionSettings::IteratorUndav::Next(iteradorBag);
		string appenderType = UndavAppenderType::appenderTypeToString(ULAppenderSettings::GetAppenderType(appender));
		string logLevel = UndavLogLevel::logLevelToString(ULAppenderSettings::GetLogLevel(appender));
		string stringAppender = strAppender(appenderType, logLevel);
		storeAppeders.append(stringAppender);
	}
	UndavColectionSettings::IteratorUndav::Destroy(iteradorBag);
	header += storeAppeders;
	header += "\n</logger>";
	return header;
}

UndavColectionSettings::ColectionSettings* ULLoggerSettings::getBag(const LoggerSettings* setting){
	return setting->colectionSetting;
}

void LoadLoggerSettings(string tagAppender, LoggerSettings* setting)
{
	string tipoAppender = "";
	string tipoLogLevel = "";
	string strPath = "";
    //Extraer tipo appender
    tipoAppender = StringFormat::GetAttributeValue(tagAppender.c_str(), "<appender", "type");
    //Extraer tipo LogLevel
    tipoLogLevel = StringFormat::GetAttributeValue(tagAppender.c_str(), "<appender", "logLevel");
    //Extraer pathFile
    strPath = StringFormat::GetAttributeValue(tagAppender.c_str(), "<appender", "path");
    if(tipoAppender == "console"){
        AppenderSettings *appenderSetting = ULAppenderSettings::CreateAppenderConsoleSetting(UndavLogLevel::stringToLogLevel(tipoLogLevel));
        AddAppenderSetting(setting, appenderSetting);
    }else
        if(tipoAppender == "file"){
            AppenderSettings *appenderSetting = ULAppenderSettings::CreateAppenderFileSetting(UndavLogLevel::stringToLogLevel(tipoLogLevel), strPath);
            AddAppenderSetting(setting, appenderSetting);
        }

}



LoggerSettings* ULLoggerSettings::GetLoggerSetting(string xml){

	string elementLoggerXML = StringFormat::getTagXml(xml.c_str(), LOGGER);
	string strDateTimeFormat = StringFormat::GetAttributeValue(elementLoggerXML.c_str(),
	"<logger", "dateTimeFormat");
	LoggerSettings* setting = Create(ULDateTime::stringToDateTime(strDateTimeFormat));

	char* aux = StringFormat::CreateCopy(elementLoggerXML.c_str());
	char* pdest = NULL;
	int pos = 0;
	char* searchedText = "<appender";
	int len = StringFormat::CountCharacters(searchedText);
	while((pdest = StringFormat::PointerChar(aux, searchedText))){
		LoadLoggerSettings(StringFormat::getTagXml(pdest, APPENDER), setting);
		pos = pdest - aux;
		aux += pos + len;
	}
	delete[] aux;

	return setting;

}

void ULLoggerSettings::Destroy(LoggerSettings* setting){
	UndavColectionSettings::IteratorUndav::Iterator* iterador = UndavColectionSettings::IteratorUndav::Create(setting->colectionSetting);
	void* item = NULL;
	while(!UndavColectionSettings::IteratorUndav::IsEnd(iterador)){

		item = UndavColectionSettings::IteratorUndav::Next(iterador);
		ULAppenderSettings::AppenderSettings* appenderSetting =
				(ULAppenderSettings::AppenderSettings*) item;
		ULAppenderSettings::Destroy(appenderSetting);
	}
	delete setting;
}

