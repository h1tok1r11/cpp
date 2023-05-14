#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

char* generateRandomPassword() {
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
	return pass;
}

void writePassword2File(char* pass) {
	ofstream file;
	file.open("key.txt", ios::binary);
	file.write(pass, 65);
	file.close();
}

void encryptWithAES(char* pass) {
	string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in database.bin -out database.bin.enc -pass pass:";
	command += pass;
	system(command.c_str());
}

void encryptWithRSAViaPublicKey() {
	string command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
	system(command.c_str());
}

void encrypt() {
	char* pass = generateRandomPassword();
	encryptWithAES(pass);
	if (remove("database.bin") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
	writePassword2File(pass);
	encryptWithRSAViaPublicKey();
	if (remove("key.txt") != 0) {
		cout << "[ERROR] - deleting file" << endl;
	}
}