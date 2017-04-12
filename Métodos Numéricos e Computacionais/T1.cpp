/* Carlos Braile
   Elisa Castro
   Marcelo Cordeiro
Compilador: Borland C++ 5.5
*/
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define PRINT
#define PRINT_DEV

float Funcao(int iID, float rX)
{
    switch(iID)
    {
        case 01: return rX*rX*rX*rX*rX-1.5*rX*rX*rX+3.1*rX;
        case 02: return ((rX*rX*rX-2.5*rX*rX+2)/(0.5*rX))+7*rX;
        case 03: return ((4*rX*rX*rX*rX*rX-2*rX*rX*rX+rX)/(rX*rX-9)) + rX;
    }
}

void Bisseccao(float rA, float rB, int iFuncao, float rPrecisao, int iMax, float *rRaiz, int *iCont)
{
    float rX;
    *iCont = 0;
    if ((Funcao(iFuncao,rA)*Funcao(iFuncao,rB)) > 0)
    {
        printf("\nConvergencia nao garantida no intervalo [%.10f, %.10f].\n",rA,rB);
        return;
    }
    do
    {
        (*iCont)++;
        #ifdef PRINT
            printf("\n\nIteracao %d\nIntervalo [%.10f, %.10f]",(*iCont),rA,rB);
        #endif
        rX = (rA+rB)/2;
        #ifdef PRINT
            printf("\nX = %.10f",rX);
        #endif
        if ((Funcao(iFuncao,rX)*Funcao(iFuncao,rA)) < 0)
            rB = rX;
        else
            rA = rX;
        #ifdef PRINT
            printf("\nF(%.10f) = %.10f",rX,Funcao(iFuncao,rX));
        #endif
    }while((fabs(Funcao(iFuncao,rX)) > rPrecisao) && (fabs(rB-rA) > rPrecisao) && ((*iCont) < iMax));
    *rRaiz = rX;
}

void PosicaoFalsa(float rA, float rB, int iFuncao, float rPrecisao, int iMax, float *rRaiz, int *iCont)
{
    float rX;
    *iCont = 0;
    if ((Funcao(iFuncao,rA)*Funcao(iFuncao,rB)) > 0)
    {
        printf("\nConvergencia nao garantida no intervalo [%.10f, %.10f].\n",rA,rB);
        return;
    }
    do
    {
        (*iCont)++;
        #ifdef PRINT
            printf("\n\nIteracao %d\nIntervalo [%.10f, %.10f]",(*iCont),rA,rB);
        #endif
        rX = (rA*Funcao(iFuncao,rB)-rB*Funcao(iFuncao,rA))/(Funcao(iFuncao,rB)-Funcao(iFuncao,rA));
        #ifdef PRINT
            printf("\nX = %.10f",rX);
        #endif
        if ((Funcao(iFuncao,rX)*Funcao(iFuncao,rA)) < 0)
            rB = rX;
        else
            rA = rX;
        #ifdef PRINT
            printf("\nF(%.10f) = %.10f",rX,Funcao(iFuncao,rX));
        #endif
    }while((fabs(Funcao(iFuncao,rX)) > rPrecisao) && (fabs(rB-rA) > rPrecisao) && ((*iCont) < iMax));
    *rRaiz = rX;
}

void PosicaoFalsaModificado(float rA, float rB, int iFuncao, float rPrecisao, int iMax, float *rRaiz, int *iCont)
{
    float rX, rXAnt, rFA, rFB;
    *iCont = 0;
    rFA = Funcao(iFuncao,rA);
    rFB = Funcao(iFuncao,rB);
    if ((rFA*rFB) > 0)
    {
        printf("\nConvergencia nao garantida no intervalo [%.10f, %.10f].\n",rA,rB);
        return;
    }
    do
    {
        (*iCont)++;
        #ifdef PRINT
            printf("\n\nIteracao %d\nIntervalo [%.10f, %.10f]",(*iCont),rA,rB);
        #endif
        rXAnt = rX;
        rX = (rA*rFB-rB*rFA)/(rFB-rFA);
        #ifdef PRINT
            printf("\nX = %.10f",rX);
        #endif
        if ((Funcao(iFuncao,rX)*Funcao(iFuncao,rA)) < 0)
        {
            rB = rX;
            rFB = Funcao(iFuncao,rX);
            if (Funcao(iFuncao,rX)*Funcao(iFuncao,rXAnt)>0)
                rFA = rFA/2;
        }
        else
        {
            rA = rX;
            rFA = Funcao(iFuncao,rX);
            if (Funcao(iFuncao,rX)*Funcao(iFuncao,rXAnt)>0)
                rFB = rFB/2;
        }
        #ifdef PRINT
            printf("\nF(%.10f) = %.10f",rX,Funcao(iFuncao,rX));
        #endif
    }while((fabs(Funcao(iFuncao,rX)) > rPrecisao) && (fabs(rB-rA) > rPrecisao) && ((*iCont) < iMax));
    *rRaiz = rX;
}

