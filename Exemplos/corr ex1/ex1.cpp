/*
------------ PROJETO GENESIS --------------
Autor : Marcos Romero (RH Games - Beljogos)
Email : romero1978@gmail.com
Página: http://romerogames.blogspot.com
-------------------------------------------
*/

/*
ARQUIVO	: EX1.CPP

DATA		: 02 DE MAIO DE 2001

COMENTÁRIOS:

				Jogo exemplo do MRDX. 
*/


#include "mrdx.h"

//velocidade dos objetos
#define JOG_VEL		8
#define BAND_VEL	10
#define MAX_CARROS 3

//dados extras dos carros
#define TEMPO		0
#define DIR			1

//direção dos carros
#define RETO			0
#define ESQUERDA	1
#define DIREITA		2

//protótipos
void Jogo_Inicio(void);
void Jogo_Fim(void);
void Menu(void);
void Novo_Jogo(void);
void Jogador(void);
void Bandeira(void);
void Carros(void);
void Desenha_Dados(void);

//variáveis
IMAGEM carros[MAX_CARROS];
IMAGEM jogador;
IMAGEM bandeira;

int menu;//se 1 está no menu; se 0 está no jogo
int vel_carro;
int nivel;
int dist_carro;
int pontos;
int n_bandeiras;
int inicio=1;
int i;
char texto[80];
//sons
int musica_mid;
int bip_wav;

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

	//desenhar pista
	Limpar_Tela(VERDE);
	Desenhar_Retangulo(160,0,479,479,CINZA);

	Desenha_Dados();

	if(menu)
	{
		Menu();
	}
	else //está no jogo
	{
		//processar objetos
		Bandeira();
		Carros();
		Jogador();
	}


	Mostrar_Tela();
	Esperar_Relogio(40);//40 milisegundos -> 25 quadros por segundo

}//fim Jogo_Main

/////////////////////////////////////////
void Jogo_Inicio(void)
{
	int i;
		
		Carregar_Bitmap("carros.bmp");

		Criar_Imagem(jogador,40,64,1);
		Carregar_Quadro(jogador,0,0,0);

		for(i=0; i< MAX_CARROS; i++)
		{
			Criar_Imagem(carros[i],40,64,1);
			Carregar_Quadro(carros[i],0,1,0);
		}

		Carregar_Bitmap("bandeira.bmp");
		Criar_Imagem(bandeira,32,32,1);
		Carregar_Quadro(bandeira,0,0,0);

		//carregar som
		musica_mid = Carregar_Midi("arpe.mid");

		bip_wav = Carregar_Wav("bip.wav");

		menu = 1;//ir p/ menu

}
/////////////////////////////////////////
void Jogo_Fim(void)
{
		
		//liberar memória das imagens
		Destruir_Imagem(jogador);
		Destruir_Imagem(bandeira);
		for(i=0; i< MAX_CARROS; i++)
		{
			Destruir_Imagem(carros[i]);
		}
		Finalizar_Jogo();

}
/////////////////////////////////////////
void Menu(void)
{
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
	bandeira.estado = INATIVO;
	for(i=0;i<MAX_CARROS;i++)
	{
		carros[i].estado = INATIVO;
	}

	jogador.x = 300;
	jogador.y = 400;
	pontos = 0;
	dist_carro=0;
	vel_carro = 4;
	nivel=1;

	
}
/////////////////////////////////////////
void Bandeira(void)
{
	if(bandeira.estado IGUAL INATIVO)
	{
		//inicia uma bandeira
		bandeira.estado = ATIVO;
		bandeira.x = Aleatorio(160,479-bandeira.largura);
		bandeira.y = - bandeira.altura;
	}

	bandeira.y += BAND_VEL;

	if(bandeira.y > 479)
	{
		bandeira.estado = INATIVO;
	}

	Desenhar_Imagem(bandeira);
}

