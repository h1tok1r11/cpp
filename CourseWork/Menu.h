#pragma once
#include "windows.h"
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include "InputValidation.h"
#include "List.h"

template <typename T>
class Menu
{
private:
	string upTitle;
	List<T> items; 
	string downTitle;
public:

	Menu(string upTitle) {
		this->upTitle = move(upTitle);
		//upTitle =  _upTitle;
	}

	Menu() : Menu("Header") {
		downTitle = "Bottom header";
	}

	void addMenuItem(string _item) {
		items.push_back(_item);
	}

	void insertMenuItem(string _item, int idx) {
		items.insert(_item, idx);
	}

	void editMenuItem(string _item, int idx) {
		deleteMenuItem(idx);
		insertMenuItem(_item, idx);
	}

	void deleteMenuItem(int idx) {
		items.removeAt(idx);
	}

	void draw() {
		system("cls");
		cout << upTitle << endl;
		//int count = items.getCount();
		//for (int i = 0; i < count; i++) {
		//	cout << i << ". " << items.getItem(i) << endl;
		//}
		items.printItems();
		cout << downTitle;
	}
	int run() {
		draw();
		InputValidation* cl = new InputValidation;
		cl->setLabel("");
		int min = 0, max = items.getSize();
		int selectItem = cl->getData(editType::onlyDigits, min, max);
		delete cl;
		return selectItem;

	}

};
