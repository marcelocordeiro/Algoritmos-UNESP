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

typedef enum {SINTAXE, FECHAPARENTESE, ABRECOLCHETE, FECHACOLCHETE, DIGITOESPERADO,
                NUMEROINVALIDO, DESCONHECIDO} CodErros;

void erro(char str[], CodErros cod, int *iErro)
{
    switch(cod)
    {
        case SINTAXE:
            printf("Erro de sintaxe. [%5s]\n", str);
            break;

        case FECHAPARENTESE:
            printf(") Esperado. [%5s]\n", str);
            break;

        case ABRECOLCHETE:
            printf("[ esperado. [%5s]\n", str);
            break;

        case FECHACOLCHETE:
            printf("] esperado. [%5s]\n", str);
            break;

        case DIGITOESPERADO:
            printf("Digito esperado. [%5s]\n", str);
            break;

        case NUMEROINVALIDO:
            printf("Numero invalido. [%5s]\n", str);
            break;

        default:
            printf("Erro desconhecido. [%5s]\n", str);
            break;
    }
    *iErro = 1;
}

int charToInt(char c, int *iErro)
{
    int ind = c-'0';
    if (ind < 0 || ind > 9)
    {
        char s[2];
        s[0] = c;
        s[1] = 0;
        erro(s,DIGITOESPERADO, &(*iErro));
        return 0;
    }
    else
        return ind;
}

float expressao(char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro);
float fator(char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro);
float termo(float fator, char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro);

float fator(char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro)
{
    char c = exp[(*posAtual)++];

    if (c == '(')
    {
        float f = expressao(exp, posAtual, sPlanilha, &(*iErro));
        if(exp[*posAtual] != ')')
        {
            erro(&exp[(*posAtual - 1)], FECHAPARENTESE, *(&iErro));
            return 0;
        }
        (*posAtual)++;

        return f;
    }
    else if((toupper(c) >= 'A')&&(toupper(c) <= 'I'))
    {
        int iLinha, iColuna;

        switch(toupper(c))
        {
            case 'A': iColuna = 0; break;
            case 'B': iColuna = 1; break;
            case 'C': iColuna = 2; break;
            case 'D': iColuna = 3; break;
            case 'E': iColuna = 4; break;
            case 'F': iColuna = 5; break;
            case 'G': iColuna = 6; break;
            case 'H': iColuna = 7; break;
            case 'I': iColuna = 8; break;
        }

        iLinha = charToInt(exp[(*posAtual)++],&(*iErro)) - 1;
        return atof(sPlanilha[iColuna][iLinha]);
    }
    else if('0' <= c && c <= '9')
    {

        /*Isso testa se o caractere atual e um numero, se for, converte para float e
        retorna esse valor.*/
        char *fim;
        float f = strtod(&exp[(*posAtual)-1], &fim);
        *posAtual = fim - exp;
        return f;
    }
    else
    {

        /*Se nao caiu em nenhum dos casos, e porque e um erro de sintaxe / nao tratado.*/
        erro(&exp[(*posAtual - 1)], SINTAXE, &(*iErro));
        return 0;
    }

}   //--fator


float termo(char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro)
{

    /*Essa funcao presume:
        <numero / coordenada> <* , /> <numero / coordenada>
           se ela encontra o operador correto, faz a operacao e retorna, caso contrario
           ela apenas entende o 1o numero e volta para a funcao que a chamou (Expressao).
        La o programa ira cuidar da soma e subtracao.
    */

    float t = fator(exp, posAtual, sPlanilha, &(*iErro));
    char continua = 1;

    while(continua)
    {
        switch(exp[*posAtual])
        {
            case '*':
                (*posAtual)++;
                t *= fator(exp, posAtual, sPlanilha, &(*iErro));
                break;

            case '/':
                (*posAtual)++;
                t /= fator(exp, posAtual, sPlanilha, &(*iErro));
                break;

            default:
                continua = 0;
        }
    }
    return t;
}   //--termo


float expressao(char exp[], int *posAtual, char sPlanilha[10][coluna][linha], int *iErro)
{

    /*Essa funcao basicamente le um operador <+,-> ou o primeiro elemento da expressao
         e faz a soma enquanto existirem + ou -

      continua poderia ser substituido por um bool
    */

    float e;
    char continua = 1;

    switch(exp[*posAtual])
    {
        case '+':
            (*posAtual)++;
            e = termo(exp, posAtual, sPlanilha, &(*iErro));
            break;

        case '-':
            (*posAtual)++;
            e = -termo(exp, posAtual, sPlanilha, &(*iErro));
            break;

        default:

            /*esse default serve para o comeco da expressao. Se voce for testar se a expressao
              comeca com um '=', talvez esse seja um bom lugar.*/
            e = termo(exp, posAtual, sPlanilha, &(*iErro));
    }

    while(continua)
    {
        switch(exp[*posAtual])
        {
            case '+':
                (*posAtual)++;
                e += termo(exp, posAtual, sPlanilha, &(*iErro));
                break;

            case '-':
                (*posAtual)++;
                e -= termo(exp, posAtual, sPlanilha, &(*iErro));
                break;

            default:
                continua = 0;
        }
    }
    return e;

}

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

int ValidarComando(char *sComando, char sPlanilha[10][coluna][linha])
{
    char sAuxComando[20];
    float fNum;
    int iErro = 0, iAux = 0;
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
                                {
                                    ReciclarComando(sAuxComando,6);
                                    fNum = expressao(sAuxComando,&iAux,sPlanilha,&iErro);
                                    return (!iErro);
                                }
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

void GetComando(char *sComando, char sPlanilha[10][coluna][linha])
{
    int iCont;
    printf("\nComandos: (A)lterar <coluna><linha> <celula>, (F)ormulas, (R)esultados,\n");
    printf("          (S)alvar <nome arquivo>, (C)arregar <nome arquivo>, (T)erminar.\n");
    printf("Digite um comando: ");
    fflush(stdin);
    gets(sComando);
    for(iCont=0;iCont<strlen(sComando);iCont++)
        sComando[iCont]=toupper(sComando[iCont]);
    while(!ValidarComando(sComando,sPlanilha))
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
                        int iAux = 1, iErro = 0;
                        printf("   %4.2f ",expressao(sPlanilha[iColuna][iLinha],&iAux,sPlanilha,&iErro));
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
        GetComando(sComando, sPlanilha); //ja retorna tudo maiusculo
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
