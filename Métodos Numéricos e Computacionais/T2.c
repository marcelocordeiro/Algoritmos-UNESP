#include <stdio.h>
#include <math.h>

#define MAX 50

void MontaMatrizCofatora(int Ordem, float M[MAX][MAX],float Aux[MAX][MAX],int l)
{
	int cont = 0;
	int i;
	int j;
	for(i = 0; i < Ordem; i++)
	{
		if(i != l)
		{
			for(j = 1; j < Ordem; j++)
			{
				Aux[cont][j-1] = M[i][j];
			}
			cont++;
		}
	}
}
float Determinante(int Ordem, float M[MAX][MAX] )
{
	float somatoria = 0;
	float Aux[MAX][MAX];
	if(Ordem != 0)
    {
        int i;
        for(i = 0; i < Ordem; i++)
        {
            MontaMatrizCofatora(Ordem,M,Aux,i);
            somatoria += M[i][0] * pow(-1,i) * Determinante(Ordem - 1, Aux);
        }
        return somatoria;
    }
	else
    {
        return 1;
    }
}
void SistemaTriangularSuperior(int n,float a[MAX][MAX],float b[MAX],float x[MAX])
{
    int i,j;
    float aux;
    x[n-1] = b[n-1]/a[n-1][n-1];
    for(i=n-2;i>=0;i--)
    {
        aux = 0;
        for(j=i+1;j<=n-1;j++)
            aux += a[i][j]*x[j];
        x[i]=(b[i]-aux)/a[i][i];
    }
}
void SistemaTriangularInferior(int n,float a[MAX][MAX],float b[MAX],float x[MAX])
{
    int i,j;
    float aux;
    x[0] = b[0]/a[0][0];
    for(i=1;i<n;i++)
    {
        aux = 0;
        for(j=0;j<i;j++)
            aux += a[i][j]*x[j];
        x[i]=(b[i]-aux)/a[i][i];
    }
}
int MontaSubMatriz(int OrdemSub, float M[MAX][MAX], float Sub[MAX][MAX])
{
	int i,j;
	for(i = 0; i < OrdemSub; i++)
		for(j= 0;j < OrdemSub; j++)
			Sub[i][j] = M[i][j];
}
int VerificaMatriz(int Ordem, float M[MAX][MAX])
{
    float Aux[MAX][MAX];
    int i;
	for(i = 1; i <= Ordem; i++)
	{
		MontaSubMatriz(i,M,Aux);
		if(Determinante(i,Aux) <= 0) return 0;
	}
	return 1;
}
void DecomposicaoLU(int Ordem, float M[MAX][MAX], float B[MAX], float X[MAX])
{
    float L[MAX][MAX], U[MAX][MAX], Y[MAX], aux=0; //[linha][coluna]
    int cont1, cont2, cont3;
    printf("\n");
    if (!(VerificaMatriz(Ordem,M)))
    {
        printf("Convergencia nao garantida.");
        return;
    }
    for (cont1=0; cont1<Ordem;cont1++)
    {
        U[0][cont1] = M[0][cont1];
        L[cont1][0] = M[cont1][0]/U[0][0];
    }
    for(cont1=1;cont1<Ordem;cont1++)
    {
        for(cont2=0;cont2<cont1;cont2++)
        {
             for(cont3=0;cont3<=(cont2-1);cont3++)
                  aux += L[cont1][cont3] * U[cont3][cont2];
             L[cont1][cont2] = (M[cont1][cont2] - aux) / U[cont2][cont2];
             aux = 0;
        }
        L[cont1][cont1] = 1;
        for(cont2=cont1;cont2<Ordem;cont2++)
        {
             for(cont3=0;cont3<=(cont1-1);cont3++)
                  aux += L[cont1][cont3] * U[cont3][cont2];
             U[cont1][cont2] = M[cont1][cont2] - aux;
             aux = 0;
        }
    }
	SistemaTriangularInferior(Ordem,L,B,Y);
    SistemaTriangularSuperior(Ordem,U,Y,X);
}
int Simetria(int Ordem, float M[MAX][MAX])
{
    int cont1, cont2;
    for (cont1=0;cont1<Ordem;cont1++)
        for (cont2=0;cont2<cont1;cont2++)
            if (M[cont1][cont2] != M[cont2][cont1])
                return 0;
    return 1;
}
void Cholesky(int Ordem, float M[MAX][MAX], float B[MAX], float X[MAX])
{
    float L[MAX][MAX], LT[MAX][MAX], Y[MAX], aux=0; //[linha][coluna]
    int cont1, cont2, cont3;
    if ((!(VerificaMatriz(Ordem,M)))||(!(Simetria(Ordem,M))))
    {
        printf("Convergencia nao garantida.");
        return;
    }
    for (cont1=0;cont1<Ordem;cont1++)
    {
        for (cont2=0;cont2<=cont1;cont2++)
        {
            aux = 0;
            for (cont3=0;cont3<cont2;cont3++)
                aux += L[cont1][cont3] * L[cont2][cont3];
            if (cont1 == cont2)
                L[cont1][cont1] = sqrt(M[cont1][cont1] - aux);
            else
                L[cont1][cont2] = (M[cont1][cont2] - aux)/L[cont2][cont2];
        }
    }
    for (cont1=0;cont1<Ordem;cont1++)
        for (cont2=0;cont2<Ordem;cont2++)
            LT[cont1][cont2] = L[cont2][cont1];
    SistemaTriangularInferior(Ordem,L,B,Y);
    SistemaTriangularSuperior(Ordem,LT,Y,X);
}
void MatrizInversa(int Ordem,float M[MAX][MAX],float X[MAX][MAX])
{
    float
        VetIdentidade[MAX],
        VetSolucao[MAX];
    int i,j,k;
    for(i = 0; i < Ordem; i++)
    {
        for(j = 0; j < Ordem; j++)
        {
            if(j != i)
                VetIdentidade[j] = 0;
            else
                VetIdentidade[j] = 1;
        }
        DecomposicaoLU(Ordem,M,VetIdentidade,VetSolucao);
        for(k = 0; k < Ordem; k++)
            X[k][i] = VetSolucao[k];
    }
}
int CriterioLinhas(int Ordem,float M[MAX][MAX])
{
	int i, j;
	float somatoria, maximo;
	for(i = 0; i < Ordem; i++)
	{
		somatoria = 0;
		for(j = 0; j < Ordem; j++)
		{
			if(j != i)
				somatoria += fabs((M[i][j]/M[i][i]));
		}
		if(i != 0)
			if(somatoria > maximo)
				maximo = somatoria;
		else
			maximo = somatoria;
	}
	if (maximo - 1 >= 0)
		return 0;
	return 1;
}
int CriterioColunas(int Ordem,float M[MAX][MAX])
{
	int i, j;
	float somatoria, maximo;
	for(j = 0; j < Ordem; j++)
	{
		somatoria = 0;
		for(i = 0; i < Ordem; i++)
		{
			if(j != i)
				somatoria += fabs((M[i][j]/M[j][j]));
		}
		if(j != 0)
			if(somatoria > maximo)
				maximo = somatoria;
		else
			maximo = somatoria;
	}
	if (maximo - 1 >= 0)
		return 0;
	return 1;
}
int CriterioParadaJacobi(float VetK[MAX],float VetAproximacao[MAX],int Ordem, float Ep)
{
	int i;
	float maximoCima = fabs(VetAproximacao[0] - VetK[0]);
	float maximoBaixo = 1;
	for(i = 0; i < Ordem; i++)
	{
		if(fabs(VetK[i] - VetAproximacao[i]) > maximoCima)
			maximoCima = fabs(VetK[i] - VetAproximacao[i]);
		if(fabs(VetK[i]) > 1)
			maximoBaixo = fabs(VetK[i]);
	}
	if(maximoCima/maximoBaixo < Ep) return 1;
	return 0;
}
void Jacobi(int Ordem,float M[MAX][MAX],float VetInd[MAX],float Ep, float VetAproximacao[MAX],int K, float X[MAX], int *N)
{
	int parada = 0;
    int i, j, continua = 1;
    for(i = 1; i <= Ordem && continua; i++) 		//O i seria a ordem da 'sub-matriz', por
        if(Determinante(i,M) == 0) continua = 0; 	//isso precisa variar de 1 a N.
    if(continua && (((CriterioLinhas(Ordem,M)) || (CriterioColunas(Ordem,M)))))
    {
    	float VetK[MAX];
    	do
		{
			for(i = 0; i < Ordem; i++)
			{
				float somatoria = 0;
				for(j = 0; j < Ordem; j++)
				{
					if(j != i)
						somatoria += (M[i][j] *VetAproximacao[j]);
				}
				VetK[i] = (VetInd[i] - somatoria)/M[i][i];
			}
			K--;
			parada = CriterioParadaJacobi(VetK,VetAproximacao,Ordem,Ep);
			for(i = 0; i < Ordem; i++)
				VetAproximacao[i] = VetK[i];
			(*N)++;
		}
		while(!parada && K);
		for(i = 0; i < Ordem; i++)
				X[i] = VetK[i];
    }
}
int CriterioSassenfeld(int Ordem,float M[MAX][MAX])
{
	float
		B[MAX],
		maximo,
		somatoria1,
		somatoria2;
	int i,j,k;
	maximo = 1;
	for(i = 0; i <  Ordem; i++)
	{
		somatoria1 = 0;
		somatoria2 = 0;
		for(j = 0; j < i - 1; j++)
		{
			somatoria1 += fabs(M[i][j]/M[i][i]) * B[j];
		}
		for(j = i+1; j < Ordem; j++)
		{
			somatoria2 += fabs(M[i][j]/M[i][i]);
		}
		B[i] = somatoria1 + somatoria2;
		if(B[i] -1 >= 0) return 0;
		return 1;
	}

}
void GaussSeidel(int Ordem,float M[MAX][MAX],float VetInd[MAX],float Ep, float VetAproximacao[MAX],int K, float X[MAX], int *N)
{
	int parada = 0;
    int i, j, continua = 1;
    for(i = 0; i < Ordem; i++)
		if(M[i][i] == 0)
			continua = 0;
	if(Determinante(Ordem,M) == 0)
		continua = 0;
    if(continua && (((CriterioLinhas(Ordem,M)) || (CriterioSassenfeld(Ordem,M)))))
    {
    	float VetK[MAX];
    	do
		{
			for(i = 0; i < Ordem; i++)
			{
				float somatoria1 = 0;
				float somatoria2 = 0;
				for(j = i; j < Ordem-i; j++)
				{
					if(j != i)
						somatoria1 += (M[i][j] *VetAproximacao[j]);
				}
				for(j = 0; j < i;j++)
					somatoria2 += (M[i][j] * VetK[j]);
				VetK[i] = (VetInd[i] - (somatoria1 + somatoria2))/M[i][i];
			}
			K--;
			parada = CriterioParadaJacobi(VetK,VetAproximacao,Ordem,Ep);
			for(i = 0; i < Ordem; i++)
				VetAproximacao[i] = VetK[i];
			(*N)++;
		}
		while(!parada && K);
		for(i = 0; i < Ordem; i++)
				X[i] = VetK[i];
    }
}
void Swap(int V[], int x, int y)
{
	int aux = V[x];
	V[x] = V[y];
	V[y] = aux;
}
void SistemaTriangularSuperiorGauss(int Ordem,float M[MAX][MAX],float VetInd[MAX],int VetPivo[MAX],float X[MAX])
{
    int i,j;
    float aux;
    for(i = Ordem-1; i >= 0; i--)
    {
        aux = 0;
        for(j = i ; j < Ordem - 1 ; j++)
        {
        	aux += M[VetPivo[i]][j+1]*X[j+1];
        }
        X[i]=(VetInd[VetPivo[i]]-aux)/M[VetPivo[i]][i];
    }
}
void GaussSTL(int Ordem,float M[MAX][MAX],float VetInd[MAX],float X[MAX])
{
	int VetPivo[MAX], iPivo= 0 ,i,j;
	float multiplicador;
	for(i = 0; i < Ordem; i++) //Inicia o Pivo
		VetPivo[i] = i;
	for(i = 0; i < Ordem-1; i++)
	{
		float maximo = M[VetPivo[i]][i];
		for(j = i; j < Ordem; j++)
		{
			if(fabs(M[VetPivo[j]][i]) > maximo)
			{
				maximo = fabs(M[VetPivo[j]][i]);
				iPivo = j;
			}
		}
		Swap(VetPivo,i,iPivo);
		for(j = i+1 ; j < Ordem; j++)
		{
			int k,m;
			multiplicador = M[VetPivo[j]][i]/M[VetPivo[i]][i];
			for(k = i; k < Ordem; k++)
			{
				M[VetPivo[j]][k] = M[VetPivo[j]][k]-multiplicador*M[VetPivo[i]][k];
			}
			VetInd[VetPivo[j]] = VetInd[VetPivo[j]] - multiplicador*VetInd[VetPivo[i]];
		}
	}
	SistemaTriangularSuperiorGauss(Ordem,M,VetInd,VetPivo,X);
}
int main()
{
	char opcao;
	printf("Trabalho 2 de Metodos Numericos Computacionais\n\n\n");
	do
	{
		printf("O que voce deseja?\n");
		printf("1. Resolucao de Sistemas Lineares\n2. Calculo da Matriz Inversa\n3. Sair\n");
		opcao = toupper(getch());
		system("cls");
		switch(opcao)
		{
			case '1':
			{
				int Ordem,i,j;
				float M[MAX][MAX],VetInd[MAX],x,X[MAX];
				char opcMenu;
				printf("Qual metodo deseja utilizar?\n");
				printf("1. Decomposicao LU\n2. Cholesky\n3. Gauss\n");
				printf("4. Jacobi\n5. Gauss-Seidel\n");
				opcMenu = toupper(getch());
				system("cls");
				printf("Qual a ordem de sua matriz?\n");
				scanf("%d",&Ordem);
				for(i = 0; i < Ordem; i++)
				{
					for(j = 0; j < Ordem; j++)
					{
						printf("M[%d][%d] = ",i,j);
						scanf("%f",&x);
						M[i][j] = x;
					}
				}
				system("cls");
				printf("Digite os termos independentes: \n");
				for(i = 0; i < Ordem; i++)
				{
					printf("B[%d] = ",i);
					scanf("%f",&x);
					VetInd[i] = x;
				}
				system("cls");
				switch(opcMenu)
				{
					case '1':
					{
						DecomposicaoLU(Ordem,M,VetInd,X);
						printf("Solucao: \n");
						for(i = 0; i < Ordem; i++)
							printf("%.5f\n",X[i]);
						break;
					}
					case '2':
					{
						Cholesky(Ordem,M,VetInd,X);
						printf("Solucao: \n");
						for(i = 0; i < Ordem; i++)
							printf("%.5f\n",X[i]);
						break;
					}
					case '3':
					{
						GaussSTL(Ordem,M,VetInd,X);
						printf("Solucao: \n");
						for(i = 0; i < Ordem; i++)
							printf("%.5f\n",X[i]);
						break;
					}
					case '4':
					{
						float Ep,VetAp[MAX];
						int n = 0,Iteracoes;
						printf("Com qual precisao deseja seus calculos?");
						scanf("%f",&Ep);
						printf("Digite os elementos do Vetor de aproximacao: \n");
						for(i = 0; i < Ordem; i++)
						{
							scanf("%f",&x);
							VetAp[i] = x;
						}
						printf("Qual seria o maximo de iteracoes?\n");
						scanf("%d",Iteracoes);
						Jacobi(Ordem,M,VetInd,Ep,VetAp,Iteracoes,X,&n);
						printf("Vetor aproximado: \n");
						for(i = 0; i < Ordem; i++)
						{
							printf("%.5f\n",X[i]);
						}
						printf("Numero de iteracoes executadas: %d",n);
						break;
					}
					case '5':
					{
						float Ep,VetAp[MAX];
						int n = 0,Iteracoes;
						printf("Com qual precisao deseja seus calculos?");
						scanf("%f",&Ep);
						printf("Digite os elementos do Vetor de aproximacao: \n");
						for(i = 0; i < Ordem; i++)
						{
							scanf("%f",&x);
							VetAp[i] = x;
						}
						printf("Qual seria o maximo de iteracoes?\n");
						scanf("%d",Iteracoes);
						GaussSeidel(Ordem,M,VetInd,Ep,VetAp,Iteracoes,X,&n);
						printf("Vetor aproximado: \n");
						for(i = 0; i < Ordem; i++)
						{
							printf("%.5f\n",X[i]);
						}
						printf("Numero de iteracoes executadas: %d",n);
						break;
						break;
					}
					default:
					{
						printf("Opcao invalida!");
					}
				}

				break;
			}
			case '2':
			{
				int Ordem,i,j;
				float M[MAX][MAX],x,Minv[MAX][MAX];
				printf("Qual a ordem de sua matriz?\n");
				scanf("%d",&Ordem);
				for(i = 0; i < Ordem; i++)
				{
					for(j = 0; j < Ordem; j++)
					{
						printf("M[%d][%d] = ",i,j);
						scanf("%f",&x);
						M[i][j] = x;
					}
				}
				MatrizInversa(Ordem,M,Minv);
				printf("------Matriz Inversa------\n");
				for(i = 0; i < Ordem; i++)
				{
					for(j = 0; j < Ordem; j++)
					{
						printf("%.5f   ",Minv[i][j]);
					}
					printf("\n");
				}
				printf("\n--------------------------\n");
				break;
			}
			case '3':
			{
				break;
			}
			default:
			{
				system("cls");
				printf("\nEssa opcao nao existe.\nTente pressionar 1, 2 ou 3.\n\n\n");
			}
		}
	}
	while(opcao != '3');
	return 0;
}
