/*
ARQUIVO	: MRDX.H

AUTOR		: MARCOS ROMERO

E-MAIL	: MAROMERO@ZAZ.COM.BR

EMPRESA	: RH GAMES  -  WWW.GEOCITIES.COM/RHGAMES

DATA		: 26 DE ABRIL DE 2001

COMENTÁRIOS:

				Neste arquivo encontram-se os protótipos das funções 
				que serão usadas nos jogos.

|\/\/\/|
|      |
|   0 0)
C     _)
 | ,__|				
 |   /

*/

// Não permitir múltiplas inclusões
#ifndef MRDX
#define MRDX

// INCLUSÕES ///////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream> 
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h> 
#include <direct.h>
#include <wchar.h>

#include <ddraw.h>    // cabeçalhos do directX 
#include <dinput.h>	
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>

// DEFINIÇÕES ///////////////////////////////////////////

//cores básicas da biblioteca
#define	PRETO		0
#define BRANCO		1
#define VERDE		2
#define AZUL		3
#define VERMELHO	4
#define AMARELO		5
#define CINZA		6
#define	ROXO		7

//usado para repetir sons
#define REPETIR	1

//estados de IMAGEM
#define ATIVO			1
#define INATIVO		0

//valores máximos
#define		MAX_QUADROS		128
#define		MAX_WAV				256
#define		MAX_MIDI			64
#define		MAX_DADOS			32

//facilitar a Ling. C
#define IGUAL		==
#define E				&&
#define OU			||

//ESTRUTURAS//////////////////////////////////////////////

struct IMAGEM
				{
					int x,y;
					int largura;
					int altura;
					int num_quadros;
					int quadro_atual;
					int estado;
					int dados[MAX_DADOS];
					LPDIRECTDRAWSURFACE4 quadros[MAX_QUADROS];
				};


// PROTÓTIPOS /////////////////////////////////////////////

void Jogo_Main(void);

int Directx_Iniciar(void);
int Directx_Encerrar(void);
int Mostrar_Tela(void);
int Limpar_Tela(int cor=0);
int Iniciar_Relogio(void);
int Esperar_Relogio(unsigned int tempo_espera);
int	Desenhar_Retangulo(int x1, int y1, int x2, int y2, int cor);
int Anexar_Clipper(void);
int Carregar_Bitmap(char *nome_arq);
int Inverter_Bitmap(unsigned char *dados, int largura, int altura);
int Cores_Basicas(void);
int Testar_Tecla(int dik_cod);
int Escreve_Texto(char *texto, int x, int y, int cor);
int Criar_Imagem(IMAGEM &imagem,int largura, int altura, int num_quadros);
int Destruir_Imagem(IMAGEM &imagem);
int Desenhar_Imagem(IMAGEM &imagem);
int Carregar_Quadro(IMAGEM &imagem, int quadro, int cx, int cy);
int Colisao_Imagens(IMAGEM &imagem1, IMAGEM &imagem2);
int Finalizar_Jogo(void);
int Aleatorio(int min, int max);
int Atualizar_Teclado(void);
int Atualizar_Mouse(void);
int	Mouse_Xvar(void);
int	Mouse_Yvar(void);
int Mouse_Bot_Esquerdo(void);
int Mouse_Bot_Direito(void);
int Inicia_Joystick(void);
int Atualizar_Joystick(void);
int Joy_Existe(void);
int Joy_Cima(void);
int Joy_Baixo(void);
int Joy_Esquerda(void);
int Joy_Direita(void);
int Joy_Bot(int bot);
int Carregar_Wav(char *nome_arq);
int Tocar_Wav(int id,int modo=0);
int Parar_Wav(int id);
int Parar_Todos_Wav(void);
int Wav_Tocando(int id);
int Carregar_Midi(char *nome_arq);
int Tocar_Midi(int id);
int Parar_Midi(int id);
int Midi_Tocando(int id);

#endif
