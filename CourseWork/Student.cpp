#include "Student.h"
#include "Menu.h"
#include <fstream>
#include <string>

Student::Student()
{
	nameOfFile = "database.bin";
	editData = new InputValidation();
}

Student::~Student()
{
	delete editData;
}

string tmpstr;
//Student::Student(DateOfBirth dateOfBirth, unsigned short yearOfAdmission, string faculty, string department, string group, string numberOfrecordBook) :
//	yearOfAdmission(yearOfAdmission), faculty(faculty), department(department), group(group), numberOfrecordBook(numberOfrecordBook){}

//bool Student::findStudentByRecordBook(string recordBook, List<Student> students)
//{
//	/*for (auto& student : students) {
//		if (!strcmp(student.GetRecordBook(), recordBook)) return true;
//	return false;*/
//	for (auto p = std::begin(students);)
//}

void Student::setLastName() {
	editData->clear(studentData.lastName); editData->setLabel("Введите фамилию: ");
	tmpstr = editData->getData(editType::onlyAlpha, 30); //почему нельзя убрать c_str
	strncpy_s(studentData.lastName, tmpstr.c_str(), tmpstr.size());
}

void Student::setName() {
	editData->clear(studentData.name); editData->setLabel("Введите имя: ");
	tmpstr = editData->getData(editType::onlyAlpha, 20);
	strncpy_s(studentData.name, tmpstr.c_str(), tmpstr.size());
}

void Student::setPatronymic() {
	editData->clear(studentData.patronymic); editData->setLabel("Введите отчество: ");
	tmpstr = editData->getData(editType::onlyAlpha, 30);
	strncpy_s(studentData.patronymic, tmpstr.c_str(), tmpstr.size());
}

void Student::setDateOfBirth() {
	editData->clear(studentData.dateOfBirthString); editData->setLabel("Введите дату рождения: ");
	tmpstr = editData->getData(editType::date, "01.01.1960", "01.01.2023");
	strncpy_s(studentData.dateOfBirthString, tmpstr.c_str(), tmpstr.size());
}

void Student::setYearOfAdmission(){
	editData->clear(to_string(studentData.yearOfAdmission)); editData->setLabel("Введите год поступления: ");
	studentData.yearOfAdmission = editData->getData(editType::onlyDigits, 2000, 2023);
}

void Student::setFaculty() {
	editData->clear(studentData.faculty); editData->setLabel("Введите факультет (институт): ");
	tmpstr = editData->getData(editType::onlyAlpha, 30);
	strncpy_s(studentData.faculty, tmpstr.c_str(), tmpstr.size());
}

void Student::setDepartment() {
	editData->clear(studentData.department); editData->setLabel("Введите кафедру: ");
	tmpstr = editData->getData(editType::onlyAlpha, 30);
	strncpy_s(studentData.department, tmpstr.c_str(), tmpstr.size());
}

void Student::setGroup() {
	editData->clear(studentData.group); editData->setLabel("Введите группу: ");
	tmpstr = editData->getData(editType::all, 11);
	strncpy_s(studentData.group, tmpstr.c_str(), tmpstr.size());
}

void Student::setNumberOfRecordBook() {
	editData->clear(studentData.numberOfrecordBook); editData->setLabel("Введите номер зачётной книжки: ");
	tmpstr = editData->getData(editType::all, 8);
	strncpy_s(studentData.numberOfrecordBook, tmpstr.c_str(), tmpstr.size());
}

void Student::setSex(string header) {
	int sexItem = -1;
	Menu<string>* MenuOfEditingSex = new Menu<string>(header);
	MenuOfEditingSex->addMenuItem("Выход"); // 0
	MenuOfEditingSex->addMenuItem("Мужской"); // 1 
	MenuOfEditingSex->addMenuItem("Женский"); // 2
	MenuOfEditingSex->addMenuItem("Боевовертолётный"); // 3
	while (sexItem != 0) {
		sexItem = MenuOfEditingSex->run();
		if (sexItem == 1) { studentData.sex = sex::man; sexItem = 0; }
		if (sexItem == 2) { studentData.sex = sex::woman; sexItem = 0; }
		if (sexItem == 3) { studentData.sex = sex::attackHelicopter; sexItem = 0; }
	}
	delete MenuOfEditingSex;
}

