{Nome: Marcelo Augusto Cordeiro
  RA: 121023265
  Linguagem de programacao: Pascal
  Compilador: Borland Pascal 7.0
  Sistema operacional: Windows 7
  Senha: NOTA10}

uses crt,dos;

type VetorFrac = Array[1..2] of LongInt;


procedure LimparFinalLinha(iX, iY: integer);
begin
	gotoxy(iX,iY);
	clreol;
	gotoxy(79,iY);
	write(chr(186));
	gotoxy(iX,iY);
end;



procedure DesenharMoldura(sEntrada: String);
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
		gotoxy(iCont,7);
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
	gotoxy(2,7);
	write(chr(204));
	gotoxy(79,7);
	write(chr(185));
	gotoxy(29,3);
	write('BANCO WEBLANDS ISLANDS');
	gotoxy(6,5);
	write(sEntrada,': ');
end;



procedure ImprimirMenu1;
begin
	gotoxy(6,9);
	write('1 - Fazer um saque');
	gotoxy(6,10);
	write('2 - Preencher um cheque');
	gotoxy(6,11);
	write('3 - Sair');
	LimparFinalLinha(13,5);
end;



function ValidarOpcao(sOpcao: String; iInicial,iFinal: integer): integer;
var
	iOpcao, iEstado: integer;
begin
	val(sOpcao,iOpcao,iEstado);
	if ((iOpcao<iInicial)or(iOpcao>iFinal)) then
	begin
		repeat
			gotoxy(30,21);
			write('Opcao invalida.');
			LimparFinalLinha(30,22);
			write('Digite novamente: ');
			readln(sOpcao);
			LimparFinalLinha(48,21);
			LimparFinalLinha(13,5);
			write(sOpcao);
			val(sOpcao,iOpcao,iEstado);
		until((iOpcao>=iInicial)and(iOpcao<=iFinal));
	end;
	LimparFinalLinha(30,21);
	LimparFinalLinha(30,22);
	ValidarOpcao:=iOpcao;
end;



procedure ImprimirMolduraCheque(sData: String);
var
	iFor, iBarra: integer;
    iAno,iMes,iDia,iSemana: word;
	sAno,sMes,sDia: String[5];
begin
	gotoxy(12,10);
	write(chr(201));
	for iFor:=13 to 67 do
	begin
		gotoxy(iFor,10);
		write(chr(205));
		gotoxy(iFor,21);
		write(chr(205));
	end;
	gotoxy(68,10);
	write(chr(187));
	for iFor:=11 to 20 do
	begin
		gotoxy(12,iFor);
		write(chr(186));
		gotoxy(68,iFor);
		write(chr(186));
	end;
	gotoxy(12,21);
	write(chr(200));
	gotoxy(68,21);
	write(chr(188));
	gotoxy(17,11);
	write('BANCO WEBLANDS ISLANDS');
	if (sData='0') then
		getdate(iAno,iMes,iDia,iSemana)
	else
	begin
		iBarra:=pos('/',sData);
		sDia:=copy(sData,1,iBarra-1);
		sData:=copy(sData,iBarra+1,length(sData));
		iBarra:=pos('/',sData);
		sMes:=copy(sData,1,iBarra-1);
		sAno:=copy(sData,iBarra+1,length(sData));
		val(sDia,iDia,iBarra);
		val(sMes,iMes,iBarra);
		val(sAno,iAno,iBarra);
	end;
	gotoxy(35,19);
	write('Bauru, ');
	if (iDia<10) then
		write('0');
	write(iDia,' de ');
	case iMes of
		1: write('janeiro');
		2: write('fevereiro');
		3: write('março');
		4: write('abril');
		5: write('maio');
		6: write('junho');
		7: write('julho');
		8: write('agosto');
		9: write('setembro');
		10: write('outubro');
		11: write('novembro');
		12: write('dezembro');
	end;
	write(' de ',iAno);
end;



procedure SepararFrac(rEntrada: real; var viNum: VetorFrac);
var
	iPonto, iConvert: integer;
	sEntrada, sInteiro, sFrac: String;
begin
	str(rEntrada:1:2,sEntrada);
	iPonto:=pos('.',sEntrada);
	if (iPonto=0) then
	begin
		viNum[1]:=trunc(rEntrada);
		viNum[2]:=0;
	end
	else
	begin
		sInteiro:=copy(sEntrada,1,(length(sEntrada)-(length(sEntrada)-iPonto))-1);
		sFrac:=copy(sEntrada,iPonto+1,2);
		val(sInteiro,viNum[1],iConvert);
		val(sFrac,viNum[2],iConvert);
	end;
