#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter menu item");



    ui->comboBoxVariant->addItems({"Nutrients", "In stock", "Quickly to eat", "All"});
    size = 0;
    ui->show->setEnabled(false);

    connect( &validTimer, SIGNAL( timeout() ), SLOT( setDefaultColor() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    QString key = ui->lineEdit->text();
    bool nutr = ui->nutrcheck->isChecked();
    bool quick = ui->qcheck->isChecked();
    bool instock = ui->instockcheck->isChecked();

    if(key != ""){

        if (nutr == true)
        {
            if(!Nutrients[key.toStdString()]){
                Nutrients << key.toStdString();
                ui->listWidget->addItem(QString("%1\n[Nutrients]").arg(key));
            }else{
                validError();
            }

        }

        if (quick == true)
        {
            if(!Fast[key.toStdString()]){
                Fast << key.toStdString();
                ui->listWidget->addItem(QString("%1\n[Quickly to eat]").arg(key));
            }else{
                validError();
            }

        }

        if (instock == true)
        {
            if(!Stock[key.toStdString()]){
                Stock << key.toStdString();
                ui->listWidget->addItem(QString("%1\n[In stock]").arg(key));
            }else{
                validError();
            }

        }
        size++;
        ui->show->setEnabled(true);
    }else{
        validError();
    }

}

void MainWindow::on_Delete_clicked()
{
    QString key = ui->lineEdit->text();
    bool nutr = ui->nutrcheck->isChecked();
    bool quick = ui->qcheck->isChecked();
    bool instock = ui->instockcheck->isChecked();
    int i = 0;

    if(key != "" || size == 0){
        if (nutr == true){
            if(Nutrients.deleteElement( key.toStdString())){
                while(ui->listWidget->item(i)->text() != QString("%1\n[Nutrients]").arg(key)){
                    i++;
                }
                delete ui->listWidget->item(i);
            }else{
                validError();
            }

    }
        if (quick == true){
            if(Fast.deleteElement( key.toStdString())){
                while(ui->listWidget->item(i)->text() != QString("%1\n[Quickly to eat]").arg(key)){
                    i++;
                }
                delete ui->listWidget->item(i);
            }else{
                validError();
            }
        }
        if (instock == true){
            if(Stock.deleteElement( key.toStdString())){
                while(ui->listWidget->item(i)->text() != QString("%1\n[In stock]").arg(key)){
                    i++;
                }
                delete ui->listWidget->item(i);
            }else{
                validError();
            }
        }

        size--;
        if(size == 0){
            ui->show->setEnabled(true);
        }
    }else{
        validError();
    }
}

void MainWindow::on_actionClear_all_triggered()
{
    Stock.clearAll();
    Fast.clearAll();
    Nutrients.clearAll();
    for(int i = 0; i < size; i++){
        delete ui->listWidget->item(0);
    }
    size = 0;
}

void MainWindow::on_actionOpen_triggered(){
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
        return;
    }
    Nutrients.clearAll();
    Nutrients.readData(file_name + "_nut");
    Fast.clearAll();
    Fast.readData(file_name + "_fast");
    Stock.clearAll();
    Stock.readData(file_name + "_stoc");

    int cnt = Nutrients.getbuffer_size();

    for(size_t i = 0; i < cnt; i++){
        if(Nutrients.possibleIndex(i)){
            ui->listWidget->addItem(QString("%1\n[Nutrients]").arg(QString::fromStdString(Nutrients.getWithIndex(i))));
        }
    }

    cnt = Fast.getbuffer_size();

    for(size_t i = 0; i < cnt; i++){
        if(Fast.possibleIndex(i)){
            ui->listWidget->addItem(QString("%1\n[Quickly to eat]").arg(QString::fromStdString(Fast.getWithIndex(i))));
        }
    }

    cnt = Stock.getbuffer_size();

    for(size_t i = 0; i < cnt; i++){
        if(Stock.possibleIndex(i)){
            ui->listWidget->addItem(QString("%1\n[In stock]").arg(QString::fromStdString(Stock.getWithIndex(i))));
        }
    }


}


void MainWindow::setDefaultColor(){
    ui->lineEdit->setStyleSheet("QLineEdit { background-color: white }");
}

void MainWindow::validError(){
    ui->lineEdit->setStyleSheet("QLineEdit { background-color: pink }");
    validTimer.start(250);
}

void MainWindow::on_show_clicked()
{
    Collection<std::string> result;
    int cnt = ui->comboBoxVariant->currentIndex();
    switch (cnt) {
    case 0:
        result = (Nutrients);
        break;
    case 1:
        result = Stock;
        break;
    case 2:
        result = Fast;
        break;
    case 3:
        result = Fast && (Stock && Nutrients);
        break;

    }

    result.printCollection();
    //window.printCollection(&result);
    if(result.getSize() > 0){
        Dialog window;
        window.setModal(true);
        window.printCollection(&result);
        window.setWindowTitle("Сommon elements");
        window.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("No common elements");
        msgBox.exec();
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Error","File is not open");
        return;
    }
    Nutrients.writeData(file_name + "_nut");
    Fast.writeData(file_name + "_fast");
    Stock.writeData(file_name + "_stoc");
}
