{Nome: Marcelo Augusto Cordeiro
  RA: 121023265
  Linguagem de programacao: Pascal
  Compilador: Borland Pascal 7.0
  Sistema operacional: Windows 7}

uses crt;

const
	MAX = 10;
	COR = LIGHTGREEN;

type 
	matriz = Array[1..MAX,1..MAX] of integer;
	vetor = Array[1..MAX] of integer;

{----------------------------------------------------------------------------}
procedure LimparFinalLinha(iX, iY, iMax: integer);
begin
	gotoxy(iX,iY);
	clreol;
	gotoxy(iMax,iY);
	write(chr(186));
	gotoxy(iX,iY);
end;
{----------------------------------------------------------------------------}
procedure DesenharMoldura;
var
	iCont: integer;
begin
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr;
	for iCont:=3 to 78 do
	begin
		gotoxy(iCont,2);
		write(chr(205));
		gotoxy(iCont,24);
		write(chr(205));
		gotoxy(iCont,4);
		write(chr(205));
	end;
	for iCont:=3 to 23 do
	begin
		gotoxy(2,iCont);
		write(chr(186));
		gotoxy(79,iCont);
		write(chr(186));
	end;
	gotoxy(2,2);
	write(chr(201));
	gotoxy(79,2);
	write(chr(187));
	gotoxy(2,24);
	write(chr(200));
	gotoxy(79,24);
	write(chr(188));
	gotoxy(2,4);
	write(chr(204));
	gotoxy(79,4);
	write(chr(185));
	gotoxy(33,3);
	write('ARRAYS CALCULATOR');
end;
{----------------------------------------------------------------------------}
procedure ImprimirMenu1(iSelect: integer);
begin
	gotoxy(26,9);
	write('Obter a matriz transposta');
	gotoxy(26,10);
	write('Somar as duas matrizes');
	gotoxy(26,11);
	write('Subtrair as duas matrizes');
	gotoxy(26,12);
	write('Calcular o produto matricial');
	gotoxy(26,13);
	write('Verificar simetria');
	gotoxy(26,14);
	write('Verificar quadrado magico');
	gotoxy(26,15);
	write('Verificar permutacao');
	gotoxy(26,16);
	write('Verificar quadrado latino');
	gotoxy(26,17);
	write('Configuracoes');
	gotoxy(26,18);
	write('Sair');
	textcolor(COR);
	case iSelect of
		01: begin
				gotoxy(26,9);
				write(chr(175),' Obter a matriz transposta ',chr(174));
			end;
		02: begin
				gotoxy(26,10);
				write(chr(175),' Somar as duas matrizes ',chr(174));
			end;
		03: begin
				gotoxy(26,11);
				write(chr(175),' Subtrair as duas matrizes ',chr(174));
			end;
		04: begin
				gotoxy(26,12);
				write(chr(175),' Calcular o produto matricial ',chr(174));
			end;
		05: begin
				gotoxy(26,13);
				write(chr(175),' Verificar simetria ',chr(174));
			end;
		06: begin
				gotoxy(26,14);
				write(chr(175),' Verificar quadrado magico ',chr(174));
			end;
		07: begin
				gotoxy(26,15);
				write(chr(175),' Verificar permutacao ',chr(174));
			end;
		08: begin
				gotoxy(26,16);
				write(chr(175),' Verificar quadrado latino ',chr(174));
			end;
		09: begin
				gotoxy(26,17);
				write(chr(175),' Configuracoes ',chr(174));
			end;
		10: begin
				gotoxy(26,18);
				write(chr(175),' Sair ',chr(174));
			end;
	end;
	textcolor(WHITE);
end;
{----------------------------------------------------------------------------}
procedure Selecionar(iX, iY, iAntes, iMax, iTela: integer; sTexto1, sTexto2: String; lDirec: boolean);
{TRUE para cima e FALSE para baixo}
begin
	LimparFinalLinha(iX,iY,iTela);
	write(sTexto1); {escrevi o que estava selecionado antes}
	if lDirec then {seta para cima}
		if (iAntes=1) then
			LimparFinalLinha(iX,iY+iMax-iAntes,iTela) {limpei a última linha}
		else
			LimparFinalLinha(iX,iY-1,iTela) {limpei a linha de cima}
	else {seta para baixo}
		if (iAntes=iMax) then
			LimparFinalLinha(iX,iY-iMax+1,iTela) {limpei a primeira linha}
		else
			LimparFinalLinha(iX,iY+1,iTela); {limpei a linha de baixo}
	textcolor(COR);
	write(chr(175),' ',sTexto2,' ',chr(174)); {escrevi o texto selecionado}
	textcolor(WHITE);
