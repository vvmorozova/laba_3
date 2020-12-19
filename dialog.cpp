#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::printCollection(Collection<std::string>* value){
    QString str;
    int cnt = value->getbuffer_size();
    for(int i =0; i < cnt; i++){
        if(value->possibleIndex(i)){
            ui->listWidget->addItem(QString::fromStdString(value->getWithIndex(i)));
        }
    }
}
