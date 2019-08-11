#include "DateTime.h"
#include "FormatString.h"
#include <ctime>
#include <string>

using ULDateTime::DateTime;
using std::string;
using std::to_string;
using namespace StringFormat;

struct ULDateTime::DateTime{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
};

//Pre:-
//Post: Devuelve true si todos los valores dados por parametro son válidos para una fecha.
//Caso contrario devuelve false
bool ValidDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, int minutes, int seconds);

//Pre:- Los valores dados por parametros representan una fecha valida
//Post: Crea una instancia valida de DateTime
DateTime* CreateDateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, int minutes, int seconds);


//Si @flag es true devuelve el instante actual,
//Si @flag es false devuelve la hora en formato universal
DateTime* BaseNow(bool flag){
	time_t tiempo = time(NULL);
	struct tm* fechaHora = NULL;
	if(flag){
		fechaHora = localtime(&tiempo);
	}else{
		fechaHora = gmtime(&tiempo);
	}
	DateTime* datetime=  CreateDateTime(fechaHora->tm_year+1900,
							fechaHora->tm_mon+1,
							fechaHora->tm_mday,
							fechaHora->tm_hour,
							fechaHora->tm_min,
							fechaHora->tm_sec);
	return datetime;
}

DateTime* ULDateTime::Now(){
  	DateTime* datetime = BaseNow(true);
  	return datetime;
}

DateTime* ULDateTime::UTCNow(){
  	DateTime* datetime = BaseNow(false);
  	return datetime;

}

bool ValidDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, int minutes, int seconds){
	// El año puede ser cualquier entero
	bool bisiesto = false;
	bool fechaValida = false;

	if((year%4==0) && ((year%100!=100) || (year%400==0))){ bisiesto = true;}
    if(day>0 && day<32 && month>0 && month<13 && year>0){
        if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
        {
           fechaValida = true;
        }
        else{
            if(month==2 && day<30 && bisiesto)
                fechaValida = true;
            else if(month==2 && day<29 && !bisiesto)
                fechaValida = true;
            else if(month!=2 && day<31)
                fechaValida = true;
            else
                fechaValida = false;
        	}
    }else{
        fechaValida = false;
		}
	bool validHour = hour >= 0 && hour < 24;
	bool validMinute = minutes >= 0 && minutes < 60;
	bool validSecond = seconds >= 0 && seconds < 60;
	return fechaValida && validHour && validMinute && validSecond;
}

DateTime* CreateDateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, int minutes, int seconds){
	DateTime* datetime = new DateTime;
	datetime->year = year;
	datetime->month = month;
	datetime->day = day;
	datetime->hour = hour;
	datetime->minute = minutes;
	datetime->second = seconds;
	return datetime;
}

DateTime* ULDateTime::Create(unsigned int year = 2019, unsigned int month = 1, unsigned int day = 1, unsigned int hour=0, int minutes=0, int seconds=0){
	if(ValidDate(year, month, day, hour, minutes, seconds)){
		DateTime* datetime = CreateDateTime(year, month, day, hour, minutes, seconds);
		return datetime;
	}else{
		return NULL;
	}
}

unsigned int ULDateTime::GetYear(const DateTime* dateTime){
	return dateTime->year;
}

unsigned int  ULDateTime::GetMonth(const DateTime* dateTime){
	return dateTime->month;
}

unsigned int ULDateTime::GetDay(const DateTime* dateTime){
	return dateTime->day;
}

unsigned int ULDateTime::GetHour(const DateTime* dateTime){
	return dateTime->hour;
}

unsigned int ULDateTime::GetMinutes(const DateTime* dateTime){
	return dateTime->minute;
}

unsigned int ULDateTime::GetSeconds(const DateTime* dateTime){
	return dateTime->second;
}

//Pre: @format es una instancia valida
//Post: imprime el formato
string ULDateTime::PrintFormat(DateTimeFormat format){
	string fecha;
	switch(format){
		case YYYYMMDD_HHmmss: fecha = "YYYYMMDD_HHmmss";
			break;
		case YYYYMMDD_hhmmss: fecha = "YYYYMMDD_hhmmss";
			break;
		case DDMMYYYY_hhmmss: fecha = "DDMMYYYY_hhmmss";
			break;
		case DDMMYYYY_HHmmss: fecha = "DDMMYYYY_HHmmss";
			break;
		case YYYYMMDDHHmmss: fecha = "YYYYMMDDHHmmss";
			break;
		case YYMD_Hms: fecha = "YYMD_Hms";
			break;
		case YYMD_hms: fecha = "YYMD_hms";
			break;
		case DMYY_hms: fecha = "DMYY_hms";
			break;
		case DMYY_Hms: fecha = "DMYY_Hms";
			break;
		default:
			return NULL;
	}
	return fecha;
}

