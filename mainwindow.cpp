#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"


#define EMPLOYEES_FILE_PATH "load/employees.txt"
#define SCHEDULE_FILE_PATH "load/schedule/"

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
    schedule_draw();
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

    string position;
    if(ui->radioButton_ps->isChecked()) position = "PS";
    else if(ui->radioButton_zms->isChecked()) position = "ZMS";
    else position = "MS";

    string time = ui->doubleSpinBox_time->text().toStdString();

    if(name != "" && surname != "" && position != "" && time != "")
    {
        ui->lineEdit_name->clear();
        ui->lineEdit_surname->clear();

        ui->radioButton_ms->setAutoExclusive(false);
        ui->radioButton_ms->setChecked(false);
        ui->radioButton_ms->setAutoExclusive(true);


        ui->radioButton_zms->setAutoExclusive(false);
        ui->radioButton_zms->setChecked(false);
        ui->radioButton_zms->setAutoExclusive(true);

        ui->radioButton_ps->setAutoExclusive(false);
        ui->radioButton_ps->setChecked(false);
        ui->radioButton_ps->setAutoExclusive(true);

        ui->doubleSpinBox_time->setValue(1);

        add_employee(name,surname,position,time);

        employees_load(employees);
        employees_draw();
        schedule_draw();
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
    for(int i= ui->tableWidget_schedule->rowCount()-1; i>=0; i--)
        ui->tableWidget_schedule->removeRow(i);

    schedule_draw_empty_slots();

    QString qstr;
    for(int i = 0; i < schedules.show_size(); i++)
    {
        for(unsigned long long j = 0; j < employees.size(); j++)
        {
            if(schedules.show_ID(i) == employees[j].show_employee_ID())
            {
                if(find_name(schedules.show_ID(i)) != "" )
                {

                    qstr = QString::fromStdString(schedules.show_Mo(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 3, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_Tu(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 4, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_We(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 5, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_Th(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 6, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_Fr(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 7, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_Sa(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 8, new QTableWidgetItem(qstr));

                    qstr = QString::fromStdString(schedules.show_Su(i));
                    if(qstr != "_")
                    ui->tableWidget_schedule->setItem(j, 9, new QTableWidgetItem(qstr));


                }
            }
        }
    }
    schedule_read_only();
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

void MainWindow::schedule_draw_empty_slots()
{
    QString qstr;
    for(unsigned long long j = 0; j < employees.size(); j++)
    {
            ui->tableWidget_schedule->insertRow ( ui->tableWidget_schedule->rowCount() );

            qstr = QString::fromStdString(employees[j].show_employee_ID());
            ui->tableWidget_schedule->setItem(j, 0, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(employees[j].show_employee_name());
            ui->tableWidget_schedule->setItem(j, 1, new QTableWidgetItem(qstr));

            qstr = QString::fromStdString(employees[j].show_employee_surname());
            ui->tableWidget_schedule->setItem(j, 2, new QTableWidgetItem(qstr));
    }

}


void MainWindow::on_pushButton_schedule_undo_changes_clicked()
{
    schedule_load();
    schedule_draw();
}


void MainWindow::on_pushButton_schedule_save_changes_clicked()
{
    fstream file;
    QString one_row;
    QTableWidgetItem *item;
    string file_path;
    QDate selected_date = ui->calendar_grafik->selectedDate();
    int selected_year = selected_date.year();
    int selected_week = selected_date.weekNumber();

    string s_selected_year = to_string(selected_year);
    string s_selected_week = to_string(selected_week);

    file_path += SCHEDULE_FILE_PATH;
    file_path += s_selected_week;
    file_path += "_";
    file_path += s_selected_year;
    file_path += ".txt";

    file.open(file_path, ios::out);
    for(int i = 0; i < ui->tableWidget_schedule->rowCount(); i++)
    {
        one_row = "";
        item = ui->tableWidget_schedule->item(i, 0);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 0)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 3);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 3)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 4);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 4)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 5);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 5)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 6);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 6)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 7);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 7)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 8);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 8)->text();
        one_row += " ";

        item = ui->tableWidget_schedule->item(i, 9);
        if(!item || item->text().isEmpty()) one_row += "_"; else  one_row += ui->tableWidget_schedule->item(i, 9)->text();

        if( file.good() )
        {
            file << one_row.toStdString();
        }
        if(i < ui->tableWidget_schedule->rowCount()-1)
            file << endl;

    }       file.close();

    schedule_load();
    schedule_draw();
}

void MainWindow::schedule_read_only()
{
    QTableWidgetItem *item;
    for(unsigned long long j = 0; j < employees.size(); j++)
    {
        item = ui->tableWidget_schedule->item(j, 0);
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);

        item = ui->tableWidget_schedule->item(j, 1);
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);

        item = ui->tableWidget_schedule->item(j, 2);
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
    }
}