void Student::setMark(string header, int numderOfSession, int numberOfSubject) {
	int markItem = -1;
	Menu<string>* MenuOfEditingMark = new Menu<string>(header);
	MenuOfEditingMark->addMenuItem("Выход"); // 0
	MenuOfEditingMark->addMenuItem("Незачёт"); // 1 
	MenuOfEditingMark->addMenuItem("Зачёт"); // 2
	MenuOfEditingMark->addMenuItem("Неудовлетворительно"); // 3
	MenuOfEditingMark->addMenuItem("Удовлетворительно"); // 4
	MenuOfEditingMark->addMenuItem("Хорошо"); // 5
	MenuOfEditingMark->addMenuItem("Отлично"); // 6
	while (markItem != 0) {
		markItem = MenuOfEditingMark->run();
		switch (markItem)
		{
		case 1:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::fail; markItem = 0;
			break;
		case 2:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::pass; markItem = 0;
			break;
		case 3:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::bad; markItem = 0;
			break;
		case 4:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::satisfactory; markItem = 0;
			break;
		case 5:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::good; markItem = 0;
			break;
		case 6:
			studentData.sessions[numderOfSession][numberOfSubject].markType = markType::excellent; markItem = 0;
			break;
		}
	}
	delete MenuOfEditingMark;
}

string Student::returnMarkString(enum markType mark) {
	if (mark == markType::fail) return "Незачёт";
	if (mark == markType::pass) return "Зачёт";
	if (mark == markType::bad) return "Неудовлетворительно";
	if (mark == markType::satisfactory) return "Удовлетворительно";
	if (mark == markType::good) return "Хорошо";
	if (mark == markType::excellent) return "Отлично";
}

void Student::setSessions(string header, int numberOfStudent) {
	int sessionItem = -1;
	Menu<string>* MenuOfEditingSessions = new Menu<string>(header);
	MenuOfEditingSessions->addMenuItem("Выход"); //0
	for (int i = 1; i < 10; i++) {
		MenuOfEditingSessions->addMenuItem("Посмотреть результаты " + to_string(i) + " сессии");
	}
	while (sessionItem != 0) {
		writeToFileStudentData(numberOfStudent);
		sessionItem = MenuOfEditingSessions->run();
		switch (sessionItem)
		{
		case 1:
			setSubjects("Меню редактирования предметов первой сессии", 0, numberOfStudent); break;
		case 2:
			setSubjects("Меню редактирования предметов второй сессии", 1, numberOfStudent); break;
		case 3:
			setSubjects("Меню редактирования предметов третьей сессии", 2, numberOfStudent); break;
		case 4:
			setSubjects("Меню редактирования предметов четвёртой сессии", 3, numberOfStudent); break;
		case 5:
			setSubjects("Меню редактирования предметов пятой сессии", 4, numberOfStudent); break;
		case 6:
			setSubjects("Меню редактирования предметов шестой сессии", 5, numberOfStudent); break;
		case 7:
			setSubjects("Меню редактирования предметов седьмой сессии", 6, numberOfStudent); break;
		case 8:
			setSubjects("Меню редактирования предметов восьмой сессии", 7, numberOfStudent); break;
		case 9:
			setSubjects("Меню редактирования предметов девятой сессии", 8, numberOfStudent); break;
		default:
			break;
		}
	}
	
}