float df(int iFuncao, float rX, int iMax, float rPrecisao)
{
    float rH=1, rDev, rDevAnt, rErro, rErroAnt;
    int iCont = 0;
    rErro = rPrecisao + 1;
    do
    {
        iCont++;
        #ifdef PRINT_DEV
            printf("\n\nIteracao %d",iCont);
        #endif
        rDev = (Funcao(iFuncao,rX+rH)-Funcao(iFuncao,rX-rH))/(2*rH);
        #ifdef PRINT_DEV
            printf("\nF'(%.10f) = %.10f",rX,rDev);
        #endif
        if(iCont > 1)
        {
            rErro = (fabs(rDev-rDevAnt))/(fabs(rDev)>1?fabs(rDev):1);
            #ifdef PRINT_DEV
                printf("\nErro: %.10f",rErro);
            #endif
        }
        /*Essa parte iria comparar o erro atual com o anterior, se for maior, retorna a derivada anterior.
          Porém, com esse critério de parada a derivada fica bem longe do resultado correto.
          Portanto, com base em testes decidimos retirar esse critério.
        if(iCont> 1)
            if(rErro > rErroAnt)
                return rDevAnt;
            else
                rErroAnt = rErro;*/
        rDevAnt = rDev;
        rH /= 2;
    }while((rErro > rPrecisao) && (iCont < iMax));
    return rDev;
}

void Newton(float rX0, int iFuncao, float rPrecisao, int iMax, float *rRaiz, int *iCont)
{
    float rX, rXAnt, rDev;
    rXAnt = rX = rX0;
    *iCont = 0;
    do
    {
        (*iCont)++;
        #ifdef PRINT
            printf("\n- Iteracao %d\n",(*iCont));
            #ifdef PRINT_DEV
                printf("\nIniciando calculo da derivada no ponto %.10f",rXAnt);
            #endif
        #endif
        rDev = df(iFuncao,rXAnt,iMax,rPrecisao);
        #ifdef PRINT_DEV
            printf("\n\nCalculo da derivada finalizado.");
        #endif
        if (rDev == 0)
        {
            printf("\nConvergencia nao garantida iniciando no ponto %.10f.\n",rX0);
            *iCont = 0;
            return;
        }
        rXAnt = rX;
        rX = rXAnt - (Funcao(iFuncao,rXAnt)/rDev);
        #ifdef PRINT
            printf("\n\nX = %.10f\nF(X) = %.10f\n",rX,Funcao(iFuncao,rX));
        #endif
    }while((fabs(Funcao(iFuncao,rX)) > rPrecisao) && ((fabs(rX-rXAnt)/fabs(rX>1?rX:1)) > rPrecisao) && ((*iCont) < iMax));
    *rRaiz = rX;
}

void NewtonModificado(float rX0, int iFuncao, float rPrecisao, int iMax, float *rRaiz, int *iCont)
{
    float rX, rXAnt, rDev;
    rXAnt = rX = rX0;
    *iCont = 0;
    #ifdef PRINT_DEV
        printf("\nIniciando calculo da derivada no ponto %.10f",rX0);
    #endif
    rDev = df(iFuncao,rX0,iMax,rPrecisao);
    #ifdef PRINT_DEV
        printf("\n\nCalculo da derivada finalizado.");
    #endif
    if (rDev == 0)
    {
        printf("\nConvergencia nao garantida iniciando no ponto %.10f.\n",rX0);
        return;
    }
    do
    {
        (*iCont)++;
        #ifdef PRINT
            printf("\n- Iteracao %d\n",(*iCont));
        #endif
        rXAnt = rX;
        rX = rXAnt - (Funcao(iFuncao,rXAnt)/rDev);
        #ifdef PRINT
            printf("\n\nX = %.10f\nF(X) = %.10f\n",rX,Funcao(iFuncao,rX));
        #endif
    }while((fabs(Funcao(iFuncao,rX)) > rPrecisao) && ((*iCont) < iMax));
    //&& ((fabs(rX-rXAnt)/fabs(rX>1?rX:1)) > rPrecisao) também foi retirado pois fazia o método parar com um erro muito grande
    *rRaiz = rX;
}

