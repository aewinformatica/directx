/*
------------ PROJETO GENESIS --------------
Autor : Marcos Romero (RH Games - Beljogos)
Email : romero1978@gmail.com
Página: http://romerogames.blogspot.com
-------------------------------------------
*/


/*
ARQUIVO	: MRDX.H

DATA		: 

Versão 1.0 - 26 DE ABRIL DE 2001
Versão 1.1 - 26 DE ABRIL DE 2011

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
#include <iostream.h> 
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
#define	PRETO		248
#define BRANCO		249
#define VERDE		250
#define AZUL		251
#define VERMELHO	252
#define AMARELO		253
#define CINZA		254
#define	ROXO		255

//usado para repetir sons
#define REPETIR	1

//estados de IMAGEM
#define ATIVO		1
#define INATIVO		0

//valores máximos
#define		MAX_QUADROS		128
#define		MAX_WAV			256
#define		MAX_MIDI		64
#define		MAX_DADOS		32

//facilitar a Ling. C
#define IGUAL		==
#define E			&&
#define OU			||

//Constantes de Transformação de Imagem (MRDX 1.1)
#define MRDX_NAO_ESPELHAR		0  
#define MRDX_ESPELHAR_HOR		1  
#define MRDX_ESPELHAR_VERT		2
#define MRDX_ESPELHAR_HOR_VERT	3

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
					bool clone; //MRDX 1.1
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

//Prototipos MRDX 1.1
int Carregar_Quadro(IMAGEM &imagem, int quadro, int cx, int cy, bool borda=false, int origemX=0, int origemY=0);
int Desenhar_Imagem(IMAGEM &imagem, int espelhar=0, int escalaX=0, int escalaY=0 );
int Clone_Imagem(IMAGEM &imagem_fonte, IMAGEM &imagem_destino);
int Transicao_Tela(int cor);

#endif
