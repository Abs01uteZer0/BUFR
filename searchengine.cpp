#include "searchengine.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

SearchEngine::SearchEngine(char *SFileName, char *NewFileName, char *data, int number)//Конструктор, открывает файлы и принимает номер сообщения
{
    SFile = fopen(SFileName, "rb");
    NewFile = fopen(NewFileName, "wb");
    strcpy(Info,data);
    switchchoice = number;
}
SearchEngine::~SearchEngine()                                               //Деструктор, закрывает все файлы, выводит сообщение о том, что поиск завершен
{
    fclose(SFile);
    fclose(NewFile);
}
bool SearchEngine::NextMessageFounder()                                     //Ищет начало следующего сообщения
{
    char str[5000];
    while (!feof(SFile))
    {
        fgets(str,5000,SFile);
        if ((str[0]=='Н')&&(str[1]=='о')&&(str[2]=='в')&&(str[3]=='о')&&(str[4]=='е'))
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
bool SearchEngine::IfCatch()                                                //Функция поиска совпадений в сообщении
{
    char str[5000];
    switch (switchchoice)
        {
    case 1:                                                                 //на номер сообщений
        fgets(str,5000,SFile);
        if ((str[18]==Info[0])&&(str[19]==Info[1])&&(str[20]==Info[2]))
        {
            return true;
        }
        else return false;
    case 2:                                                                 //Отправитель
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if ((str[14]==Info[0])&&(str[15]==Info[1])&&(str[16]==Info[2])&&(str[17]==Info[3])&&(str[18]==Info[4])&&(str[19]==Info[5])&&(str[20]==Info[6])&&(str[21]==Info[7])&&(str[22]==Info[8])&&(str[23]==Info[9])&&(str[24]==Info[10])&&(str[25]==Info[11])&&(str[26]==Info[12])&&(str[27]==Info[13])&&(str[28]==Info[14])&&(str[29]==Info[15])&&(str[30]==Info[16])&&(str[31]==Info[17]))
        {
            return true;
        }
        else return false;
    case 3:                                                                 //Номер центра
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if (str[13]=='4')
        {
            fgets(str,5000,SFile);
            if ((str[0]=='О')&&(str[1]=='ш')&&(str[2]=='и'))
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
            if ((str[0]=='О')&&(str[1]=='ш')&&(str[2]=='и'))
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
    case 4:                                                                 //Содержание сообщения
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        fgets(str,5000,SFile);
        if ((str[0]=='О')&&(str[1]=='ш')&&(str[2]=='и'))
        {
            return false;
        }
        for (;;)
        {
            fgets(str,5000,SFile);
            if ((str[0]=='С')&&(str[1]=='о')&&(str[2]=='д')&&(str[3]=='е')&&(str[4]=='р'))
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
void SearchEngine::converter()                                              //Переносит сообщение
{
    char str[5000];
    fputs("\nНовое сообщение!\n",NewFile);
    fsetpos(SFile, &pos);
    do
    {
        fgets(str,5000,SFile);
        fputs(str,NewFile);
    }
    while ((str[0]!='_')&&(str[1]!='_')&&(str[2]!='_'));
}
void SearchEngine::build()                                                  //Соединение всех частей вместе.
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