end;
{----------------------------------------------------------------------------}
function SelecionarOpcao1(iSelect: integer):integer;
var
	cTecla: char;
	lFuncao, lEnter: boolean;
begin
	repeat
		lFuncao := true;
		lEnter := false;
		cTecla := ReadKey;
		if (cTecla = #0) then
			cTecla := ReadKey
		else
			lFuncao := false;
		if lFuncao then
			case cTecla of
				#72: begin {seta para cima}
						case iSelect of
							01: begin
									Selecionar(26,9,1,10,79,'Obter a matriz transposta','Sair',true);
									iSelect:=10;
								end;
							02: begin
									Selecionar(26,10,2,10,79,'Somar as duas matrizes','Obter a matriz transposta',true);
									iSelect:=1;
								end;
							03: begin
									Selecionar(26,11,3,10,79,'Subtrair as duas matrizes','Somar as duas matrizes',true);
									iSelect:=2;
								end;
							04: begin
									Selecionar(26,12,4,10,79,'Calcular o produto matricial','Subtrair as duas matrizes',true);
									iSelect:=3;
								end;
							05: begin
									Selecionar(26,13,5,10,79,'Verificar simetria','Calcular o produto matricial',true);
									iSelect:=4;
								end;
							06: begin
									Selecionar(26,14,6,10,79,'Verificar quadrado magico','Verificar simetria',true);
									iSelect:=5;
								end;
							07: begin
									Selecionar(26,15,7,10,79,'Verificar permutacao','Verificar quadrado magico',true);
									iSelect:=6;
								end;
							08: begin
									Selecionar(26,16,8,10,79,'Verificar quadrado latino','Verificar permutacao',true);
									iSelect:=7;
								end;
							09: begin
									Selecionar(26,17,9,10,79,'Configuracoes','Verificar quadrado latino',true);
									iSelect:=8;
								end;
							10: begin
									Selecionar(26,18,10,10,79,'Sair','Configuracoes',true);
									iSelect:=9;
								end;
						end;
					end;
				#80: begin {seta para baixo}
						case iSelect of
							01: begin
									Selecionar(26,9,1,10,79,'Obter a matriz transposta','Somar as duas matrizes',false);
									iSelect:=2;
								end;
							02: begin
									Selecionar(26,10,2,10,79,'Somar as duas matrizes','Subtrair as duas matrizes',false);
									iSelect:=3;
								end;
							03: begin
									Selecionar(26,11,3,10,79,'Subtrair as duas matrizes','Calcular o produto matricial',false);
									iSelect:=4;
								end;
							04: begin
									Selecionar(26,12,4,10,79,'Calcular o produto matricial','Verificar simetria',false);
									iSelect:=5;
								end;
							05: begin
									Selecionar(26,13,5,10,79,'Verificar simetria','Verificar quadrado magico',false);
									iSelect:=6;
								end;
							06: begin
									Selecionar(26,14,6,10,79,'Verificar quadrado magico','Verificar permutacao',false);
									iSelect:=7;
								end;
							07: begin
									Selecionar(26,15,7,10,79,'Verificar permutacao','Verificar quadrado latino',false);
									iSelect:=8;
								end;
							08: begin
									Selecionar(26,16,8,10,79,'Verificar quadrado latino','Configuracoes',false);
									iSelect:=9;
								end;
							09: begin
									Selecionar(26,17,9,10,79,'Configuracoes','Sair',false);
									iSelect:=10;
								end;
							10: begin
									Selecionar(26,18,10,10,79,'Sair','Obter a matriz transposta',false);
									iSelect:=1;
								end;
						end;
					end;
				#59: begin {F1}
						clrscr;
						DesenharMoldura;
						ImprimirMenu1(9);
						iSelect:=9; {configuracoes}
						lEnter:=true;
					end;
			end
		else
			case cTecla of
				#27: begin {ESC}
						iSelect:=10; {sair}
						lEnter:=true;
					end;
				#13: lEnter := true; {ENTER}
			end;
		SelecionarOpcao1:=iSelect;
	until (lEnter);
end;
{----------------------------------------------------------------------------}
function SelecionarOpcao2(iSelect: integer):integer;
var
	cTecla: char;
	lFuncao, lEnter: boolean;
begin
	repeat
		lFuncao := true;
		lEnter := false;
		cTecla := ReadKey;
		if (cTecla = #0) then
			cTecla := ReadKey
		else
			lFuncao := false;
		if lFuncao then
			case cTecla of
				#72: begin {seta para cima}
						case iSelect of
							01: begin
									Selecionar(4,2,1,5,25,'Trocar matriz 1','Voltar',true);
									iSelect:=5;
								end;
							02: begin
									Selecionar(4,3,2,5,25,'Trocar matriz 2','Trocar matriz 1',true);
									iSelect:=1;
								end;
							03: begin
									Selecionar(4,4,3,5,25,'Ver matriz 1','Trocar matriz 2',true);
									iSelect:=2;
								end;
							04: begin
									Selecionar(4,5,4,5,25,'Ver matriz 2','Ver matriz 1',true);
									iSelect:=3;
								end;
							05: begin
									Selecionar(4,6,5,5,25,'Voltar','Ver matriz 2',true);
									iSelect:=4;
								end;
						end;
					end;
				#80: begin {seta para baixo}
						case iSelect of
							01: begin
									Selecionar(4,2,1,5,25,'Trocar matriz 1','Trocar matriz 2',false);
									iSelect:=2;
								end;
							02: begin
									Selecionar(4,3,2,5,25,'Trocar matriz 2','Ver matriz 1',false);
									iSelect:=3;
								end;
							03: begin
									Selecionar(4,4,3,5,25,'Ver matriz 1','Ver matriz 2',false);
									iSelect:=4;
								end;
							04: begin
									Selecionar(4,5,4,5,25,'Ver matriz 2','Voltar',false);
									iSelect:=5;
								end;
							05: begin
									Selecionar(4,6,5,5,25,'Voltar','Trocar matriz 1',false);
									iSelect:=1;
								end;
						end;
					end;
			end
		else
			case cTecla of
				#27: begin {ESC}
						iSelect:=5; {voltar}
						lEnter:=true;
					end;
				#13: lEnter := true; {ENTER}
			end;
		SelecionarOpcao2:=iSelect;
	until (lEnter);
end;
{----------------------------------------------------------------------------}
function SelecionarOpcao3(iSelect: integer):integer;
var
	cTecla: char;
	lFuncao, lEnter: boolean;
begin
	repeat
		lFuncao := true;
		lEnter := false;
		cTecla := ReadKey;
		if (cTecla = #0) then
			cTecla := ReadKey
		else
			lFuncao := false;
		if lFuncao then
			case cTecla of
				#72: begin {seta para cima}
						case iSelect of
							01: begin
									Selecionar(4,2,1,3,18,'Matriz 1','Voltar',true);
									iSelect:=3;
								end;
							02: begin
									Selecionar(4,3,2,3,18,'Matriz 2','Matriz 1',true);
									iSelect:=1;
								end;
							03: begin
									Selecionar(4,4,3,3,18,'Voltar','Matriz 2',true);
									iSelect:=2;
								end;
						end;
					end;
				#80: begin {seta para baixo}
						case iSelect of
							01: begin
									Selecionar(4,2,1,3,18,'Matriz 1','Matriz 2',false);
									iSelect:=2;
								end;
							02: begin
									Selecionar(4,3,2,3,18,'Matriz 2','Voltar',false);
									iSelect:=3;
								end;
							03: begin
									Selecionar(4,4,3,3,18,'Voltar','Matriz 1',false);
									iSelect:=1;
								end;
						end;
					end;
			end
		else
			case cTecla of
				#27: begin {ESC}
						iSelect:=3; {voltar}
						lEnter:=true;
					end;
				#13: lEnter := true; {ENTER}
			end;
		SelecionarOpcao3:=iSelect;
	until (lEnter);
end;
{----------------------------------------------------------------------------}
function ValidarEntrada(sNum: string; iMin, iMax, iX, iY: integer): integer;
var
	iEstado,iNum: integer;
begin
	val(sNum, iNum, iEstado);
	if (((iNum<iMin) or (iNum>iMax))or(iEstado<>0)) then
	begin
		repeat
			LimparFinalLinha(iX,iY,79);
			textcolor(RED);
			write(sNum,'!');
			textcolor(WHITE);
			sound(900);
			delay(500);
			nosound;
			LimparFinalLinha(iX,iY,79);
			readln(sNum);
			val(sNum, iNum, iEstado);
		until(((iNum>=iMin) and (iNum<=iMax))and(iEstado=0));
	end;
	ValidarEntrada:=iNum;
end;
{----------------------------------------------------------------------------}
procedure LerMatriz(iNum: integer; var iColuna, iLinha: integer; var miMat: matriz);
var
	iColuna2, iLinha2: integer;
	sColuna, sLinha, sNum: string[10];
begin
	DesenharMoldura;
	gotoxy(6,7);
	write('Digite a quantidade de colunas da matriz ',iNum,' (de 1 a 10): ');
	readln(sColuna);
	iColuna:=ValidarEntrada(sColuna,1,10,62,7);
	gotoxy(6,9);
	write('Digite a quantidade de linhas da matriz ',iNum,' (de 1 a 10): ');
	readln(sLinha);
	iLinha:=ValidarEntrada(sLinha,1,10,61,9);
	DesenharMoldura;
	gotoxy(6,7);
	write('Digite os elementos da matriz ',iNum,' (numeros entre -999 e 999)');
	for iColuna2:=1 to iColuna do
	begin
		gotoxy(32-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),10);
		write(chr(205),chr(205),chr(205),chr(205),chr(205));
		gotoxy(34-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),9);
		write(iColuna2);
	end;
	for iLinha2:=1 to iLinha do
	begin
		gotoxy(36-(((iColuna-1)*5) div 2),10+iLinha2);
		write(chr(186));
		if iLinha2=10 then
			gotoxy(33-(((iColuna-1)*5) div 2),10+iLinha2)
		else
			gotoxy(34-(((iColuna-1)*5) div 2),10+iLinha2);
		write(iLinha2);
	end;
	gotoxy(36-(((iColuna-1)*5) div 2),10);
	write(chr(201));
	for iColuna2:=1 to iColuna do
	begin
		for iLinha2:=1 to iLinha do
		begin
			gotoxy(34-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),10+iLinha2);
			readln(sNum);
			miMat[iColuna2,iLinha2]:=ValidarEntrada
			(sNum,-999,999,(34-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2))),(10+iLinha2));
		end;
	end;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