end;



procedure Imprimir (sTexto: string; var iX, iY: integer);
begin
	if ((iX + length(sTexto)) > 65) then
	begin
		inc(iY);
		iX:=18;
	end;
	gotoxy(iX,iY);
	iX:=iX+length(sTexto);
	write(sTexto);
end;



procedure EscreverQuantia (iCentenas, iDezenas, iUnidades: integer; var iX, iY: integer);
var
	vsUnidades, vs11_19, vsDezenas, vsCentenas: Array[1..9] of String[15];
	iRestante: integer;
begin
	vsUnidades[1]:='UM';
	vsUnidades[2]:='DOIS';
	vsUnidades[3]:='TRES';
	vsUnidades[4]:='QUATRO';
	vsUnidades[5]:='CINCO';
	vsUnidades[6]:='SEIS';
	vsUnidades[7]:='SETE';
	vsUnidades[8]:='OITO';
	vsUnidades[9]:='NOVE';
	vs11_19[1]:='ONZE';
	vs11_19[2]:='DOZE';
	vs11_19[3]:='TREZE';
	vs11_19[4]:='QUATORZE';
	vs11_19[5]:='QUINZE';
	vs11_19[6]:='DEZESSEIS';
	vs11_19[7]:='DEZESSETE';
	vs11_19[8]:='DEZOITO';
	vs11_19[9]:='DEZENOVE';
	vsDezenas[1]:='DEZ';
	vsDezenas[2]:='VINTE';
	vsDezenas[3]:='TRINTA';
	vsDezenas[4]:='QUARENTA';
	vsDezenas[5]:='CINQUENTA';
	vsDezenas[6]:='SESSENTA';
	vsDezenas[7]:='SETENTA';
	vsDezenas[8]:='OITENTA';
	vsDezenas[9]:='NOVENTA';
	vsCentenas[1]:='CEM';
	vsCentenas[2]:='DUZENTOS';
	vsCentenas[3]:='TREZENTOS';
	vsCentenas[4]:='QUATROCENTOS';
	vsCentenas[5]:='QUINHENTOS';
	vsCentenas[6]:='SEISCENTOS';
	vsCentenas[7]:='SETECENTOS';
	vsCentenas[8]:='OITOCENTOS';
	vsCentenas[9]:='NOVECENTOS';
	iRestante:=iCentenas+iDezenas+iUnidades;
	if (iRestante>0) then
	begin
		iRestante:=iDezenas+iUnidades;
		if (iCentenas>0) then
		begin
			if (iCentenas>1) then
			begin
				Imprimir(vsCentenas[iCentenas],iX,iY);
			end
			else
			begin
				if (iRestante>0) then
				begin
					Imprimir('CENTO',iX,iY);
				end
				else
				begin
					Imprimir(vsCentenas[1],iX,iY);
				end;
			end;
			if (iRestante>0) then
			begin
				Imprimir(' E ',iX,iY);
			end;
		end;
		if (iRestante>0) then
		begin
			iRestante:=iUnidades;
			if (iDezenas>0) then
			begin
				if (iDezenas>1) then
				begin
					Imprimir(vsDezenas[iDezenas],iX,iY);
				end
				else
				begin
					if (iRestante>0) then
					begin
						Imprimir(vs11_19[iUnidades],iX,iY);
						exit;
					end
					else
					begin
						Imprimir(vsDezenas[1],iX,iY);
					end;
				end;
				if (iRestante>0) then
				begin
					Imprimir(' E ',iX,iY);
				end;
			end;
		end;
		if (iRestante>0) then
		begin
			Imprimir(vsUnidades[iUnidades],iX,iY);
		end;
	end;
end;



procedure PreencherCheque(rQuantia: real; sNome, sData: String);
var
	i1, i2, i3, i4, i5, i6, i7, i8, i9, iCentavos, iX, iY, iRestante, iEscrito: integer;
	iInteiro: LongInt;
	viNum: VetorFrac;
