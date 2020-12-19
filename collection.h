#ifndef COLLECTION_H
#define COLLECTION_H
#include <iostream>
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>


template <class T>
class Collection{
public:

    Collection();   //default constructor
    Collection(const Collection& copy); //copy constructor
    ~Collection(); //destructor

    void clearAll(); //delete all elements
    bool deleteElement(const T& value); //delete element T

    T getWithIndex(const int index) const;
    bool possibleIndex(const int index) const;
    bool isEqual(const T& value);

    int getSize() const; //return number of items
    int getbuffer_size() const;
    int getsize_all_non_nullptr() const;

    void writeData(QString path) const; // save in file
    void readData(QString path); // write from file

    void printCollection() const;

    bool operator[](const T &right) const;
    Collection<T> operator<<(const T &value);
    bool operator==(const Collection &value) const;
    const Collection<T> operator&&(const Collection &second);
    Collection<T>& operator=(const Collection& value);     // copying assignment operator

private:
    static const int default_size = 8; // default size of table
    constexpr static const double rehash_size = 0.75; // coeff increasing of table

    struct Node
        {
            T value;
            bool state; // if state = false, array item was deleted
            Node(const T& value_) : value(value_), state(true) {}
        };

    Node** arr; //array of Node*
    int size; // number of elements of aaray without deleted
    int buffer_size; // memory for tableы
    int size_all_non_nullptr; // number of elements of array with deleted

    int HashFunction(const std::string& s, int table_size, const int key) const;
    void Resize();
    void Rehash();
    bool Add(const T &value);



};

#endif // COLLECTION_H
