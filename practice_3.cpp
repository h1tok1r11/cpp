#include <iostream>
#include <windows.h>
#include <string.h>
#include <iomanip>

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

struct Node {
    Record data;
    Node* pnext;
    Node* pprev;
};

Node* head = NULL; Node* tail = NULL;
int cnt_of_items = 0;

/// <summary>
/// Добавление элемента в начало
/// </summary>
/// <param name="data"></param>
void insert_at_head(Record data) {
    Node* pnew = new Node;
    pnew->data = data;
    pnew->pnext = head;
    if (cnt_of_items == 0) {
        head = pnew;
        tail = head;
        //head->pnext = head;
    }
    else
        head->pprev = pnew;
        //pnew->pprev = pnew;
    cnt_of_items++;
}

/// <summary>
/// Добавление элемента в конец
/// </summary>
/// <param name="data"></param>
void insert_at_tail(Record data) {
    Node* pnew = new Node;
    pnew->data = data;
    if (cnt_of_items == 0) {
        head = pnew;
        head->pnext = tail;
    }
    else {
        tail->pnext = pnew;
        pnew->pprev = tail;
    }
    tail = pnew;
    cnt_of_items++;
}

/// <summary>
/// Добавление элемента по индексу
/// </summary>
/// <param name="idx"></param>
/// <param name="data"></param>
void insert_by_idx(int idx, Record data) {
    if (not(idx <= cnt_of_items and idx >= 0 and cnt_of_items >= 0))
        return;
    if (idx == 0)
        insert_at_head(data);
    else {
        Node* pcur = head;
        for (int i = 0; i < idx - 1; i++)
            pcur = pcur->pnext;
        Node* paft = pcur->pnext;
        Node* pnew = new Node;
        pnew->data = data;
        pnew->pnext = paft; paft->pprev = pnew;
        pnew->pprev = pcur; pcur->pnext = pnew;
        cnt_of_items++;
    }
}

/// <summary>
/// Нахождение одинаковых элементов и вставка перед каждым элементом
/// </summary>
/// <param name="idx"></param>
void edit_by_value(int value, Record data) {
    Node* pcur = head;
    int fixed_cnt = cnt_of_items;
    for (int i = 0; i < fixed_cnt; i++) {
        if (pcur->data.place == value) {
            if (i != 0) {
                Node* paft = pcur;
                Node* pbfr = pcur->pprev;
                Node* pnew = new Node;
                pnew->data = data;
                pnew->pnext = paft; paft->pprev = pnew;
                pnew->pprev = pbfr; pbfr->pnext = pnew;
                cnt_of_items++;
                pcur->pnext = paft->pnext;
            }
            else {
                Node* paft = pcur;
                Node* pnew = new Node;
                pnew->data = data;
                pnew->pnext = paft; paft->pprev = pnew;
                pnew->pprev = nullptr;
                cnt_of_items++;
                pcur->pnext = paft->pnext;
                head = pnew;
            }
            if (pcur == nullptr)
                return;
        }
        pcur = pcur->pnext;
    }
}

void myCentr(string s, int wLine) {
    unsigned short w = s.length();
    int delta = (wLine - w) / 2;
    cout << left;
    cout.width(delta); cout << " ";
    cout << s;
    cout.width(delta + 1); cout << " ";
}


void Printdate(unsigned short day, unsigned short month, unsigned short year, int wLine)
{
    int w = 10;
    int delta = (wLine - w) / 2 - 1;
    cout << left;
    cout.width(delta); cout << " ";
    if (day > 9) {
        cout << day;
    }
    else {
        cout << "0" << day;
    }
    cout << ".";
    if (month > 9) {
        cout << month;
    }
    else {
        cout << "0" << month;
    }
    cout << ".";
    cout << year;
    cout.width(delta);
    cout << " ";
}

void border(int width) {
    cout.width(width); cout.fill('-'); cout << "-" << endl;
}