begin
	LimparFinalLinha(6,5);
	ImprimirMolduraCheque(sData);
	gotoxy(45,11);
	write('Valor: B$ ',rQuantia:1:2);
	SepararFrac(rQuantia,viNum);
	iCentavos:=viNum[2];
	iInteiro:=viNum[1];
	i9 := iInteiro div 100000000;
	i8 := (iInteiro mod 100000000) div 10000000;
	i7 := ((iInteiro mod 100000000) mod 10000000) div 1000000;
	i6 := (((iInteiro mod 100000000) mod 10000000) mod 1000000) div 100000;
	i5 := ((((iInteiro mod 100000000) mod 10000000) mod 1000000) mod 100000) div 10000;
	i4 := (((((iInteiro mod 100000000) mod 10000000) mod 1000000) mod 100000) mod 10000) div 1000;
	i3 := ((((((iInteiro mod 100000000) mod 10000000) mod 1000000) mod 100000) mod 10000) mod 1000) div 100;
	i2 := (((((((iInteiro mod 100000000) mod 10000000) mod 1000000) mod 100000) mod 10000) mod 1000) mod 100) div 10;
	i1 := (((((((iInteiro mod 100000000) mod 10000000) mod 1000000) mod 100000) mod 10000) mod 1000) mod 100) mod 10;
	gotoxy(17,13);
	write('Pague por este cheque a quantia de');
	iX:=18;
	iY:=14;
	gotoxy(iX,iY);
	iRestante:=i9+i8+i7;
	EscreverQuantia(i9,i8,i7,iX,iY);
	if (iRestante>0) then
	begin
		if ((iRestante=1) and (i7=1)) then
			Imprimir(' MILHAO',iX,iY)
		else
			Imprimir(' MILHOES',iX,iY);
	end;
	iRestante:=i6+i5+i4+i3+i2+i1;
	iEscrito:=i9+i8+i7;
	if ((iRestante > 0) and (iEscrito > 0)) then
	begin
		iRestante:=i6+i5+i4;
		if (iRestante > 0) then
			Imprimir(', ',iX,iY)
		else
			Imprimir(' E ',iX,iY);
	end;
	EscreverQuantia(i6,i5,i4,iX,iY);
	iEscrito:=i6+i5+i4;
	if (iEscrito > 0) then
	begin
		Imprimir(' MIL',iX,iY)
	end;
	iRestante:=i3+i2+i1;
	if (iEscrito > 0) then
		if (i3 < 0) then
			Imprimir(' E ',iX,iY)
		else
			Imprimir(', ',iX,iY);
	EscreverQuantia(i3,i2,i1,iX,iY);
	iRestante:=i9+i8+i7+i6+i5+i4+i3+i2;
	iEscrito:=i9+i8+i7+i6+i5+i4+i3+i2+i1;
	if (iEscrito>0) then
		if ((iRestante>0) or (i1>1)) then
			Imprimir(' BITS',iX,iY)
		else
			Imprimir(' BIT',iX,iY);
	if (iCentavos>0) then
	begin
		if (iEscrito>0) then
			Imprimir(' E ',iX,iY);
		i1:=iCentavos div 10;
		i2:=iCentavos mod 10;
		EscreverQuantia(0,i1,i2,iX,iY);
		if (iCentavos>1) then
			Imprimir(' CENTBITS',iX,iY)
		else
			Imprimir(' CENTBIT',iX,iY);
	end;
	gotoxy(17,iY+1);
	write('a ',sNome,'.');
	gotoxy(6,5);
	write('Pressione qualquer tecla para continuar');
	ReadKey;
end;



function Upper(sNormal: String): String;
var
	iCont: integer;
    sUpper: String[100];
begin
	for iCont:=0 to length(sNormal) do
		sUpper[iCont]:=UpCase(sNormal[iCont]);
	Upper:=sUpper;
end;



procedure ValidarSenha(sSenha: String);
var
	sEntrada: String[20];
	iCont, iDelay: integer;
begin
	for iCont:=1 to 5 do
	begin
		LimparFinalLinha(48,5);
		readln(sEntrada);
		sEntrada:=Upper(sEntrada);
		if (sEntrada=sSenha) then
		begin
			gotoxy(35,15);
			write('Senha valida');
			iDelay:=0;
			repeat
				delay(1);
				inc(iDelay);
			until((iDelay=4000)or(KeyPressed));
			if(KeyPressed)then
				ReadKey;
			exit;
		end
		else
		begin            
			gotoxy(32,15);
			write('Senha invalida');
			gotoxy(29,16);
			if(iCont<>5)then
				write('Restam ',5-iCont,' tentativas');
			iDelay:=0;
			repeat
				delay(1);
				inc(iDelay);
			until((iDelay=4000)or(KeyPressed));
			if(KeyPressed)then
				ReadKey;
			LimparFinalLinha(32,15);
			LimparFinalLinha(29,16);
		end;
	end;
	gotoxy(29,15);
	write('Tentativas esgotadas');
	for iCont:=5 downto 1 do
	begin
		gotoxy(15,16);
		write('O programa fechara automaticamente em ',iCont,' segundos');
		delay(2000); {com 1000 fica muito rapido}
        LimparFinalLinha(15,16);
	end;
	halt;
