#pragma once
#include"Stack.hpp"

class Data {
public:
	Data();
	Data(int, int, std::string, std::string, std::string, std::string, std::string, int, Stack);
	Data(Data const&);
	~Data();

	Stack getStack()const;
	void setStack(Stack);

	int getRecord() const;
	void setRecord(int);

	int getID() const;
	void setID(int);

	std::string getName() const;
	void setName(std::string);

	std::string getEmail() const;
	void setEmail(std::string);

	std::string getUnit() const;
	void setUnit(std::string);

	std::string getProgram() const;
	void setProgram(std::string);

	std::string getLevel() const;
	void setLevel(std::string);

	int getAbsence() const;
	void setAbsence(int);

private:
	int record;
	int ID;
	std::string name;
	std::string email;
	std::string units;
	std::string program;
	std::string level;
	int absences;
	Stack absence_dates;
};


Data::Data() {
	record = 0;
	ID = 0;
	name = "";
	email = "";
	units = "";
	program = "";
	level = "";
	absences = 0;
}
Data::Data(int newRecord, int newIdentity, std::string newName, std::string newEmail, std::string newUnits, std::string newProgram, std::string newLevel, int newAbsence, Stack newStack) {
	record = newRecord;
	ID = newIdentity;
	name = newName;
	email = newEmail;
	units = newUnits;
	program = newProgram;
	level = newLevel;
	absences = newAbsence;
	absence_dates = newStack;
}
Data::Data(Data const& copy) {
	record = copy.getRecord();
	ID = copy.getID();
	name = copy.getName();
	email = copy.getEmail();
	units = copy.getUnit();
	program = copy.getProgram();
	level = copy.getLevel();
	absences = copy.getAbsence();
	absence_dates = getStack();
}

Data::~Data() {};

int Data::getRecord() const {
	return record;
}
void Data::setRecord(int newRecord) {
	record = newRecord;
}

int Data::getID() const {
	return ID;
}
void Data::setID(int newID) {
	ID = newID;
}

std::string Data::getName() const {
	return name;
}
void Data::setName(std::string newName) {
	name = newName;
}

std::string Data::getEmail() const {
	return email;
}
void Data::setEmail(std::string newEmail) {
	email = newEmail;
}

std::string Data::getUnit() const {
	return units;
}
void Data::setUnit(std::string newUnit) {
	units = newUnit;
}

std::string Data::getProgram() const {
	return program;
}
void Data::setProgram(std::string newProgram) {
	program = newProgram;
}

std::string Data::getLevel() const {
	return level;
}
void Data::setLevel(std::string newLevel) {
	level = newLevel;
}

int Data::getAbsence() const {
	return absences;
}
void Data::setAbsence(int newAbsence) {
	absences = newAbsence;
}

Stack Data::getStack() const {
	return absence_dates;
}
void Data::setStack(Stack stack) {
	absence_dates = stack;
}