void Student::setSubjects(string header, int numberOfSession, int numberOfStudent) {
	int subjectItem = -1;
	string space = " ";
	Menu<string>* MenuOfEditingSubjects = new Menu<string>(header);
	MenuOfEditingSubjects->addMenuItem("Выход"); //0
	MenuOfEditingSubjects->addMenuItem("Добавить предмет"); //1
	for (int i = 0; i < 10; i++) {
		if (studentData.sessions[numberOfSession][i].isEmpty)
			MenuOfEditingSubjects->addMenuItem("Пусто");// 2-11
		else
			MenuOfEditingSubjects->addMenuItem(studentData.sessions[numberOfSession][i].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][i].markType));
	}
	int subjectInfoItem = -1;
	Menu<string>* MenuOfEditingSubjectInfo = new Menu<string>(header);
	MenuOfEditingSubjectInfo->addMenuItem("Выход"); //0
	MenuOfEditingSubjectInfo->addMenuItem("Удалить предмет"); //1
	MenuOfEditingSubjectInfo->addMenuItem("Изменить информацию о предмете"); //2
	//MenuOfEditingSubjectInfo->addMenuItem("Изменить оценку"); //3
	//MenuOfEditingSubjects->addMenuItem("Математический анализ"); //2
	//MenuOfEditingSubjects->addMenuItem("Линейная алгебра"); //3
	//MenuOfEditingSubjects->addMenuItem("Языки программирования"); //4
	while (subjectItem != 0) {
		writeToFileStudentData(numberOfStudent);
		subjectItem = MenuOfEditingSubjects->run();
		switch (subjectItem)
		{
		case 1:
			for (int j = 0; j < 10; j++) {
				if (not(studentData.sessions[numberOfSession][j].isEmpty)) continue;
				else {
					editData->clear(studentData.sessions[numberOfSession][j].nameOfSubject);
					editData->setLabel("Введите название предмета");
					tmpstr = editData->getData(editType::onlyAlpha, 30);
					strncpy_s(studentData.sessions[numberOfSession][j].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						
					string nameOfSubjectString(studentData.sessions[numberOfSession][j].nameOfSubject);
					//string mark = setMark("Введите оценку по предмету " + nameOfSubjectString, i, j);
					setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, j);
					MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][j].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][j].markType), j + 2);
					studentData.sessions[numberOfSession][j].isEmpty = false;
				}
				break;
			break;
			}
		break;
		case 2:
			if (studentData.sessions[numberOfSession][0].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][0].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][0].isEmpty = true;
						studentData.sessions[numberOfSession][0].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][0].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 2);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][0].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][0].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 0);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][0].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][0].markType), 2);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 3:
			if (studentData.sessions[numberOfSession][1].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][1].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][1].isEmpty = true;
						studentData.sessions[numberOfSession][1].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][1].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 3);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][1].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][1].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 1);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][1].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][1].markType), 3);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 4:
			if (studentData.sessions[numberOfSession][2].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][2].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][2].isEmpty = true;
						studentData.sessions[numberOfSession][2].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][2].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 4);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][2].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][2].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 2);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][2].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][2].markType), 4);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 5:
			if (studentData.sessions[numberOfSession][3].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][3].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][3].isEmpty = true;
						studentData.sessions[numberOfSession][3].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][3].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 5);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][3].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][3].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 3);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][3].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][3].markType), 5);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 6:
			if (studentData.sessions[numberOfSession][4].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][4].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][4].isEmpty = true;
						studentData.sessions[numberOfSession][4].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][0].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 6);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][4].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][4].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 4);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][4].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][4].markType), 6);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 7:
			if (studentData.sessions[numberOfSession][5].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][5].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][5].isEmpty = true;
						studentData.sessions[numberOfSession][5].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][5].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 7);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][5].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][5].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 5);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][5].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][5].markType), 7);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 8:
			if (studentData.sessions[numberOfSession][6].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][0].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][6].isEmpty = true;
						studentData.sessions[numberOfSession][6].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][6].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 8);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][6].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][6].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 6);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][6].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][6].markType), 8);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 9:
			if (studentData.sessions[numberOfSession][7].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][7].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][7].isEmpty = true;
						studentData.sessions[numberOfSession][7].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][7].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 9);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][7].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][7].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 7);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][7].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][7].markType), 9);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 10:
			if (studentData.sessions[numberOfSession][8].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][8].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][8].isEmpty = true;
						studentData.sessions[numberOfSession][8].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][8].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 10);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][8].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][8].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 8);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][8].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][8].markType), 10);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		case 11:
			if (studentData.sessions[numberOfSession][9].isEmpty) break;
			else {
				subjectInfoItem = -1;
				while (subjectInfoItem != 0) {
					subjectInfoItem = MenuOfEditingSubjectInfo->run();
					string nameOfSubjectString(studentData.sessions[numberOfSession][9].nameOfSubject);
					switch (subjectInfoItem)
					{
					case 1:
						studentData.sessions[numberOfSession][9].isEmpty = true;
						studentData.sessions[numberOfSession][9].markType = markType::bad;
						strcpy_s(studentData.sessions[numberOfSession][9].nameOfSubject, "");
						MenuOfEditingSubjects->editMenuItem("Пусто", 11);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					case 2:
						editData->clear(studentData.sessions[numberOfSession][9].nameOfSubject);
						editData->setLabel("Введите название предмета");
						tmpstr = editData->getData(editType::onlyAlpha, 30);
						strncpy_s(studentData.sessions[numberOfSession][9].nameOfSubject, tmpstr.c_str(), tmpstr.size());
						setMark("Введите оценку по предмету " + nameOfSubjectString, numberOfSession, 9);
						MenuOfEditingSubjects->editMenuItem(studentData.sessions[numberOfSession][9].nameOfSubject + space + returnMarkString(studentData.sessions[numberOfSession][9].markType), 11);
						subjectInfoItem = 0;
						writeToFileStudentData(numberOfStudent);
						break;
					default:
						break;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	delete MenuOfEditingSubjectInfo;
	delete MenuOfEditingSubjects;
}

void Student::setDefaultData1()
{
	strcpy_s(studentData.lastName, "Бритва");
	strcpy_s(studentData.name, "Борис");
	strcpy_s(studentData.patronymic, "Анатолич");
	strcpy_s(studentData.dateOfBirthString, "28.02.1980");
	studentData.yearOfAdmission = 2008;
	strcpy_s(studentData.faculty, "ИКБ");
	strcpy_s(studentData.department, "Информационная безопасность");
	strcpy_s(studentData.group, "БББО-05-22");
	strcpy_s(studentData.numberOfrecordBook, "1055А67");
	studentData.sex = sex::attackHelicopter;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 10; j++) {
			studentData.sessions[i][j].isEmpty = true;
			strcpy_s(studentData.sessions[i][j].nameOfSubject, "");
			studentData.sessions[i][j].markType = markType::bad;
		}
}

void Student::setDefaultData2()
{
	strcpy_s(studentData.lastName, "Скальпель");
	strcpy_s(studentData.name, "Антон");
	strcpy_s(studentData.patronymic, "Генадич");
	strcpy_s(studentData.dateOfBirthString, "27.03.1984");
	studentData.yearOfAdmission = 2018;
	strcpy_s(studentData.faculty, "ИКБ");
	strcpy_s(studentData.department, "Информационная безопасность");
	strcpy_s(studentData.group, "БББО-05-22");
	strcpy_s(studentData.numberOfrecordBook, "1034А77");
	studentData.sex = sex::man;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 10; j++) {
			studentData.sessions[i][j].isEmpty = true;
			strcpy_s(studentData.sessions[i][j].nameOfSubject, "");
			studentData.sessions[i][j].markType = markType::bad;
		}
}
void Student::setDefaultData3()
{
	strcpy_s(studentData.lastName, "Резьба");
	strcpy_s(studentData.name, "Жанна");
	strcpy_s(studentData.patronymic, "Санна");
	strcpy_s(studentData.dateOfBirthString, "23.05.1999");
	studentData.yearOfAdmission = 2028;
	strcpy_s(studentData.faculty, "ИКБ");
	strcpy_s(studentData.department, "Информационная безопасность");
	strcpy_s(studentData.group, "БББО-05-22");
	strcpy_s(studentData.numberOfrecordBook, "1983А56");
	studentData.sex = sex::woman;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 10; j++) {
			studentData.sessions[i][j].isEmpty = true;
			strcpy_s(studentData.sessions[i][j].nameOfSubject, "");
			studentData.sessions[i][j].markType = markType::bad;
		}
}

