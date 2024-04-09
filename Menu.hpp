#pragma once
#include"List.hpp"

class Menu {
public:
	void run();
private:
	List<Data> info;

	int menu();
	void import();
	void load();
	void store();
	void mark();
	void edit();
	void generate();

	void invalid();
};

//Function that runs certain functions depending on what the user wants to do
void Menu::run() {
	int choice;
	info;

	do {
		system("cls");
		choice = menu();
		if (choice == 1) {import();}
		else if (choice == 2) {load();}
		else if (choice == 3) {store();}
		else if (choice == 4) {mark();}
		else if (choice == 5) {edit();}
		else if (choice == 6) {generate();}
		else if (choice == 7) {
			system("cls");
			cout << "Exiting Application...Goodbye" << endl;
		}
		else {invalid();}

	} while (choice != 7);
}

//Menu that shows the options and a prompt on which to choose
int Menu::menu() {
	int num;
	cout << "Attendance Tracker\n\n1. Import course list\n2. Load master list\n3. Store master list\n4. Mark absences\n5. Edit absences\n6. Generate report\n7. Exit\n\nPlease choose one of the options above:" << " ";
	cin >> num;
	return num;
}

//Imports the info in the classList csv file and stores it inside a linked list, parses from record to level
void Menu::import() {
	system("cls");
	cout << "Import Menu:\n\nImporting classList.csv..." << endl;
	fstream infile;
	Data student;
	char line[100];
	char line2[100];

	infile.open("classList.csv");
	if (infile.is_open()) {
		std::string first;
		std::getline(infile, first);
		while (!infile.eof()) {
			//Parse Records
			infile.getline(line, 100, ',');
			student.setRecord(atoi(line));

			//Parse ID
			infile.getline(line, 100, ',');
			student.setID(atoi(line));

			//Parse Name
			infile.getline(line, 100, ',');
			infile.getline(line2, 100, ',');
			strcat(line, ",");
			strcat(line, line2);
			student.setName(line);

			//Parse Email
			infile.getline(line, 100, ',');
			student.setEmail(line);

			//Parse Unit
			infile.getline(line, 100, ',');
			student.setUnit(line);

			//Parse Major
			infile.getline(line, 100, ',');
			student.setProgram(line);

			//Parse Grade
			infile.getline(line, 100, '\n');
			student.setLevel(line);

			info.insertAtFront(student);
		}
		cout << "Import Complete!\n" << endl;
		cout << "Press ENTER to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	else {
		cout << "Error Loading File" << endl;
		cout << "\nPress ENTER to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	infile.close();
}

//loads the data that is written inside the masterlist csv file, destroys the previous list, and then refills the linked list with updated info.
void Menu::load() {
	system("cls");
	cout << "Load Menu:\n\nLoading MasterList.csv..." << endl;
	fstream infile;
	Data student;
	char line[100];

	infile.open("MasterList.csv");
	if (infile.is_open()) {
		info.destroyList(info.getHead());
		char* last = nullptr; // Declare lastName outside of the switch
		while (infile.getline(line, 100)) { // Read line by line
			char* token = strtok(line, ","); // Get the first token
			int i = 0;
			Stack stack; // Stack to store dates
			std::string full; // Declare fullName outside the switch

			while (token != nullptr) {
				switch (i) {
				case 0:
					student.setRecord(atoi(token));
					break;
				case 1:
					student.setID(atoi(token));
					break;
				case 2:
					// Parse and set name
					last = token;
					token = strtok(nullptr, ",");
					full = last; 
					full += ",";
					full += token; 
					student.setName(full);
					break;
				case 3:
					//Parse and set email
					student.setEmail(token);
					break;
				case 4:
					//Parse and set unit
					student.setUnit(token);
					break;
				case 5:
					//Parse and set program
					student.setProgram(token);
					break;
				case 6:
					// Parse and set level
					student.setLevel(token);
					break;
				case 7:
					// Parse and set absence
					student.setAbsence(atoi(token));
					break;
				default:
					// Parse and push dates to stack
					stack.push(token);
					break;
				}
				token = strtok(nullptr, ","); 
				i++;
			}
			student.setStack(stack); 
			info.insertAtFront(student);
		}
		cout << "Loading Complete!" << endl;
		cout << "\nPress ENTER to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	else {
		cout << "Error Loading File" << endl;
		cout << "\nPress ENTER to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	infile.close();
}

//Stores the data inside the linked list, whether it is from the classlist or the masterlist. Storing means outputting the info to the masterlist csv file, except this file has absences AND absence dates
void Menu::store() {
	fstream outfile;
	system("cls");
	cout << "Store Menu:\n\nOpening MasterList.csv..." << endl;
	outfile.open("MasterList.csv");
	if (outfile.is_open()) {
		Node<Data>* temp = info.getHead();
		while (temp != nullptr) {
			outfile << temp->getData()->getRecord() << ",";
			outfile << temp->getData()->getID() << ",";
			outfile << temp->getData()->getName() << ",";
			outfile << temp->getData()->getEmail() << ",";
			outfile << temp->getData()->getUnit() << ",";
			outfile << temp->getData()->getProgram() << ",";
			outfile << temp->getData()->getLevel() << ",";
			outfile << temp->getData()->getAbsence() << ",";

			Stack tempStack = temp->getData()->getStack();
			Stack reverse; 

			
			while (!tempStack.isEmpty()) {
				reverse.push(tempStack.pop());
			}

		
			while (!reverse.isEmpty()) {
				std::string date = reverse.pop();
				outfile << date;
				if (!reverse.isEmpty()) {
					outfile << ",";
				}
				tempStack.push(date);
			}

			outfile << "\n";
			temp = temp->getNext();
		}
	}
	else {
		cout << "Error Loading File" << endl;
		cout << "\nPress ENTER to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	outfile.close();
	cout << "Storing Complete!" << endl;
	cout << "\nPress ENTER to continue..." << endl;
	cin.ignore();
	cin.get();
}

//Uses code provided in the PA to generate a date that is incremented by one every time this function activates. Allows the user to mark students absent or not based on that date.
void Menu::mark() {
	system("cls");
	cout << "Attendance Marker:\n" << endl;
	time_t t = time(0);
	struct tm* now = localtime(&t);
	static int year = now->tm_year + 1900;
	static int month = now->tm_mon + 1;
	static int day = now->tm_mday;

	std::string yearS = std::to_string(year);
	std::string monthS = std::to_string(month);
	std::string dayS = std::to_string(day);
	std::string date = yearS + '-' + monthS + '-' + dayS;
	cout << "Date: " << date << endl;

	char answer;
	int absence;
	Node<Data>* temp = info.getHead();
	while (temp != nullptr) {
		cout << "Is " << temp->getData()->getName() << " in attendance today? (Y/N)" << endl << "Answer: ";
		cin >> answer;
		if (answer == 'N' || answer == 'n') {
			absence = temp->getData()->getAbsence();
			absence++;
			temp->getData()->setAbsence(absence);
			Stack stack = temp->getData()->getStack();
			stack.push(date);
			temp->getData()->setStack(stack);
		}
		temp = temp->getNext();
	}

	system("cls");
	cout << "Attendance Marker:\n" << endl << "Attendance for " << date << " Marked!";
	cout << "\n\nPress ENTER to continue..." << endl;
	cin.ignore();
	cin.get();
	day++;
}

//Allows the user to input a student ID and remove a date of absence of their choosing.
void Menu::edit() {
	system("cls");
	cout << "Edit Menu:\n" << endl;
	Node<Data>* temp = info.getHead();
	Node<Data>* target = nullptr;
	int ID;
	cout << "Please Enter the Student's ID (4 DIGITS): \n";
	cin >> ID;
	while (temp != nullptr) {
		if (ID == temp->getData()->getID()) {
			target = temp;
			Stack stack = temp->getData()->getStack();

			cout << "Dates of Absences:" << endl;
			while (!stack.isEmpty()) {
				cout << stack.pop() << endl;
			}
			break;
		}
		temp = temp->getNext();
	}

	if (target != nullptr) {
		cout << "\nPlease enter the exact date to remove (Y-M-D): ";
		std::string date;
		cin >> date;

		Stack modStack = target->getData()->getStack();
		Stack tempStack;
		while (!modStack.isEmpty()) {
			std::string dateRemove = modStack.pop();
			if (date == dateRemove) {
				int absence = target->getData()->getAbsence();
				absence--;
				target->getData()->setAbsence(absence);
			}
			else {
				tempStack.push(dateRemove);
			}
		}
		target->getData()->setStack(tempStack);
	}
	else {
		cout << "Student with the provided ID not found." << endl;
	}
}

//Generates two types of reports, one with every student and their most recent absence. And one which outputs the students that have been absent more then a specified amount of times.
void Menu::generate() {
	system("cls");
	int num;
	do {
		cout << "Report Generator:\n" << endl << "1. Generate Report of All Student Absences + Recent Absence\n2. Generate Report of Students Absent More than Specified Amount\n3. Exit\n\nAnswer: ";
		cin >> num;
		if (num == 1) {
			system("cls");
			cout << "Report Generator:\n" << "Generate Report of All Student Absences + Recent Absence\n" << endl;
			Node<Data>* temp1 = info.getHead();
			while (temp1 != nullptr) {
				cout << "Student: " << temp1->getData()->getName() << "|| Most Recent Absence: " << temp1->getData()->getStack().peek() << endl;
				temp1 = temp1->getNext();
			}
			cout << "\nReport Complete" << endl;
			cout << "\nPress ENTER to continue..." << endl;
			cin.ignore();
			cin.get();
			system("cls");
		}
		else if (num == 2) {
			Node<Data>* temp2 = info.getHead();
			system("cls");
			cout << "Report Generator:\n" << "Generate Report of Students Absent More than Specified Amount\n" << "\nEnter Number to Check for Exceeding Absences: ";
			int num2;
			cin >> num2;
			cout << endl << "\nStudents with Exceeding Absences:\n";
			bool found = false;
			while (temp2 != nullptr) {
				if (temp2->getData()->getAbsence() > num2) {
					cout << temp2->getData()->getName() << endl;
					found = true;
				}
				temp2 = temp2->getNext();
			}
			if (!found) {
				cout << "No students exceeded the specified absence limit." << endl;
			}
			cout << "\nReport Complete" << endl;
			cout << "\nPress ENTER to continue..." << endl;
			cin.ignore();
			cin.get();
			system("cls");
		}
		else if (num == 3) {
			return;
		}
		else {
			invalid();
		}
	} while (num != 3);
}

//Helper code
void Menu::invalid() {
	cout << "\nInvalid Selection" << endl;
	cout << "\nPress ENTER to continue..." << endl;
	cin.ignore();
	cin.get();
	system("cls");
}