procedure ImprimirMatriz(iColuna, iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2: integer;
begin
	DesenharMoldura;
	for iColuna2:=1 to iColuna do
	begin
		gotoxy(32-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),7);
		write(chr(205),chr(205),chr(205),chr(205),chr(205));
		gotoxy(34-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),6);
		write(iColuna2);
	end;
	for iLinha2:=1 to iLinha do
	begin
		gotoxy(36-(((iColuna-1)*5) div 2),7+iLinha2);
		write(chr(186));
		if iLinha2=10 then
			gotoxy(33-(((iColuna-1)*5) div 2),7+iLinha2)
		else
			gotoxy(34-(((iColuna-1)*5) div 2),7+iLinha2);
		write(iLinha2);
	end;
	gotoxy(36-(((iColuna-1)*5) div 2),7);
	write(chr(201));
	for iColuna2:=1 to iColuna do
	begin
		for iLinha2:=1 to iLinha do
		begin
			gotoxy(34-(((iColuna-1)*5) div 2)+(iColuna2+(4*iColuna2)),7+iLinha2);
			write(miMatriz[iColuna2,iLinha2]);
		end;
	end;
end;
{----------------------------------------------------------------------------}
procedure DesenharMoldurazinha(iX1, iY1, iX2, iY2: integer);
var
	iCont: integer;
