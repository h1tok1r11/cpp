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
	int day;
	int month;
	int year;
public:
	clDate() {
		setDate(24, 04, 2004);
	}
	clDate(unsigned short _day, unsigned short _month, unsigned short _year) {
		setDate(_day, _month, _year);
	}
	clDate(Date myDate) {
		setDate(myDate);
	}
	clDate(Date* pmyDate) {
		setDate(pmyDate);
		
	}
	clDate(const clDate& p) {
		day = p.day;
		month = p.month;
		year = p.year;
		if (day < 26)
			day += 5;
		else {
			cout << "Недопустимая дата" << endl;
		}
	}
	//~clDate();
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
	}
	void printDate() {
		if (0 < this->day < 10)
			cout << 0;
		cout << this->day << ".";
		if (0 < this->month < 10)
			cout << 0;
		cout << this->month << "." << this->year;
	}
	~clDate() { cout << "Деструктор clDate" << endl; }
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
		setRecord("Зайцев", 'Ш', 23.23, 3, {28, 02, 1980});
	}
	clRecord(ifstream &file) {
		setRecord(file);
	}
	clRecord(Record* myDate) {
		setRecord(myDate);
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
		string day;
		string month;
		string year;
		getline(file, day, '.');
		getline(file, month, '.');
		getline(file, year, '.');
		int _day = stoi(day);
		int _month = stoi(month);
		int _year = stoi(year);
		date.setDate(_day, _month, _year);
		setRecord(surname, code, count, place, date);
	}
	~clRecord() { cout << "Деструктор clRecord" << endl; }
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Date myDate = {2, 2, 2022};
	clDate* myDynamicDate = new clDate;
	ifstream file("Зайцев.txt");

	clDate A;
	clDate B(myDate);
	clDate C(12, 12, 2023);
	delete myDynamicDate;
	clDate D(A);

	clRecord E(file);
}