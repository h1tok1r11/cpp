#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

void decryptFileViaPrivateKey() {
	string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
	system(command.c_str());
}

char* readPasswordfromFile() {
	char* pass = new char[64];
	ifstream file;
	file.open("key.txt", ios::binary);
	file.read(pass, 65);
	file.close();
	return pass;
}

void decryptWithAES(char* pass) {
	string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in database.bin.enc -out database.bin -pass pass:";
	command += pass;
	system(command.c_str());
}

void decrypt() {
	decryptFileViaPrivateKey();
	if (remove("key.txt.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	char* pass = readPasswordfromFile();
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	decryptWithAES(pass);
	if (remove("database.bin.enc") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}