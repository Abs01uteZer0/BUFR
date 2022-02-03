#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include <iostream>

class SearchEngine
{
private:
    FILE *SFile;                                                             //Адрес уже расшифрованного файла, где мы хотим найти сообщения с вводимым нам номером
    FILE *NewFile;                                                           //Новый файл, который создается для вывода
    char Info[18];
    int switchchoice;
    fpos_t pos;
public:
    SearchEngine(char *SFile,char *NewFile, char *data, int number);      //Конструктор, открывает файлы и принимает номер сообщения
    ~SearchEngine();                                                         //Деструктор, закрывает все файлы, выводит сообщение о том, что поиск завершен
    bool NextMessageFounder();                                               //Ищет начало следующего сообщения
    bool IfCatch();                                                          //Сверяет номера сообщений
    void converter();                                                        //Переносит сообщение
    void build();                                                            //Соединение всех частей вместе.
};

#endif // SEARCHENGINE_H
