// Реализация ИС для деканата:
// Программа позволяет вести учет студентов, групп, оценок, предметов, 
// выводить данные в файл, читать из файла

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <windows.h>
using namespace std;

class Student {
public:
	std::string name;
	int age;
	Student(std::string n, int a) {
		name = n;
		age = a;
	}
public: std::string get_name() { return name; }
};
struct Subject {
public:
	std::string Name;
	std::vector<std::vector<int>> results;
};
class Group {
public:
	std::string nameGroup;
	std::vector<Student*> student;
	std::vector<Subject*> subject;
	void addSubject(std::string name) {
		Subject* sub = new Subject; sub->Name = name;
		subject.push_back(sub);
	}
	void addResults(Subject* sub, int id, int res) {
		sub->results[id].push_back(res);
	}
	Subject* subjectFind(std::string name) {
		for (auto el : subject)
			if (el->Name == name) return el;
	}
	void removeSubject(std::string name) {
		for (auto it = subject.begin(); it != subject.end(); it++) {
			Subject* n = *it;
			if (n->Name == name) {
				subject.erase(it);
				n->Name = "";
				break;
			}
		}
	}
	Student* studentFind(std::string studentName) {
		for (auto it = student.begin(); it != student.end(); it++) {
			auto n = *it;
			if (n->name == studentName)
				return *it;
		}
	}
	int studentFindIndex(std::string studentName) {
		int index = 0;
		for (auto it = student.begin(); it != student.end(); it++) {
			auto n = *it;
			if (n->name == studentName)
				return index;
			index++;
		}
	}
	void addStudent(Student* st) {
		student.push_back(st);
		for (auto el : subject)
			el->results.push_back(std::vector<int>());
	}
	void deleteStudent(Student* st) {
		student.erase(remove(student.begin(), student.end(), st), student.end());
	}
	void printGroup() {
		std::cout << "Группа: " << nameGroup << "\n";
		std::cout << "Студенты: \n";
		for (auto el : student) std::cout << el->name << "   " << el->age << "\n";
		std::cout << "Предметы: \n";
		for (auto el : subject) std::cout << el->Name << "\n";
		std::cout << endl;
	}
	void printGroupinfile() {
		ofstream file;
		file.open("d:\\decanat.txt");
		file << "Группа: " << nameGroup << "\n";
		file << "Студенты: \n";
		for (auto el : student) file << el->name << "   " << el->age << "\n";
		file << "Предметы: \n";
		for (auto el : subject) file << el->Name << "\n";
		file << std::endl;
		file.close();
	}
	void showresstud(Student* st) {
		std::cout << st->name << std::endl;
		int id = studentFindIndex(st->name);
		for (auto el : subject) {
			double sr = 0; int k = 0;
			std::cout << el->Name << ": " << std::endl;
			for (int j = 0; j < el->results[id].size(); j++)
			{
				std::cout << el->results[id][j] << " ";
				sr += el->results[id][j]; k++;
			}
			sr = sr / k;
			std::cout << std::endl << "Средняя оценка: " << sr;
			std::cout << endl;
		}
	}
	void showresgroup() {
		int i = 0;
		for (auto el : subject) {
			double sr = 0; int k = 0;
			std::cout << el->Name << ": " << std::endl;
			for (vector<int>& vec_current : el->results) {
				std::cout << student[i]->name << ": " << std::endl;
				for (int& value : vec_current) {
					std::cout << value << " ";
					sr += value; k++;
				}
				cout << endl; i++;
				sr = sr / k;
				std::cout << std::endl << "Средняя оценка: " << sr << std::endl;
			}
			std::cout << endl;
			i = 0;
		}
	}
};
class Decanat {
public:
	std::vector<Group*> groups;
	void transaction(std::string studentName, std::string group1, std::string group2) {
		Group* Group1 = groupFind(group1);
		Group* Group2 = groupFind(group2);
		Student* stud = Group1->studentFind(studentName);
		Group1->deleteStudent(stud);
		Group2->addStudent(stud);
	}
	Group* addGroup(std::string name) {
		Group* group = new Group; group->nameGroup = name;
		groups.push_back(group);
		return group;
	}
	void removeGroup(std::string name) {
		Group* gr = groupFind(name);
		groups.erase(remove(groups.begin(), groups.end(), gr), groups.end());
	}
	Student* makeStudent() {
		std::string name; int age;
		std::cout << "Введите имя - возраст\n";
		std::cin >> name;
		std::cin >> age;
		Student* st = new Student(name, age);
		return st;
	}
	Group* groupFind(std::string groupName) {
		for (auto it = groups.begin(); it != groups.end(); it++) {
			Group* n = *it;
			if (n->nameGroup == groupName) return *it;
		}
	}
	void print() {
		for (auto el : groups) el->printGroup();
	}
	void printinfile() {
		for (auto el : groups) el->printGroupinfile();
	}
};
void ReadInFile(Decanat* decanat) {
	std::string name; int age = 0;
	std::getline(std::cin, name);
	Group* group = decanat->addGroup(name);
	group->nameGroup = "ИСИТ";
	std::string s, s2;
	ifstream f2;
	f2.open("d:\\subs.txt");
	while (!f2.eof()) {
		getline(f2, s);
		group->addSubject(s);
	}
	f2.close();
	ifstream f;
	f.open("d:\\names.txt");
	int  i = 0;
	while (!f.eof()) {
		s2 = ""; s = "";
		getline(f, s);
		while (s[i] != ' ') {
			++i;
		}
		s2.append(s, 0, 2);
		s.erase(0, 3);
		age = stoi(s2);
		i = 0;
		Student* st = new Student(s, age);
		group->addStudent(st);
	}
	f.close();
	decanat->print();
}
void PrintInFile(Decanat* decanat) {
	decanat->printinfile();
}
void AddStud(Decanat* d) {
	std::string str;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	Group* group = d->groupFind(str);
	group->addStudent(d->makeStudent());
}
void AddSub(Decanat* d) {
	std::string str, str2;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	std::cout << "Введите имя предмета \n";
	std::cin >> str2;
	Group* group = d->groupFind(str);
	group->addSubject(str2);
}
void AddResults(Decanat* d) {
	std::string str, str2, stud; int y, res, id;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	std::cout << "Введите имя предмета \n";
	std::cin >> str2;
	Group* group = d->groupFind(str);
	Subject* sub = group->subjectFind(str2);
	while (true) {
		cout << "Выход - 0\n";
		cout << "Продолжить - 1\n";
		cin >> y;
		if (y == 0) break;
		else {
			cout << "Введите имя студента: \n";
			cin >> stud;
			cout << "Введите оценку: \n";
			cin >> res;
			id = group->studentFindIndex(stud);
			group->addResults(sub, id, res);
		}
	}
}

