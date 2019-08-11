#ifndef APPENDER_H_
#define APPENDER_H_

#include <string>
#include <fstream>
#include "LogLevel.h"
#include "AppenderSettings.h"
using ULAppenderSettings::AppenderSettings;

using std::string;
using UndavLogLevel::LogLevel;
using UndavLogLevel::LogLevel::NULO;

namespace ULAppender{

	struct Appender;
	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Si @pathFile es un path invalido devuelve NULL.
	 * Si @pathFile es valido devuelve una instancia de Appender del tipo archivo. Si el archivo ya existia no lo debe truncar (borrar el contenido)
	 * Parametros:
	 * 		@pathFile: ruta y nombre del archivo donde se desea escribir
	 * 		@return: Instancia de Appender lista para ser utilizada por las primitivas del TDA Appender
	 */
	Appender* CreateFileAppender(string pathFile);

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Devuelve una instancia de Appender del tipo consola.
	 * Parametros:
	 * 		@return: Instancia de Appender lista para ser utilizada por las primitivas del TDA Appenders
	 */
	Appender* CreateConsoleAppender();

	/*
	 * Precondicion: @appender fue creado con alguna de las primitivas: CreateFileAppender o CreateConsoleAppender
	 * Postcondicion: Si el @appender es del tipo Consola escribe @message en una nueva linea en la salida estandard
	 * Si @appender es del tipo archivo escribe @message en una nueva linea al final del archivo
	 * Parametros:
	 * 		@appender: Instancia de Appender donde se desea escribir el @message
	 * 		@message: Mensaje que se desea escribir en el log.
	 */

	void Write(Appender* appender, string message, LogLevel logLevel, std::ofstream &archivo);

	//Pre: @appender es una instancia valida
	//Post: agrega un logLevel al appender
	void SetLogLevel(Appender* appender, LogLevel logLevel=NULO);

	//Post: devuelve true si los appender son iguales
	//Dos appenderConsole son siempre iguales y los appenderFile, son iguales
	//si los pathFile lo son
	bool Comparator(void* ptrVoidAppender1, void* ptrVoidAppender2);

	bool EsTipoArchivo(Appender* appender);

	string getPathFile(Appender* appender);


	void Open(std::ofstream &archivo, string pathFile);

	void Close(std::ofstream &archivo);

	Appender* SetAppenderSettings(AppenderSettings* appenderSetting);

	/*
	 * Precondicion: @appender fue creado con alguna de las primitivas: CreateFileAppender o CreateConsoleAppender
	 * Postcondicion: Libera los rescursos asociados a @appender.
	 * Parametros:
	 * 		@appender: Instancia de Appender que se desea destruir
	 */
	void Destroy(Appender* appender);
}

#endif
