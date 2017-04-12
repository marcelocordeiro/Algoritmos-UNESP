/*Nome: Marcelo Augusto Cordeiro
  RA: 121023265
  Linguagem de programacao: C
  Compilador: Turbo C++ 3.0
  Sistema operacional: Windows 7*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define DECIMAL 0.000001

void LimparFinalLinha(int iX, int iY)
{
	gotoxy(iX,iY);
	clreol();
	gotoxy(79,iY);
	printf("%c",186);
	gotoxy(iX,iY);
}

void DesenharMoldura(char *sEntrada)
{
	int iCont;
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	for (iCont=3;iCont<=78;iCont++)
	{
		gotoxy(iCont,2);
		printf("%c",205);
		gotoxy(iCont,24);
		printf("%c",205);
		gotoxy(iCont,7);
		printf("%c",205);
	}
	for (iCont=3;iCont<=23;iCont++)
	{
		gotoxy(2,iCont);
		printf("%c",186);
		gotoxy(79,iCont);
		printf("%c",186);
	}
	gotoxy(2,2);
	printf("%c",201);
	gotoxy(79,2);
	printf("%c",187);
	gotoxy(2,24);
	printf("%c",200);
	gotoxy(79,24);
	printf("%c",188);
	gotoxy(2,7);
	printf("%c",204);
	gotoxy(79,7);
	printf("%c",185);
	gotoxy(29,3);
	printf("FUN%cOES TRIGONOMETRICAS",128);
	gotoxy(6,5);
	printf("%s: ",sEntrada);
}

void ImprimirMenu1(void)
{
	gotoxy(6,9);
	printf("1 - Digitar um angulo e calcular as funcoes");
	gotoxy(6,10);
	printf("2 - Digitar uma funcao e calcular o angulo");
	gotoxy(6,11);
	printf("3 - Sair");
	LimparFinalLinha(13,5);
}

void ImprimirMenu2(void)
{
	LimparFinalLinha(6,9);
	printf("1 - Digitar o angulo em graus");
	LimparFinalLinha(6,10);
	printf("2 - Digitar o angulo em radianos");
	LimparFinalLinha(6,11);
	printf("3 - Voltar");
	LimparFinalLinha(13,5);
}

void ImprimirMenu3(void)
{
	LimparFinalLinha(6,9);
	printf("1 - Seno");
	LimparFinalLinha(6,10);
	printf("2 - Coseno");
	LimparFinalLinha(6,11);
	printf("3 - Tangente");
	LimparFinalLinha(6,12);
	printf("4 - Secante");
	LimparFinalLinha(6,13);
	printf("5 - Cossecante");
	LimparFinalLinha(6,14);
	printf("6 - Cotangente");
	LimparFinalLinha(6,15);
	printf("7 - Voltar");
	LimparFinalLinha(13,5);
}

int IfFloat(float rNum1, float rNum2) //Retorna 0 se for igual e 1 se for diferente
{
	int iResult;
	iResult = 1;
	if ((((rNum1-rNum2)<(DECIMAL))&&((rNum1-rNum2)>(-DECIMAL)))||(rNum1==rNum2))
		iResult = 0;
	return iResult;
}

int ValidarOpcao(char sOpcao[10],int iInicial,int iFinal)
{
	int iOpcao;
	iOpcao = atoi(sOpcao);
	if ((iOpcao<iInicial)||(iOpcao>iFinal))
	{
		do
		{
		gotoxy(30,21);
		printf("Opcao invalida.");
		LimparFinalLinha(30,22);
		printf("Digite novamente: ");
		scanf("%s",sOpcao);
		LimparFinalLinha(48,21);
		LimparFinalLinha(13,5);
		printf("%s",sOpcao);
		iOpcao = atoi(sOpcao);
		}while((iOpcao<iInicial)||(iOpcao>iFinal));
	}
	LimparFinalLinha(30,21);
	LimparFinalLinha(30,22);
	return iOpcao;
}

float ConverterGrausRad(float rGraus)
{
	return ((rGraus*M_PI)/180);
}

float ConverterRadGraus(float rRad)
{
	return ((rRad*180)/M_PI);
}

void CalcularImprimirAngulos(float rFuncao,int iFuncao)
{
	float rGraus, rRad, iValido; //iValido tem 0 como false e 1 como true
	iValido = 1;
	rRad = 0;
	switch(iFuncao)
	{
		case 1: if ((rFuncao<-1)||(rFuncao>1))
				iValido = 0;
			else
				rRad = asin(rFuncao);
			break;
		case 2: if ((rFuncao<-1)||(rFuncao>1))
				iValido = 0;
			else
				rRad = acos(rFuncao);
			break;
		case 3: rRad = atan(rFuncao);
			break;
		case 4: if ((rFuncao>(-1))&&(rFuncao<1))
				iValido = 0;
			else
				rRad = acos(1/rFuncao);
			break;
		case 5: if ((rFuncao>(-1))&&(rFuncao<1))
				iValido = 0;
			else
				rRad = asin(1/rFuncao);
			break;
		case 6: if ((IfFloat(rFuncao,0))==0)
				iValido = 0;
			else
				rRad = atan(1/rFuncao);
			break;
	}
	if (rRad < 0)
		rRad = fabs(rRad) + M_PI;
	rGraus = ConverterRadGraus(rRad);
	gotoxy(6,9);
	printf("Angulo em radianos: ");
	if (iValido == 0)
		printf("INEXISTENTE");
	else
		printf("%.3f", rRad);
	gotoxy(6,11);
	printf("Angulo em graus: ");
	if (iValido == 0)
		printf("INEXISTENTE");
	else
		printf("%.3f",rGraus);
	gotoxy(23,21);
	printf("Pressione qualquer tecla para continuar.");
	getch();
}

void CalcularImprimirFuncoes(float rAngulo,int iAngulo)
{
	float rSeno, rCosseno, rTangente;
	if (iAngulo==1)
		rAngulo=ConverterGrausRad(rAngulo);
	rSeno = sin(rAngulo);
	if ((IfFloat(rSeno,0))==0)
		rSeno=fabs(rSeno);
	rCosseno = cos(rAngulo);
	if ((IfFloat(rCosseno,0))==0)
		rCosseno=fabs(rCosseno);
	rTangente = tan(rAngulo);
	gotoxy(6,9);
	printf("Seno: %.3f",rSeno);
	gotoxy(6,11);
	printf("Cosseno: %.3f",rCosseno);
	gotoxy(6,13);
	printf("Tangente: ");
	if ((IfFloat(rCosseno,0))==1)
		printf("%.3f",rTangente);
	else
		printf("INEXISTENTE");
	gotoxy(6,15);
	printf("Secante: ");
	if ((IfFloat(rCosseno,0))==1)
		printf("%.3f",(1/rCosseno));
	else
		printf("INEXISTENTE");
	gotoxy(6,17);
	printf("Cossecante: ");
	if ((IfFloat(rSeno,0))==1)
		printf("%.3f",(1/rSeno));
	else
		printf("INEXISTENTE");
	gotoxy(6,19);
	printf("Cotangente: ");
	if (((IfFloat(rTangente,0))==1)&&((IfFloat(rCosseno,0))==1))
		printf("%.3f",(1/rTangente));
	else
		printf("INEXISTENTE");
	gotoxy(23,21);
	printf("Pressione qualquer tecla para continuar.");
	getch();
}

int main()
{
	int iOpcao;
	float rEntrada;
	char sOpcao[10], sEntrada[10];
	INICIO:;
	DesenharMoldura("Opcao");
	ImprimirMenu1();
	scanf("%s",sOpcao);
	iOpcao=ValidarOpcao(sOpcao,1,3);
	switch(iOpcao)
	{
		case 1: ImprimirMenu2();
			scanf("%s",sOpcao);
			iOpcao=ValidarOpcao(sOpcao,1,3);
			switch(iOpcao)
			{
				case 1: DesenharMoldura("Angulo em graus");
					break;
				case 2: DesenharMoldura("Angulo em radianos");
					break;
				case 3: goto INICIO;
			}
			scanf("%f",&rEntrada);
			CalcularImprimirFuncoes(rEntrada,iOpcao);
			goto INICIO;
		case 2: ImprimirMenu3();
			scanf("%s",sOpcao);
			iOpcao=ValidarOpcao(sOpcao,1,7);
			switch(iOpcao)
			{
				case 1: DesenharMoldura("Seno");
					break;
				case 2: DesenharMoldura("Cosseno");
					break;
				case 3: DesenharMoldura("Tangente");
					break;
				case 4: DesenharMoldura("Secante");
					break;
				case 5: DesenharMoldura("Cossecante");
					break;
				case 6: DesenharMoldura("Cotangente");
					break;
				case 7: goto INICIO;
			}
			scanf("%f",&rEntrada);
			CalcularImprimirAngulos(rEntrada,iOpcao);
			goto INICIO;
		case 3: return 0;
	}
	return 0;
}