int veubor() {
	int b;
	std::cout << "1-Добавить студента\n";
	std::cout << "2-Добавить предмет\n";
	std::cout << "3-Выход\n";
	std::cin >> b;
	return b;
}
int AddGroup(Decanat* d) {
	std::string name, str;
	std::cout << "Введите имя группы\n";
	std::cin >> name;
	Group* gr = d->addGroup(name);
	while (true) {
		switch (veubor()) {
		case 1: gr->addStudent(d->makeStudent()); break;
		case 2:
			std::cout << "Введите имя предмета \n";
			std::cin >> str;
			gr->addSubject(str); break;
		case 3: return 0;
		}
		system("cls");
	}
	return 0;
}


void DeleteStudent(Decanat* d) {
	std::string str, str2;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	std::cout << "Введите имя студента \n";
	std::cin >> str2;
	Group* group = d->groupFind(str);
	group->deleteStudent(group->studentFind(str2));
}
void DeleteSubject(Decanat* d) {
	std::string str, str2;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	std::cout << "Введите имя предмета \n";
	std::cin >> str2;
	Group* group = d->groupFind(str);
	group->removeSubject(str2);
}
void DeleteGroup(Decanat* d) {
	std::string  name;
	std::cout << "Введите имя группы\n";
	std::cin >> name;
	d->removeGroup(name);
}
void ShowGroups(Decanat* d) {
	for (auto it = d->groups.begin(); it != d->groups.end(); it++) {
		Group* n = *it;
		std::cout << n->nameGroup << std::endl;
	}
}
void ShowResStud(Decanat* d) {
	std::string str, str2;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	std::cout << "Введите имя студента \n";
	std::cin >> str2;
	Group* group = d->groupFind(str);
	Student* st = group->studentFind(str2);
	group->showresstud(st);
}
void ShowResGroup(Decanat* d) {
	std::string str, str2;
	std::cout << "Введите имя группы \n";
	std::cin >> str;
	Group* group = d->groupFind(str);
	group->showresgroup();
}
int menu() {
	int t;
	std::cout << "1-Прочесть данные из файла\n";
	std::cout << "2-Вывести данные в файл\n";
	std::cout << "3-Добавить студента\n";
	std::cout << "4-Добавить предмет\n";
	std::cout << "5-Добавить оценки\n";
	std::cout << "6-Добавить группу\n";
	std::cout << "7-Удалить студента\n";
	std::cout << "8-Удалить предмет\n";
	std::cout << "9-Удалить группу\n";
	std::cout << "10-Вывести группы\n";
	std::cout << "11-Вывести оценки студента\n";
	std::cout << "12-Вывести оценки группы\n";
	std::cout << "13-Вывести данные обо всех группах\n";
	std::cout << "14-Выход\n";
	std::cin >> t;
	system("cls");
	return t;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Decanat* decanat = new Decanat;
	while (true) {
		switch (menu()) {
		case 1: ReadInFile(decanat); break; //+
		case 2: PrintInFile(decanat); break; //+
		case 3: AddStud(decanat); break; //+
		case 4: AddSub(decanat); break; //+
		case 5: AddResults(decanat); break; //+ 
		case 6: AddGroup(decanat); break; //+
		case 7: DeleteStudent(decanat); break; //+
		case 8: DeleteSubject(decanat); break; //+
		case 9: DeleteGroup(decanat); break; //+
		case 10: ShowGroups(decanat); break; //+
		case 11: ShowResStud(decanat); break; //+
		case 12: ShowResGroup(decanat); break; //+
		case 13: decanat->print();  break; //+
		case 14: return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}