begin
	for iCont:=2 to (iX2-iX1) do
	begin
		gotoxy(iCont,1);
		write(chr(205));
		gotoxy(iCont,iY2-iY1+1);
		write(chr(205));
	end;
	for iCont:=2 to (iY2-iY1) do
	begin
		gotoxy(1,iCont);
		write(chr(186));
		gotoxy(iX2-iX1+1,iCont);
		write(chr(186));
	end;
	gotoxy(1,1);
	write(chr(201));
	gotoxy(iX2-iX1+1,1);
	write(chr(187));
	gotoxy(1,iY2-iY1+1);
	write(chr(200));
	gotoxy(iX2-iX1+1,iY2-iY1+1);
	write(chr(188));
end;
{----------------------------------------------------------------------------}
procedure Configurar(var iColuna1,iLinha1,iColuna2,iLinha2: integer; var miMat1, miMat2: matriz);
var
	iOpcao: integer;
begin
	window(27,14,52,20);
	clrscr;
	DesenharMoldurazinha(27,14,51,20);
	gotoxy(4,2);
	textcolor(COR);
	write(chr(175),' Trocar matriz 1 ',chr(174));
	textcolor(WHITE);
	gotoxy(4,3);
	write('Trocar matriz 2');
	gotoxy(4,4);
	write('Ver matriz 1');
	gotoxy(4,5);
	write('Ver matriz 2');
	gotoxy(4,6);
	write('Voltar');
	iOpcao:=SelecionarOpcao2(1);
	window(1,1,80,25);
	case iOpcao of
		01: LerMatriz(1,iColuna1,iLinha1,miMat1);
		02: LerMatriz(2,iColuna2,iLinha2,miMat2);
		03:	begin
				ImprimirMatriz(iColuna1,iLinha1,miMat1);
				gotoxy(19,iLinha1+10);
				write('Pressione qualquer tecla para continuar.');
				readkey;
			end;
		04: begin
				ImprimirMatriz(iColuna2,iLinha2,miMat2);
				gotoxy(19,iLinha2+10);
				write('Pressione qualquer tecla para continuar.');
				readkey;
			end;
	end;
	DesenharMoldura;
	ImprimirMenu1(9);
