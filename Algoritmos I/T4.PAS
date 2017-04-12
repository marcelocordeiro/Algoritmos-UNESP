{Nome: Marcelo Augusto Cordeiro
  RA: 121023265
  Linguagem de programacao: Pascal
  Compilador: Borland Pascal 7.0
  Sistema operacional: Windows 7}

uses crt,dos;
{----------------------------------------------------------------------------}
procedure CorrerWelcomeToStacker;
var
	vsWelcome: Array[1..6] of string;

procedure ImprimirCorrerWelcome(iTam: integer); {imprime os iTam caracteres da mensagem WELCOME TO STACKER}
var
	iCont, iCont2: integer;
begin
	if (iTam>77) then {nao cabe na tela}
		iCont:=iTam-77 {ja imprimiu os primeiros, entao imprimo so o resto}
	else
		iCont:=1;
	while iCont<=iTam do
	begin
		gotoxy(78-iTam+iCont,9);
		write(vsWelcome[1][iCont]);
		gotoxy(78-iTam+iCont,10);
		write(vsWelcome[2][iCont]);
		gotoxy(78-iTam+iCont,11);
		write(vsWelcome[3][iCont]);
		gotoxy(78-iTam+iCont,12);
		write(vsWelcome[4][iCont]);
		gotoxy(78-iTam+iCont,13);
		write(vsWelcome[5][iCont]);
		gotoxy(78-iTam+iCont,14);
		write(vsWelcome[6][iCont]);
		inc(iCont);
	end;
end;

var
	iCont: integer;