float df2(int iFuncao, float rX, int iMax, float rPrecisao)
{
    float rH=1, rDev, rDevAnt, rErro;
    int iCont = 0;
    rErro = rPrecisao + 1;
    do
    {
        iCont++;
        #ifdef PRINT
            printf("\n\nIteracao %d",iCont);
        #endif
        rDev = (Funcao(iFuncao,rX+2*rH)-2*Funcao(iFuncao,rX)+Funcao(iFuncao,rX-2*rH))/(4*rH*rH);
        #ifdef PRINT
            printf("\nF''(%.10f) = %.10f",rX,rDev);
        #endif
        if(iCont > 1)
        {
            rErro = (fabs(rDev-rDevAnt))/(fabs(rDev)>1?fabs(rDev):1);
            #ifdef PRINT
                printf("\nErro: %.10f",rErro);
            #endif
        }
        rDevAnt = rDev;
        rH /= 2;
    }while((rErro > rPrecisao) && (iCont < iMax));
    return rDev;
}

int main()
{
    int iFunc, iMetodo, iMax, iCont;
    float rA, rB, rPrecisao, rRaiz;
    char cResp;
    do
    {
        printf("\n- Funcoes disponiveis -");
        printf("\n1 - x^5 - 1.5 * x^3 + 3.1 * x\n2 - ((x^3 - 2.5 * x^2 + 2) / (0.5 * x)) + 7 * x\n3 - ((4 * x^5 - 2 * x^3 + x) / (x^2 - 9)) + x");
        printf("\nFuncao desejada: ");
        scanf("%d",&iFunc);
        printf("\n- Zero de funcao -");
        printf("\n1 - Bissecao\n2 - Posicao Falsa\n3 - Posicao Falsa Modificado\n4 - Newton\n5 - Newton Modificado");
        printf("\n\n- Diferenciacao -");
        printf("\n6 - Derivada primeira\n7 - Derivada segunda");
        printf("\n\nMetodo desejado: ");
        scanf("%d",&iMetodo);
        if ((iMetodo>=1)&&(iMetodo<=3))
        {
            printf("\nLimite inferior: ");
            scanf("%f",&rA);
            printf("Limite superior: ");
            scanf("%f",&rB);
            printf("Precisao: ");
            scanf("%f",&rPrecisao);
            printf("Numero maximo de iteracoes: ");
            scanf("%d",&iMax);
        }
        if ((iMetodo>=4)&&(iMetodo<=5))
        {
            printf("\nX inicial: ");
            scanf("%f",&rA);
            printf("Precisao: ");
            scanf("%f",&rPrecisao);
            printf("Numero maximo de iteracoes: ");
            scanf("%d",&iMax);
        }
        if ((iMetodo>=6)&&(iMetodo<=7))
        {
            printf("\nPonto: ");
            scanf("%f",&rA);
            printf("Precisao: ");
            scanf("%f",&rPrecisao);
            printf("Numero maximo de iteracoes: ");
            scanf("%d",&iMax);
        }
        switch(iMetodo)
        {
            case 01: Bisseccao(rA,rB,iFunc,rPrecisao,iMax,&rRaiz,&iCont);
                break;
            case 02: PosicaoFalsa(rA,rB,iFunc,rPrecisao,iMax,&rRaiz,&iCont);
                break;
            case 03: PosicaoFalsaModificado(rA,rB,iFunc,rPrecisao,iMax,&rRaiz,&iCont);
                break;
            case 04: Newton(rA,iFunc,rPrecisao,iMax,&rRaiz,&iCont);
                break;
            case 05: NewtonModificado(rA,iFunc,rPrecisao,iMax,&rRaiz,&iCont);
                break;
            case 06: printf("\n\nDerivada primeira no ponto %.10f: %.10f",rA,df(iFunc,rA,iMax,rPrecisao));
                break;
            case 07: printf("\n\nDerivada segunda no ponto %.10f: %.10f",rA,df2(iFunc,rA,iMax,rPrecisao));
                break;
        }
        if (iCont != 0)
        {
            if ((iMetodo>=1)&&(iMetodo<=5))
            {
                printf("\nIteracoes realizadas: %d",iCont);
                if (iCont == iMax)
                    printf("\nNumero maximo de iteracoes atingido. Melhor aproximacao encontrada: ");
                else
                    printf("\nRaiz encontrada: ");
                printf("%.10f",rRaiz);
            }
        }
        printf("\n\nDesejar sair do programa (S/N)? ");
        fflush(stdin);
        scanf("%c",&cResp);
    }while(toupper(cResp)!='S');
    return 0;
}
