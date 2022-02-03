#include "searchengine.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

SearchEngine::SearchEngine(char *SFileName, char *NewFileName, char *data, int number)//�����������, ��������� ����� � ��������� ����� ���������
{
    SFile = fopen(SFileName, "rb");
    NewFile = fopen(NewFileName, "wb");
    strcpy(Info,data);
    switchchoice = number;
}
SearchEngine::~SearchEngine()                                               //����������, ��������� ��� �����, ������� ��������� � ���, ��� ����� ��������
{
    fclose(SFile);
    fclose(NewFile);
}
bool SearchEngine::NextMessageFounder()                                     //���� ������ ���������� ���������
{
    char str[5000];
    while (!feof(SFile))
    {
        fgets(str,5000,SFile);
        if ((str[0]=='�')&&(str[1]=='�')&&(str[2]=='�')&&(str[3]=='�')&&(str[4]=='�'))
        {
            fgetpos (SFile,&pos);
            return true;
        }
        else if (feof(SFile))
        {
            return false;
        }
    }
}
bool SearchEngine::IfCatch()                                                //������� ������ ���������� � ���������
{
    char str[5000];
    switch (switchchoice)
        {
    case 1:                                                                 //�� ����� ���������
        fgets(str,5000,SFile);
        if ((str[18]==Info[0])&&(str[19]==Info[1])&&(str[20]==Info[2]))
        {
            return true;
        }
        else return false;
    case 2:                                                                 //�����������
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if ((str[14]==Info[0])&&(str[15]==Info[1])&&(str[16]==Info[2])&&(str[17]==Info[3])&&(str[18]==Info[4])&&(str[19]==Info[5])&&(str[20]==Info[6])&&(str[21]==Info[7])&&(str[22]==Info[8])&&(str[23]==Info[9])&&(str[24]==Info[10])&&(str[25]==Info[11])&&(str[26]==Info[12])&&(str[27]==Info[13])&&(str[28]==Info[14])&&(str[29]==Info[15])&&(str[30]==Info[16])&&(str[31]==Info[17]))
        {
            return true;
        }
        else return false;
    case 3:                                                                 //����� ������
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if (str[13]=='4')
        {
            fgets(str,5000,SFile);
            if ((str[0]=='�')&&(str[1]=='�')&&(str[2]=='�'))
            {
                return false;
            }
            fgets(str,5000,SFile);
            fgets(str,5000,SFile);
            fgets(str,5000,SFile);
            if((Info[0]==str[14])&&(Info[1]==str[15])&&(Info[2]==str[16]))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if ((str[13]=='2')||(str[13]=='3'))
        {
            fgets(str,5000,SFile);
            if ((str[0]=='�')&&(str[1]=='�')&&(str[2]=='�'))
            {
                return false;
            }
            fgets(str,5000,SFile);
            fgets(str,5000,SFile);
            fgets(str,5000,SFile);
            fgets(str,5000,SFile);
            if((Info[0]==str[14])&&(Info[1]==str[15])&&(Info[2]==str[16]))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else return false;
    case 4:                                                                 //���������� ���������
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if ((str[0]=='�')&&(str[1]=='�')&&(str[2]=='�'))
        {
            return false;
        }
        for (;;)
        {
            fgets(str,5000,SFile);
            if ((str[0]=='�')&&(str[1]=='�')&&(str[2]=='�')&&(str[3]=='�')&&(str[4]=='�'))
            {
                for(;;)
                {
                    fgets(str,5000,SFile);
                    if ((str[0]==Info[0])&&(str[1]==Info[1])&&(str[2]==Info[2])&&(str[3]==Info[3])&&(str[4]==Info[4])&&(str[5]==Info[5])&&(str[6]==Info[6])&&(str[7]==Info[7]))
                    {
                        return true;
                    }
                    if ((str[0]=='_')&&(str[1]=='_')&&(str[2]=='_'))
                    {
                        return false;
                        break;
                    }
                }
            }
        }
        return false;
    }
}
void SearchEngine::converter()                                              //��������� ���������
{
    char str[5000];
    fputs("\n����� ���������!\n",NewFile);
    fsetpos(SFile, &pos);
    do
    {
        fgets(str,5000,SFile);
        fputs(str,NewFile);
    }
    while ((str[0]!='_')&&(str[1]!='_')&&(str[2]!='_'));
}
void SearchEngine::build()                                                  //���������� ���� ������ ������.
{
    do
    {
        if (NextMessageFounder())
        {
            if (IfCatch())
            {
                converter();
            }
        }
    }
    while (!feof(SFile));
}

