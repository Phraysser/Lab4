#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Класс, инкапсулирующий функции работы с файлами
class CFile {
protected:
    ifstream inFile;
    ofstream outFile;

public:
    CFile() {}

    // Открыть файл для чтения
    bool OpenRead(const string& filename) {
        inFile.open(filename);
        return inFile.is_open();
    }

    // Открыть файл для записи
    bool OpenWrite(const string& filename) {
        outFile.open(filename);
        return outFile.is_open();
    }

    // Закрыть файл
    void Close() {
        if (inFile.is_open())
            inFile.close();
        if (outFile.is_open())
            outFile.close();
    }

    // Переместить указатель файла
    void Seek(int pos) {
        inFile.seekg(pos);
    }

    // Чтение данных из файла
    bool Read(string& data) {
        char buffer[256]; // Буфер для считывания данных из файла
        inFile.getline(buffer, sizeof(buffer)); // Считываем строку из файла
        if (inFile.fail()) // Проверяем на ошибку
            return false;
        data = buffer; // Записываем считанную строку в аргумент data
        return true;
    }

    // Запись данных в файл
    void Write(const string& data) {
        outFile << data;
    }

    // Получить текущую позицию указателя в файле
    int GetPosition() {
        return inFile.tellg();
    }

    // Получить длину файла
    int GetLength() {
        inFile.seekg(0, ios::end);
        int length = inFile.tellg();
        inFile.seekg(0, ios::beg);
        return length;
    }
};

// Производный класс, представляющий файл с данными и заголовком
class CMyDataFile : public CFile {
private:
    string header;

public:
    CMyDataFile(const string& header) : header(header) {}

    // Получить заголовок файла
    string GetHeader() {
        return header;
    }
};

int main() {
    // Создаем объекты файлов
    CFile file;
    CMyDataFile myDataFile("Header: My Data");

    // Открываем файлы для чтения и записи
    if (file.OpenRead("test.txt")) {
        cout << "File opened successfully for reading." << endl;

        // Пример использования методов CFile
        string data;
        while (file.Read(data)) {
            cout << "Data from file: " << data << endl;
        }

        file.Close();
    }
    else {
        cout << "Failed to open file for reading." << endl;
    }

    if (myDataFile.OpenWrite("output.txt")) {
        cout << "File opened successfully for writing." << endl;

        // Пример использования методов CFile и CMyDataFile
        myDataFile.Write(myDataFile.GetHeader());
        myDataFile.Write("\nSome data to write to the file.");

        myDataFile.Close();
    }
    else {
        cout << "Failed to open file for writing." << endl;
    }

    return 0;
}