#include <iostream>
#include "Person.h"

#pragma once
#include "windows.h"
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>

#include "OneLinkedList.h"
#include "Subject.h"
#include "List.h"
//#include "ListOfSessions.h"
#include "Menu.h"
#include "Student.h"

#include <wincrypt.h>
#include "CryptoTools.h"

using namespace std;

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
    //Subject Sub1("math", markType::bad);
    //Subject Sub2("OIB", markType::excellent);
    //Subject Sub3("Economic", markType::good);
    //Subject Sub[5] = { Sub1, Sub2, Sub3 };
    //List<Subject> list;
    ///*List<int> lst;
    //lst.push_back(1);
    //lst.push_back(2);
    //lst.push_back(3);*/

    //for (int i = 0; i < 3; i++)
    //    list.push_back(Sub[i]);

    ///*List<Subject> list;
    //list.push_back();
    //list.push_back(3);
    //list.push_back(2);
    //list.insert(15, 1);*/

    ///*for (int i = 0; i < list.getSize(); i++)
    //{
    //    cout << list[i].getMark() << " " << list[i].getSubjectName() << endl;
    //}
    //cout << endl << endl;*/

    ///*list.removeAt(2);
    //for (int i = 0; i < list.getSize(); i++)
    //{
    //    cout << list[i] << endl;
    //}*/


    //List<List<Subject>> listOfSessions;
    //listOfSessions.push_back(list);

    /*Menu<string> menu;
    menu.addMenuItem("Zhopa");
    menu.addMenuItem("Ruka");
    menu.run();*/
    Student student;

    /*student.setDefaultData1();
    student.addStudentToFile();
    student.setDefaultData2();
    student.addStudentToFile();
    student.setDefaultData3();
    student.addStudentToFile();*/
    //student.addStudentToFile();
    //student.setStudentData();
    //student.addStudentToFile();
    //student.getShortInfoFromFile();
    //student.setStudentData(1);
    //student.writeToFileStudentData(2);
    //student.deleteFromFileStudentData(2);
    student.bubbleSortMarksInDescendingOrder();

    //HCRYPTPROV hProv;
    //HCRYPTKEY hSessionKey;
    //// Получение контекста криптопровайдера
    //if (!CryptAcquireContext(&hProv, NULL, NULL,
    //    PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    //{
    //    std::cout << "CryptAcquireContext" << std::endl;
    //    return 0;
    //}
    //std::cout << "Cryptographic provider initialized" << std::endl;
    //// Генерация сессионного ключа
    //if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey))
    //{
    //    std::cout << "CryptGenKey" << std::endl;
    //    return 0;
    //}
    //std::cout << "Session key generated" << std::endl;
    //// Данные для шифрования
    //char string[] = "TestTest";
    //char string1[100], string2[100];
    ////memcpy(string2, '\0', 100);
    //strcpy_s(string1, string);
    //DWORD count = strlen(string);
    //// Шифрование данных
    //if (!CryptEncrypt(hSessionKey, 0, true, 0, (BYTE*)string, &count, strlen(string)))
    //{
    //    std::cout << "CryptEncrypt" << std::endl;
    //    return 0;
    //}
    //std::cout << "Encryption completed" << std::endl;
    //// Тестовый вывод на экран
    //std::cout << "Encrypted string: " << string << "::::" << strlen(string) << std::endl;
    ////-----------------------------------------------------------------------------
    //// работа с файлом
    ////--------------------------------------------------------------------------
    //FILE* out = nullptr, * in = nullptr;
    //char c;
    //fopen_s(&out, "AAA.ddd", "w");
    //fwrite(string, strlen(string), 1, out);
    //fclose(out);
    //cin >> c;
    //fopen_s(&in, "AAA.ddd", "r");
    //fread(string1, strlen(string), 1, in);
    //fclose(in);
    //DWORD count1 = strlen(string1);
    //std::cout << "Encrypted string: " << string1 << "::::" << strlen(string1) << std::endl;
    //if (!CryptDecrypt(hSessionKey, 0, true, 0, (BYTE*)string1, &count1))
    //{
    //    std::cout << "CryptDecrypt" << std::endl;
    //    return 0;
    //}
    //std::cout << "Decrypted string: " << string1 << "::::" << strlen(string1) << std::endl;

    //Crypt();
    //Decrypt();
}