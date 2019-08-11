#ifndef LOGGERSETTINGS_H_
#define LOGGERSETTINGS_H_

#include "AppenderSettings.h"
#include "DateTime.h"
#include "ColectionSettings.h"
#include "cstring"

using std::string;
using ULAppenderSettings::AppenderSettings;
using ULDateTime::DateTimeFormat;
using UndavColectionSettings::ColectionSettings;

namespace ULLoggerSettings{
	struct LoggerSettings;

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Devuelve una instancia valida de un setting de logger
	 * que tiene asociado un @dateTimeFormat
	 */
	LoggerSettings* Create(DateTimeFormat dateTimeFormat);

	/*
	 * Precondicion: @setting y @appenderSetting son instancias validas
	 * Postcondicion: Agrega a @setting un @appenderSetting
	 */
	void AddAppenderSetting(LoggerSettings* setting, AppenderSettings* appenderSetting);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Devuelve una representacion XML de @setting donde
	 * - Hay un tag llamado [logger] que tiene un atributo  [dateTimeFormat] con el valor asociado de dateTimeFormat de @setting
	 * - Por cada cada appender setting hay un tag llamado [appender] con los atributos [logLevel] y [type] que tienen como valor el log level y el type del appender
	 * - Los tag [appender] son hijos de el tag [logger]
	 */
	string ToXml(const LoggerSettings* setting);


	enum DateTimeFormat getDateTime(const LoggerSettings* setting);

	ColectionSettings* getBag(const LoggerSettings* setting);

	//Dado un @xml que contiene la configuracion del logger devuelve
	//una instancia validad para esa configuracion
	LoggerSettings* GetLoggerSetting(string xml);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Libera todos los recursos asociados de @setting
	 */
	void Destroy(LoggerSettings* setting);
}

#endif
