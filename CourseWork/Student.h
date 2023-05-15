//#include "DateOfBirth.h"
//#include "RecordBook.h"
//#include "Person.h"
#include "InputValidation.h"
#pragma once

enum sex : char { man, woman, attackHelicopter };
enum markType : int { fail, pass, bad, satisfactory, good, excellent };


struct Sessions {
	char nameOfSubject[50];
	enum markType markType;
	bool isEmpty;
};

struct StudentNode  
{
	char lastName[30];
	char name[20];
	char patronymic[30];
	char dateOfBirthString[15];
	int yearOfAdmission;
	char faculty[30];
	char department[30];
	char group[15];	
	char numberOfrecordBook[10];
	enum sex sex;
	Sessions sessions[9][10];
};

class Student// : public Person
{
private:
	string nameOfFile;
	StudentNode studentData;
	InputValidation* editData;
public:
	Student();
	~Student();
	//Student(DateOfBirth dateOfBirth, unsigned short yearOfAdmission, string faculty, string department, string group, string numberOfrecordBook);
	//static bool findStudentByRecordBook(string recordBook, List<Student> students);
	void setLastName();
	void setName();
	void setPatronymic();
	void setDateOfBirth();
	void setYearOfAdmission();
	void setFaculty();
	void setDepartment();
	void setGroup();
	void setNumberOfRecordBook();
	void setSex(string header);
	void setMark(string header, int numberOfSession, int numberOfSubject);
	string returnMarkString(enum markType mark);
	void setSessions(string header, int numberOfStudent);
	void setSubjects(string header, int numberOfSesssion, int numberOfStudent);
	void setDefaultData1();
	void setDefaultData2();
	void setDefaultData3();
	void printData();
	void editStudent(int numberOfSesssion);
	void setStudentData(int numberOfSesssion);
	void setStudentNodeFromFile(int num);
	void addStudentToFile();
	void writeToFileStudentData(int	num);
	void deleteFromFileStudentData(int num);
	int countNumberOfRecords();
	void getShortInfoFromFile();
	void getShortInfoFromFile(int min, int max);
	void clearStudentNode();

	void bubbleSortMarksInDescendingOrder(int numberOfSession);
};