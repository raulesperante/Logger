#include "FormatString.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;


//"[datetime] [logLevel]: @message"
string StringFormat::GetLoggerFormatFor(string datetime, string logLevel, string message){
	string out = "\n[" + datetime + "] [" + logLevel + "]: " + message;
	return out;
}

// Precondicion: n es un numero de una o dos cifras
// Postcondicion: Si n es de una cifra devuelve el string "0n". Caso contrario devuelve el string "n"
string StringFormat::ToStringWithPadding(int n){
	string numberWithPadding;
	int asciiCodeForZero = 48;
	if(n<10){
		numberWithPadding.push_back('0');
		numberWithPadding.push_back((char)asciiCodeForZero + n);
	}else{
		int decena = n / 10;// Obtengo el digito de la decena dividiendo por 10
		int unidad = n % 10;// Obtengo el digito de la unidad tomando el resto de la division por 10

		numberWithPadding.push_back(asciiCodeForZero + decena);
		numberWithPadding.push_back(asciiCodeForZero + unidad);
	}

	return numberWithPadding;
}

int StringFormat::CountCharacters(const char *texto){
	const char *primerDireccionMemoria = texto;
	while(*texto++);
	return (texto - primerDireccionMemoria) - 1;
}

int StringFormat::IndexOf(const char* texto, const char* textoBusqueda){
	int caracteresTexto = CountCharacters(texto);
	int caracteresBusqueda = CountCharacters(textoBusqueda);
	for(int i = 0; i<caracteresTexto-caracteresBusqueda; i++){
		int j;
		for(j=0; j<caracteresBusqueda;j++)
			if(texto[i+j] != textoBusqueda[j]) break;
		if(j==caracteresBusqueda) return i;
	}

	return caracteresTexto;
}


string StringFormat::GetAttributeValue(const char* tagOfElement,
							const char* elementName,
							const char* attributeName){
	string attributeFormat = "";
	const char* xmlLoggerElement = &tagOfElement[IndexOf(tagOfElement, elementName)];
	int indexAttributeName = IndexOf(xmlLoggerElement, attributeName);
	const char* xmlDateFormatAttribute = &xmlLoggerElement[indexAttributeName];
	int beginAttributeValue = IndexOf(xmlDateFormatAttribute, "\"") + 1;
	for(int i=beginAttributeValue; xmlDateFormatAttribute[i]!='"'; ++i){
		attributeFormat.push_back(xmlDateFormatAttribute[i]);
	}

	return attributeFormat;

}

string StringFormat::getElementLoggerXML(const char* xmlLogger, const char* elementName,
		const char* closeTag){
	string salida;
	int indiceComienzoEtiquetaApertura = IndexOf(xmlLogger, elementName);
	int indiceComienzoEtiquetaCierre = IndexOf(xmlLogger, closeTag);
	int indiceFinEtiquetaCierre = indiceComienzoEtiquetaCierre + CountCharacters(closeTag) - 1;
	for(int i=indiceComienzoEtiquetaApertura; i<=indiceFinEtiquetaCierre; ++i){
		salida.push_back(xmlLogger[i]);
	}
	return salida;
}

//Post: Devuelve el elemento xml que se corresponde con el @tag dado
string StringFormat::getTagXml(const char* xmlLogger, Tag tag){
	switch(tag){
		case LOGGER:
			return getElementLoggerXML(xmlLogger, "<logger", "</logger>");
			break;
		case APPENDER:
			return getElementLoggerXML(xmlLogger, "<appender", "/>");
			break;
		default:
			return NULL;
	}
}

char* StringFormat::PointerChar(const char* txt, const char* textoBusqueda){
	char* texto = new char[CountCharacters(txt)];
	std::strcpy(texto, txt);
	int caracteresTexto = CountCharacters(texto);
	int caracteresBusqueda = CountCharacters(textoBusqueda);
	for(int i = 0; i<caracteresTexto-caracteresBusqueda; i++){
		int j;
		for(j=0; j<caracteresBusqueda;j++)
			if(texto[i+j] != textoBusqueda[j
				]) break;
		if(j==caracteresBusqueda) return &texto[i];
	}

	if(1){
		return NULL;
	}
}

string StringFormat::ConvertFileToString(string pathFile){
	ifstream file;
	string line;
	string xml = "";

	file.open("config.txt", ios::in);

	if(file.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
		exit(1);
	}

	while(!file.eof()){
		getline(file, line);
		xml.append(line + "\n");
	}
	file.close();
	return xml;
}

char* StringFormat::CreateCopy(const char* origen){
	int cantCaracteres = StringFormat::CountCharacters(origen);
	char* aux = new char[cantCaracteres];
	std::strcpy(aux, origen);
	return aux;
}
