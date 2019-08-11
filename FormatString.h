#ifndef STRINGFORMAT_H_
#define STRINGFORMAT_H_
#include <string>
using std::string;
enum Tag{LOGGER, APPENDER};

namespace StringFormat{
	// "[datetime] [FATAL]: @message"
	//Pre:-
	//Post: Devuelve un string en el siguiente formato
	//"[datetime] [logLevel]: @message"
	string GetLoggerFormatFor(string datetime, string logLevel, string message);
	string ToStringWithPadding(int n);

	int CountCharacters(const char *texto);
	// Precondicion: ninguna
	// Postcondicion: Devuelve el indice en @texto donde se encuentra la PRIMER aparicion de
	// @textoBusqueda. Si no se encuentra, devuelve el indice del barra cero de @texto
	int IndexOf(const char* texto, const char* textoBusqueda);

	// Precondicion: @tagOfElement es una cadena que representa el elemento xml
	// @elementoName es una cadena de caracteres del elemento xml sobre el que se quiere
	//buscar el valor de un attributeName
	// Postcondicion: Devuelve el valor del atributo @nombreAtributo que se encuentra
	//en @elementoXml
	string GetAttributeValue(const char* tagOfElement,
								const char* elementName,
								const char* attributeName);

	string getElementLoggerXML(const char* xmlLogger, const char* elementName,
			const char* closeTag);

	//Post: Devuelve el elemento xml que se corresponde con el @tag dado
	string getTagXml(const char* xmlLogger, Tag tag);

	//Post: Si @textoBusqueda esta en @txt devuelve la direccion de memoria
	//Del primer caracter donde encontro a @textoBusqueda
	//Si no lo encuentra devuelve NULL
	char* PointerChar(const char* txt, const char* textoBusqueda);

	string ConvertFileToString(string pathFile);

	char* CreateCopy(const char* origen);

}


#endif /* STRINGFORMAT_H_ */
