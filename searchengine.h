#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include <iostream>

class SearchEngine
{
private:
    FILE *SFile;                                                             //����� ��� ��������������� �����, ��� �� ����� ����� ��������� � �������� ��� �������
    FILE *NewFile;                                                           //����� ����, ������� ��������� ��� ������
    char Info[18];
    int switchchoice;
    fpos_t pos;
public:
    SearchEngine(char *SFile,char *NewFile, char *data, int number);      //�����������, ��������� ����� � ��������� ����� ���������
    ~SearchEngine();                                                         //����������, ��������� ��� �����, ������� ��������� � ���, ��� ����� ��������
    bool NextMessageFounder();                                               //���� ������ ���������� ���������
    bool IfCatch();                                                          //������� ������ ���������
    void converter();                                                        //��������� ���������
    void build();                                                            //���������� ���� ������ ������.
};

#endif // SEARCHENGINE_H
