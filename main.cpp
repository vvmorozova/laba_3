#include "mainwindow.h"
#include <QApplication>
#include "collection.h"
#include <iostream>
#include <assert.h>

using namespace std;

void test1(){
    Collection<string> tmp;
    assert(tmp.getSize() == 0);
}

void test2(){
    Collection<string> tmp;
    tmp << string("One");
    assert(tmp.getSize() == 1);
    tmp << string("One");
    assert(tmp.getSize() == 1);

}

void test3(){
    Collection<string> tmp;
    tmp << string("One");
    assert(tmp[string("One")]);
}


void test4(){
    Collection<string> tmp;
    tmp << string("One");
    tmp << string("Two");
    tmp.deleteElement(string("One"));
    assert(tmp.getSize() == 1);
    tmp.deleteElement(string("One"));
    assert(tmp.getSize() == 1);
}


void test5(){
    Collection<string> tmp;
    tmp << string("One");
    tmp << string("Two");
    tmp.deleteElement(string("One"));
    assert(tmp[string("One")] == false);
}


void test6(){
    Collection<string> tmp;
    Collection<string> null;
    tmp << string("One");
    tmp << string("Two");
    tmp.clearAll();
    assert(tmp == null);
}


void test7(){
    Collection<string> tmp;
    Collection<string> null;
    tmp << string("One");
    tmp << string("Two");
    tmp.clearAll();
    Collection<string> gg;
    gg = (tmp && null);
    assert(gg == null);
}


void test8(){
    Collection<string> tmp;
    Collection<string> null;
    tmp << string("One");
    tmp << string("Two");

    null << string("One");
    null << string("Two");
    assert((tmp && null) == null);

}


void test9(){
    Collection<string> tmp;
    Collection<string> null;
    tmp << string("One");
    tmp << string("Two");

    null << string("One");
    null << string("Two");
    assert(tmp == null);

    tmp << string("blaBla");

    assert(!(tmp==null));
}


void test10(){
    Collection<string> tmp;
    tmp << string("OneOne");
    tmp << string("TwoTwo");
    tmp.writeData(QString("test.buc"));

    Collection<string> copy;
    copy.readData(QString("test.buc"));
    assert(copy == tmp);

}

void test(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}


int main(int argc, char *argv[]){
    test();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("List");
    w.show();
    return a.exec();
}