string ULDateTime::ToFormat(const DateTime* dateTime, DateTimeFormat format){
	//string fecha = new string;
	string fecha;
	switch(format){
    	case YYYYMMDD_HHmmss:  fecha = to_string(dateTime->year)+"-"+ToStringWithPadding(dateTime->month)+"-"+ToStringWithPadding(dateTime->day)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second);	// - YYYYMMDD_HHmmss: 2019-04-27 19:01:10
			break;
    	case YYYYMMDD_hhmmss:  if(dateTime->hour > 12){
    								fecha = to_string(dateTime->year)+"-"+ToStringWithPadding(dateTime->month)+"-"+ToStringWithPadding(dateTime->day)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second)+" p.m.";// - YYYYMMDD_hhmmss: 2019-04-27 07:01:10 p.m.
    							}else{
    								fecha = to_string(dateTime->year)+"-"+ToStringWithPadding(dateTime->month)+"-"+ToStringWithPadding(dateTime->day)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second)+" a.m.";
    							}
			break;
    	case DDMMYYYY_hhmmss:  if(dateTime->hour > 12){
    								fecha = ToStringWithPadding(dateTime->day)+"-"+ToStringWithPadding(dateTime->month)+"-"+to_string(dateTime->year)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second)+" p.m.";// - DDMMYYYY_hhmmss: 27-04-2019 07:01:10 p.m.
								}else{
									fecha = ToStringWithPadding(dateTime->day)+"-"+ToStringWithPadding(dateTime->month)+"-"+to_string(dateTime->year)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second)+" a.m.";
								}
			break;
    	case DDMMYYYY_HHmmss:  fecha = ToStringWithPadding(dateTime->day)+"-"+ToStringWithPadding(dateTime->month)+"-"+to_string(dateTime->year)+" "+ToStringWithPadding(dateTime->hour)+":"+ToStringWithPadding(dateTime->minute)+":"+ToStringWithPadding(dateTime->second);// - DDMMYYYY_HHmmss: 27-04-2019 19:01:10
			break;
    	case YYYYMMDDHHmmss:  fecha = to_string(dateTime->year)+ToStringWithPadding(dateTime->month)+ToStringWithPadding(dateTime->day)+ToStringWithPadding(dateTime->hour)+ToStringWithPadding(dateTime->minute)+ToStringWithPadding(dateTime->second);// - YYYYMMDDHHmmss
			break;
    	case YYMD_Hms:  fecha = to_string(dateTime->year).substr(2,4)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->day)+" "+to_string(dateTime->hour)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second);// - YYMD_Hms: 19-4-27 19:1:10
			break;
    	case YYMD_hms:  if(dateTime->hour > 12){
    						fecha = to_string(dateTime->year).substr(2,4)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->day)+" "+to_string(dateTime->hour-12)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second)+" p.m.";// - YYMD_hms: 19-4-27 7:1:10 p.m.
    					}else{
    						 fecha = to_string(dateTime->year).substr(2,4)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->day)+" "+to_string(dateTime->hour)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second)+" a.m.";
    					}
    		break;
    	case DMYY_hms:  if(dateTime->hour > 12){
    						fecha = to_string(dateTime->day)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->year).substr(2,4)+" "+to_string(dateTime->hour-12)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second)+" p.m.";// - DMYY_hms: 27-4-19 7:1:10 p.m.
    					}else{
    						fecha = to_string(dateTime->day)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->year).substr(2,4)+" "+to_string(dateTime->hour-12)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second)+" a.m.";
    					}
			break;
    	case DMYY_Hms:  fecha = to_string(dateTime->day)+"-"+to_string(dateTime->month)+"-"+to_string(dateTime->year).substr(2,4)+" "+to_string(dateTime->hour)+":"+to_string(dateTime->minute)+":"+to_string(dateTime->second);// - DMYY_Hms: 27-4-19 19:1:10
			break;
    	default:
    		return NULL;

	}
	return fecha;
}

enum ULDateTime::DateTimeFormat ULDateTime::stringToDateTime(string dateTimeFormat){
	if(dateTimeFormat == "YYYYMMDD_HHmmss"){
		return ULDateTime::DateTimeFormat::YYYYMMDDHHmmss;
	}else if(dateTimeFormat == "YYYYMMDD_hhmmss"){
		return ULDateTime::DateTimeFormat::YYYYMMDD_hhmmss;
	}else if(dateTimeFormat == "DDMMYYYY_HHmmss"){
		return ULDateTime::DateTimeFormat::DDMMYYYY_HHmmss;
	}else if(dateTimeFormat == "DDMMYYYY_hhmmss"){
		return ULDateTime::DateTimeFormat::DDMMYYYY_hhmmss;
	}else if(dateTimeFormat == "YYYYMMDDHHmmss"){
		return ULDateTime::DateTimeFormat::YYYYMMDDHHmmss;
	}else if(dateTimeFormat == "YYMD_Hms"){
		return ULDateTime::DateTimeFormat::YYMD_Hms;
	}else if(dateTimeFormat == "YYMD_hms"){
		return ULDateTime::DateTimeFormat::YYMD_hms;
	}else if(dateTimeFormat == "DMYY_Hms"){
		return ULDateTime::DateTimeFormat::DMYY_Hms;
	}else if(dateTimeFormat == "DMYY_hms"){
		return ULDateTime::DateTimeFormat::DMYY_hms;
	}else{
		return ULDateTime::DateTimeFormat::NULO;
	}

}

void ULDateTime::Destroy(DateTime* dateTime){
	delete dateTime;
}