/////////////////////////////////////////
void Carros(void)
{
	int i;

	dist_carro += vel_carro;
	if(dist_carro > 200)
	{
		dist_carro = 0;

		//inicia um carro
		//procurar um disponível
		i=0;

		while((carros[i].estado IGUAL ATIVO) E (i < MAX_CARROS)) i++;

		if(i < MAX_CARROS)
		{
			//inicia o carro
			carros[i].estado = ATIVO;
			carros[i].x = Aleatorio(160,479-carros[i].largura);
			carros[i].y = - carros[i].altura;
			carros[i].dados[TEMPO] = 0;
		}
	}

	//processar os carros
	for(i=0; i <MAX_CARROS; i++)
	{
		if(carros[i].estado IGUAL ATIVO)
		{
			carros[i].y += vel_carro;

			carros[i].dados[TEMPO]--;

			if(carros[i].dados[TEMPO]<0)
			{
				
				carros[i].dados[TEMPO] = 10 * Aleatorio(1,5);
				//0 - reto; 1 - esquerda ; 2 direita
				carros[i].dados[DIR] = Aleatorio(0,2);
			}

			if(carros[i].dados[DIR] == DIREITA)
			{
				carros[i].x+=vel_carro;

				if(carros[i].x > (479 - carros[i].largura)) 
				{
					carros[i].dados[DIR]= ESQUERDA;
				}
			}
			else //esquerda
			if(carros[i].dados[DIR] == ESQUERDA)
			{
				carros[i].x-=vel_carro;

				if(carros[i].x < 160) carros[i].dados[DIR]= DIREITA;
			}

			if(carros[i].y > 479) carros[i].estado = INATIVO;

			Desenhar_Imagem(carros[i]);
		}
	}


}
/////////////////////////////////////////
void Jogador(void)
{
	int i;

	//ler entrada de dados
	if(Testar_Tecla(DIK_UP) OU Joy_Cima() )
	{
			jogador.y-=JOG_VEL;
			if(jogador.y < 0) jogador.y = 0;
	}

	if(Testar_Tecla(DIK_DOWN) OU Joy_Baixo() ) 
	{
			jogador.y+=JOG_VEL;
			if(jogador.y > (479 - jogador.altura))
			{
				jogador.y = 479 - jogador.altura;
			}
	}

	if(Testar_Tecla(DIK_LEFT) OU Joy_Esquerda() ) 
	{
			jogador.x-=JOG_VEL;
			if(jogador.x < 160) jogador.x = 160;
	}
	if(Testar_Tecla(DIK_RIGHT) OU Joy_Direita() ) 
	{
		jogador.x+=JOG_VEL;
		if(jogador.x > (479 - jogador.largura))  
		{
			jogador.x = 479 - jogador.largura;
		}
	}


	//colisao com bandeira
	if(Colisao_Imagens(jogador, bandeira))
	{
		n_bandeiras++;
		pontos+=nivel;
		bandeira.estado = INATIVO;
		Tocar_Wav(bip_wav);

		if((n_bandeiras % 5 ) IGUAL 0)
		{
			//aumenta nivel
			nivel++;
			vel_carro++;
		}
	}

	//colisao com carros
	for(i=0; i< MAX_CARROS; i++)
	{
		if(carros[i].estado IGUAL ATIVO)
		{
			if(Colisao_Imagens(jogador, carros[i]))
			{
				//fim de jogo
				menu = 1;
				return;
			}

		}
	}

	Desenhar_Imagem(jogador);


}//jogador

/////////////////////////////////////////
void Desenha_Dados(void)
{
	Escreve_Texto("M R D X",500,20,BRANCO);
	Escreve_Texto("JOGO 1",500,40,BRANCO);

	sprintf(texto, "PONTOS = %d",pontos);
	Escreve_Texto(texto,500,100,BRANCO);

	sprintf(texto, "NIVEL  = %d",nivel);
	Escreve_Texto(texto,500,140,BRANCO);

	Escreve_Texto("PROGRAMA",10,50,BRANCO);
	Escreve_Texto("MARCOS",20,70,BRANCO);
	Escreve_Texto("ROMERO",20,90,BRANCO);

	Escreve_Texto("DESENHOS",10,150,BRANCO);
	Escreve_Texto("ALBERTO",10,170,BRANCO);
	Escreve_Texto("HOSHINO",10,190,BRANCO);

}