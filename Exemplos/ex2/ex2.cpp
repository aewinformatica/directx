/*
------------ PROJETO GENESIS --------------
Autor : Marcos Romero (RH Games - Beljogos)
Email : romero1978@gmail.com
Página: http://romerogames.blogspot.com
-------------------------------------------
*/

/*
ARQUIVO	: EX2.CPP

DATA		: 16 DE MAIO DE 2001

COMENTÁRIOS:

				Jogo exemplo do MRDX. 
*/


#include "mrdx.h"

//velocidade dos objetos
#define JOG_VEL		4
#define MON_VEL		4
#define MAX_MONSTROS 32

//dados extras dos monstros
#define DIR			0

//direção dos monstros
#define ESQUERDA	0
#define DIREITA		1
#define CIMA			2
#define BAIXO			3

//protótipos
void Jogo_Inicio(void);
void Jogo_Fim(void);
void Menu(void);
void Novo_Jogo(void);
void Bonus(void);
void Jogador(void);
void Monstros(void);
void Desenha_Painel(void);
void Desenha_Mapa(void);

//variáveis
IMAGEM monstros[MAX_MONSTROS];
IMAGEM jogador;
IMAGEM bonus;
IMAGEM mapa_im;
IMAGEM painel;

int menu;//se 1 está no menu; se 0 está no jogo
int nivel;
int pontos;
int n_bonus;
int inicio=1;
char texto[80];

//animação
int anim_seq[6] = {0,1,2,3,2,1};
int anim_cont;
int anim_ind;

//sons
int musica_mid;
int bip_wav;

int mapa[15][15] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
										 1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,
										 1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,
										 1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,
										 1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,
										 1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,
										 1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,
										 1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,
										 1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,
										 1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,
										 1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,
										 1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,
										 1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
										 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//função principal do jogo
void Jogo_Main(void)
{

	if(inicio)
	{
		
		inicio = 0;

		Jogo_Inicio();

	}//fim if(inicio)

	Iniciar_Relogio();

	if(Testar_Tecla(DIK_ESCAPE))
	{
		//encerrar o jogo
		Jogo_Fim();
		return;
	}

	//tocar música
	if(!Midi_Tocando(musica_mid))
	{
		Tocar_Midi(musica_mid);
	}

	
	Limpar_Tela();
	
	Desenha_Mapa();

	Desenha_Painel();

	//desenha bonus

	if(menu)
	{
		Menu();
	}
	else //está no jogo
	{
		//processar objetos
		Bonus();
		Monstros();
		Jogador();
	}


	Mostrar_Tela();
	Esperar_Relogio(40);//40 milisegundos -> 25 quadros por segundo

}//fim Jogo_Main

