//============================================================================
// Name        : lesson_01_CPP_DM.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 01 of the C++: difficult moments course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;
//----------------------------------------------------------------------------
/*
1. Создайте структуру Person с 3 полями: фамилия, имя, отчество.
Поле отчество должно быть опционального типа,
т.к. не у всех людей есть отчество.
Перегрузите оператор вывода данных для этой структуры.
Также перегрузите операторы < и == (используйте tie).
//*/

struct Person
{
  string surname;
  string name;
  optional<string> patronymic;
};

std::ostream& operator<<(std::ostream& out, const Person &person)
{
  stringstream ss;
  ss << person.surname << " ";
  ss << person.name;
  if(person.patronymic.has_value())
    ss << " " << person.patronymic.value();
  out << ss.str();
  return out;
}

bool operator<(const Person &personFirst,
               const Person &personSecond)
{
  return tie(personFirst.surname,
             personFirst.name,
             personFirst.patronymic) <
         tie(personSecond.surname,
             personSecond.name,
             personSecond.patronymic);
}

bool operator==(const Person &personFirst,
               const Person &personSecond)
{
  return tie(personFirst.surname,
             personFirst.name,
             personFirst.patronymic) ==
         tie(personSecond.surname,
             personSecond.name,
             personSecond.patronymic);
}

