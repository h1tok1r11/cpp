#pragma once
#include <iostream>
#include <string>
#include <conio.h>
//#include <stdio.h>
//#include "ClassMenu.h"

using namespace std;


enum class editType : char { onlyDigits, onlyAlpha, date,all };


class InputValidation
{
private:
	string label;
	string data;
public:
	InputValidation() {
		label = "";
		data = "";
	}
	void setLabel(string _label = "") {
		if (_label.length() > 1)
			this->label = _label;
		else
			label = "";
	}
	bool isDigit(char ch) {
		if (ch >= 48 and ch <= 57)
			return true;
		else
			return false;
	}
	bool isStringOfDigit(string _str) {
		for (int i = 0; i < _str.length(); i++)
			if (not isDigit(_str[i]))
				return false;
		if (_str.length() == 0)
			return false;
		return true;
	}
	bool isAlpha(int ch) {
		if (ch >= 65 and ch <= 90)
			return true;
		if (ch >= 97 and ch <= 122)
			return true;
		/*if (ch >= 192 and ch <= 255)
			return true;*/
		if (ch >= -200 and ch <= -1)
			return true;
		return false;
	}
	bool isSpace(char ch) {
		if (ch == 32)
			return true;
		else
			return false;
	}
	bool isSpec(char ch) {
		if (ch >= 33 and ch <= 47)
			return true;
		else
			return false;
	}
	void clear(string _data = "") {
		system("cls");
		data = _data;
	}

	string reverseDate(string date) {
		string tmpDate = "";
		for (int i = 6; i < 10; i++) {
			tmpDate += date[i];
		}
		tmpDate += ".";
		for (int i = 3; i < 5; i++) {
			tmpDate += date[i];
		}
		tmpDate += ".";
		for (int i = 0; i < 2; i++) {
			tmpDate += date[i];
		}
		return tmpDate;
	}

	bool isDateTrue(string date) {
		string strDay = "";
		string strMonth = "";
		string strYear = "";
		for (int i = 0; i < 2; i++) {
			strDay += date[i];
		}
		for (int i = 3; i < 5; i++) {
			strMonth += date[i];
		}
		for (int i = 6; i < 10; i++) {
			strYear += date[i];
		}
		int day = atoi(strDay.c_str());
		int month = atoi(strMonth.c_str());
		int year = atoi(strYear.c_str());
		if (day <= 31 && day > 0) {
			if (month <= 12 && month > 0) {
				return true;
			}
		}
		return false;
	}

	string getData(enum class editType et) {
		char ch = 0;
		cout << label << endl << data;

		while (ch != 13) {
			ch = _getch();
			if (ch == 8) {
				if (data.length() > 0) {
					data.pop_back();
					system("cls");
					cout << label << endl << data;
				}
				continue;
			}
			if (et == editType::onlyDigits)
				if (isDigit(ch)) {
					cout << ch;
					data = data + ch;
				}
			if (et == editType::onlyAlpha) {
				if (isAlpha(ch)) {
					cout << ch;
					data = data + ch;
				}
				if (isSpace(ch)) {
					cout << ch;
					data = data + ch;
				}
			}
			if (et == editType::all) {
				cout << ch;
				data = data + ch;
			}
			if (et == editType::date) {
				if (data.length() == 10) {
					return data;
				}
				if (data.length() == 2 or data.length() == 5) {
					cout << ".";
					data = data += ".";
				}
				if (isDigit(ch)){
					cout << ch;
					data = data + ch;
				}
			}
		}
		return data;
	}
	int getData(enum class editType et, int min, int max) {
		if (et == editType::onlyDigits) {
			getData(et);
			int num = max + 1;
			if (isStringOfDigit(data))
				num = atoi(data.c_str());
			if (not (num >= min and num <= max)) {
				cout << endl << "!!!ОШИБКА!!!" << endl << "Число, которое вы ввели : " << "\"" << num << "\"" << " выходит из диапазона(" << min << "; " << max << ") " << endl;
				cout << "Нажмите любую клавишу" << endl; _getch(); system("cls");
				getData(et, min, max);
			}
			if (isStringOfDigit(data))
				num = atoi(data.c_str());
			return num;
		}
	}
	string getData(enum class editType et, int len) {
		if (et == editType::onlyAlpha or et == editType::all) {
			getData(et);
			if (data.length() > len) {
				cout << endl << "!!!ОШИБКА!!!" << endl << "Слишком длинная строка: " << data.length() << " символов!" << endl << "Введите строку менее " << len - 1<< " символов!" << endl;
				cout << "Нажмите любую клавишу" << endl; _getch(); system("cls");
				getData(et, len);
			}
			return data;
		}
	}
	string getData(enum class editType et, string min, string max) {
		if (et == editType::date) {
			getData(et);
		}
		if (isDateTrue(data)) {
			if (not (reverseDate(data) >= reverseDate(min) and reverseDate(data) <= reverseDate(max))) {
				cout << endl << "!!!ОШИБКА!!!" << endl << "Число, которое вы ввели : " << "\"" << data << "\"" << " выходит из диапазона(" << min << "; " << max << ") " << endl;
				cout << "Нажмите любую клавишу" << endl; _getch(); system("cls");
				getData(et, min, max);
			}
		}
		else {
			cout << endl << "!!!ОШИБКА!!!" << endl << "Вы ввели несуществующую дату" << endl;
			cout << "Нажмите любую клавишу" << endl; _getch(); system("cls");
			getData(et, min, max);
		}
		return data;
	}
};