/////////////////////////////////////////
void Jogo_Inicio(void)
{
	int i;
		
		Carregar_Bitmap("arte.bmp");

		Criar_Imagem(jogador,32,32,4);
		for(i=0; i< 4; i++)
		{
			Carregar_Quadro(jogador,i,i,0);
		}

		for(i=0; i< MAX_MONSTROS; i++)
		{
			Criar_Imagem(monstros[i],32,32,1);
			Carregar_Quadro(monstros[i],0,1,1);
		}
		
		Criar_Imagem(bonus,32,32,1);
		Carregar_Quadro(bonus,0,2,1);

		Criar_Imagem(mapa_im,32,32,1);
		Carregar_Quadro(mapa_im,0,0,1);

		Carregar_Bitmap("painel.bmp");
		Criar_Imagem(painel,160,480,1);
		Carregar_Quadro(painel,0,0,0);
		painel.x = 480;
		painel.y = 0;


		//carregar som
		musica_mid = Carregar_Midi("tocatta.mid");

		bip_wav = Carregar_Wav("bip.wav");

		menu = 1;//ir p/ menu

}
/////////////////////////////////////////
void Jogo_Fim(void)
{
	int i;
		
		//liberar memória das imagens
		Destruir_Imagem(jogador);
		Destruir_Imagem(bonus);
		Destruir_Imagem(mapa_im);
		Destruir_Imagem(painel);
		for(i=0; i< MAX_MONSTROS; i++)
		{
			Destruir_Imagem(monstros[i]);
		}
		Finalizar_Jogo();

}
/////////////////////////////////////////
void Menu(void)
{
	Desenhar_Retangulo(170,80,350,200,AZUL);
	Escreve_Texto("ENTER - Iniciar",200,100,BRANCO);
	Escreve_Texto("ESC   - Sair",200,150,BRANCO);

	if(Testar_Tecla(DIK_RETURN))
	{
		menu = 0;
		Novo_Jogo();
	}
}
/////////////////////////////////////////
void Novo_Jogo(void)
{
	int i;

	//iniciar valores
	bonus.estado = INATIVO;
	for(i=0;i<MAX_MONSTROS;i++)
	{
		//posiçào inicial 
		monstros[i].x = 7 * 32;
		monstros[i].y = 7 * 32;
		monstros[i].dados[DIR] = Aleatorio(0,3);//direção
	}

	pontos = 0;
	nivel=1;

	jogador.x = 7 * 32;
	jogador.y = 12 * 32;
	jogador.quadro_atual = 0;

	anim_cont = 0;
	anim_ind = 0;
	
}
/////////////////////////////////////////
void Bonus(void)
{
	int mapa_x, mapa_y;

	if(bonus.estado IGUAL INATIVO)
	{
		//inicia bonus em uma posição aleatória
		bonus.estado = ATIVO;

		//pega uma posição no mapa e testa se está livre...
		do {
			mapa_y = Aleatorio(1,13);
			mapa_x = Aleatorio(1,13);
		} while(mapa[mapa_y][mapa_x] IGUAL 1);

			bonus.x = mapa_x * 32;
			bonus.y = mapa_y * 32;
	}

	Desenhar_Imagem(bonus);
}

