#include "DateOfBirth.h"

DateOfBirth::DateOfBirth()
{
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

DateOfBirth::DateOfBirth(unsigned short day, unsigned short month, unsigned short year) :
	day(day), month(month), year(year) {};

void DateOfBirth::setDateOfBirth(unsigned short day, unsigned short month, unsigned short year) {
	this->day = day;
	this->month = month;
	this->year = year;
};
