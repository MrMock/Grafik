#include "employee.h"

employee::employee(){

}

string employee::show_employee_ID(){
    return ID;
}
string employee::show_employee_surname(){
    return surname;
}
string employee::show_employee_name(){
    return name;
}
string employee::show_employee_time(){
    return time;
}
string employee::show_employee_position(){
    return position;
}

void employee::load_employee_ID(string employee_ID){
    if(employee_ID.length() >= 4 && ID.length() <= 8)
        ID = employee_ID;
}

void employee::load_employee_surname(string employee_surname){
    if(employee_surname.length() >= 2 )
        surname = employee_surname;
}

void employee::load_employee_name(string employee_name){
    if(employee_name.length() >=2 )
        name = employee_name;
}

void employee::load_employee_time(string employee_time){
    //if(etat >= 0,2 && etat <= 1)
        time = employee_time;
}

void employee::load_employee_position(string employee_position){
    if(employee_position.length() >= 1)
        position = employee_position;
}
