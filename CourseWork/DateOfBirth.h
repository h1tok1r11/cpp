#pragma once

class DateOfBirth
{
private:
	unsigned short day;
	unsigned short month;
	unsigned short year;
public:
	DateOfBirth();
	DateOfBirth(unsigned short day, unsigned short month, unsigned short year);
	void setDateOfBirth(unsigned short day, unsigned short month, unsigned short year);
	unsigned short getDay() { return day; };
	unsigned short getMonth() { return month; };
	unsigned short getYear() { return year; };
};

