#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"


#define EMPLOYEES_FILE_PATH "load/employees.txt"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    employees_load(employees);
    employees_draw();


    schedule_load();
    schedule_draw();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::employees_load(vector <employee> & pracow)
{

    ui->tableWidget->setRowCount(0);
    employees.clear();

    fstream file;
    string word;
    string employee_ID;
    string employee_surname;
    string employee_name;
    string employee_time;
    string employee_position;
    employee employee_help;

    file.open( EMPLOYEES_FILE_PATH, ios::in );
    if( file.good() )
    {
        while( !file.eof() )
        {

             file >> employee_ID;
             file >> employee_name;
             file >> employee_surname;
             file >> employee_position;
             file >> employee_time;


             employee new_employee;

             new_employee.load_employee_ID(employee_ID);
             new_employee.load_employee_surname(employee_surname);
             new_employee.load_employee_name(employee_name);
             new_employee.load_employee_time(employee_time);
             new_employee.load_employee_position(employee_position);

             pracow.push_back(new_employee);
        }
        file.close();
    }

}

void MainWindow::employees_draw()
{
    for(unsigned long long i=0; i < employees.size(); i++)
    {
        ui->tableWidget->insertRow ( ui->tableWidget->rowCount() );

        QString qstr = QString::fromStdString(employees[i].show_employee_ID());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(qstr));

        qstr = QString::fromStdString(employees[i].show_employee_name());
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(qstr));

        qstr = QString::fromStdString(employees[i].show_employee_surname());
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(qstr));

        qstr = QString::fromStdString(employees[i].show_employee_position());
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(qstr));

        qstr = QString::fromStdString(employees[i].show_employee_time());
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(qstr));
    }

}

void MainWindow::add_employee(string name, string surname, string position, string time)
{
        fstream file;
        string help;

        for(unsigned long long i=0; i < employees.size(); i++)
        {
                help += employees[i].show_employee_ID();
                help += " ";

                help += employees[i].show_employee_name();
                help += " ";

                help += employees[i].show_employee_surname();
                help += " ";

                help += employees[i].show_employee_position();
                help += " ";

                help += employees[i].show_employee_time();
                help += "\n";

        }

        help += random_ID();
        help += " ";
        help += name;
        help += " ";
        help += surname;
        help += " ";
        help += position;
        help += " ";
        help += time;

        file.open(EMPLOYEES_FILE_PATH, ios::out);
        if( file.good() )
        {
            file << help;
        }

        employees_load(employees);
        employees_draw();

}

void MainWindow::delete_employee(string ID)
{

    string help;
    for(unsigned long long i=0; i < employees.size(); i++)
    {
        if(employees[i].show_employee_ID() != ID)
        {
            help += employees[i].show_employee_ID();
            help += " ";

            help += employees[i].show_employee_name();
            help += " ";

            help += employees[i].show_employee_surname();
            help += " ";

            help += employees[i].show_employee_position();
            help += " ";

            help += employees[i].show_employee_time();
            help += "\n";

        }
    }
    help.pop_back();
    fstream file;
    file.open( EMPLOYEES_FILE_PATH, ios::out );
    if( file.good() )
    {
        file << help;
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QString QS_ID = ui->lineEdit_employee_delete->text();
    string ID = QS_ID.toStdString();
    delete_employee(ID);
    ui->lineEdit_employee_delete->clear();

    employees_load(employees);
    employees_draw();
}


void MainWindow::on_pushButton_add_employee_clicked()
{
    string name = ui->lineEdit_name->text().toStdString();
    string surname = ui->lineEdit_surname->text().toStdString();
    string position = ui->lineEdit_position->text().toStdString();
    string time = ui->lineEdit_time->text().toStdString();

    if(name != "" && surname != "" && position != "" && time != "")
    {
        ui->lineEdit_name->clear();
        ui->lineEdit_surname->clear();
        ui->lineEdit_position->clear();
        ui->lineEdit_time->clear();

        add_employee(name,surname,position,time);

        employees_load(employees);
        employees_draw();
    }

}

string MainWindow::random_ID()
{
    bool same = false;
    srand( time( NULL ) );
    int random_int;
    string random_string;
    do
    {
        random_int = (rand() % 99999) + 10000;
        random_string = to_string(random_int);
        for(unsigned long long i=0; i < employees.size(); i++)
        {
            if(employees[i].show_employee_ID() == random_string)
                same = true;
        }

    }while(same);
    return random_string;
}

void MainWindow::schedule_load()
{
    schedules.clear();
    QDate selected_date = ui->calendar_grafik->selectedDate();
    int selected_year = selected_date.year();
    int selected_week = selected_date.weekNumber();
    schedules.load_date(to_string(selected_week), to_string(selected_year));
    schedules.load_schedule();
}

void MainWindow::schedule_draw()
{

    QString qstr;
    for(int i = 0; i < schedules.show_size(); i++)
    {
        string help = schedules.show_ID(i);
        if(find_name(schedules.show_ID(i)) != "" )
        {
            ui->tableWidget_schedule->insertRow ( ui->tableWidget_schedule->rowCount() );

            qstr = QString::fromStdString(schedules.show_ID(i));
            ui->tableWidget_schedule->setItem(i, 0, new QTableWidgetItem(qstr));

            //qstr = QString::fromStdString(schedules.show_name(i));
            //ui->tableWidget_schedule->setItem(i, 0, new QTableWidgetItem(qstr));

           // qstr = QString::fromStdString(schedules.show_ID(i));
            //ui->tableWidget_schedule->setItem(i, 0, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Mo(i));
            ui->tableWidget_schedule->setItem(i, 3, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Tu(i));
            ui->tableWidget_schedule->setItem(i, 4, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_We(i));
            ui->tableWidget_schedule->setItem(i, 5, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Th(i));
            ui->tableWidget_schedule->setItem(i, 6, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Fr(i));
            ui->tableWidget_schedule->setItem(i, 7, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Sa(i));
            ui->tableWidget_schedule->setItem(i, 8, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(schedules.show_Su(i));
            ui->tableWidget_schedule->setItem(i, 9, new QTableWidgetItem(qstr));


        }
    }
}

string MainWindow::find_name(string ID){
    for(unsigned long long i = 0; i < employees.size(); i++)
    {
        if(employees[i].show_employee_ID() == ID )
            return employees[i].show_employee_name();
    }return "";
}
string MainWindow::find_surname(string ID){
    for(unsigned long long i = 0; i < employees.size(); i++)
    {
        if(employees[i].show_employee_ID() == ID )
            return employees[i].show_employee_surname();
    }return "";
}

void MainWindow::on_calendar_grafik_selectionChanged()
{
    ui->tableWidget_schedule->setRowCount(0);
    schedule_load();
    schedule_draw();
}


void MainWindow::on_lcdNumber_overflow()
{
    ui->lcdNumber->value();
}
