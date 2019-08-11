#include <iostream>
#include <fstream>
#include <string>
#include "Appender.h"
#include "LogLevel.h"
#include "AppenderSettings.h"
#include "AppenderType.h"

using ULAppender::Appender;
using ULAppenderSettings::AppenderSettings;
using namespace UndavLogLevel;
using std::string;

enum Tipo{TypeConsole, TypeFile};

struct ULAppender::Appender{
	Tipo tipo;
	string pathFile;
	LogLevel logLevel;
	string message;
};

//Pre: Recibe una instancia valida de appender
//Devuelve true si @appender es del tipo archivo, sino devuelve false
bool ULAppender::EsTipoArchivo(Appender* appender);

//pre: @appender y message son instancias validas
//post: escribe @message al final del archivo
void WriteFile(Appender* appender, string message);

Appender* ULAppender::CreateFileAppender(string pathFile){
	Appender* appender = new Appender;
	appender->tipo = TypeFile;
	appender->pathFile = pathFile;
	appender->logLevel = NULO;
	appender->message = "";
	return appender;
}

Appender* ULAppender::CreateConsoleAppender(){
	Appender* appender = new Appender;
	appender->tipo = TypeConsole;
	string strVacio = "";
	appender->pathFile = strVacio;
	appender->logLevel = NULO;
	appender->message = "";
	return appender;
}

bool ULAppender::EsTipoArchivo(Appender* appender){return appender->tipo == TypeFile;}

void  ULAppender::Open(std::ofstream &archivo, string pathFile){

	archivo.open(pathFile, std::ios::app);
}

void  ULAppender::Close(std::ofstream &archivo){
	archivo.close();
}

void WriteFile(Appender* appender, string message, std::ofstream &archivo){
//	std::ofstream archivo;
//
//	archivo.open(appender->pathFile, std::ios::app);

	if(archivo.fail()){
		std::cout<<"No se pudo abrir el archivo"<<std::endl;
		exit(1);
	}

	archivo<<message<<std::endl;

//	archivo.close();
}

void OutStream(const string message, Appender* appender, std::ofstream &archivo) {
	if (EsTipoArchivo(appender)) {
		WriteFile(appender, message, archivo);
	} else {
		std::cout << message << std::endl;
	}
}

void ULAppender::Write(Appender* appender, string message, LogLevel logLevel, std::ofstream &archivo){
	if(logLevel != NULO){
		// Nuevo Comportamiento
		if(logLevel == FATAL){
			if(appender->logLevel != OFF){
				OutStream(message, appender, archivo);
			}
		}else if(logLevel == ERROR){
			if(appender->logLevel == ERROR ||
			   appender->logLevel == WARN ||
			   appender->logLevel == INFO ||
			   appender->logLevel == DEBUG ||
			   appender->logLevel == TRACE){
				OutStream(message, appender, archivo);
			}
		}else if(logLevel == WARN){
			if(appender->logLevel == WARN ||
			   appender->logLevel == INFO ||
			   appender->logLevel == DEBUG ||
			   appender->logLevel == TRACE){
				OutStream(message, appender, archivo);
			}
		}else if(logLevel == INFO){
			if(appender->logLevel == INFO ||
			   appender->logLevel == DEBUG ||
			   appender->logLevel == TRACE){
				OutStream(message, appender, archivo);
			}
		}else if(logLevel == DEBUG){
			if(appender->logLevel == DEBUG ||
			   appender->logLevel == TRACE){
				OutStream(message, appender, archivo);
			}
		}else if(logLevel == TRACE){
			if(appender->logLevel == TRACE){
				OutStream(message, appender, archivo);
			}
		}
	}else{
		OutStream(message, appender, archivo);
	}
}
//LogLevel puede ser NULO
void ULAppender::SetLogLevel(Appender* appender, LogLevel logLevel){
	if(logLevel != NULO) appender->logLevel = logLevel;
}

bool ULAppender::Comparator(void* ptrVoidAppender1, void* ptrVoidAppender2){
	Appender* appender1 = (Appender*) ptrVoidAppender1;
	Appender* appender2 = (Appender*) ptrVoidAppender2;
	if(appender1->tipo == TypeConsole && appender2->tipo == TypeConsole){
		return true;
	}
	if(appender1->tipo == TypeFile && appender2->tipo == TypeFile){
		if(appender1->pathFile == appender2->pathFile){
			return true;
		}
		return false;
	}
	return false;
}

string ULAppender::getPathFile(Appender* appender){
	return appender->pathFile;
}

Appender* ULAppender::SetAppenderSettings(AppenderSettings* appenderSetting){
	if(ULAppenderSettings::GetAppenderType(appenderSetting) == UndavAppenderType::AppenderType::Console){
		Appender* appender = CreateConsoleAppender();
		SetLogLevel(appender, ULAppenderSettings::GetLogLevel(appenderSetting));
		return appender;
	}else if(ULAppenderSettings::GetAppenderType(appenderSetting) == UndavAppenderType::AppenderType::File){
		Appender* appender = CreateFileAppender(ULAppenderSettings::GetPathFile(appenderSetting));
		SetLogLevel(appender, ULAppenderSettings::GetLogLevel(appenderSetting));
		return appender;
	}else{
		return NULL;
	}
}

void ULAppender::Destroy(Appender* appender){
	delete appender;
}
