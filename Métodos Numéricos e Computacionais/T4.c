#include <stdio.h>
#include <conio.h>
#include <math.h>
#define maxpontos 50
typedef float vetor[maxpontos];
typedef float matriz[maxpontos][maxpontos];
typedef float (*funcao)(float);

float f1(float x)
{
	return pow(x,3)+3*pow(x,2)/(x-1);
}

float f2(float x)
{
	return pow(x,2);
}

float Trapezio(funcao f, float a, float b, int subIntervalos)
{
	float h = (b - a)/subIntervalos;
	float somatorio = 0;
	int i;
	for(i = 0; i < subIntervalos; i++)
		somatorio += ((f(a + i*h)+f(a+(i+1)*h))*h)/2;
	return somatorio;

}

float UmTercoSimpson(funcao f, float a, float b, int subIntervalos)
{
	float h = (float)((float)(b - a)/(float)subIntervalos);
    float som_2=0, som=0, integral;
    int i;
    if (subIntervalos == 3)
        return (float)((float)h/(float)3*(f(a) + 4*f(a+h) + f(b)));
    if (subIntervalos%2 == 0)
    {
        for (i=1;i<subIntervalos;i++)
            if (i%2 == 0)
                som_2 += f(a+i*h);
            else
                som += f(a+i*h);
        integral = (float)((float)h/(float)3*(f(a) + 4*som + 2*som_2 + f(b)));
    }
    else
    {
        for (i=1;i<subIntervalos-1;i++)
            if (i%2 == 0)
                som_2 += f(a+i*h);
            else
                som += f(a+i*h);
        integral = (float)((float)h/(float)3*(f(a) + 4*som + 2*som_2 + f(b)));
        integral += Trapezio(f,b-h,b,2);
    }
    return integral;
}

float TresOitavosSimpson(funcao f, float a, float b, int subIntervalos)
{
    float h = (float)((float)(b - a)/(float)subIntervalos);
    float som_3=0, som=0;
    int i;
    if (subIntervalos == 4)
        return (float)((float)3/(float)8*(float)h*(f(a) + 3*f(a+h) + 3*f(b-h) + f(b)));
    for (i=1;i<subIntervalos;i++)
        if (i%3 == 0)
            som_3 += f(a+i*h);
        else
            som += f(a+i*h);
    return (float)((float)3/(float)8*((float)h)*(f(a) + 3*som + 2*som_3 + f(b)));
}

float QuadraturaGaussiana(funcao f, float a, float b, int subIntervalos)
{
    struct Gaussiana
    {
        float t[4], A[4];
    };
    int cont;
    float integral = 0;
    struct Gaussiana gauss[8];

    gauss[0].t[0] = 0;
    gauss[0].A[0] = 2;

    gauss[1].t[0] = 0.57735027;
    gauss[1].A[0] = 1;

    gauss[2].t[0] = 0.77459667;
    gauss[2].t[1] = 0;
    gauss[2].A[0] = 0.55555556;
    gauss[2].A[1] = 0.88888889;

    gauss[3].t[0] = 0.86113631;
    gauss[3].t[1] = 0.33998104;
    gauss[3].A[0] = 0.34785484;
    gauss[3].A[1] = 0.65214516;

    gauss[4].t[0] = 0.90617985;
    gauss[4].t[1] = 0.53846931;
    gauss[4].t[2] = 0;
    gauss[4].A[0] = 0.23692688;
    gauss[4].A[1] = 0.47862868;
    gauss[4].A[2] = 0.56888889;

    gauss[5].t[0] = 0.93246951;
    gauss[5].t[1] = 0.66120939;
    gauss[5].t[2] = 0.23861919;
    gauss[5].A[0] = 0.17132450;
    gauss[5].A[1] = 0.36076158;
    gauss[5].A[2] = 0.46791394;

    gauss[6].t[0] = 0.94910791;
    gauss[6].t[1] = 0.74153119;
    gauss[6].t[2] = 0.40584515;
    gauss[6].t[3] = 0;
    gauss[6].A[0] = 0.12948496;
    gauss[6].A[1] = 0.27970540;
    gauss[6].A[2] = 0.38183006;
    gauss[6].A[3] = 0.41795918;

    gauss[7].t[0] = 0.96028986;
    gauss[7].t[1] = 0.79666648;
    gauss[7].t[2] = 0.52553242;
    gauss[7].t[3] = 0.18343464;
    gauss[7].A[0] = 0.10122854;
    gauss[7].A[1] = 0.22238104;
    gauss[7].A[2] = 0.31370664;
    gauss[7].A[3] = 0.36268378;

    for (cont=0;cont<=((int)(subIntervalos/2)-1);cont++)
        integral += gauss[subIntervalos-1].A[cont]*(0.5*(b-a)*f(0.5*(b-a)*(-1)*gauss[subIntervalos-1].t[cont]+0.5*(b-a)));
    if (subIntervalos%2 != 0)
        integral += gauss[subIntervalos-1].A[subIntervalos/2]*(0.5*(b-a)*f(0.5*(b-a)*(-1)*gauss[subIntervalos-1].t[subIntervalos/2]+0.5*(b-a)));
    for (cont=((subIntervalos/2)-1);cont>=0;cont--)
        integral += gauss[subIntervalos-1].A[cont]*(0.5*(b-a)*f(0.5*(b-a)*gauss[subIntervalos-1].t[cont]+0.5*(b-a)));

    return integral;
}

