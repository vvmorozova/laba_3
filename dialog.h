#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "collection.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void printCollection(Collection<std::string>* value);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
