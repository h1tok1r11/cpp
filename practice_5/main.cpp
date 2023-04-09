#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct Record
{
	char surname[20];
	char code;
	double count;
	unsigned short place;
	struct Date date;
};

class clDate {
private:
	unsigned short day;
	unsigned short month;
	unsigned short year;
public:
	clDate() {
		setDate(24, 04, 2004);
		//cout << "Конструктор clDate" << endl;
	}
	clDate(unsigned short _day, unsigned short _month, unsigned short _year) {
		setDate(_day, _month, _year);
		//cout << "Конструктор clDate" << endl;
	}
	clDate(Date myDate) {
		setDate(myDate);
		//cout << "Конструктор clDate" << endl;
	}
	clDate(Date* pmyDate) {
		setDate(pmyDate);
		//cout << "Конструктор clDate" << endl;
	}
	clDate(const clDate& p) {
		day = p.day;
		month = p.month;
		year = p.year;
		if (day < 26)
			day += 5;
		else
			cout << "Недопустимая дата" << endl;
		//cout << "Конструктор clDate" << endl;
	}
	void setDate(unsigned short _day, unsigned short _month, unsigned short _year) {
		day = _day;
		month = _month;
		year = _year;
	}
	void setDate(Date myDate) {
		setDate(myDate.day, myDate.month, myDate.year);
	}
	void setDate(Date *myDate) {
		setDate(myDate->day, myDate->month, myDate->year);
	}
	Date getDate() {
		Date myDate;
		myDate.day = this->day;
		myDate.month = this->month;
		myDate.year = this->year;
		printDate();
		return myDate;
	}
	void printDate() {
		if (0 < this->day < 10)
			cout << 0;
		cout << this->day << ".";
		if (0 < this->month < 10)
			cout << 0;
		cout << this->month << "." << this->year;
	}
	~clDate() {}
};

class clRecord {
	string surname;
private:
	double count;
protected:
	unsigned short place;
	clDate date;
public:
	char code;
	clRecord() {
		setRecord("Зайцев", 'Ш', 23.23, 3, {23, 02, 1980});
		//cout << "Конструктор clRecord" << endl;
	}
	clRecord(ifstream &file) {
		setRecord(file);
		//cout << "Конструктор clRecord" << endl;
	}
	clRecord(Record* myRecord) {
		setRecord(myRecord);
		//cout << "Конструктор clRecord" << endl;
	}
	void setRecord(string mySurname, char myCode, double myCount, unsigned short myPlace, clDate myDate) {
		surname = mySurname;
		code = myCode;
		count = myCount;
		place = myPlace;
		date = myDate;
	}
	void setRecord(Record* myRecord) {
		setRecord(myRecord->surname, myRecord->code, myRecord->count, myRecord->place, myRecord->date);
	}
	void setRecord(ifstream &file) {
		file.open("Зайцев.txt");
		file >> surname;
		file >> code;
		file >> count;
		file >> place;
		unsigned short day;
		unsigned short month;
		unsigned short year;
		file >> day;
		file >> month;
		file >> year;
		date.setDate(day, month, year);
	}
	void getRecord() {
		//cout << surname << code << count << place << endl;
		date.getDate();
	}
	~clRecord() {}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Record records[10];
	records[0] = { "Баландин", 'С', 123.7000, 2, {6,6,2022} };
	records[1] = { "Шишков", 'Ш', 79.9800, 3, {7,7,2022} };
	records[2] = { "Кравченко", 'Д', 134.8000, 1, {7,6,2022} };

	Date myDate = {2, 2, 2022};
	clDate* myDynamicDate = new clDate;
	ifstream file("Зайцев.txt");

	clDate A;
	clDate B(myDate);
	clDate C(12, 12, 2023);
	clDate D(A);

	clRecord E(file);
	clRecord* myDynamicRecord = new clRecord;

	delete myDynamicDate;
	delete myDynamicRecord;

	clRecord arr[3];
	arr[0] = clRecord();
	arr[0].getRecord();
	arr[0].setRecord("Баландин", 'С', 123.7000, 2, { 6,6,2022 });
	arr[1].setRecord("Шишков", 'Ш', 79.9800, 3, { 7,7,2022 });
	arr[2].setRecord("Кравченко", 'Д', 134.8000, 1, { 7,6,2022 });
}