begin
	vsWelcome[1]:='.______    _______ .___  ___.      ____    ____  __  .__   __.  _______   ______   ';
	vsWelcome[2]:='|   _  \  |   ____||   \/   |      \   \  /   / |  | |  \ |  | |       \ /  __  \  ';
	vsWelcome[3]:='|  |_)  | |  |__   |  \  /  |  _____\   \/   /  |  | |   \|  | |  .--.  |  |  |  | ';
	vsWelcome[4]:='|   _  <  |   __|  |  |\/|  | |______\      /   |  | |  . `  | |  |  |  |  |  |  | ';
	vsWelcome[5]:='|  |_)  | |  |____ |  |  |  |         \    /    |  | |  |\   | |  ''--''  |  `--''  | ';
	vsWelcome[6]:='|______/  |_______||__|  |__|          \__/     |__| |__| \__| |_______/ \______/  ';
	vsWelcome[1]:=vsWelcome[1]+'    '+'     ___       ______   ';
	vsWelcome[2]:=vsWelcome[2]+'    '+'    /   \     /  __  \  ';
	vsWelcome[3]:=vsWelcome[3]+'    '+'   /  ^  \   |  |  |  | ';
	vsWelcome[4]:=vsWelcome[4]+'    '+'  /  /_\  \  |  |  |  | ';
	vsWelcome[5]:=vsWelcome[5]+'    '+' /  _____  \ |  `--''  | ';
	vsWelcome[6]:=vsWelcome[6]+'    '+'/__/     \__\ \______/  ';
	vsWelcome[1]:=vsWelcome[1]+'    '+'     _______.___________.    ___       ______  __  ___  _______ .______      ';
	vsWelcome[2]:=vsWelcome[2]+'    '+'    /       |           |   /   \     /      ||  |/  / |   ____||   _  \     ';
	vsWelcome[3]:=vsWelcome[3]+'    '+'   |   (----`---|  |----`  /  ^  \   |  ,----''|  ''  /  |  |__   |  |_)  |    ';
	vsWelcome[4]:=vsWelcome[4]+'    '+'    \   \       |  |      /  /_\  \  |  |     |    <   |   __|  |      /     ';
	vsWelcome[5]:=vsWelcome[5]+'    '+'.----)   |      |  |     /  _____  \ |  `----.|  .  \  |  |____ |  |\  \----.';
	vsWelcome[6]:=vsWelcome[6]+'    '+'|_______/       |__|    /__/     \__\ \______||__|\__\ |_______|| _| `._____|';
	for iCont:=1 to length(vsWelcome[1]) do
	begin
		ImprimirCorrerWelcome(iCont);
		delay(100);{!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
	end;
end;
{----------------------------------------------------------------------------}
procedure PiscarStacker;
var
	vsStack: Array[1..6] of String[80];
	iCont, iNum: integer;
begin
	vsStack[1]:='     _______.___________.    ___       ______  __  ___  _______ .______      ';
	vsStack[2]:='    /       |           |   /   \     /      ||  |/  / |   ____||   _  \     ';
	vsStack[3]:='   |   (----`---|  |----`  /  ^  \   |  ,----''|  ''  /  |  |__   |  |_)  |    ';
	vsStack[4]:='    \   \       |  |      /  /_\  \  |  |     |    <   |   __|  |      /     ';
	vsStack[5]:='.----)   |      |  |     /  _____  \ |  `----.|  .  \  |  |____ |  |\  \----.';
	vsStack[6]:='|_______/       |__|    /__/     \__\ \______||__|\__\ |_______|| _| `._____|';
	for iNum:=1 to 5 do
	begin
		textbackground(RED);
		clrscr;
		for iCont:=1 to 6 do
		begin
			gotoxy(2,8+iCont);
			write(vsStack[iCont]);
		end;
		delay(500);
		textbackground(BLACK);
		clrscr;
		for iCont:=1 to 6 do
		begin
			gotoxy(2,8+iCont);
			textcolor(RED);
			write(vsStack[iCont]);
			textcolor(WHITE);
		end;
		delay(500);
	end;
end;
{----------------------------------------------------------------------------}
procedure SubirStacker;
var
	vsStack: Array[1..6] of String[80];
	iCont1, iCont2: integer;
begin
	vsStack[1]:='     _______.___________.    ___       ______  __  ___  _______ .______      ';
	vsStack[2]:='    /       |           |   /   \     /      ||  |/  / |   ____||   _  \     ';
	vsStack[3]:='   |   (----`---|  |----`  /  ^  \   |  ,----''|  ''  /  |  |__   |  |_)  |    ';
	vsStack[4]:='    \   \       |  |      /  /_\  \  |  |     |    <   |   __|  |      /     ';
	vsStack[5]:='.----)   |      |  |     /  _____  \ |  `----.|  .  \  |  |____ |  |\  \----.';
	vsStack[6]:='|_______/       |__|    /__/     \__\ \______||__|\__\ |_______|| _| `._____|';
	for iCont1:=1 to 5 do	{para subir 5 linhas}
	begin
		delay(500);
		clrscr;
		for iCont2:=1 to 6 do {para escrever STACKER de novo}
		begin
			gotoxy(2,9-iCont1+iCont2); {subi uma linha}
			textcolor(RED);
			write(vsStack[iCont2]);
			textcolor(WHITE);
		end;
	end;
end;
{----------------------------------------------------------------------------}
procedure ImprimirMenu;
begin
	gotoxy(35,15);
	textcolor(RED);
	delay(500);
	write(chr(175),' Novo jogo ',chr(174));
	textcolor(WHITE);
	gotoxy(35,16);
	delay(500);
	write('Ajuda');
	gotoxy(35,17);
	delay(500);
	write('Creditos');
	gotoxy(35,18);
	delay(500);
	write('Sair');
end;
{----------------------------------------------------------------------------}
procedure Abertura;
begin
	textbackground(BLACK);
	clrscr;
	textcolor(WHITE);
	CorrerWelcomeToStacker;
	PiscarStacker;
end;
{----------------------------------------------------------------------------}
procedure Selecionar(iX, iY, iAntes, iMax: integer; sTexto1, sTexto2: String; lDirec: boolean);
{TRUE para cima e FALSE para baixo}
begin
	gotoxy(iX,iY);
	clreol;
	write(sTexto1); {escrevi o que estava selecionado antes}
	if lDirec then {seta para cima}
		if (iAntes=1) then
		begin
			gotoxy(iX,iY+iMax-iAntes);
			clreol; {limpei a última linha}
		end
		else
		begin
			gotoxy(iX,iY-1);
			clreol; {limpei a linha de cima}
		end
	else {seta para baixo}
		if (iAntes=iMax) then
		begin
			gotoxy(iX,iY-iMax+1);
			clreol; {limpei a primeira linha}
		end
		else
		begin
			gotoxy(iX,iY+1); 
			clreol; {limpei a linha de baixo}
		end;
	textcolor(RED);
	write(chr(175),' ',sTexto2,' ',chr(174)); {escrevi o texto selecionado}
	textcolor(WHITE);
end;
{----------------------------------------------------------------------------}
function SelecionarOpcao(iSelect: integer):integer;
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
									Selecionar(35,15,1,4,'Novo jogo','Sair',true);
									iSelect:=4;
								end;
							02: begin
									Selecionar(35,16,2,4,'Ajuda','Novo jogo',true);
									iSelect:=1;
								end;
							03: begin
									Selecionar(35,17,3,4,'Creditos','Ajuda',true);
									iSelect:=2;
								end;
							04: begin
									Selecionar(35,18,4,4,'Sair','Creditos',true);
									iSelect:=3;
								end;
						end;
					end;
				#80: begin {seta para baixo}
						case iSelect of
							01: begin
									Selecionar(35,15,1,4,'Novo jogo','Ajuda',false);
									iSelect:=2;
								end;
							02: begin
									Selecionar(35,16,2,4,'Ajuda','Creditos',false);
									iSelect:=3;
								end;
							03: begin
									Selecionar(35,17,3,4,'Creditos','Sair',false);
									iSelect:=4;
								end;
							04: begin
									Selecionar(35,18,4,4,'Sair','Novo jogo',false);
									iSelect:=1;
								end;
						end;
					end;
				#59: begin {F1}
						clrscr;
						iSelect:=2; {ajuda}
						lEnter:=true;
					end;
			end
		else
			case cTecla of
				#27: begin {ESC}
						iSelect:=4; {sair}
						lEnter:=true;
					end;
				#13: lEnter := true; {ENTER}
			end;
		SelecionarOpcao:=iSelect;
	until (lEnter);
end;
{----------------------------------------------------------------------------}
procedure DesenharMalha;
var
	iLinha,iColuna,iX,iY:integer;
begin
	iX:=6;
	for iColuna:=1 to 6 do
	begin
		gotoxy(iX,1);
		if (iColuna=1) then
			write(chr(218))
		else
			write(chr(194));
		write(chr(196),chr(196),chr(196),chr(196));
		if (iColuna=6) then
			write(chr(191))
		else
			write(chr(194));
		iY:=25;
		for iLinha:=1 to 8 do
		begin
			gotoxy(iX,iY);
			if (iColuna=1) and (iLinha=1) then
				write(chr(192))
			else
				if (iColuna=1) then
					write(chr(195))
				else
					if (iLinha=1) then
						write(chr(193))
					else
						write(chr(197));
			write(chr(196),chr(196),chr(196),chr(196));
			if (iColuna=6) and (iLinha=1) then
				write(chr(217))
			else
				if (iColuna=6) then
					write(chr(180))
				else
					write(chr(197));
			gotoxy(iX,iY-2);
			write(chr(179));
			gotoxy(iX,iY-1);
			write(chr(179));
			gotoxy(iX+5,iY-2);
			write(chr(179));
			gotoxy(iX+5,iY-1);
			write(chr(179));
			iY:=iY-3;
		end;
		iX:=iX+5;
	end;
end;
{----------------------------------------------------------------------------}
procedure PintarBloco(iColuna,iLinha,iCor:integer);
begin
	iColuna:=02+(iColuna*5);
	iLinha:=(iLinha*3)-1;
	textcolor(iCor);
	gotoxy(iColuna,iLinha);
	write(chr(219),chr(219),chr(219),chr(219));
	gotoxy(iColuna,iLinha+1);
	write(chr(219),chr(219),chr(219),chr(219));
	textcolor(WHITE);
end;
{----------------------------------------------------------------------------}
function CorrerLinha1(iLinha:integer):integer;
var
	iColuna:integer;
	lVolta:boolean;
begin
	iColuna:=2;
	lVolta:=false;
	PintarBloco(1,iLinha,RED);
	delay(125*iLinha);
	repeat
		if not lVolta then
		begin
			PintarBloco(iColuna-1,iLinha,BLACK);
			PintarBloco(iColuna,iLinha,RED);
			inc(iColuna);
		end;
		if ((iColuna=7) or lVolta) then {foi tudo, agora precisa voltar}
		begin
			lVolta:=true;
			dec(iColuna);
			if ((iColuna+1)<=6) then
				PintarBloco(iColuna+1,iLinha,BLACK);
			PintarBloco(iColuna,iLinha,RED);
		end;
		if ((iColuna=1) and lVolta) then
		begin
			lVolta:=false; {voltou tudo}
			iColuna:=2;
		end;
		case iLinha of
			01: delay(250);
			02:	delay(325);
			03: delay(400);
			04: delay(475);
		end;
	until(KeyPressed);
	readkey;
	
	{repeat
		PintarBloco(1,iLinha,RED);
		PintarBloco(4,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(3,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(2,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(2,iLinha,RED);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(3,iLinha,RED);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(4,iLinha,RED);
		PintarBloco(1,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(5,iLinha,RED);
		PintarBloco(2,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(6,iLinha,RED);
		PintarBloco(3,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(4,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(5,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(5,iLinha,RED);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(4,iLinha,RED);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(3,iLinha,RED);
		PintarBloco(6,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
		PintarBloco(2,iLinha,RED);
		PintarBloco(5,iLinha,BLACK);
		delay(125*iLinha);
		if (KeyPressed) then
			exit;
	until(KeyPressed);}
end;
{----------------------------------------------------------------------------}
function CorrerLinha2(iLinha:integer):integer; {retorna a posicao mais a direita do ultimo quadradinho quando para}
begin

end;
{----------------------------------------------------------------------------}
function CorrerLinha3(iLinha:integer):integer; {retorna a posicao mais a direita do ultimo quadradinho quando para}
begin

end;
{----------------------------------------------------------------------------}
procedure IniciarJogo;
var
	iParada: integer;
begin
	clrscr;
	DesenharMalha;
	iParada:=CorrerLinha3(8);
	iParada:=CorrerLinha3(7);
	iParada:=CorrerLinha2(6);
	iParada:=CorrerLinha2(5);
	iParada:=CorrerLinha1(4);
	iParada:=CorrerLinha1(3);
	iParada:=CorrerLinha1(2);
	iParada:=CorrerLinha1(1);
	readkey;
end;
{----------------------------------------------------------------------------}
{PROGRAMA PRINCIPAL}	
var
	iOpcao: integer;
begin
	Abertura;
	gotoxy(20,17);
	textcolor(RED);
	write(chr(175),' Pressione qualquer tecla para continuar ',chr(174));
	textcolor(WHITE);
	readkey;
	repeat
		SubirStacker;
		ImprimirMenu;
		iOpcao:=SelecionarOpcao(1);
		case iOpcao of
			01: begin
					IniciarJogo;
				end;
			02: begin
				
				end;
			03: begin
			
				end;
		end;
	until(iOpcao=4);
end.

{http://www.network-science.de/ascii/    STARWARS}