int main()
{
	char opc;
	printf("TRABALHO 4 DE METODOS NUMERICOS COMPUTACIONAIS\n\n\n");
	do
	{
	    int iFuncao;
        float (*funcao)(float); //ponteiro pra funcao
        system("cls");
        printf("Com qual funcao gostaria de trabalhar?\n");
        printf("1. f(x) = x^3+3*x^2/(x-1)\n");
        printf("2. f(x) = x^2\n");
        scanf("%d",&iFuncao);
        if(iFuncao == 1)
            funcao = &f1;
        else if(iFuncao == 2)
            funcao = &f2;
        else
        {
            printf("Opcao Invalida");
            printf("Tecle para continuar...\n");
            getch();
            system("cls");
            break;
        }
        if(iFuncao == 1 || iFuncao == 2)
        {
            char opc2;
            float a;
            float b;
            int nSubintervalos;
            system("cls");
            printf("Qual metodo gostaria de usar?\n");
            printf("1. Trapezio 2. 1/3 Simpson \n3. 3/8 Simpson 4. Quadratura Gaussiana\n");
            fflush(stdin);
            opc2 = getch();
            printf("Digite o valor de a: ");
            scanf("%f",&a);
            printf("Digite o valor de b: ");
            scanf("%f",&b);
            printf("Digite o numero de subintervalos: ");
            scanf("%d",&nSubintervalos);
            switch(opc2)
            {
                case '1':
                {
                    system("cls");
                    printf("Integral no intervalo [%.3f %.3f] = %.4f\n",a,b,Trapezio(funcao,a,b,nSubintervalos));
                    printf("Tecle para continuar...\n");
                    getch();
                    system("cls");
                    break;
                }
                case '2':
                {

                    system("cls");
                    printf("Integral no intervalo [%.3f %.3f] = %.4f\n",a,b,UmTercoSimpson(funcao,a,b,nSubintervalos));
                    printf("Tecle para continuar...\n");
                    getch();
                    system("cls");
                    break;
                }
                case '3':
                {
                    system("cls");
                    if ((nSubintervalos%3 != 0) && (nSubintervalos != 4))
                    {
                        printf("O numero de intervalos deve ser 4 ou algum multiplo de 3.");
                        break;
                    }
                    printf("Integral no intervalo [%.3f %.3f] = %.4f\n",a,b,TresOitavosSimpson(funcao,a,b,nSubintervalos));
                    printf("Tecle para continuar...\n");
                    getch();
                    system("cls");
                    break;
                }
                case '4':
                {
                    system("cls");
                    if (nSubintervalos > 8)
                    {
                        printf("O numero de intervalos deve ser no maximo 8.");
                        break;
                    }
                    printf("Integral no intervalo [%.3f %.3f] = %.4f\n",a,b,QuadraturaGaussiana(funcao,a,b,nSubintervalos));;
                    printf("Tecle para continuar...\n");
                    getch();
                    system("cls");
                    break;
                }
                default:
                {
                    system("cls");
                    printf("Opcao Invalida\n");
                    break;
                }
            }
            getch();
            system("cls");
        }
        printf("Gostaria de sair do programa? (S/N)\n");
        fflush(stdin);
        scanf("%c",&opc);
	}
	while((opc != 'S')&&(opc != 's'));
	return 0;
}