void Student::printData() {
	cout << endl << "_________Информация о студенте:_________" << endl;
	cout << "Фамилия: " << studentData.lastName << endl << "Имя: " << studentData.name << endl <<
		"Отчество: " << studentData.patronymic << endl << "Дата рождения: " << studentData.dateOfBirthString << endl << "Год поступления: " << studentData.yearOfAdmission << endl <<
		"Факультет (институт): " << studentData.faculty << endl << "Кафедра: " << studentData.department << endl <<
		"Группа: " << studentData.group << endl << "Номер зачётной книжки: " << studentData.numberOfrecordBook << endl;
	cout << "Пол: ";
	if (studentData.sex == sex::man) { cout << "Человек " << endl; }
	if (studentData.sex == sex::woman) { cout << "Женщина " << endl; }
	if (studentData.sex == sex::attackHelicopter) { cout << "Боевой вертолёт " << endl; }
	cout << "________________________________________" << endl << endl;
}

void Student::editStudent(int numberOfSesssion) {
	//Student::setDefaultData1();
	Menu<string>* menuOfStudents = new Menu<string>("___Меню редактирования студента___");

	menuOfStudents->addMenuItem("Выход"); // 0
	menuOfStudents->addMenuItem("Изменить фамилию"); // 1 
	menuOfStudents->addMenuItem("Изменить имя"); // 2
	menuOfStudents->addMenuItem("Изменить отчество"); // 3
	menuOfStudents->addMenuItem("Изменить дату рождения"); // 4
	menuOfStudents->addMenuItem("Изменить год постулпения"); // 5
	menuOfStudents->addMenuItem("Изменить факультет (институт)"); // 6
	menuOfStudents->addMenuItem("Изменить кафедру"); //7
	menuOfStudents->addMenuItem("Изменить группу"); // 8
	menuOfStudents->addMenuItem("Изменить номер зачётной книжки"); // 9
	menuOfStudents->addMenuItem("Изменить пол"); // 10
	menuOfStudents->addMenuItem("Просмотреть/изменить успеваемость"); // 11
	int selectedItem = -1;
	while (selectedItem != 0) {
		printData();
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		selectedItem = menuOfStudents->run();
		switch (selectedItem)
		{
		case 1:
			setLastName();
			break;
		case 2:
			setName();
			break;
		case 3:
			setPatronymic();
			break;
		case 4:
			setDateOfBirth();
			break;
		case 5:
			setYearOfAdmission();
			break;
		case 6:
			setFaculty();
			break;
		case 7:
			setDepartment();
			break;
		case 8:
			setGroup();
			break;
		case 9:
			setNumberOfRecordBook();
			break;
		case 10:
			setSex("Меню редактирования пола студента");
			break;
		case 11:
			setSessions("Меню редактирования результатов сессии", numberOfSesssion);
			break;
		deafault:
			break;
		}
	}
	delete menuOfStudents;

}

