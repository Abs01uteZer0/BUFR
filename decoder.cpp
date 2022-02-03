#include "decoder.h"
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
decoder::decoder(char *inputname, char *outputname)                         //����������� (��������� ������� � ����� ��� ������ � ������)
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
decoder::~decoder()                                                         //���������� (��������� ��� ����� � �������, ������� ��������� � ���, ��� ������������ ���������)
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
void decoder::Zap()                                                         //������� ����� �� �������������� ����� � ����, ������� ����� �����������
{
    char c;
    c=fgetc(out);
    long int number=0;
    if ((int)c>0)                                               //� �������� ����� ��� char ��������� �������� �� -128 �� 127, �������, ���� ����� �������������, ��������� 256
    {
        number=(int)c;
    }
    else
    {
        number=(int)c+256;
    }
    if (number==32)
    {
        fputs("0",in);                                          //� ������������� ����� �� ���������� ��� ������� ������ 0 ������� ������, �������, ���� number=32, �� ������� 0 � ����
    }
    else
    {
        long int k=0,zam=number;                                //����� ��������� ����� �����������, �� ����, ���� number = 132, �� ������� � ���� ���� 1, ����� 3, ����� 2
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
void decoder::Zap(char c)                                                   //������������� ������� Zap, ������� �������� � ���� ����������� ������
{
    long int number=0;
    if ((int)c>0)                                               //� �������� ����� ��� char ��������� �������� �� -128 �� 127, �������, ���� ����� �������������, ��������� 256
    {
        number=(int)c;
    }
    else
    {
        number=(int)c+256;
    }
    if (number==32)
    {
        fputs("0",in);                                          //� ������������� ����� �� ���������� ��� ������� ������ 0 ������� ������, �������, ���� number=32, �� ������� 0 � ����
    }
    else
    {
        long int k=0,zam=number;                                //����� ��������� ����� �����������, �� ����, ���� number = 132, �� ������� � ���� ���� 1, ����� 3, ����� 2
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
void decoder::PushNumber(long int num)                                      //���������� ����(�����) � ��������� ����.
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
long int decoder::GetDouble()                                               //������� ��������� ����� �� 2 ���� �������������� �����
{
    char c;
    int number1=0;
    char binnumchar[16];
    long int number=0,binnumber[2]={0};
    for (int i=0;i<2;i++)                                       //������� �������� �������� �� �������������� �����
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
                number1=(int)c+256;                             //����� �������� �� ��� �����
            }
            int bin = 0, k = 1;
            while (number1)                                     //����� ��� ����� ��������� � 2 ������� ���������
            {
                bin += (number1 % 2) * k;
                k *= 10;
                number1 /= 2;
            }
            binnumber[i]=bin;                                   //� ��� ����� � 2 ������� ��������� ��������� � ������
        }
    }
    for (int i=0;i<15;i++)                                      //������� ������ ���� char � ��������� ��� ������
    {
        binnumchar[i]=48;
    }
    if (binnumber[0]!=0)                                        //���������� ��������� �������� ����� � ���������� ������ 2 ����
    {
        long int zam;
        zam=binnumber[0];
        for (int i=7;i>=0;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    if (binnumber[1]!=0)                                        //��� ��� ����� ��� ��������� ��������� ����� ���������� �� 2 ������
    {
        long int zam;
        zam=binnumber[1];
        for (int i=15;i>=8;i--)
        {
            binnumchar[i]=(zam%10)+48;
            zam/=10;
        }
    }
    for (int i=0,j=15;i<16;i++,j--)                             //���������� ��������� ������ ���������� ������� �������� ����� � ����� ���� long int
    {
        if ((int)binnumchar[i]==49)
            number+=pow(2,j);
    }
    return number;
}
long int decoder::GetTriple()                                               //������� ��������� ����� �� 3 ���� �������������� ����� (2 �������, ����������� ��� ���������)
{
    char c;
    int number1=0;
    char binnumchar[24];
    long int number=0,binnumber[3]={0};
    for (int i=0;i<3;i++)                                       //������� ��������� ��������� ����������, �� ����������� ����, ��� ����� ���������� 3
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
    return number;                                              //���������� ��������
}
bool decoder::NewMessageFounder()                                           //���� -New Message-, ��������� ��������� �� ����� �����
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
void decoder::ZeroPoint()                                                   //������ ����������� ������� 0
{
    char str[5000];
    fputs("\n_______________________________________",in);                      //�������� ���������� ���������
    fputs("\n����� ���������!\n",in);                                           //�������� ���������� � �����
    fgets(str,5000,out);
    fputs("����� ��������� - ",in);
    fputc(str[0],in);
    fputc(str[1],in);
    fputc(str[2],in);
    fputs("\n����������� - ",in);
    fgets(str,5000,out);
    for (int i=0;i<=17;i++)
    {
        fputc(str[i],in);
    }
    fputs("\n��������� - ", in);
    fgets(str,5,out);
    fputs("BUFR",in);
    fputs("\n����� ��������� - ",in);
    messageLenght=GetTriple();
    PushNumber(messageLenght);
    fputs("\nBUFR ������: ",in);
    version=(int)fgetc(out);
    PushNumber(version);
}
void decoder::FirstPoint()                                                  //������ ����������� ������� 1
{
    long int sec1Lenght=0;
    fputs("\n������ 1:\n",in);                                                  //������ ������
    fputs("����� �������: ",in);
    sec1Lenght=GetTriple();
    PushNumber(sec1Lenght);
    fputs("\n��������� ������� ��� ���� BUFR - ",in);
    char c;
    c=fgetc(out);
    Zap(c);
    if (c==' ')
    {
        fputs(" - ������������",in);
    }
    else
    {
        fputs(" - �� ����������������� ������",in);
    }
    if ((version==3)||(version==2))
    {
        int numcen=0,numsub=0;                                                  //���������� ������ � ���������
        char c1=0,c2=0,center[3],subcenter[6];                                  //�� ������ � ������ ������ BUFR ��������� ������� ���� ��������, � ����� ��� �����, ������� �������� ����� ����� 2 �������� � �������� � ����
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
        for (int i=0;i<6;i++)                                                   //��� ������������� ������� subcenter ������ ��������� � ����: ������ 3 ������� - ����� ������, ��������� 3 - ����� ���������
        {
            subcenter[i]=48;
        }
        for (int i=0;i<3;i++)
        {
            center[i]=48;
        }
        for (int i=2;i>=0;i--)                                                  //���������� ��������
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
        if ((center[0]!=49)&&(center[0]!=50))                                   //������������� ��������� ����������� � ������� ���������� �������������� �������
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
        fputs("\n����� ���������: ",in);
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
        if (feof(subcenters))                                                    //���� ���� ����������, �� ����� �������� �����������
        {
            fputs("0 - �������� ����������� ��� �� ������ � �������.",in);
        }
        fputs("\n����� ������: ",in);
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
        fputs("\n���������������� ����� ����������: ",in);                      //���������� ����������� � ���������� �����
        Zap(c);
        long int number=0;
        if (c==' ')
        {
            fputs(" - ��� ���������",in);
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
        if (number>=128)                                                        //���� ������ ��� ����� 1, �� ��������� �������� ������
        {
            fputs("\n��������� �������� ������ 2.",in);
            IfSection2=true;
        }
        else
        {
            fputs("\n��������� �� �������� ������ 2.",in);
            IfSection2=false;
        }
        fputs("\n��������� ������: ",in);
        Zap();
        fputs("\n������������ ������: ",in);
        Zap();
        fputs("\n����� ������ ��������� �������: ",in);
        Zap();
        fputs("\n����� ��������� �������: ",in);
        Zap();
        fputs("\n��� �������� ����: ",in);
        Zap();
        fputs("\n�����: ",in);
        Zap();
        fputs("\n����: ",in);
        Zap();
        fputs("\n���: ",in);
        Zap();
        fputs("\n������: ",in);
        Zap();
        if (sec1Lenght>17)                                                      //����� ��������� ������, ������������ ��������
        {
            fputs("\n������ ��� �������� ������������� �������� ���: ",in);
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
        fputs("\n����� ������: ",in);                                           //����� ��������� ������ � ���������
        for (int i=0;i<6;i++)                                                   //��������� ������ ��� ����������� ������� �������
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
        fputs("\n����� ���������: ",in);
        for (int i=5;i>=0;i--)                                                  //��������� ������ ��� ������������� ������� ����������
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
            fputs("0 - �������� ����������� ��� �� ������ � �������",in);                                  //���������� ��������� ���� �������
        }
        c=fgetc(out);
        fputs("\n���������������� ����� ����������: ",in);
        Zap(c);
        if (c==' ')
        {
            fputs(" - ��� ���������",in);
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
            fputs("\n��������� �������� ������ 2.",in);                         //�������� �� ������ ������
            IfSection2=true;
        }
        else
        {
            fputs("\n��������� �� �������� ������ 2.",in);
            IfSection2=false;
        }
        fputs("\n��������� ������: ",in);
        Zap();
        fputs("\n������������� ������������ ������: ",in);
        Zap();
        fputs("\n��������� ������������ ������: ",in);
        Zap();
        fputs("\n����� ������ ��������� �������: ",in);
        Zap();
        fputs("\n����� ��������� �������: ",in);
        Zap();
        fputs("\n���: ",in);
        PushNumber(GetDouble());
        fputs("\n�����: ",in);
        Zap();
        fputs("\n����: ",in);
        Zap();
        fputs("\n���: ",in);
        Zap();
        fputs("\n������: ",in);
        Zap();
        fputs("\n�������: ",in);
        Zap();
        if (sec1Lenght>22)                                                      //����� ������ ��� �������� �������������
        {
            fputs("\n������ ��� �������� ������������� �������� ���: ",in);
            while (sec1Lenght!=22)
            {
                Zap();
                fputs(" ",in);
                sec1Lenght--;
            }
        }
    }
}
void decoder::SecondPoint()                                                 //������ ����������� ������� 2, ���� �� ����������
{
    fputs("\n������ 2: ",in);                                               //������� ������ � ���
    fputs("\n����� �������: ",in);
    long int sec2Lenght;
    sec2Lenght=GetTriple();
    PushNumber(sec2Lenght);
    fgetc(out);
    if (sec2Lenght>4)
    {
        fputs("\n������ ��� �������� ������������� �������� ���: ",in);     //����� ��������� ������
        while (sec2Lenght!=4)
        {
            Zap();
            fputs(" ",in);
            sec2Lenght--;
        }
    }
}
void decoder::ThirdPoint()                                                  //����������� ������� 3 �� ���������� (������������)
{
    long int number;
    char c;
    fputs("\n������ 3: ",in);                                                   //������ 3
    fputs("\n����� �������: ",in);                                               //���������� ���������� ����� (������, ������ � ��)
    long int sec3Lenght;
    sec3Lenght=GetTriple();
    PushNumber(sec3Lenght);
    fgetc(out);
    fputs("\n���������� ���������� ������: ",in);
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
        fputs("\n������ ���������� ��� ������",in);
    }
    else if (number==192)
    {
        fputs("\n������ ���������� � �������",in);
    }
    else if (number==64)
    {
        fputs("\n������ ������ � �������",in);
    }
    else
    {
        fputs("\n������ ������ ��� ������",in);
    }
    if (sec3Lenght>7)
    {
        long int zam=0;
        fputs("\n���������� ���������: \n",in);                                   //������ ������ � �����������
        while (sec3Lenght>8)
        {
            char binnumber[17],F=0,X[2],Y[3];
            int x=0,y=0;
            number=GetDouble();                                                 //�������� ����� �� 2 ����
            zam=number;
            for(int i=0;i<16;i++)                                               //����������� ����� ���, �����
            {                                                                   //��� � ��� ��������� ������ ���� char, ���������� 2 �������� ����� �����������
                binnumber[i]=48;
            }
            int j=15;
            while(zam>0)
            {
                binnumber[j]=zam%2+48;
                zam/=2;
                j--;
            }
            F=(binnumber[0]-48)*2+(binnumber[1]-48)+48;                         //������� F,X,Y ��� ������ � ��������
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
            fputc(F,in);                                                        //������� F,X,Y � ����
            fputs(" ",in);
            fputc(X[0],in);
            fputc(X[1],in);
            fputs(" ",in);
            fputc(Y[0],in);
            fputc(Y[1],in);
            fputc(Y[2],in);
            fputs(" - ",in);
            if (F==48)                                                          //���� F=0, ��
            {
                char String[11], Output[250];
                while (!feof(B))                                                //���� ������� �� ����������
                {
                    fgets(String,9,B);                                          //�������� ������ �� �������
                    if((F==String[0])&&(X[0]==String[2])&&(X[1]==String[3])&&(Y[0]==String[5])&&(Y[1]==String[6])&&(Y[2]==String[7])) //���������� ������ �� ��������� � ������ �� �������
                    {
                        fgets(Output,250,B);                                    //�������� ���������� ������ �� ������ �������
                        fputs(Output,in);                                       //������� ��� ������ � ��������� ����
                        rewind(B);                                              //������������ � ������ �������
                        break;
                    }
                    fgets(Output,250,B);                                        //���� ������ �� �������, �� ������� �� ����� ������, ����� ������� �� ���������
                }
                if (feof(B))                                                    //���� ������ �� ���� ������� � �������, �� ������� "������ �� �������"
                {
                    fputs("������ �� ������� � �������\n",in);
                }
                rewind(B);                                                      //������������ � ������ �������
            }
            if (F==49)                                                          //���� F=1, �� (����������� ��������� ���� �����, ��� � ��� F=0)
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
                    fputs("������ �� ������� � �������\n",in);
                }
                rewind(A);
            }
            if (F==50)                                                          //���� F=2, �� (����������� ��������� ���� �����, ��� � ��� F=0)
            {
                char String[11], Output[250];
                while (!feof(C))
                {
                    fgets(String,9,C);
                    if (((X[0]==48)&&(X[1]>=49)&&(X[1]<=54))||((X[0]==50)&&(X[1]==49))) //�� ����������� ������������� ��� ������������� �������
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
                    fputs("������ �� ������� � �������\n",in);
                }
                rewind(C);
            }
            if (F==51)                                                          //���� F=51, ��
            {
                char String[7],Output[2000];
                while (!feof(D))                                                //���� ���� ������� �� ����������
                {
                    fgets(String,7,D);                                          //����� ������ �� �������
                    if ((F==String[0])&&(X[0]==String[1])&&(X[1]==String[2])&&(Y[0]==String[3])&&(Y[1]==String[4])&&(Y[2]==String[5]))  //���������� �������� ��������� � ��������
                    {
                        fgets(Output,2000,D);                                   //����� ����� ���������� ����� ������ �������
                        int count=strlen(Output);
                        count=(count - 1)/6;                                    //������� ���������� ���������� ���������
                        for (int i=0;i<count;i++)                               //���� ������ �� ��������
                        {
                            F=Output[i*6];                                      //�������� ��������� �� ������
                            X[0]=Output[i*6+1];
                            X[1]=Output[i*6+2];
                            Y[0]=Output[i*6+3];
                            Y[1]=Output[i*6+4];
                            Y[2]=Output[i*6+5];
                            if (F==48)                                          //� ���������� ����� ����� �� �������, ��� � ��� (F=0),(F=1),(F=2)
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
                                    fputs("������ �� ������� � �������\n",in);
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
                                    fputs("������ �� ������� � �������\n",in);
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
                                        //����� ���� �����������.
                                        fputs(out,in);
                                        rewind(C);
                                        break;
                                    }
                                    fgets(Output,250,C);
                                }
                                if(feof(C))
                                {
                                    fputs("������ �� ������� � �������\n",in);
                                }
                                rewind(C);
                            }
                        }
                    }
                    else                                                        //���� ������ �� ���� �������, �� �������� ������ �� �����
                    {
                        fgets(Output,2000,D);
                    }
                }
                if (feof(D))                                                    //���� ���� ����������, �� �������, ��� ������ ��� � �������
                {
                    fputs("������ �� ������� � ������� \n",in);
                }
                rewind(D);
            }
            sec3Lenght=sec3Lenght-2;
            number=0;
        }
    }
}
void decoder::RewindAll()                                                   //���������� ������� � ������ � ���� ������
{
    rewind(A);
    rewind(B);
    rewind(C);
    rewind(D);
    rewind(centers);
    rewind(subcenters);
}
void decoder::FinalPoint()                                                  //��������� ������ ���� �������� ������
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
                    fputs("\n������!!!\n ������� ������� ����� ���������!",in);
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