end;



function ValidarSaque(rEntrada: real):real;
var
	iFrac: integer;
	viNum: VetorFrac;
begin
	SepararFrac(rEntrada,viNum);
	iFrac:=viNum[2];
	while ((iFrac mod 5)<>0) do
	begin
		gotoxy(30,21);
		write('Valor invalida.');
		LimparFinalLinha(30,22);
		write('Digite novamente: ');
		readln(rEntrada);
		SepararFrac(rEntrada,viNum);
		iFrac:=viNum[2];
		LimparFinalLinha(30,21);
		LimparFinalLinha(30,22);
		LimparFinalLinha(48,21);
		LimparFinalLinha(32,5);
		write(rEntrada:1:2);
	end;
	ValidarSaque:=rEntrada;
end;



procedure FazerSaque(rEntrada: real);
var
	lVinteCinco: boolean;
	iY, iFrac: integer;
	iQuantia, iInteiro: LongInt;
	viNum: VetorFrac;
begin
	rEntrada:=ValidarSaque(rEntrada);
	SepararFrac(rEntrada,viNum);
	iFrac:=viNum[2];
	if (((iFrac div 5) mod 2)<>0) then
	begin
		lVinteCinco:=true;
		rEntrada:=rEntrada-0.25;
	end
	else
		lVinteCinco:=false;
	SepararFrac(rEntrada,viNum);
	iFrac:=viNum[2];
	iInteiro:=viNum[1];
	iY:=9;
	iQuantia:=iInteiro div 100;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 100');
	end;
	iInteiro:=iInteiro mod 100;
	iQuantia:=iInteiro div 50;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 50');
	end;
	iInteiro:=iInteiro mod 50;
	iQuantia:=iInteiro div 20;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 20');
	end;
	iInteiro:=iInteiro mod 20;
	iQuantia:=iInteiro div 10;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 10');
	end;
	iInteiro:=iInteiro mod 10;
	iQuantia:=iInteiro div 5;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 5');
	end;
	iInteiro:=iInteiro mod 5;
	iQuantia:=iInteiro div 2;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' notas')
		else
			write(iQuantia,' nota');
		write(' de B$ 2');
	end;
	iInteiro:=iInteiro mod 2;
	iQuantia:=iInteiro div 1;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' moedas')
		else
			write(iQuantia,' moeda');
		write(' de B$ 1');
	end;
	iInteiro:=iInteiro mod 1;
	iQuantia:=iFrac div 50;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' moedas')
		else
			write(iQuantia,' moeda');
		write(' de B$ 0.50');
	end;
	iFrac:=iFrac mod 50;
	if (lVinteCinco) then
	begin
		gotoxy(10,iY);
		inc(iY);
		write('1 moeda de B$ 0.25');
	end;
	iQuantia:=iFrac div 10;
	if (iQuantia>0) then
	begin
		gotoxy(10,iY);
		inc(iY);
		if (iQuantia>1) then
			write(iQuantia,' moedas')
		else
			write(iQuantia,' moeda');
		write(' de B$ 0.10');
	end;
	gotoxy(22,21);
	write('Pressione qualquer tecla para continuar');
	ReadKey;
end;


{PROGRAMA PRINCIPAL}
var
	iOpcao: integer;
	rEntrada: real;
	sNome: String[50];
	sOpcao, sData: String[11];
begin
	DesenharMoldura('Digite sua senha para acessar o programa');
	ValidarSenha('NOTA10');
	repeat
		clrscr;
		DesenharMoldura('Opcao');
		ImprimirMenu1;
		readln(sOpcao);
		iOpcao:=ValidarOpcao(sOpcao,1,3);
		case iOpcao of
			1:	begin
					DesenharMoldura('Valor desejado (em Bits)');
					readln(rEntrada);
					FazerSaque(rEntrada);
				end;
			2:	begin
					DesenharMoldura('Pago a');
					readln(sNome);
					DesenharMoldura('A quantia (em Bits)');
					readln(rEntrada);
					DesenharMoldura('Na seguinte data (DD/MM/AAAA ou 0 para a data atual)');
					readln(sData);
					PreencherCheque(rEntrada,sNome,sData);
				end;
			3: 	exit;
		end;
	until(iOpcao=3);
end.