void Student::setStudentData(int numberOfSesssion) {
	clearStudentNode();
	setLastName();
	setName();
	setPatronymic();
	setDateOfBirth();
	setYearOfAdmission();
	setFaculty();
	setDepartment();
	setGroup();
	setNumberOfRecordBook();
	setSex("Меню бинаризации");
	setSessions("Меню просмотра сессий", numberOfSesssion);
}

void Student::setStudentNodeFromFile(int num) {
	FILE* binaryFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	fseek(binaryFile, num * sizeof(studentData), SEEK_SET);
	fread_s(&studentData, sizeof(studentData), sizeof(studentData), 1, binaryFile);
	fclose(binaryFile);
}

void Student::addStudentToFile() {
	FILE* binaryFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "a+");
	fwrite(&studentData, sizeof(studentData), 1, binaryFile);
	fclose(binaryFile);
	/*ofstream fout(nameOfFile, ios::binary);
	fout.write(lastName, sizeof(lastName));
	fout.write(name, sizeof(name));
	fout.write(patronymic, sizeof(patronymic));
	fout.write(dateOfBirth, sizeof(dateOfBirth));
	fout.write((char*)yearOfAdmission, sizeof(yearOfAdmission));
	fout.write(faculty, sizeof(faculty));
	fout.write(department, sizeof(department));
	fout.write(group, sizeof(group));
	fout.write(numberOfrecordBook, sizeof(numberOfrecordBook));
	fout.write((char*)sex, sizeof(sex));
	fout.write(lastName, sizeof(lastName));
	fout.write((char*)sessions, sizeof(sessions));
	fout.close();*/
}

void Student::writeToFileStudentData(int num) {
	int size = countNumberOfRecords();
	FILE* binaryFile;
	FILE* tmpFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	fopen_s(&tmpFile, "tmp.txt", "w+");
	StudentNode tmpStudentData;
	for (int i = 0; i < size; i++) {
		fread_s(&tmpStudentData, sizeof(tmpStudentData), sizeof(tmpStudentData), 1, binaryFile);
		if (i + 1 == num)
			fwrite(&studentData, sizeof(studentData), 1, tmpFile);
		else
			fwrite(&tmpStudentData, sizeof(tmpStudentData), 1, tmpFile);
	}
	fclose(binaryFile);
	fclose(tmpFile);
	remove(nameOfFile.c_str());
	rename("tmp.txt", nameOfFile.c_str());

}

void Student::deleteFromFileStudentData(int num){
	int size = countNumberOfRecords();
	FILE* binaryFile;
	FILE* tmpFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	fopen_s(&tmpFile, "tmp.txt", "w+");
	StudentNode tmpStudentData;
	for (int i = 0; i < size; i++) {
		fread_s(&tmpStudentData, sizeof(tmpStudentData), sizeof(tmpStudentData), 1, binaryFile);
		if (i != num)
			fwrite(&tmpStudentData, sizeof(tmpStudentData), 1, tmpFile);
	}
	fclose(binaryFile);
	fclose(tmpFile);
	remove(nameOfFile.c_str());
	rename("tmp.txt", nameOfFile.c_str());
}

