#include "collection.h"

template <class T>
Collection<T>::Collection(){
    buffer_size = default_size;
    size = 0;
    size_all_non_nullptr = 0;
    arr = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr[i] = nullptr;
}


template <class T>
Collection<T>::Collection(const Collection& copy){
    buffer_size = copy.getbuffer_size();
    size = copy.getSize();
    size_all_non_nullptr = copy.getsize_all_non_nullptr();

    arr = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i){
        if(copy.possibleIndex(i)){
            arr[i] = new Node(copy.getWithIndex(i));
        }else{
            arr[i] = nullptr;
        }
    }
}


template <class T>
Collection<T>::~Collection(){
    for (int i = 0; i < buffer_size; ++i)
        if (arr[i])
            delete arr[i];
    delete[] arr;
}


template <class T>
void Collection<T>::clearAll(){
    for (int i = 0; i < buffer_size; ++i)
        if (arr[i])
            arr[i]->state = false;
    size = 0;
}

template <class T>
bool Collection<T>::deleteElement(const T& value){
    int h1 = HashFunction(value, buffer_size, buffer_size - 1); // start position
    int h2 = HashFunction(value, buffer_size, buffer_size + 1); // step in table

    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value == value && arr[h1]->state)
        {
            arr[h1]->state = false;
            --size;
            return true;
        }
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    return false;
}

template <class T>
T Collection<T>::getWithIndex(const int index) const{
    if(arr[index] != nullptr && arr[index]->state){
        return arr[index]->value;
    }else{
        return NULL;
    }
}


template <class T>
bool Collection<T>::possibleIndex(const int index) const{
    if(arr[index] != nullptr && arr[index]->state){
        return true;
    }else{
        return false;
    }
}




template <class T>
int Collection<T>::getSize() const{
    return size;
}

template <class T>
int Collection<T>::getbuffer_size() const{
    return buffer_size;
}

template <class T>
int Collection<T>::getsize_all_non_nullptr() const{
    return size_all_non_nullptr;
}

template <class T>
void Collection<T>::writeData(QString path) const{
    if(size > 0){
        QFile file(path);

        if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);

            out << size << endl;
            for(int i = 0; i < buffer_size; i++){
                if(arr[i] != nullptr && arr[i]->state){
                    out << QString::fromUtf8(arr[i]->value.c_str()) << endl;
                }
            }
        }
    }
}

template <class T>
void Collection<T>::readData(QString path){
    QFile file(path);
    QString tmp;

    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        int cnt;
        in >> cnt;
        for(int i = 0; i < cnt; i++){
            in >> tmp;
            Add(tmp.toUtf8().constData());
        }
    }
}

template <class T>
void Collection<T>::printCollection() const{
    for(int i = 0; i < buffer_size; i++){
        if(arr[i] != nullptr && arr[i]->state){
            std::cout << arr[i]->value << std::endl;
        }
    }
}

template <class T>
bool Collection<T>::Add(const T &value){
    if (size + 1 > int(rehash_size * buffer_size))
        Resize();
    else if (size_all_non_nullptr > 2 * size)
        Rehash(); // rehash cause of too many deleted items

    int h1 = HashFunction(value, buffer_size, buffer_size - 1); // start position
    int h2 = HashFunction(value, buffer_size, buffer_size + 1); // step table

    int i = 0;
    int first_deleted = -1; // remember first deleteed item

    while (arr[h1] != nullptr && i < buffer_size){
        if (arr[h1]->value == value && arr[h1]->state)
            return false; // can not enter repeated element

        if (!arr[h1]->state && first_deleted == -1) // place for new
            first_deleted = h1;

        h1 = (h1 + h2) % buffer_size;
        i++;
    }

    if (first_deleted == -1){ //if there is no place for new create new Node
        arr[h1] = new Node(value);
        this->size_all_non_nullptr++; // if there is a space write that the place is occuped
    }
    else{
        arr[first_deleted]->value = value;
        arr[first_deleted]->state = true;
    }
    this->size++; // in any varian increase number in table

    return true;
};


template <class T>
bool Collection<T>::operator[](const T &value) const{
    int h1 = HashFunction(value, buffer_size, buffer_size - 1); // start position
    int h2 = HashFunction(value, buffer_size, buffer_size + 1); // step in table
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size){
        if (arr[h1]->value == value && arr[h1]->state)
            return true; // такой элемент есть
        h1 = (h1 + h2) % buffer_size;
        ++i; // if i >=  buffer_size, then we ckecked all the cells.
    }
    return false;
}


template <class T>
Collection<T> Collection<T>::operator<<(const T &value){
    Add(value);
    return Collection(*this);
}


template <class T>
bool Collection<T>::operator==(const Collection &value) const{
    bool result = false;
    if(this->size == value.getSize()){
        result = true;
        for(int i = 0; i < this->size; i++){
            if(arr[i]!=nullptr && arr[i]->state){
                result &= value[arr[i]->value];
            }
        }
    }
    return result;
}


template <class T>
const Collection<T> Collection<T>::operator&&(const Collection &second){
    Collection result;
    T tmp;
    for(int i = 0; i < buffer_size; i++){
        if(possibleIndex(i)){
            tmp = arr[i] -> value;
            if(second[tmp]){
                result.Add(tmp);
            }
        }
    }

    int cnt = second.getbuffer_size();
    for(int i = 0; i < cnt; i++){
        if(second.possibleIndex(i)){
            tmp = second.getWithIndex(i);
            if(this->operator[](tmp)){
                result.Add(tmp);
            }
        }
    }

    return result;
}


template <class T>
Collection<T>& Collection<T>::operator=(const Collection& value){
    buffer_size = value.getbuffer_size();
    size = value.getSize();
    size_all_non_nullptr = value.getsize_all_non_nullptr();

    arr = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i){
        if(value.possibleIndex(i)){
            arr[i] = new Node(value.getWithIndex(i));
        }else{
            arr[i] = nullptr;
        }
    }

    return *this;
}

template <class T>
int Collection<T>::HashFunction(const std::string& s, int table_size, const int key) const{
    int hash_result = 0;
    for (int i = 0; i != s.size(); ++i)
        hash_result = (key * hash_result + s[i]) % table_size;
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
};

template <class T>
void Collection<T>::Resize(){
    int past_buffer_size = buffer_size;
    buffer_size *= 2;
    size_all_non_nullptr = 0;
    size = 0;
    Node** arr2 = new Node * [buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < past_buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
            this->operator<<(arr2[i]->value); // add new elements
    }
    // delete array
    for (int i = 0; i < past_buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
};


template <class T>
void Collection<T>::Rehash(){
    size_all_non_nullptr = 0;
    size = 0;
    Node** arr2 = new Node * [buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
            this->operator<<(arr2[i]->value);
    }
    // delete array
    for (int i = 0; i < buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}


template class Collection<std::string>;

