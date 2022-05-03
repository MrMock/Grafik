#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "employee.h"
#include "schedule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void employees_load(vector <employee> & pracow);
    void employees_draw();
    void schedule_load();
    void schedule_draw();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_add_employee_clicked();

    void on_calendar_grafik_selectionChanged();

    void on_lcdNumber_overflow();

    void schedule_draw_empty_slots();

    void on_pushButton_schedule_undo_changes_clicked();

    void on_pushButton_schedule_save_changes_clicked();

    void schedule_read_only();


private:
    Ui::MainWindow *ui;
    vector <employee> employees;
    schedule schedules;
    void delete_employee(string ID);
    void add_employee(string name, string surname, string position, string time);
    string random_ID();
    string find_name(string ID);
    string find_surname(string ID);

};
#endif // MAINWINDOW_H