/////////////////////////////////////////
void Monstros(void)
{
	int i, dir;
	int mapa_x, mapa_y;
	int caminho_livre;
	
	//o número de monstros é igual ao nivel
	for(i=0; i < nivel; i++)
	{
		dir = monstros[i].dados[DIR];
		//mover monstro
		switch(dir)
		{
			case ESQUERDA	: monstros[i].x -= MON_VEL; break;
			case DIREITA	: monstros[i].x += MON_VEL; break;
			case CIMA			: monstros[i].y -= MON_VEL; break;
			case BAIXO		: monstros[i].y += MON_VEL; break;
		}

		//se monstro estiver totalmente em uma célula então
		//decidir próxima direção
		if( ( monstros[i].x % 32 IGUAL 0) E 
				( monstros[i].y % 32 IGUAL 0) )
		{
			caminho_livre = 0;

			mapa_x = monstros[i].x / 32;
			mapa_y = monstros[i].y / 32;

			//talvez mudar direção 
			if(Aleatorio(1,10) IGUAL 10) dir = Aleatorio(0,3);

			do
			{
				switch(dir)
				{
					case ESQUERDA	:	if(mapa[mapa_y][mapa_x - 1] IGUAL 0) 
													{
															caminho_livre = 1;
													}
													break;
					case DIREITA	: if(mapa[mapa_y][mapa_x + 1] IGUAL 0) 
													{
															caminho_livre = 1;
													}
													break;
					case CIMA			: if(mapa[mapa_y - 1][mapa_x] IGUAL 0) 
													{
															caminho_livre = 1;
													}
													break;
					case BAIXO		: if(mapa[mapa_y + 1][mapa_x] IGUAL 0) 
													{
															caminho_livre = 1;
													}
													break;
				}

				//se não está livre, tentar outra direção
				if(caminho_livre IGUAL 0) dir = Aleatorio(0,3);

			} while(caminho_livre IGUAL 0);

			monstros[i].dados[DIR] = dir;

		}//if

		Desenhar_Imagem(monstros[i]);

	}//for
}
/////////////////////////////////////////
void Jogador(void)
{
	int i;
	int mapa_x,mapa_y;

	//testar lab...
	//ler entrada de dados
	if(Testar_Tecla(DIK_UP) OU Joy_Cima() )
	{
		//o 4 é usado para tolerância
			mapa_y = jogador.y / 32;//topo

		 mapa_x = (jogador.x + 4) / 32;//esquerda 

		 //testar dois lados
		 if(mapa[mapa_y][mapa_x] IGUAL 0) 
		 {
			 mapa_x = (jogador.x + 31 - 4) / 32;//direita

			 if(mapa[mapa_y][mapa_x] IGUAL 0) 
			 {
					jogador.y-=JOG_VEL;
			 }
		 }
			
	}

	if(Testar_Tecla(DIK_DOWN) OU Joy_Baixo() ) 
	{
		 
		 mapa_y = (jogador.y + 31) / 32;//base

		 mapa_x = (jogador.x + 4) / 32;//esquerda
		 
		 if(mapa[mapa_y][mapa_x] IGUAL 0) 
		 {
			 mapa_x = (jogador.x + 31 - 4) / 32;//direita

			 if(mapa[mapa_y][mapa_x] IGUAL 0) 
			 {
					jogador.y+=JOG_VEL;
			 }
		 }
			
	}

	if(Testar_Tecla(DIK_LEFT) OU Joy_Esquerda() ) 
	{
		 mapa_x = jogador.x / 32;//esquerda

		 mapa_y = (jogador.y + 4) / 32;//cima
 
		 
		 if(mapa[mapa_y][mapa_x] IGUAL 0) 
		 {
			 mapa_y = (jogador.y + 31 - 4) / 32;//baixo

			 if(mapa[mapa_y][mapa_x] IGUAL 0) 
			 {
					jogador.x-=JOG_VEL;
			 }
		 }
	}
	if(Testar_Tecla(DIK_RIGHT) OU Joy_Direita() ) 
	{
		 mapa_x = (jogador.x + 31) / 32;//direita

		 mapa_y = (jogador.y + 4) / 32;//cima
		 
		 if(mapa[mapa_y][mapa_x] IGUAL 0) 
		 {
			 mapa_y = (jogador.y + 31 - 4) / 32;//baixo

			 if(mapa[mapa_y][mapa_x] IGUAL 0) 
			 {
				jogador.x+=JOG_VEL;
			 }
		 }
		
	}


	//colisao com bonus
	if(Colisao_Imagens(jogador, bonus))
	{
		n_bonus++;
		pontos+=nivel;
		bonus.estado = INATIVO;
		Tocar_Wav(bip_wav);

		if((n_bonus % 5 ) IGUAL 0)
		{
			//aumenta nivel
			nivel++;
			
		}
	}

	//colisao com monstros. O nº de monstros é igual ao nivel
	for(i=0; i< nivel; i++)
	{
			if(Colisao_Imagens(jogador, monstros[i]))
			{
				//fim de jogo
				menu = 1;
				return;
			}
	}

	//animação
	anim_cont++;
	if(anim_cont IGUAL 4)
	{
		anim_cont = 0;
		anim_ind++;
		if(anim_ind IGUAL 6) anim_ind = 0;

		jogador.quadro_atual = anim_seq[anim_ind];
	}

	Desenhar_Imagem(jogador);

}//jogador

/////////////////////////////////////////
void Desenha_Painel(void)
{
	Desenhar_Imagem(painel);

	sprintf(texto, "%d",pontos);
	Escreve_Texto(texto,555,174,BRANCO);

	sprintf(texto, "%d",nivel);
	Escreve_Texto(texto,555,234,BRANCO);

	
}
/////////////////////////////////////////
void Desenha_Mapa(void)
{
	int i,j;

	for(i=0; i<15; i++)
		for(j=0; j < 15; j++)
		{
			if(mapa[i][j])
			{
				mapa_im.x = j * 32;
				mapa_im.y = i * 32;
				Desenhar_Imagem(mapa_im);
			}
		}
}