#include "decoder.h"
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
decoder::decoder(char *inputname, char *outputname)                         //Конструктор (открывает таблицы и файлы для чтения и записи)
{
    out = fopen(outputname, "rb");
    in = fopen(inputname, "wb");
    A = fopen("Table A.txt\0", "rt");
    B = fopen("Table B.txt\0", "rt");
    C = fopen("Table C.txt\0", "rt");
    D = fopen("Table D (no space).txt\0", "rt");
    centers = fopen("Centers.txt\0", "rt");
    subcenters = fopen("SubCenters.txt\0", "rt");
}
decoder::~decoder()                                                         //Деструктор (Закрывает все файлы и таблицы, выводит сообщение о том, что расшифрровка завершена)
{
    fclose(in);
    fclose(out);
    fclose(A);
    fclose(B);
    fclose(C);
    fclose(D);
    fclose(centers);
    fclose(subcenters);
}
void decoder::Zap()                                                         //Перенос числа из зашифрованного файла в файл, который будет расшифрован
{
    char c;
    c=fgetc(out);
    long int number=0;
    if ((int)c>0)                                               //В входящем файле тип char принимает значения от -128 до 127, поэтому, если число отрицательное, добавляем 256
    {
        number=(int)c;
    }
    else
    {
        number=(int)c+256;
    }
    if (number==32)
    {
        fputs("0",in);                                          //В зашифрованном файле по непонятной мне причине вместо 0 выходит пробел, поэтому, если number=32, то выводим 0 в файл
    }
    else
    {
        long int k=0,zam=number;                                //Иначе добавляем число поэлементно, то есть, если number = 132, то сначала в файл идет 1, потом 3, потом 2
        while (zam)
        {
            zam/=10;
            k++;
        }
        char chnumber[k];
        zam=number;
        for (int i=k;i>0;i--)
        {
            chnumber[i]=(zam%10)+48;
            zam/=10;
        }
        for (int i=1;i<=k;i++)
        {
            fputc(chnumber[i],in);
        }
        for (int i=0;i<=k;i++)
        {
            chnumber[i]=48;
        }
        number=0;
    }
}
void decoder::Zap(char c)                                                   //Перегруженная функция Zap, которая передает в файл принимаемый символ
{
    long int number=0;
    if ((int)c>0)                                               //В входящем файле тип char принимает значения от -128 до 127, поэтому, если число отрицательное, добавляем 256
    {
        number=(int)c;
    }
    else
    {
        number=(int)c+256;
    }
    if (number==32)
    {
        fputs("0",in);                                          //В зашифрованном файле по непонятной мне причине вместо 0 выходит пробел, поэтому, если number=32, то выводим 0 в файл
    }
    else
    {
        long int k=0,zam=number;                                //Иначе добавляем число поэлементно, то есть, если number = 132, то сначала в файл идет 1, потом 3, потом 2
        while (zam)
        {
            zam/=10;
            k++;
        }
        char chnumber[k];
        zam=number;
        for (int i=k;i>0;i--)
        {
            chnumber[i]=(zam%10)+48;
            zam/=10;
        }
        for (int i=1;i<=k;i++)
        {
            fputc(chnumber[i],in);
        }
        for (int i=0;i<=k;i++)
        {
            chnumber[i]=48;
        }
        number=0;
    }
}
void decoder::PushNumber(long int num)                                      //Добавление цифр(числа) в выходящий файл.
{
    long int k=0,zam=num;
    while (zam)
    {
        zam/=10;
        k++;
    }
    char chnumber[k];
    zam=num;
    for (int i=k;i>0;i--)
    {
        chnumber[i]=(zam%10)+48;
        zam/=10;
    }
    for (int i=1;i<=k;i++)
    {
        fputc(chnumber[i],in);
    }
}
long int decoder::GetDouble()                                               //Функция получения числа из 2 байт зашифрованного файла
{
    char c;
    int number1=0;
    char binnumchar[16];
    long int number=0,binnumber[2]={0};
    for (int i=0;i<2;i++)                                       //Сначала получаем элементы из зашифрованного файла
    {
        c=fgetc(out);
        if ((int)c!=32)
        {
            if ((int)c>0)
            {
                number1=(int)c;
            }
            else
            {
                number1=(int)c+256;                             //Затем получаем из них числа
            }
            int bin = 0, k = 1;
            while (number1)                                     //Затем эти числа переводим в 2 систему счисления
            {
                bin += (number1 % 2) * k;
                k *= 10;
                number1 /= 2;
            }
            binnumber[i]=bin;                                   //И уже числа в 2 системе счисления добавляем в массив
        }
    }
    for (int i=0;i<15;i++)                                      //Создаем массив типа char и заполняем его нулями
    {
        binnumchar[i]=48;
    }
    if (binnumber[0]!=0)                                        //Поразрядно переносим двоичные числа в символьный массив 2 раза
    {
        long int zam;
        zam=binnumber[0];
        for (int i=7;i>=0;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    if (binnumber[1]!=0)                                        //Все это нужно для получения двоичного числа состоящего из 2 байтов
    {
        long int zam;
        zam=binnumber[1];
        for (int i=15;i>=8;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    for (int i=0,j=15;i<16;i++,j--)                             //Поразрядно переводим массив содержащий большое двоичное число в число типа long int
    {
        if ((int)binnumchar[i]==49)
            number+=pow(2,j);
    }
    return number;
}
long int decoder::GetTriple()                                               //Функция получения числа из 3 байт зашифрованного файла (2 функции, необходимые для программы)
{
    char c;
    int number1=0;
    char binnumchar[24];
    long int number=0,binnumber[3]={0};
    for (int i=0;i<3;i++)                                       //Функция полностью идентична предыдущей, за исключением того, что числа получается 3
    {
        c=fgetc(out);
        if ((int)c!=32)
        {
            if ((int)c>0)
            {
                number1=(int)c;
            }
            else
            {
                number1=(int)c+256;
            }
            int bin = 0, k = 1;
            while (number1)
            {
                bin += (number1 % 2) * k;
                k *= 10;
                number1 /= 2;
            }
            binnumber[i]=bin;
        }
    }
    for (int i=0;i<23;i++)
    {
        binnumchar[i]=48;
    }
    if (binnumber[0]!=0)
    {
        long int zam;
        zam=binnumber[0];
        for (int i=7;i>=0;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    if (binnumber[1]!=0)
    {
        long int zam;
        zam=binnumber[1];
        for (int i=15;i>=8;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    if (binnumber[2]!=0)
    {
        long int zam;
        zam=binnumber[2];
        for (int i=23;i>=16;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    for (int i=0,j=23;i<24;i++,j--)
    {
        if ((int)binnumchar[i]==49)
            number+=pow(2,j);
    }
    return number;                                              //Возвращаем значение
}
bool decoder::NewMessageFounder()                                           //Ищет -New Message-, проверяет достигнут ли конец файла
{
    char str[5000];
    while (!feof(out))
    {
        fgets(str,5000,out);
        if (((str[1]=='-')&&(str[2]=='N')&&(str[3]=='e')&&(str[4]=='w'))||((str[0]=='-')&&(str[1]=='N')&&(str[2]=='e')&&(str[3]=='w')))
        {
            return true;
        }
        else if (feof(out))
        {
            return false;
        }
    }
}
void decoder::ZeroPoint()                                                   //Полная расшифровка раздела 0
{
    char str[5000];
    fputs("\n_______________________________________",in);                      //Начинаем заполнение сообщения
    fputs("\nНовое сообщение!\n",in);                                           //Основная информация о файле
    fgets(str,5000,out);
    fputs("Номер сообщения - ",in);
    fputc(str[0],in);
    fputc(str[1],in);
    fputc(str[2],in);
    fputs("\nОтправитель - ",in);
    fgets(str,5000,out);
    for (int i=0;i<=17;i++)
    {
        fputc(str[i],in);
    }
    fputs("\nКодировка - ", in);
    fgets(str,5,out);
    fputs("BUFR",in);
    fputs("\nДлина сообщения - ",in);
    messageLenght=GetTriple();
    PushNumber(messageLenght);
    fputs("\nBUFR версия: ",in);
    version=(int)fgetc(out);
    PushNumber(version);
}
void decoder::FirstPoint()                                                  //Полная расшифровка раздела 1
{
    long int sec1Lenght=0;
    fputs("\nРаздел 1:\n",in);                                                  //Первый раздел
    fputs("Длина раздела: ",in);
    sec1Lenght=GetTriple();
    PushNumber(sec1Lenght);
    fputs("\nЭталонная таблица для кода BUFR - ",in);
    char c;
    c=fgetc(out);
    Zap(c);
    if (c==' ')
    {
        fputs(" - Метеорология",in);
    }
    else
    {
        fputs(" - Не метеорологические данные",in);
    }
    if ((version==3)||(version==2))
    {
        int numcen=0,numsub=0;                                                  //Заполнение центра и подцентра
        char c1=0,c2=0,center[3],subcenter[6];                                  //Во второй и третей версии BUFR сообщения сначала идет подцентр, а потом уже центр, поэтому пришлось брать сразу 2 элемента и работать с ними
        c2=fgetc(out);
        c1=fgetc(out);
        if ((int)c1>0)
        {
            numcen=(int)c1;
        }
        else
        {
            numcen=(int)c1+256;
        }
        if ((int)c2>0)
        {
            numsub=(int)c2;
        }
        else
        {
            numsub=(int)c2+256;
        }
        for (int i=0;i<6;i++)                                                   //Для использования таблицы subcenter должен содержать в себе: первые 3 символа - номер центра, последние 3 - номер подцентра
        {
            subcenter[i]=48;
        }
        for (int i=0;i<3;i++)
        {
            center[i]=48;
        }
        for (int i=2;i>=0;i--)                                                  //Заполнение массивов
        {
            if (numcen!=0)
            {
                center[i]=numcen%10+48;
                numcen/=10;
            }
        }
        for (int i=5;i>=0;i--)
        {
            if (numsub!=0)
            {
                subcenter[i]=numsub%10+48;
                numsub/=10;
            }
        }
        if ((center[0]!=49)&&(center[0]!=50))                                   //Корректировка ошибочных результатов с помощью добавления дополнительных условий
        {
            subcenter[0]=48;
        }
        else subcenter[0]=center[0];
        if (center[1]==48)
        {
            subcenter[1]=48;
        }
        else subcenter[1]=center[1];
        if (center[2]==48)
        {
            subcenter[2]=48;
        }
        else subcenter[2]=center[2];
        fputs("\nНомер подцентра: ",in);
        char string[10],output[100];
        while (!feof(subcenters))
        {
            fgets(string,7,subcenters);
            if ((subcenter[0]==string[0])&&(subcenter[1]==string[1])&&(subcenter[2]==string[2])&&(subcenter[3]==string[3])&&(subcenter[4]==string[4])&&(subcenter[5]==string[5]))
            {
                fputc(subcenter[3],in);
                fputc(subcenter[4],in);
                fputc(subcenter[5],in);
                fputs(" -",in);
                fgets(output,100,subcenters);
                fputs(output,in);
                break;

            }
            else fgets(output,100,subcenters);
        }
        if (feof(subcenters))                                                    //Если файл закончился, то номер подцентр отсутствует
        {
            fputs("0 - Подцентр отсутствует или не указан в таблице.",in);
        }
        fputs("\nНомер центра: ",in);
        char String[4], Output[100];
        while (!feof(centers))
        {
            fgets(String,4,centers);
            if ((String[0]==center[0])&&(String[1]==center[1])&&(String[2]==center[2]))
            {
                fputc(center[0],in);
                fputc(center[1],in);
                fputc(center[2],in);
                fputs(" -",in);
                fgets(Output,100,centers);
                Output[strlen(Output)-1]=46;
                fputs(Output,in);
                break;

            }
            else fgets(Output,100,centers);
        }
        c=fgetc(out);
        fputs("\nПоследовательный номер обновления: ",in);                      //Продолжаем расшифровку и заполнение файла
        Zap(c);
        long int number=0;
        if (c==' ')
        {
            fputs(" - без изменений",in);
        }
        c=fgetc(out);
        if ((int)c>0)
        {
            number=(int)c;
        }
        else
        {
            number=(int)c+256;
        }
        if (number>=128)                                                        //Если первый бит равен 1, то сообщение содержит раздел
        {
            fputs("\nСообщение содержит раздел 2.",in);
            IfSection2=true;
        }
        else
        {
            fputs("\nСообщение не содержит раздел 2.",in);
            IfSection2=false;
        }
        fputs("\nКатегория данных: ",in);
        Zap();
        fputs("\nПодкатегория данных: ",in);
        Zap();
        fputs("\nНомер версии эталонной таблицы: ",in);
        Zap();
        fputs("\nНомер локальной таблицы: ",in);
        Zap();
        fputs("\nГод текущего века: ",in);
        Zap();
        fputs("\nМесяц: ",in);
        Zap();
        fputs("\nДень: ",in);
        Zap();
        fputs("\nЧас: ",in);
        Zap();
        fputs("\nМинута: ",in);
        Zap();
        if (sec1Lenght>17)                                                      //Вывод локальных данных, используемых центрами
        {
            fputs("\nДанные для местного использования центрами АОД: ",in);
            while (sec1Lenght!=17)
            {
                Zap();
                fputs(" ",in);
                sec1Lenght--;
            }
        }
    }
    else if (version==4)
    {
        char center[3],subcenter[6];
        long int numb1=GetDouble(), numb2=GetDouble();
        fputs("\nНомер центра: ",in);                                           //Также заполняем центры и подцентры
        for (int i=0;i<6;i++)                                                   //Изменение данных для испозования таблицы центров
        {
            subcenter[i]=48;
        }
        for (int i=0;i<3;i++)
        {
            center[i]=48;
        }
        for (int i=2;i>=0;i--)
        {
            if (numb1!=0)
            {
                center[i]=numb1%10+48;
                numb1/=10;
            }
        }
        char String[4], Output[100];
        while (!feof(centers))
        {
            fgets(String,4,centers);
            if ((String[0]==center[0])&&(String[1]==center[1])&&(String[2]==center[2]))
            {
                fputc(center[0],in);
                fputc(center[1],in);
                fputc(center[2],in);
                fputs(" -",in);
                fgets(Output,100,centers);
                Output[strlen(Output)-1]=46;
                fputs(Output,in);
                break;

            }
            else
            {
                fgets(Output,100,centers);
            }
        }
        fputs("\nНомер подцентра: ",in);
        for (int i=5;i>=0;i--)                                                  //Изменение данных для использования таблицы подцентров
        {
            if (numb2!=0)
            {
                subcenter[i]=numb2%10+48;
                numb2/=10;
            }
        }
        if ((center[0]!=49)&&(center[0]!=50))
        {
            subcenter[0]=48;
        }
        else subcenter[0]=center[0];
        if (center[1]==48)
        {
            subcenter[1]=48;
        }
        else subcenter[1]=center[1];
        if (center[2]==48)
        {
            subcenter[2]=48;
        }
        else subcenter[2]=center[2];
        char string[10],output[100];
        while (!feof(subcenters))
        {
            fgets(string,7,subcenters);
            if ((subcenter[0]==string[0])&&(subcenter[1]==string[1])&&(subcenter[2]==string[2])&&(subcenter[3]==string[3])&&(subcenter[4]==string[4])&&(subcenter[5]==string[5]))
            {
                fputc(subcenter[3],in);
                fputc(subcenter[4],in);
                fputc(subcenter[5],in);
                fputs(" -",in);
                fgets(output,100,subcenters);
                fputs(output,in);
                break;

            }
            else fgets(output,100,subcenters);
        }
        if (feof(subcenters))
        {
            fputs("0 - Подцентр отсутствует или не указан в таблице",in);                                  //Продолжаем заполнять файл данными
        }
        c=fgetc(out);
        fputs("\nПоследовательный номер обновления: ",in);
        Zap(c);
        if (c==' ')
        {
            fputs(" - без изменений",in);
        }
        c=fgetc(out);
        long int number=0;
        if ((int)c>0)
        {
            number=(int)c;
        }
        else
        {
            number=(int)c+256;
        }
        if (number>=128)
        {
            fputs("\nСообщение содержит раздел 2.",in);                         //Проверка на второй раздел
            IfSection2=true;
        }
        else
        {
            fputs("\nСообщение не содержит раздел 2.",in);
            IfSection2=false;
        }
        fputs("\nКатегория данных: ",in);
        Zap();
        fputs("\nМеждународная подкатегория данных: ",in);
        Zap();
        fputs("\nЛокальная подкатегория данных: ",in);
        Zap();
        fputs("\nНомер версии эталонной таблицы: ",in);
        Zap();
        fputs("\nНомер локальной таблицы: ",in);
        Zap();
        fputs("\nГод: ",in);
        PushNumber(GetDouble());
        fputs("\nМесяц: ",in);
        Zap();
        fputs("\nДень: ",in);
        Zap();
        fputs("\nЧас: ",in);
        Zap();
        fputs("\nМинута: ",in);
        Zap();
        fputs("\nСекунда: ",in);
        Zap();
        if (sec1Lenght>22)                                                      //Вывод данных для местного использования
        {
            fputs("\nДанные для местного использования центрами АОД: ",in);
            while (sec1Lenght!=22)
            {
                Zap();
                fputs(" ",in);
                sec1Lenght--;
            }
        }
    }
}
void decoder::SecondPoint()                                                 //Полная расшифровка раздела 2, если он существует
{
    fputs("\nРаздел 2: ",in);                                               //Выводим данные о нем
    fputs("\nДлина раздела: ",in);
    long int sec2Lenght;
    sec2Lenght=GetTriple();
    PushNumber(sec2Lenght);
    fgetc(out);
    if (sec2Lenght>4)
    {
        fputs("\nДанные для местного использования центрами АОД: ",in);     //Вывод локальных данных
        while (sec2Lenght!=4)
        {
            Zap();
            fputs(" ",in);
            sec2Lenght--;
        }
    }
}
void decoder::ThirdPoint()                                                  //Расшифровка раздела 3 до описателей (включительно)
{
    long int number;
    char c;
    fputs("\nРаздел 3: ",in);                                                   //Раздел 3
    fputs("\nДлина раздела: ",in);                                               //Заполнение выходящего файла (раздел, данные и тд)
    long int sec3Lenght;
    sec3Lenght=GetTriple();
    PushNumber(sec3Lenght);
    fgetc(out);
    fputs("\nКоличество поднаборов данных: ",in);
    long int opisateli;
    opisateli=GetDouble();
    PushNumber(opisateli);
    c=fgetc(out);
    if ((int)c>0)
    {
        number=(int)c;
    }
    else
    {
        number=(int)c+256;
    }
    if (number==128)
    {
        fputs("\nДанные наблюдения без сжатия",in);
    }
    else if (number==192)
    {
        fputs("\nДанные наблюдения с сжатием",in);
    }
    else if (number==64)
    {
        fputs("\nДругие данные с сжатием",in);
    }
    else
    {
        fputs("\nДругие данные без сжатия",in);
    }
    if (sec3Lenght>7)
    {
        long int zam=0;
        fputs("\nСодержание сообщения: \n",in);                                   //Начало работы с описателями
        while (sec3Lenght>8)
        {
            char binnumber[17],F=0,X[2],Y[3];
            int x=0,y=0;
            number=GetDouble();                                                 //Получаем число из 2 байт
            zam=number;
            for(int i=0;i<16;i++)                                               //Преобразуем числа так, чтобы
            {                                                                   //Что у нас поучается массив типа char, содержащий 2 двоичных числа посимвольно
                binnumber[i]=48;
            }
            int j=15;
            while(zam>0)
            {
                binnumber[j]=zam%2+48;
                zam/=2;
                j--;
            }
            F=(binnumber[0]-48)*2+(binnumber[1]-48)+48;                         //Получем F,X,Y для работы с таблицей
            x=(binnumber[2]-48)*32+(binnumber[3]-48)*16+(binnumber[4]-48)*8+(binnumber[5]-48)*4+(binnumber[6]-48)*2+(binnumber[7]-48);
            X[1]=x%10+48;
            x/=10;
            X[0]=x%10+48;
            y=(binnumber[8]-48)*128+(binnumber[9]-48)*64+(binnumber[10]-48)*32+(binnumber[11]-48)*16+(binnumber[12]-48)*8+(binnumber[13]-48)*4+(binnumber[14]-48)*2+(binnumber[15]-48);
            for (int i=2;i>=0;i--)
            {
                if (y!=0)
                {
                    Y[i]=y%10+48;
                    y/=10;
                }
                else Y[i]=48;
            }
            fputc(F,in);                                                        //Выводим F,X,Y в файл
            fputs(" ",in);
            fputc(X[0],in);
            fputc(X[1],in);
            fputs(" ",in);
            fputc(Y[0],in);
            fputc(Y[1],in);
            fputc(Y[2],in);
            fputs(" - ",in);
            if (F==48)                                                          //Если F=0, то
            {
                char String[11], Output[250];
                while (!feof(B))                                                //Пока таблица не закончился
                {
                    fgets(String,9,B);                                          //Получаем строку из таблицы
                    if((F==String[0])&&(X[0]==String[2])&&(X[1]==String[3])&&(Y[0]==String[5])&&(Y[1]==String[6])&&(Y[2]==String[7])) //Сравниваем данные из описателя и строки из таблицы
                    {
                        fgets(Output,250,B);                                    //Получаем оставшиеся данные из строки таблицы
                        fputs(Output,in);                                       //Выводим эту строку в выходящий файл
                        rewind(B);                                              //Возвращаемся в начало таблицы
                        break;
                    }
                    fgets(Output,250,B);                                        //Если данные не совпали, то доходим до конца строки, чтобы перейти на следующую
                }
                if (feof(B))                                                    //Если данные не были найдены в таблице, то вывести "Данные не найдены"
                {
                    fputs("Данные не найдены в таблице\n",in);
                }
                rewind(B);                                                      //Возвращаемся в начало таблицы
            }
            if (F==49)                                                          //Если F=1, то (проделываем абсолютно тоже самое, что и для F=0)
            {
                char String[11], Output[250];
                while (!feof(A))
                {
                    fgets(String,4,A);
                    if((X[0]==String[1])&&(X[1]==String[2]))
                    {

                        fgets(Output,250,A);
                        fputs(Output,in);
                        rewind(A);
                        break;
                    }
                    fgets(Output,250,A);
                }
                if(feof(A))
                {
                    fputs("Данные не найдены в таблице\n",in);
                }
                rewind(A);
            }
            if (F==50)                                                          //Если F=2, то (проделываем абсолютно тоже самое, что и для F=0)
            {
                char String[11], Output[250];
                while (!feof(C))
                {
                    fgets(String,9,C);
                    if (((X[0]==48)&&(X[1]>=49)&&(X[1]<=54))||((X[0]==50)&&(X[1]==49))) //За исключением корректировки для использования таблицы
                    {
                        Y[0]=89; Y[1]=89; Y[2]=89;
                    }
                    if((F==String[0])&&(X[0]==String[2])&&(X[1]==String[3])&&(Y[0]==String[5])&&(Y[1]==String[6])&&(Y[2]==String[7]))
                    {
                        fgets(Output,250,C);
                        fputs(Output,in);
                        rewind(C);
                        break;
                    }
                    fgets(Output,250,C);
                }
                if(feof(C))
                {
                    fputs("Данные не найдены в таблице\n",in);
                }
                rewind(C);
            }
            if (F==51)                                                          //Если F=51, то
            {
                char String[7],Output[2000];
                while (!feof(D))                                                //Пока файл таблицы не закончится
                {
                    fgets(String,7,D);                                          //Берем строку из таблицы
                    if ((F==String[0])&&(X[0]==String[1])&&(X[1]==String[2])&&(Y[0]==String[3])&&(Y[1]==String[4])&&(Y[2]==String[5]))  //Сравниваем значения описателя с таблицей
                    {
                        fgets(Output,2000,D);                                   //Тогда берем оставшуюся часть строки таблицы
                        int count=strlen(Output);
                        count=(count - 1)/6;                                    //Считаем количество оставшихся элементов
                        for (int i=0;i<count;i++)                               //Пока строка не кончится
                        {
                            F=Output[i*6];                                      //Получаем описатели из строки
                            X[0]=Output[i*6+1];
                            X[1]=Output[i*6+2];
                            Y[0]=Output[i*6+3];
                            Y[1]=Output[i*6+4];
                            Y[2]=Output[i*6+5];
                            if (F==48)                                          //И используем точно такие же условия, что и для (F=0),(F=1),(F=2)
                            {
                                char Str[11], out[250];
                                while (!feof(B))
                                {
                                    fgets(Str,9,B);
                                    if((F==Str[0])&&(X[0]==Str[2])&&(X[1]==Str[3])&&(Y[0]==Str[5])&&(Y[1]==Str[6])&&(Y[2]==Str[7]))
                                    {
                                        fgetc(B);
                                        fgets(out,250,B);
                                        fputs(out,in);
                                        rewind(B);
                                        break;
                                    }
                                    fgets(out,250,B);
                                }
                                if (feof(B))
                                {
                                    fputs("Данные не найдены в таблице\n",in);
                                }
                                rewind(B);
                            }
                            if (F==49)
                            {
                                char Str[11], out[250];
                                while (!feof(A))
                                {
                                    fgets(Str,4,A);
                                    if((X[0]==Str[1])&&(X[1]==Str[2]))
                                    {
                                        fgetc(A);
                                        fgets(out,250,A);
                                        fputs(out,in);
                                        rewind(A);
                                        break;
                                    }
                                    fgets(out,250,A);
                                }
                                if(feof(A))
                                {
                                    fputs("Данные не найдены в таблице\n",in);
                                }
                                rewind(A);
                            }
                            if (F==50)
                            {
                                char Str[11], out[250];
                                while (!feof(C))
                                {
                                    fgets(Str,9,C);
                                    if (((X[0]==48)&&(X[1]>=49)&&(X[1]<=54))||((X[0]==50)&&(X[1]==49)))
                                    {
                                        Y[0]=89; Y[1]=89; Y[2]=89;
                                    }
                                    if((F==Str[0])&&(X[0]==Str[2])&&(X[1]==Str[3])&&(Y[0]==Str[5])&&(Y[1]==Str[6])&&(Y[2]==Str[7]))
                                    {
                                        fgetc(C);
                                        fgets(out,250,C);
                                        //Здесь были исправления.
                                        fputs(out,in);
                                        rewind(C);
                                        break;
                                    }
                                    fgets(Output,250,C);
                                }
                                if(feof(C))
                                {
                                    fputs("Данные не найдены в таблице\n",in);
                                }
                                rewind(C);
                            }
                        }
                    }
                    else                                                        //Если данные не были найдены, то проходим строку до конца
                    {
                        fgets(Output,2000,D);
                    }
                }
                if (feof(D))                                                    //Если файл закончился, то выводим, что данных нет в таблице
                {
                    fputs("Данные не найдены в таблице \n",in);
                }
                rewind(D);
            }
            sec3Lenght=sec3Lenght-2;
            number=0;
        }
    }
}
void decoder::RewindAll()                                                   //Возвращает калитку в начало у всех файлов
{
    rewind(A);
    rewind(B);
    rewind(C);
    rewind(D);
    rewind(centers);
    rewind(subcenters);
}
void decoder::FinalPoint()                                                  //Финальная сборка всех разделов вместе
{
    do
    {
        if (NewMessageFounder())
        {
            while(!feof(out))
            {
                RewindAll();
                ZeroPoint();
                if (messageLenght>=15000)
                {
                    fputs("\nОшибка!!!\n Слишком большая длина сообщения!",in);
                    break;
                }
                FirstPoint();
                if (IfSection2)
                {
                    SecondPoint();
                }
                ThirdPoint();
                if (feof(out))
                {
                    break;
                }
                break;
            }
        }
        else break;
    }
    while (!feof(out));
}
