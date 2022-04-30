#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
using namespace std;

class employee
{
public:
    employee();

    void load_employee_ID(string employee_ID);
    void load_employee_surname(string employee_surname);
    void load_employee_name(string employee_name);
    void load_employee_time(string employee_time);
    void load_employee_position(string employee_position);

    string show_employee_ID();
    string show_employee_surname();
    string show_employee_name();
    string show_employee_time();
    string show_employee_position();

private:
    string ID;
    string surname;
    string name;
    string time;
    string position;
};

#endif // EMPLOYEE_H