end;
{----------------------------------------------------------------------------}
procedure VerificarSimetria(iColuna, iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2: integer;
	lSimet: boolean;
begin
	lSimet:=true;
	iColuna2:=2;
	if (iLinha=iColuna) then
	begin
		while ((iColuna2<=iColuna) and lSimet) do
		begin
			iLinha2:=1;
			while ((iLinha2<=iColuna2-1) and lSimet) do
			begin
				if (miMatriz[iColuna2,iLinha2]<>miMatriz[iLinha2,iColuna2]) then
					lSimet:=false;
				inc(iLinha2);
			end;
			inc(iColuna2);
		end;
	end
	else
		lSimet:=false;
	ImprimirMatriz(iColuna,iLinha,miMatriz);
	gotoxy(34,iLinha+9);
	if lSimet then
		write ('Simetrica')
	else
		write ('Nao simetrica');
	gotoxy(19,iLinha+10);
	if (iLinha<>iColuna) then
		write('Apenas matrizes quadradas podem ser simetricas.');
	gotoxy(19,iLinha+12);
	write('Pressione qualquer tecla para continuar.');
	readkey;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
procedure ObterTransposta(iColuna,iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2: integer;
	miTransp: matriz;
begin
	for iColuna2:=1 to iColuna do
		for iLinha2:=1 to iLinha do
			miTransp[iLinha2,iColuna2]:=miMatriz[iColuna2,iLinha2];
	ImprimirMatriz(iColuna,iLinha,miMatriz);
	gotoxy(34,iLinha+9);
	write ('Original');
	gotoxy(19,iLinha+11);
	write('Pressione qualquer tecla para ver a tranposta.');
	readkey;
	ImprimirMatriz(iLinha,iColuna,miTransp);
	gotoxy(34,iLinha+9);
	write('Transposta');
	LimparFinalLinha(19,iLinha+11,79);
	write('Pressione qualquer tecla para continuar.');
	readkey;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
procedure EscolherMatriz(iSelect, iColuna1, iLinha1, iColuna2, iLinha2: integer; 
var iLinha, iColuna: integer; mi1, mi2: matriz; var miEscolha: matriz; var lEscolheu: boolean);
var
	iOpcao: integer;
begin
	lEscolheu:=true;
	window(30,6+iSelect,48,10+iSelect);
	clrscr;
	DesenharMoldurazinha(30,6+iSelect,47,10+iSelect);
	gotoxy(4,2);
	textcolor(COR);
	write(chr(175),' Matriz 1 ',chr(174));
	textcolor(WHITE);
	gotoxy(4,3);
	write('Matriz 2');
	gotoxy(4,4);
	write('Voltar');
	iOpcao:=SelecionarOpcao3(1);
	window(1,1,80,25);
	DesenharMoldura;
	case iOpcao of
		01: begin
				miEscolha:=mi1;
				iColuna:=iColuna1;
				iLinha:=iLinha1;
			end;
		02: begin
				miEscolha:=mi2;
				iColuna:=iColuna2;
				iLinha:=iLinha2;
			end;
		03: begin
				lEscolheu:=false;
				ImprimirMenu1(iSelect);
			end;
	end;
end;
{----------------------------------------------------------------------------}
procedure AvisarColunaLinha(iSelect: integer);
begin
	if (iSelect in [2..3]) then
	begin
		window(22,6+iSelect,55,10+iSelect);
		clrscr;
		DesenharMoldurazinha(22,6+iSelect,54,10+iSelect);
		gotoxy(4,2);
		write('Apenas matrizes com o mesmo');
		gotoxy(4,3);
		write('numero de linhas e colunas');
		gotoxy(4,4);
		write('podem ser ');
		case iSelect of
			02: write('somadas.');
			03: write('subtraidas.');
		end;
	end;
	if (iSelect=4) then
	begin
		window(22,6+iSelect,56,11+iSelect);
		clrscr;
		DesenharMoldurazinha(22,6+iSelect,55,11+iSelect);
		gotoxy(4,2);
		write('O produto matricial so existe');
		gotoxy(4,3);
		write('se o numero de colunas da ma-');
		gotoxy(4,4);
		write('triz 1 for igual ao numero de');
		gotoxy(4,5);
		write('linhas da matriz 2.');
	end;
	readkey;
	clrscr;
	window(1,1,80,25);
end;
{----------------------------------------------------------------------------}
procedure SomarMatrizes(iColuna1,iLinha1,iColuna2,iLinha2:integer; mi1,mi2:matriz);
var
	miSoma: matriz;
	iColuna, iLinha, iDelay: integer;
begin
	if (iColuna1=iColuna2) and (iLinha1=iLinha2) then
	begin
		for iColuna:=1 to iColuna1 do
			for iLinha:=1 to iLinha1 do
				miSoma[iColuna,iLinha]:=mi1[iColuna,iLinha]+mi2[iColuna,iLinha];
		ImprimirMatriz(iColuna1,iLinha1,miSoma);
		gotoxy(19,iLinha+12);
		write('Pressione qualquer tecla para continuar.');
		readkey;
		DesenharMoldura;
	end
	else
		AvisarColunaLinha(2);
end;
{----------------------------------------------------------------------------}
procedure SubtrairMatrizes(iColuna1,iLinha1,iColuna2,iLinha2:integer; mi1,mi2:matriz);
var
	miSoma: matriz;
	iColuna, iLinha, iDelay: integer;
begin
	if (iColuna1=iColuna2) and (iLinha1=iLinha2) then
	begin
		for iColuna:=1 to iColuna1 do
			for iLinha:=1 to iLinha1 do
				miSoma[iColuna,iLinha]:=mi1[iColuna,iLinha]-mi2[iColuna,iLinha];
		ImprimirMatriz(iColuna1,iLinha1,miSoma);
		gotoxy(19,iLinha+12);
		write('Pressione qualquer tecla para continuar.');
		readkey;
		DesenharMoldura;
	end
	else
		AvisarColunaLinha(2);
end;
{----------------------------------------------------------------------------}
procedure MultiplicarMatrizes(iColuna1,iLinha1,iColuna2,iLinha2:integer; mi1,mi2:matriz);
var
	miMult: matriz;
	iColuna, iLinha, iDelay, iCont: integer;
begin
	if (iColuna1=iLinha2) then
	begin
		for iColuna:=1 to iColuna2 do
			for iLinha:=1 to iLinha1 do
			begin
				miMult[iColuna,iLinha]:=0;
				for iCont:=1 to iColuna1 do
					miMult[iColuna,iLinha]:=miMult[iColuna,iLinha]+mi1[iCont,iLinha]*mi2[iColuna,iCont];
			end;
		ImprimirMatriz(iColuna,iLinha,miMult);
		gotoxy(19,iLinha+12);
		write('Pressione qualquer tecla para continuar.');
		readkey;
		DesenharMoldura;
	end
	else
		AvisarColunaLinha(4);
end;
{----------------------------------------------------------------------------}
procedure VerificarQuadMagico(iColuna, iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2, iSoma, iAux: integer;
	lMagic: boolean;
begin
	lMagic:=true;
	if (iColuna=iLinha) then
	begin
		iSoma:=0;
		iAux:=iSoma;
		iColuna2:=1;
		while (lMagic) and (iColuna2<=iColuna) do
		begin
			iLinha2:=1;
			iSoma:=0;
			while (iLinha2<=iLinha) do
			begin
				iSoma:=iSoma+miMatriz[iColuna2,iLinha2]; {somando as colunas}
				inc(iLinha2);
			end;
			if ((iAux<>iSoma) and (iColuna2<>1)) then
				lMagic:=false
			else
				iAux:=iSoma;
			iLinha2:=1;
			iSoma:=0;
			while ((lMagic) and (iLinha2<=iLinha)) do
			begin
				iSoma:=iSoma+miMatriz[iLinha2,iColuna2]; {somando as linhas}
				inc(iLinha2);
			end;
			if (iAux<>iSoma) then
				lMagic:=false
			else
				iAux:=iSoma;
			inc(iColuna2);
		end;
	end
	else
		lMagic:=false;
	iSoma:=0;
	if (lMagic) then {verificar soma da diagonal principal}
		for iColuna2:=1 to iColuna do
			iSoma:=iSoma+miMatriz[iColuna2,iColuna2];
	if (iSoma<>iAux) then
		lMagic:=false;
	ImprimirMatriz(iColuna,iLinha,miMatriz);
	gotoxy(32,iLinha+9);
	if lMagic then
		write ('Quadrado magico')
	else
		write ('Nao e quadrado magico');
	gotoxy(15,iLinha+10);
	if (iLinha<>iColuna) then
		write('Apenas matrizes quadradas podem ser quadrados magicos.');
	gotoxy(19,iLinha+12);
	write('Pressione qualquer tecla para continuar.');
	readkey;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
procedure VerificarPermutacao(iColuna, iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2, iNum1L, iNum1C: integer;
	lPermut: boolean;
begin
	lPermut:=true;
	if (iLinha=iColuna) then
	begin
		iColuna2:=1;
		while ((lPermut) and (iColuna2<=iColuna)) do
		begin
			iLinha2:=1;
			iNum1L:=0;
			iNum1C:=0;
			while ((lPermut) and (iLinha2<=iLinha)) do
			begin
				if (miMatriz[iColuna2,iLinha2]=1) then {comparando colunas}
					inc(iNum1C)
				else
					if(miMatriz[iColuna2,iLinha2]<>0)and(iNum1C>=1)then
						lPermut:=false;
				if not (miMatriz[iColuna2,iLinha2] in [0..1]) then
					lPermut:=false;
				
				if (miMatriz[iLinha2,iColuna2]=1) then {comparando linhas}
					inc(iNum1L)
				else
					if(miMatriz[iLinha2,iColuna2]<>0)and(iNum1L>=1)then
						lPermut:=false;
				if not (miMatriz[iLinha2,iColuna2] in [0..1]) then
					lPermut:=false;
				inc(iLinha2);
			end;
			if ((iNum1L>1)or(iNum1C>1)) then
				lPermut:=false;
			inc(iColuna2);
		end;
	end
	else
		lPermut:=false;
	ImprimirMatriz(iColuna,iLinha,miMatriz);
	gotoxy(32,iLinha+9);
	if lPermut then
		write ('E uma matriz de permutacao')
	else
		write ('Nao e uma matriz de permutacao');
	gotoxy(15,iLinha+10);
	if (iLinha<>iColuna) then
		write('Apenas matrizes quadradas podem ser matrizes de permutacao.');
	gotoxy(19,iLinha+12);
	write('Pressione qualquer tecla para continuar.');
	readkey;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
function EncontrarElemento(viVetor:vetor; iOrdem,iElemento:integer):boolean; {procura o iElemento no viVetor}
var
	iCont: integer;
begin
	for iCont:=1 to iOrdem do
		if (viVetor[iCont]=iElemento) then
		begin
			EncontrarElemento:=true;
			exit
		end;
	EncontrarElemento:=false;
end;
{----------------------------------------------------------------------------}
function VetorLatino(viVetor: vetor; iOrdem: integer):boolean; {verifica se viVetor é um "vetor latino"}
var
	iCont: integer;
begin
	for iCont:=1 to iOrdem do
		if not (EncontrarElemento(viVetor,iOrdem,iCont)) then
		begin
			VetorLatino:=false;
			exit;
		end;
	VetorLatino:=true;
end;
{----------------------------------------------------------------------------}
procedure GerarVetor(miMatriz:matriz; iColuna, iLinha, iOrdem: integer; var viVetor:vetor);
var
	iCont: integer;
begin
	if (iColuna=0) then {o vetor vai pegar alguma linha de miMatriz}
	begin
		for iCont:=1 to iOrdem do
			viVetor[iCont]:=miMatriz[iCont,iLinha];
	end;
	if (iLinha=0) then {o vetor vai pegar alguma coluna de miMatriz}
	begin
		for iCont:=1 to iOrdem do
			viVetor[iCont]:=miMatriz[iColuna,iCont];
	end;
end;
{----------------------------------------------------------------------------}
procedure VerificarQuadLatino(iColuna, iLinha: integer; miMatriz: matriz);
var
	iColuna2, iLinha2: integer;
	lLatino: boolean;
	viVetor: vetor;
begin
	lLatino:=true;
	if (iLinha=iColuna) then
	begin
		iColuna2:=1;
		while ((lLatino) and (iColuna2<=iLinha)) do
		begin
			GerarVetor(miMatriz,iColuna2,0,iColuna,viVetor); {gero um vetor com a coluna iColuna2 de miMatriz}
			lLatino:=VetorLatino(viVetor,iLinha); {verifico se essa coluna tem todos os numeros de 1 a iLinha}
			GerarVetor(miMatriz,0,iColuna2,iColuna,viVetor); {gero um vetor com a linha iColuna2 de miMatriz}
			lLatino:=VetorLatino(viVetor,iLinha); {verifico se essa linha tem todos os numeros de 1 a iLinha}
			inc (iColuna2);
		end;
	end
	else
		lLatino:=false;
	ImprimirMatriz(iColuna,iLinha,miMatriz);
	gotoxy(32,iLinha+9);
	if lLatino then
		write ('E um quadrado latino')
	else
		write ('Nao e um quadrado latino');
	gotoxy(15,iLinha+10);
	if (iLinha<>iColuna) then
		write('Apenas matrizes quadradas podem ser quadrados latinos.');
	gotoxy(19,iLinha+12);
	write('Pressione qualquer tecla para continuar.');
	readkey;
	DesenharMoldura;
end;
{----------------------------------------------------------------------------}
{PROGRAMA PRINCIPAL}
var
	iOpcao, iColuna1, iLinha1, iColuna2, iLinha2, iColuna, iLinha: integer;
	mi1, mi2, miEscolha: matriz;
	lContinua: boolean;
begin
	LerMatriz(1,iColuna1,iLinha1,mi1);
	LerMatriz(2,iColuna2,iLinha2,mi2);
	iOpcao:=1;
	repeat
		ImprimirMenu1(iOpcao);
		iOpcao:=SelecionarOpcao1(iOpcao);
		case iOpcao of
			01: begin
					EscolherMatriz(iOpcao,iColuna1,iLinha1,iColuna2,iLinha2,iLinha,iColuna,mi1,mi2,miEscolha,lContinua);
					if (lContinua) then
						ObterTransposta(iColuna,iLinha,miEscolha);
				end;
			02: SomarMatrizes(iColuna1,iLinha1,iColuna2,iLinha2,mi1,mi2);
			03: SubtrairMatrizes(iColuna1,iLinha1,iColuna2,iLinha2,mi1,mi2);
			04: MultiplicarMatrizes(iColuna1,iLinha1,iColuna2,iLinha2,mi1,mi2);
			05: begin
					EscolherMatriz(iOpcao,iColuna1,iLinha1,iColuna2,iLinha2,iLinha,iColuna,mi1,mi2,miEscolha,lContinua);
					if (lContinua) then
						VerificarSimetria(iColuna,iLinha,miEscolha);
				end;
			06: begin
					EscolherMatriz(iOpcao,iColuna1,iLinha1,iColuna2,iLinha2,iLinha,iColuna,mi1,mi2,miEscolha,lContinua);
					if (lContinua) then
						VerificarQuadMagico(iColuna,iLinha,miEscolha);
				end;
			07: begin
					EscolherMatriz(iOpcao,iColuna1,iLinha1,iColuna2,iLinha2,iLinha,iColuna,mi1,mi2,miEscolha,lContinua);
					if (lContinua) then
						VerificarPermutacao(iColuna,iLinha,miEscolha);
				end;
			08: begin
					EscolherMatriz(iOpcao,iColuna1,iLinha1,iColuna2,iLinha2,iLinha,iColuna,mi1,mi2,miEscolha,lContinua);
					if (lContinua) then
						VerificarQuadLatino(iColuna,iLinha,miEscolha);
				end;
			09: Configurar(iColuna1, iLinha1, iColuna2, iLinha2, mi1, mi2);
			10: exit;
		end;
	until(iOpcao=10);
end.