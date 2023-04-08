// var_6
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

fstream fs; 
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

/// <summmary>
/// Запись даты в файл
/// </summary>
/// <param name="day"></param>
/// <param name="month"></param>
/// <param name="year"></param>
/// <param name="wLine"></param>
void write_date(unsigned short day, unsigned short month, unsigned short year) {
    cout << left;
    if (day > 9) {
        fs << day;
    }
    else {
        fs << "0" << day;
    }
    fs << ".";
    if (month > 9) {
        fs << month;
    }
    else {
        fs << "0" << month;
    }
    fs << ".";
    fs << year;
}

/// <summary>
/// Ввод новой записи
/// </summary>
/// <param name="records"></param>
void input_new_line(struct Record* records) {
    cout << "Введите новую запись" << endl << endl;
    cout << "Фамилия участника:"; cin >> records[3].surname;
    cout << "Код команды (1 символ):"; cin >> records[3].code;
    cout << "Количество балов:"; cin >> records[3].count;
    cout << "Место в итоге:"; cin >> records[3].place;
    cout << "Дата выступления:"; cin >> records[3].date.day >> records[3].date.month >> records[3].date.year; cout << endl;
}

/// <summary>
/// Запись в текстовый файл
/// </summary>
/// <param name="path"></param>
void write_txt(string path, Record *records) {
    fs.open(path, ios::out);

    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else
        for (int i = 0; i < 3; i++) {
            fs << records[i].surname << " " << records[i].code << " " << fixed << showpoint << records[i].count << " " << records[i].place << " ";
            write_date(records[i].date.day, records[i].date.month, records[i].date.year); fs << endl;
        }
    fs.close();
}

/// <summary>
/// Считывание из текстового файла
/// </summary>
/// <param name="path"></param>
/// <param name="records"></param>
void read_txt(string path, Record* records) {
    fs.open(path);

    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else {
        string str;
        while (!fs.eof()) {

            getline(fs, str);
            cout << str << endl;
        }
    }
    fs.close();
}

/// <summary>
/// Запись в бинарный файл
/// </summary>
/// <param name="path"></param>
/// <param name="records"></param>
void write_bin(string path,Record* records) {
    fs.open(path, ios::binary | ios::out);

    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else
        for (int i = 0; i < 3; i++) {
            fs << records[i].surname << " " << records[i].code << " " << fixed << showpoint << records[i].count << " " << records[i].place << " ";
            write_date(records[i].date.day, records[i].date.month, records[i].date.year); fs << endl;
        }
    fs.close();
}

/// <summary>
/// Считывание изз бинарного файла
/// </summary>
/// <param name="path"></param>
/// <param name="records"></param>
void read_bin(string path, Record* records) {
    fs.open(path, ios::binary | ios::in);

    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else {
        string str;
        while (!fs.eof()) {

            getline(fs, str);
            cout << str << endl;
        }
    }
    fs.close();
}

/// <summary>
/// смена знака перед вещественным полем
/// </summary>
/// <param name="path"></param>
/// <param name="records"></param>
void swap_symbol(string path, Record* records) {
    int flag = 1;
    fs.open(path);
    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else {
        if (flag) {
            for (int i = 0; i < 4; i++) {
                fs << records[i].surname << " " << records[i].code << " " << fixed << showpoint << "-" << records[i].count << " " << records[i].place << " ";
                write_date(records[i].date.day, records[i].date.month, records[i].date.year); fs << endl;
            }
            flag = 0;
        }
        else {
            for (int i = 0; i < 4; i++) {
                fs << records[i].surname << " " << records[i].code << " " << fixed << showpoint << records[i].count << " " << records[i].place << " ";
                write_date(records[i].date.day, records[i].date.month, records[i].date.year); fs << endl;
            }
            flag = 1;
        }
        fs.close();
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Record records[10];

    records[0] = { "Баландин", 'С', 123.7000, 2, {6,6,2022} };
    records[1] = { "Шишков", 'Ш', 79.9800, 3, {7,7,2022} };
    records[2] = { "Кравченко", 'Д', 134.8000, 1, {7,6,2022} };

    ios::pos_type pos;

    string txt = "Зайцев.txt";

    write_txt(txt, records);
    read_txt(txt, records);

    string bin = "Зайцев.bin";

    write_bin(bin, records);
    read_bin(bin, records);

    //Запись четвёртой записи в текстовый файл
    fs.open(txt, ios::app);

    if (!fs.is_open())
        cout << "Ошибка открытия файла" << endl;
    else {
        input_new_line(records);
        fs << records[3].surname << " " << records[3].code << " " << fixed << showpoint << records[3].count << " " << records[3].place << " ";
        write_date(records[3].date.day, records[3].date.month, records[3].date.year); fs << endl;
        fs.close();
    }

    swap_symbol(txt, records);
}