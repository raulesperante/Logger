#include <cstring>
#include "Logger.h"
#include "DateTime.h"
#include "ColectionAppenders.h"
#include "LogLevel.h"
#include "FormatString.h"
#include "LoggerSettings.h"
#include "ColectionSettings.h"

using std::string;
using ULLogger::Logger;
using ULAppender::Appender;
using namespace UndavLogLevel;
using ULLoggerSettings::LoggerSettings;

struct ULLogger::Logger{
	ULDateTime::DateTimeFormat formato;
	UndavColectionAppenders::ColectionAppenders* colectionAppender;

};

Logger* ULLogger::Create(DateTimeFormat dateTimeFormat){ //= ULDateTime::DDMMYYYY_hhmmss
	Logger* newLoger = new Logger;
	newLoger->formato = dateTimeFormat;
	newLoger->colectionAppender = UndavColectionAppenders::Crear(ULAppender::Comparator);
	return newLoger;

}

/*
 * Precondicion: @logger es una instancia valida
 * Postcondicion: Establece el tipo de formato de fecha y hora del logger
 */
void ULLogger::SetDateTimeFormat(Logger* logger, DateTimeFormat dateTimeFormat){
	logger->formato = dateTimeFormat;
}

/*
 * Precondicion: @logger es una instancia valida
 * Postcondicion: Obtiene el tipo de formato de fecha y hora asociado al logger
 */
DateTimeFormat ULLogger::GetDateTimeFormat(const Logger* logger){
	return logger->formato;
}

void ULLogger::AddAppender(Logger* logger, Appender* appender, LogLevel level){
	//Si el appender no esta en el logger
	if(!UndavColectionAppenders::Contains(logger->colectionAppender, appender, ULAppender::Comparator)){
		Appender* auxAppender;
		//Le asocio al appender el level
		if(ULAppender::EsTipoArchivo(appender)){
			auxAppender = ULAppender::CreateFileAppender(ULAppender::getPathFile(appender));
			ULAppender::SetLogLevel(auxAppender, level);
		}else{
			auxAppender = ULAppender::CreateConsoleAppender();
			ULAppender::SetLogLevel(auxAppender, level);
		}
		//Agrego el appender al logger
		UndavColectionAppenders::Agregar(logger->colectionAppender, auxAppender);
	}else{
		//Si ya existe el appender, lo elimina
		RemoveAppender(logger, appender);
		//Y lo reemplaza
		UndavColectionAppenders::Agregar(logger->colectionAppender, appender);
	}
}

void ULLogger::RemoveAppender(Logger* logger, Appender* appender){
	UndavColectionAppenders::EliminarItem(logger->colectionAppender, appender);
}

void BaseLogMessage(const string message, Logger* logger, LogLevel logLevel) {
	//Solo si el logger tiene appenders
	if (!UndavColectionAppenders::EstaVacia(logger->colectionAppender)) {
		bool isFile = false;
		string pathFile = "default.txt";
		//Buscar PathFile
		UndavColectionAppenders::IteratorUndav::Iterator* i = UndavColectionAppenders::IteratorUndav::Create(
				logger->colectionAppender);
		while (!UndavColectionAppenders::IteratorUndav::IsEnd(i) && !isFile) {
			ULAppender::Appender* appender =
					(ULAppender::Appender*) (UndavColectionAppenders::IteratorUndav::Next(i));
			if (ULAppender::EsTipoArchivo(appender)) {
				pathFile = ULAppender::getPathFile(appender);
				isFile = true;
			}
		}
		UndavColectionAppenders::IteratorUndav::Destroy(i);
		std::ofstream file;
		ULAppender::Open(file, pathFile);
		UndavColectionAppenders::IteratorUndav::Iterator* iterador =
				UndavColectionAppenders::IteratorUndav::Create(logger->colectionAppender);
		string newMessage = StringFormat::GetLoggerFormatFor(
				ULDateTime::ToFormat(ULDateTime::Now(), logger->formato),
				UndavLogLevel::logLevelToString(logLevel), message);
		while (!UndavColectionAppenders::IteratorUndav::IsEnd(iterador)) {
			ULAppender::Appender* appender =
					(ULAppender::Appender*) (UndavColectionAppenders::IteratorUndav::Next(
							iterador));
			ULAppender::Write(appender, newMessage, logLevel, file);
		}
		ULAppender::Close(file);
		UndavColectionAppenders::IteratorUndav::Destroy(iterador);
	}
}

void ULLogger::LogFatalMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, FATAL);
}

void ULLogger::LogErrorMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, ERROR);
}


void ULLogger::LogWarningMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, WARN);
}

void ULLogger::LogInfoMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, INFO);
}


void ULLogger::LogDebugMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, DEBUG);
}

void ULLogger::LogTraceMessage(Logger* logger, string message){
	BaseLogMessage(message, logger, TRACE);
}


Logger* ULLogger::SetLoggerSetting(LoggerSettings* loggerSetting){
	Logger* logger = Create(ULLoggerSettings::getDateTime(loggerSetting));
	UndavColectionSettings::IteratorUndav::Iterator* iterator = UndavColectionSettings::IteratorUndav::Create(ULLoggerSettings::getBag(loggerSetting));
	while(!UndavColectionSettings::IteratorUndav::IsEnd(iterator)){
		ULAppenderSettings::AppenderSettings* appenderSetting = (ULAppenderSettings::AppenderSettings*) (UndavColectionSettings::IteratorUndav::Next(iterator));
		Appender* appender = ULAppender::SetAppenderSettings(appenderSetting);
		AddAppender(logger, appender, ULAppenderSettings::GetLogLevel(appenderSetting));
	}
	UndavColectionSettings::IteratorUndav::Destroy(iterator);

	return logger;
}

Logger* ULLogger::BuildLogger(string xmlLoggerSetting){
	LoggerSettings* setting = ULLoggerSettings::GetLoggerSetting(xmlLoggerSetting);
	Logger* logger = SetLoggerSetting(setting);
	return logger;
}

Logger* ULLogger::BuildLoggerFromConfigFile(string pathConfigFile){
	string xmlLoggerSetting = StringFormat::ConvertFileToString(pathConfigFile);
	return BuildLogger(xmlLoggerSetting);
}

void ULLogger::Destroy(Logger* logger){
	UndavColectionAppenders::IteratorUndav::Iterator* iterador = UndavColectionAppenders::IteratorUndav::Create(logger->colectionAppender);
	void* item = NULL;
	while(!UndavColectionAppenders::IteratorUndav::IsEnd(iterador)){
		item = UndavColectionAppenders::IteratorUndav::Next(iterador);
		ULAppender::Appender* appender = (ULAppender::Appender*) item;
		ULAppender::Destroy(appender);
	}
	delete logger;
}