int Student::countNumberOfRecords() {
	/*ifstream fin(nameOfFile, ios::binary);
	fin.seekg(0, ios::end);
	int size = fin.tellg();
	fin.close();
	return size / sizeof(size);*/
	FILE* binaryFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	fseek(binaryFile, 0l, SEEK_END);
	int size = ftell(binaryFile);
	fclose(binaryFile);
	return size / sizeof(studentData);
}

void Student::getShortInfoFromFile() {	
	system("cls");
	cout << "Список данных о студентах: " << endl;
	int size = countNumberOfRecords();
	FILE* binaryFile;
	fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	for (int i = 0; i < size; i++) {
		fread_s(&studentData, sizeof(studentData), sizeof(studentData), 1, binaryFile);
		//cout << i + 1 << ')'; printData();
		cout << i + 1 << ") " << studentData.lastName << " " << studentData.name << " " << studentData.patronymic << " " << studentData.dateOfBirthString << endl;
	}
	fclose(binaryFile);
	cout << "Нажмите любую клавишу" << endl;
	_getch();
	editData->clear();
	editData->setLabel("Введите номер из списка, чтобы получить подробную информацию о студенте. ");
	int num = editData->getData(editType::onlyDigits, 0, size);
	setStudentNodeFromFile(num - 1);
	editStudent(num);
	writeToFileStudentData(num);
}

void Student::getShortInfoFromFile(int min, int max) {
	//editData->setLabel("Укажите интервал года рождения студентов для дальнейшей сортировки этих студентов. ");
	//int size = countNumberOfRecords();
	//int min = editData->getData(editType::onlyDigits, 2000, 2023);
	//int max = editData->getData(editType::onlyDigits, 2000, 2023);
	//system("cls");
	//cout << "Список данных о студентах: " << endl;
	//FILE* binaryFile;
	//fopen_s(&binaryFile, nameOfFile.c_str(), "r");
	//for (int i = 0; i < size; i++) {
	//	fread_s(&studentData, sizeof(studentData), sizeof(studentData), 1, binaryFile);
	//	//cout << i + 1 << ')'; printData();
	//	cout << i << ") " << studentData.lastName << " " << studentData.name << " " << studentData.patronymic << " " << studentData.dateOfBirthString << endl;
	//}
	//fclose(binaryFile);
	//cout << "Нажмите любую клавишу" << endl;
	//_getch();
	//editData->clear();
	//editData->setLabel("Введите номер из списка чтобы получить подробную информацию о студенте. ");
	//int num = editData->getData(editType::onlyDigits, 0, size);
	//setStudentNodeFromFile(num);
	//editStudent();
	//writeToFileStudentData(num);
}

void Student::clearStudentNode() {
	strcpy_s(studentData.lastName, "");
	strcpy_s(studentData.name, "");
	strcpy_s(studentData.patronymic, "");
	strcpy_s(studentData.dateOfBirthString, "");
	studentData.yearOfAdmission = 0;
	strcpy_s(studentData.faculty, "");
	strcpy_s(studentData.department, "");
	strcpy_s(studentData.group, "");
	strcpy_s(studentData.numberOfrecordBook, "");
}

void Student::bubbleSortMarksInDescendingOrder()
{
	List<StudentNode> ListOfStudents;
	int countOfItems = countNumberOfRecords();	
	for (int i = 0; i < countOfItems; i++)
	{
		setStudentNodeFromFile(i);
		ListOfStudents.push_back(studentData);
	}

	for (int i = 0; i < countOfItems; i++) {
		for (int j = 0; j < countOfItems - 1; j++) {
			if (ListOfStudents[j].yearOfAdmission < ListOfStudents[j + 1].yearOfAdmission) {
				StudentNode tmp = ListOfStudents[j];
				ListOfStudents[j] = ListOfStudents[j + 1];
				ListOfStudents[j + 1] = tmp;
			}
		}
	}
	for (int i = 0; i < countOfItems; i++)
	{
		studentData = ListOfStudents[i];
		deleteFromFileStudentData(0);
		addStudentToFile();
	}
}
