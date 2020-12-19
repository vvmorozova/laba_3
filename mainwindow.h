#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "collection.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_clicked();

    void on_Delete_clicked();

    void on_actionClear_all_triggered();

    void on_actionOpen_triggered();

    void on_show_clicked();

    void on_actionSave_As_triggered();

    void setDefaultColor();
    void validError();

private:
    int size;
    Ui::MainWindow *ui;
    Collection<std::string> Nutrients;
    Collection<std::string> Fast;
    Collection<std::string> Stock;
    QTimer validTimer;
};
#endif // MAINWINDOW_H