/// <summary>
/// Печать списка
/// </summary>
void print_table() {
    Node* pcur = head;
    int width = 80;
    int datespace = 9;
    cout << endl; border(width + 1);
    cout.width(width); cout.fill(' '); cout << left << "|Ведомость спортивных состязаний"; cout << "|" << endl;
    border(width + 1);
    cout.fill(' ');
    cout << left << "|Фамилия участника";
    cout << left << "|Код команды";
    cout << left << "|Количество балов";
    cout << left << "|Место в итоге";
    cout << "|";  myCentr("Дата выступления", 12); cout << "|" << endl;
    cout.fill(' ');
    border(width + 1);
    cout.fill(' ');
    for (int i = 0; i < cnt_of_items; i++) {
        cout << left << "|"; cout.width(17); cout << left << pcur->data.surname;
        cout << left << "|"; cout.width(11); cout << left << pcur->data.code;
        cout << left << "|"; cout.width(16); cout << left << pcur->data.count;
        cout << left << "|"; cout.width(13); cout << fixed << showpoint << setprecision(4) << left << pcur->data.place;
        cout << left << "|";
        Printdate(pcur->data.date.day, pcur->data.date.month, pcur->data.date.year, 20);
        cout << "|" << endl;
        pcur = pcur->pnext;
    }
    border(width + 1);
    cout.fill(' '); cout.width(width - 1); cout << left << "| Примечание: Д - \"Динамо\", С - \"Спартак\", Ш - \"Шахтер\""; cout << " | " << endl;
    border(width + 1);
}

/// <summary>
/// Ввод данных
/// </summary>
/// <param name="records"></param>
void Input(struct Record* records) {
    for (int i = 0; i < 3; i++) {
        cout << "Input the " << i + 1 << " line" << endl << endl;
        cout << i + 1 << " participant's surname:"; cin >> records[i].surname;
        cout << i + 1 << " code of team:"; cin >> records[i].code;
        cout << i + 1 << " count of points:"; cin >> records[i].count;
        cout << i + 1 << " place in the end:"; cin >> records[i].place;
        cout << i + 1 << " performance date:"; cin >> records[i].date.day >> records[i].date.month >> records[i].date.year; cout << endl;
    }
}

/// <summary>
/// Освобождение памяти
/// </summary>
void delete_list() {
    Node* pcur = head;
    Node* tmp;
    for (int i = 0; i < cnt_of_items; i++) {
        tmp = pcur->pprev;
        delete[] pcur;
        pcur = tmp;
    }
}

void print() {
    cout << "Значение head = " << head << endl;
    Node* pcur = head; int i = 1; int width = 80;
    for (pcur = head; pcur != nullptr; pcur = pcur->pnext)
    {
        border(width + 1);
        //cout.fill(' '); cout.width(width);
        cout << left << i << left << "-ая фамилия участника: " << pcur->data.surname; cout << "|" << endl
            << i << "-ый код команды: " << pcur->data.code << endl
            << i << "-ое количество балов: " << pcur->data.count << endl
            << i << "-ое место в итоге: " << pcur->data.place << endl
            << i << "-ая дата выступления:"; Printdate(pcur->data.date.day, pcur->data.date.month, pcur->data.date.year, 0); cout << endl
            << "Адрес " << i << " элемента списка = " << pcur << endl
            << "Next = " << pcur->pnext << endl << "Prev = " << pcur->pprev << endl;
        i++;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct Record records[5];

     records[0] = { "Баландин", 'С', 123.7000, 2, {6,6,2022} };
     records[1] = { "Шишков", 'Ш', 79.9800, 3, {7,7,2022}};
     records[2] = { "Кравченко", 'Д', 134.8000, 1, {7,6,2022}};
     records[3] = { "Зайцев", 'Р', 666.6000, 0, {28,02,1980} };

     for (int i = 0; i < 2; i++)
         for (int j = 0; j < 3; j++)
             insert_at_tail(records[j]);
     //insert_by_idx(3, records[1]);
     print_table();
     edit_by_value(1, records[3]);
     print_table();
     print();
     delete_list();
    /*Input(records);


    Table(records);*/
}