void task_1()
{
  cout << "Task 1\n" << endl;

  Person p1,p2;

  cout << "Test 1" << endl;

  p1 = {"Fam","Name",nullopt};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n < \n" << p2 << "\n = \n";
  if(p1 < p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << "\nTest 2" << endl;

  p1 = {"Fim","Nime","Patr"};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n < \n" << p2 << "\n = \n";
  if(p1 < p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << "\nTest 3" << endl;

  p1 = {"Fim","Name","Pitr"};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n < \n" << p2 << "\n = \n";
  if(p1 < p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << "\nTest 4" << endl;

  p1 = {"Fim","Name",nullopt};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n < \n" << p2 << "\n = \n";
  if(p1 < p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << "\nTest 5" << endl;

  p1 = {"Fim","Name",nullopt};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n == \n" << p2 << "\n = \n";
  if(p1 == p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << "\nTest 6" << endl;

  p1 = {"Fim","Name","Patr"};
  p2 = {"Fim","Name","Patr"};

  cout << p1 << "\n == \n" << p2 << "\n = \n";
  if(p1 == p2)
  {
    cout << "true" << std::endl;
  }
  else
  {
    cout << "false" << std::endl;
  }

  cout << std::endl;
}

//----------------------------------------------------------------------------
/*
2. Создайте структуру PhoneNumber с 4 полями:
- код страны (целое число)
- код города (целое число)
- номер (строка)
- добавочный номер (целое число, опциональный тип)
Для этой структуры перегрузите оператор вывода.
Необходимо, чтобы номер телефона выводился в формате:
+7(911)1234567 12,
где 7 – это номер страны,
911 – номер города,
1234567 – номер,
12 – добавочный номер.
Если добавочного номера нет, то его выводить не надо.
//*/

struct PhoneNumber
{
  int codeCountry;
  int codeCity;
  string number;
  optional<int> extensionNumber;
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber &pn)
{
  stringstream ss;
  ss << "+" << pn.codeCountry << "("
      << pn.codeCity << ")" << pn.number;
  if(pn.extensionNumber.has_value())
    ss << " " << pn.extensionNumber.value();
  out << ss.str();
  return out;
}

bool operator<(const PhoneNumber &phoneNumberFirst,
               const PhoneNumber &phoneNumberSecond)
{
  return tie(phoneNumberFirst.codeCountry,
             phoneNumberFirst.codeCity,
             phoneNumberFirst.number,
             phoneNumberFirst.extensionNumber) <
         tie(phoneNumberSecond.codeCountry,
             phoneNumberSecond.codeCity,
             phoneNumberSecond.number,
             phoneNumberSecond.extensionNumber);
}

void task_2()
{
  cout << "Task 2\n" << endl;

  PhoneNumber pn;

  cout << "Test 1" << endl;

  pn = {7,911,"1234567",12};

  cout << pn << endl;

  cout << "Test 2" << endl;

  pn = {7,911,"1234567",nullopt};

  cout << pn << endl;

  cout << std::endl;
}

//----------------------------------------------------------------------------
/*
3. Создайте класс PhoneBook, который будет в контейнере хранить пары:
Человек – Номер телефона.
Конструктор этого класса должен принимать параметр типа ifstream – поток данных,
полученных из файла.
В теле конструктора происходит считывание данных из файла и заполнение контейнера.
Класс PhoneBook должен содержать перегруженный оператор вывода,
для вывода всех данных из контейнера в консоль.
В классе PhoneBook реализуйте метод SortByName,
который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке.
Если фамилии будут одинаковыми, то сортировка должна выполняться по именам,
если имена будут одинаковы, то сортировка производится по отчествам. Используйте алгоритмическую функцию sort.
Реализуйте метод SortByPhone,
который должен сортировать элементы контейнера по номерам телефонов.
Используйте алгоритмическую функцию sort.
Реализуйте метод GetPhoneNumber, который принимает фамилию человека,
а возвращает кортеж из строки и PhoneNumber.
Строка должна быть пустой, если найден ровно один человек
с заданном фамилией в списке.
Если не найден ни один человек с заданной фамилией,
то в строке должна быть запись «not found», если было найдено больше одного человека,
то в строке должно быть «found more than 1».
Для прохода по элементам контейнера используйте алгоритмическую функцию for_each.
Реализуйте метод ChangePhoneNumber, который принимает человека и
новый номер телефона и, если находит заданного человека в контейнере,
то меняет его номер телефона на новый, иначе ничего не делает.
Используйте алгоритмическую функцию find_if.
//*/

class PhoneBook
{
private:
  vector<pair<Person*,PhoneNumber*>> vecPair;
public:
  PhoneBook(ifstream &inFile);
  ~PhoneBook();
  void SortByName();
  void SortByPhone();
  tuple<string,PhoneNumber> GetPhoneNumber(const string &surname) const;
  void ChangePhoneNumber(const Person &person, const PhoneNumber &phoneNumber);

  friend std::ostream& operator<<(std::ostream& out, const PhoneBook &pb);
};

vector<string> split(const string &s, const string &delim)
{
  vector<string> vec;

  if(s.length() == 0)
    return vec;

  if(delim.length() == 0)
  {
    vec.push_back(s);
    return vec;
  }

  size_t pos = 0;
  while (pos < s.length() - 1)
  {
    size_t posDelim = s.length();
    for(const char ch: delim)
    {
      size_t p = s.find(ch,pos);
      if(p < posDelim)
        posDelim = p;
    }
    if(posDelim == pos)
    {
      ++pos;
      continue;
    }
    string substr = s.substr(pos,posDelim - pos);
    vec.push_back(substr);
    pos = posDelim + 1;
  }
  return vec;
}

PhoneBook::PhoneBook(ifstream &inFile)
{
  if (inFile.is_open())
  {
    const size_t size = 255;
    char buf[size];
    string line_of_file;
    while (!inFile.eof())
    {
      inFile.getline(buf, size);
      line_of_file = buf;

      string fullName =
          line_of_file.substr(0, line_of_file.find("+")-1);

      vector<string> vName = split(fullName," ");

      string phoneNumber =
          line_of_file.substr(line_of_file.find("+")+1,line_of_file.back());

      vector<string> vPhoneNumber = split(phoneNumber,"() ");

      if(vName.size() < 2 || vPhoneNumber.size() < 3)
        continue;

      Person *pPerson = new Person;

      pPerson->surname = vName[0];
      pPerson->name = vName[1];
      if(vName.size() > 2)
        pPerson->patronymic = vName[2];
      else
        pPerson->patronymic = nullopt;

      PhoneNumber *pPhoneNumber = new PhoneNumber;

      pPhoneNumber->codeCountry = stoi(vPhoneNumber[0]);
      pPhoneNumber->codeCity = stoi(vPhoneNumber[1]);
      pPhoneNumber->number = vPhoneNumber[2];
      if(vPhoneNumber.size() > 3)
        pPhoneNumber->extensionNumber = stoi(vPhoneNumber[3]);
      else
        pPhoneNumber->extensionNumber = nullopt;

      vecPair.push_back(make_pair(pPerson,pPhoneNumber));
    }
    inFile.close();
  }
  else
  {
    cout << "File did not open!" << endl;
  }
}

PhoneBook::~PhoneBook()
{
  for(auto& a: vecPair)
  {
    delete a.first;
    delete a.second;
  }
}

std::ostream& operator<<(std::ostream& out, const PhoneBook &pb)
{
  for(const auto& a: pb.vecPair)
  {
    out << *a.first << " " << *a.second << endl;
  }
  return out;
}

void PhoneBook::SortByName()
{
  auto Comp = [](pair<Person*,PhoneNumber*> p1,
                 pair<Person*,PhoneNumber*> p2) -> bool
    {
      return *p1.first < *p2.first;
    };

  sort(vecPair.begin(),vecPair.end(),Comp);
}

void PhoneBook::SortByPhone()
{
  auto Comp = [](pair<Person*,PhoneNumber*> p1,
                 pair<Person*,PhoneNumber*> p2) -> bool
    {
      return *p1.second < *p2.second;
    };

  sort(vecPair.begin(),vecPair.end(),Comp);
}

tuple<string,PhoneNumber> PhoneBook::GetPhoneNumber(const string &surname) const
{
  size_t cnt = 0;
  const PhoneNumber *p_pn;
  auto counter = [&cnt,surname,&p_pn](const pair<Person*,PhoneNumber*> &p){
    if(surname == p.first->surname)
    {
      ++cnt;
      p_pn = p.second;
    }
  };

  for_each(vecPair.begin(),vecPair.end(),counter);

  tuple<string,PhoneNumber> t;
  if(cnt == 0)
    t = make_tuple("Not found", PhoneNumber{0,0,"",nullopt});
  else if(cnt == 1)
    t = make_tuple("", *p_pn);
  else
    t = make_tuple("Found more than 1", PhoneNumber{0,0,"",nullopt});

  return t;
}

void PhoneBook::ChangePhoneNumber(const Person &person, const PhoneNumber &phoneNumber)
{
  auto it = find_if(vecPair.begin(),vecPair.end(),
                    [person](pair<Person*,PhoneNumber*> p) -> bool
        {
          return person == *p.first;
        }
      );

  if(it != vecPair.end())
  {
    *it->second = phoneNumber;
  }
}

string getNameFile()
{
  cout << "Enter file's name: ";
  string s;
  cin >> s;
  return s;
}

void task_3()
{
  cout << "Task 3\n" << endl;

  string nameFile = "testFile"; //getNameFile();

  ifstream fin(nameFile + ".txt");

  PhoneBook phoneBook(fin);

  cout << "Test 1" << endl;

  cout << phoneBook;

  cout << "Test 2" << endl;
  cout << "SortByName" << endl;
  phoneBook.SortByName();
  cout << phoneBook;

  cout << "Test 3" << endl;
  cout << "SortByPhone" << endl;
  phoneBook.SortByPhone();
  cout << phoneBook;

  cout << "Test 4" << endl;
  cout << "GetPhoneNumber" << endl;

  Person person{"Петров","Иван","Павлович"};
  auto found = phoneBook.GetPhoneNumber(person.surname);
  cout << person << " " << get<0>(found) << " " << get<1>(found) << endl;

  person = Person{"Елисеев","Иван",nullopt};
  found = phoneBook.GetPhoneNumber(person.surname);
  cout << person << " " << get<0>(found) << " " << get<1>(found) << endl;

  person = Person{"Коновалов","Арнольд",nullopt};
  found = phoneBook.GetPhoneNumber(person.surname);
  cout << person << " " << get<0>(found) << " " << get<1>(found) << endl;

  cout << "Test 5" << endl;
  cout << "ChangePhoneNumber" << endl;

  person = Person{"Коновалов","Арнольд",nullopt};
  PhoneNumber phoneNumber{7,999,"0290123",34};

  phoneBook.ChangePhoneNumber(person,phoneNumber);
  cout << phoneBook;

  cout << std::endl;
}

void task_3_test()
{
  cout << "\nTask 3 Test from this lesson.\n" << endl;
  ifstream file("testFile.txt"); // путь к файлу PhoneBook.txt
  PhoneBook book(file);
  cout << book;

  cout << "------SortByPhone-------" << endl;
  book.SortByPhone();
  cout << book;

  cout << "------SortByName--------" << endl;
  book.SortByName();
  cout << book;

  cout << "-----GetPhoneNumber-----" << endl;
  // лямбда функция, которая принимает фамилию и
  // выводит номер телефона этого	человека, либо строку с ошибкой
  auto print_phone_number = [&book](const string& surname)
    {
      cout << surname << "\t";
      auto answer = book.GetPhoneNumber(surname);
      if (get<0>(answer).empty())
          cout << get<1>(answer);
      else
          cout << get<0>(answer);
      cout << endl;
    };

  // вызовы лямбды
  print_phone_number("Шарапов");
  print_phone_number("Петров");

  cout << "----ChangePhoneNumber----" << endl;
  book.ChangePhoneNumber(Person{ "Комаров", "Тихон", "Еремеевич" },
                         PhoneNumber{7, 123, "15344458", nullopt});
  book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                         PhoneNumber{ 16, 465, "9155448", 13 });
  cout << book;
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //--------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //--------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //--------------------------------------------------------------------------
  // Task 3
  //*
  task_3();
  task_3_test();
  //*/
  //--------------------------------------------------------------------------
  return a.exec();
}
