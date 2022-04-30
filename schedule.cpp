#include "schedule.h"

#define SCHEDULE_FILE_PATH "load/schedule/"

schedule::schedule()
{

}

void schedule::load_schedule()
{
    fstream file;
    string help_string;
    string file_path;
    file_path += SCHEDULE_FILE_PATH;
    file_path += week;
    file_path += "_";
    file_path += year;
    file_path += ".txt";

    file.open( file_path, ios::in );
    if( file.good() )
    {
        while( !file.eof() )
        {
            getline( file, help_string);
            employees.push_back(help_string);
        }
    }
}

int schedule::show_size(){
    return employees.size();
}
string schedule::show_ID(int employee_number){
    return show_single_word(employee_number , 0);
}
string schedule::show_Mo(int employee_number){
    return show_single_word(employee_number , 1);
}
string schedule::show_Tu(int employee_number){
    return show_single_word(employee_number , 2);
}
string schedule::show_We(int employee_number){
    return show_single_word(employee_number , 3);
}
string schedule::show_Th(int employee_number){
    return show_single_word(employee_number , 4);
}
string schedule::show_Fr(int employee_number){
    return show_single_word(employee_number , 5);
}
string schedule::show_Sa(int employee_number){
    return show_single_word(employee_number , 6);
}
string schedule::show_Su(int employee_number){
    return show_single_word(employee_number , 7);
}

string schedule::show_single_word(int employee_number, int word_number){
    int actual_number = -1;
    string word;
    for(unsigned long long i = 0; i < employees[employee_number].size(); i++)
    {
        if(employees[employee_number][i] != ' ' && actual_number+1 == word_number)
             word += employees[employee_number][i];

        if(employees[employee_number][i] == ' ')
            actual_number++;

        if(word_number == actual_number)
            return word;
    }return word;
}

void schedule::load_date(string week, string year)
{
    this->week = week;
    this->year = year;
}

void schedule::clear()
{
    string week="";
    string year="";
    employees.clear();
}
