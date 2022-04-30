#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QMainWindow>
#include <fstream>
#include <iostream>

using namespace std;

class schedule
{
public:
    schedule();

    int show_size();
    void load_date(string week, string year);
    string show_ID(int employee_number);
    string show_Mo(int employee_number);
    string show_Tu(int employee_number);
    string show_We(int employee_number);
    string show_Th(int employee_number);
    string show_Fr(int employee_number);
    string show_Sa(int employee_number);
    string show_Su(int employee_number);
    void load_schedule();
    void clear();


private:
    string week;
    string year;
    vector <string> employees;


    string show_single_word(int employee_number, int word_number);
};

#endif // SCHEDULE_H
