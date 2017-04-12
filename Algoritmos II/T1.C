/*
Nome: Marcelo Augusto Cordeiro
RA: 121023265
SO: Windows 8
Compilador: Borland C++ 5.5
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#define coluna 9
#define linha 9

FILE *planilha;

void LimparPlanilha(char sPlanilha[10][coluna][linha])
{
    int iColuna,iLinha;
    for (iLinha=0;iLinha<linha;iLinha++)
    {
        for (iColuna=0;iColuna<coluna;iColuna++)
            strcpy(sPlanilha[iColuna][iLinha],"");
    }
}

void ReciclarComando(char *sComando, int iComeco)
{
    int iCont;
    for (iCont=iComeco;iCont<=strlen(sComando);iCont++)
        sComando[iCont-iComeco]=sComando[iCont];
}

int ValidarColuna(char cColuna)
{
    switch(cColuna)
    {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I': return 1;
        default: return 0;
    }
}

int ValidarLinha(char cLinha)
{
    switch(cLinha)
    {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return 1;
        default: return 0;
    }
}

int ValidarComando(char *sComando)
{
    char sAuxComando[20];
    float fNum;
    strcpy(sAuxComando,sComando);
    if(!(strcmp(sAuxComando,"CLS")))
        return 1;
    switch(sAuxComando[0])
    {
       case 'A': if (sAuxComando[1]==' ')
                     if(ValidarColuna(sAuxComando[2]))
                         if(ValidarLinha(sAuxComando[3]))
                             if(sAuxComando[4]==' ')
                             {
                                if(sAuxComando[5]=='=')
                                    if(ValidarColuna(sAuxComando[6])&&ValidarLinha(sAuxComando[7])&&ValidarColuna(sAuxComando[9])&&ValidarLinha(sAuxComando[10]))
                                        switch(sAuxComando[8])
                                        {
                                            case '+':
                                            case '-':
                                            case '*':
                                            case '/':
                                            case '%': return 1;
                                            default: return 0;
                                        }
                                    else
                                        return 0;
                                else
                                {
                                    ReciclarComando(sAuxComando,5);
                                    fNum = atof(sAuxComando);
                                    if (!(fNum))
                                        return 0;
                                    else
                                        return 1;
                                }
                             }
                             else
                                return 0;
                         else
                            return 0;
                     else
                        return 0;
                 else
                    return 0;
       case 'S':
       case 'C': if(sAuxComando[1]==' ')
                    if(sAuxComando[2]!=NULL)
                        return 1;
                    else
                        return 0;
                else
                    return 0;
       case 'F':
       case 'R':
       case 'T': if(sAuxComando[1]==NULL)
                    return 1;
                 else
                    return 0;
       default: return 0;
    }
}

void GetComando(char *sComando)
{
    int iCont;
    printf("\nComandos: (A)lterar <coluna><linha> <celula>, (F)ormulas, (R)esultados,\n");
    printf("          (S)alvar <nome arquivo>, (C)arregar <nome arquivo>, (T)erminar.\n");
    printf("Digite um comando: ");
    fflush(stdin);
    gets(sComando);
    for(iCont=0;iCont<strlen(sComando);iCont++)
        sComando[iCont]=toupper(sComando[iCont]);
    while(!ValidarComando(sComando))
    {
        printf("Comando invalido. Redigite: ");
        fflush(stdin);
        gets(sComando);
        for(iCont=0;iCont<strlen(sComando);iCont++)
            sComando[iCont]=toupper(sComando[iCont]);
    }
}

void Terminar()
{
    fclose(planilha);
    exit(0);
}

void ImprimirFormulas(char sPlanilha[10][coluna][linha])
{
    int iColuna,iLinha;
    for (iLinha=-1;iLinha<linha;iLinha++)
    {
        if (iLinha==-1)
        {
            printf("    %4s","A");
            printf("    %4s","B");
            printf("    %4s","C");
            printf("    %4s","D");
            printf("    %4s","E");
            printf("    %4s","F");
            printf("    %4s","G");
            printf("    %4s","H");
            printf("    %4s","I");
        }
        for (iColuna=-1;iColuna<coluna;iColuna++)
        {
            if ((iColuna==-1)&&(iLinha!=-1))
                printf("%2d",iLinha+1);
            else
                if ((iColuna!=-1)&&(iLinha!=-1))
                    if ((sPlanilha[iColuna][iLinha][0])=='=')
                        printf("  %s",sPlanilha[iColuna][iLinha]);
                    else
                        if ((sPlanilha[iColuna][iLinha][0])==' ')
                            printf("%8s",sPlanilha[iColuna][iLinha]);
                        else
                            printf("   %4s ",sPlanilha[iColuna][iLinha]);
        }
        printf("\n");
    }
}

void ImprimirResultados(char sPlanilha[10][coluna][linha])
{
    int iColuna,iLinha, iCol1, iLin1, iCol2, iLin2;
    for (iLinha=-1;iLinha<linha;iLinha++)
    {
        if (iLinha==-1)
        {
            printf("    %4s","A");
            printf("    %4s","B");
            printf("    %4s","C");
            printf("    %4s","D");
            printf("    %4s","E");
            printf("    %4s","F");
            printf("    %4s","G");
            printf("    %4s","H");
            printf("    %4s","I");
        }
        for (iColuna=-1;iColuna<coluna;iColuna++)
        {
            if ((iColuna==-1)&&(iLinha!=-1))
                printf("%2d",iLinha+1);
            else
                if ((iColuna!=-1)&&(iLinha!=-1))
                    if ((sPlanilha[iColuna][iLinha][0])=='=')
                    {
                        iCol1=((int)sPlanilha[iColuna][iLinha][1])-65;
                        iLin1=((int)sPlanilha[iColuna][iLinha][2])-49;
                        iCol2=((int)sPlanilha[iColuna][iLinha][4])-65;
                        iLin2=((int)sPlanilha[iColuna][iLinha][5])-49;
                        switch (sPlanilha[iColuna][iLinha][3])
                        {
                            case '+': printf("   %4.2f ",(float)((strtod(sPlanilha[iCol1][iLin1],NULL))+(strtod(sPlanilha[iCol2][iLin2],NULL)))); break;
                            case '-': printf("   %4.2f ",(float)((strtod(sPlanilha[iCol1][iLin1],NULL))-(strtod(sPlanilha[iCol2][iLin2],NULL)))); break;
                            case '*': printf("   %4.2f ",(float)((strtod(sPlanilha[iCol1][iLin1],NULL))*(strtod(sPlanilha[iCol2][iLin2],NULL)))); break;
                            case '/': printf("   %4.2f ",(float)((strtod(sPlanilha[iCol1][iLin1],NULL))/(strtod(sPlanilha[iCol2][iLin2],NULL)))); break;
                            case '%': printf("   %4d ",(((int)(strtod(sPlanilha[iCol1][iLin1],NULL)))%((int)(strtod(sPlanilha[iCol2][iLin2],NULL))))); break;
                        }
                    }
                    else
                        if ((sPlanilha[iColuna][iLinha][0])==' ')
                            printf("%8s",sPlanilha[iColuna][iLinha]);
                        else
                            printf("   %4s ",sPlanilha[iColuna][iLinha]);
        }
        printf("\n");
    }
}

void AbrirArquivo(char *sComando, char sPlanilha[10][coluna][linha])
{
    if (!(planilha=fopen(sComando,"rb")))
    {
        printf("Arquivo inexistente.\n");
        return;
    }
    else
    {
        if ((fread(sPlanilha,sizeof(char[10]),coluna*linha,planilha))==coluna*linha)
            printf("Arquivo carregado com sucesso.\n");
        else
            printf("Falha ao carregar o arquivo. Tente novamente.\n");
    }
    fclose(planilha);
}

void SalvarArquivo(char *sComando, char sPlanilha[10][coluna][linha])
{
    char cOpcao;
    if (!(planilha=fopen(sComando,"rb")))
    {
        if (planilha=fopen(sComando,"wb"))
        {
            if (fwrite(sPlanilha,sizeof(char[10]),coluna*linha,planilha))
                printf("Arquivo salvo com sucesso.\n");
            else
                printf("Falha ao salvar o arquivo. Tente novamente.\n");
        }
        else
            printf("Falha ao salvar o arquivo. Tente novamente.\n");
    }
    else
    {
        fclose(planilha);
        printf("Ja existe um arquivo com esse nome. Substituir (S\\N)? ");
        fflush(stdin);
        scanf("%c",&cOpcao);
        while((toupper(cOpcao)!='S')&&(toupper(cOpcao)!='N'))
        {
            printf("Resposta invalida. Redigite (S\\N): ");
            fflush(stdin);
            scanf("%c",&cOpcao);
        }
        if(toupper(cOpcao)=='S')
            if (planilha=fopen(sComando,"wb"))
                if (fwrite(sPlanilha,sizeof(char[10]),coluna*linha,planilha))
                    printf("Arquivo salvo com sucesso.\n");
                else
                    printf("Falha ao salvar o arquivo. Tente novamente.\n");
            else
                printf("Falha ao salvar o arquivo. Tente novamente.\n");
        else
            printf("Falha ao salvar o arquivo. Tente novamente.\n");
    }
    fclose(planilha);
}

void AlterarPlanilha(char *sComando, char sPlanilha[10][coluna][linha])
{
    char cColuna, cLinha;
    cColuna=sComando[0];
    cLinha=sComando[1];
    ReciclarComando(sComando,3);
    strcpy((sPlanilha[((int)cColuna)-65][((int)cLinha)-49]),sComando);
}

int main()
{
    char sComando[20], cComando, sPlanilha[10][coluna][linha];
    LimparPlanilha(sPlanilha);
    printf("                           PLANILHA ELETRONICA\n");
    do
    {
        GetComando(sComando); //ja retorna tudo maiusculo
        if (!(strcmp(sComando,"CLS")))
        {
            clrscr();
            strcpy(sComando,"");
        }
        if (!(strcmp(sComando,"T")))
            Terminar();
        else
            if (!(strcmp(sComando,"F")))
                ImprimirFormulas(sPlanilha);
            else
                if (!(strcmp(sComando,"R")))
                    ImprimirResultados(sPlanilha);
                else
                {
                    cComando=sComando[0];
                    ReciclarComando(sComando,2);
                    switch (cComando)
                    {
                        case 'A': AlterarPlanilha(sComando,sPlanilha);
                                  break;
                        case 'S': SalvarArquivo(sComando,sPlanilha);
                                  break;
                        case 'C': AbrirArquivo(sComando,sPlanilha);
                                  break;
                    }
                }
    }while(1);
    return 0;
}
