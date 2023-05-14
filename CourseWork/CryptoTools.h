#pragma once
//#include "Decrypt.h"
//#include "Encrypt.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;
void Crypt();
void Decrypt();
void Crypt()
{
	srand(time(NULL));
	char* pass = new char[64];
	for (int i = 0; i < 64; ++i) {
		switch (rand() % 3) {
		case 0:
			pass[i] = rand() % 10 + '0';
			break;
		case 1:
			pass[i] = rand() % 26 + 'A';
			break;
		case 2:
			pass[i] = rand() % 26 + 'a';
		}
	}
		string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in database.bin -out database.bin.enc -pass pass:";
	command += pass;
	system(command.c_str());
	
		if (remove("database.bin") != 0) {
			cout << "[ERROR] - deleting file" << endl;
		}
	ofstream file;
	file.open("key.txt", ios::binary);
	file.write(pass, 65);
	file.close();
	command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
	system(command.c_str());
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}
void Decrypt()
{
	string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
	system(command.c_str());
	if (remove("key.txt.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	char* pass = new char[64];
	ifstream file;
	file.open("key.txt", ios::binary);
	file.read(pass, 65);
	file.close();
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in database.bin.enc -out database.bin -pass pass:";
	command += pass;
	system(command.c_str());
	if (remove("database.bin.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}