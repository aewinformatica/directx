/*
------------ PROJETO MRDX -----------------
Autor : Marcos Romero (RH Games - Beljogos)
Email : romero1978@gmail.com
Página: http://romerogames.blogspot.com
-------------------------------------------

INFO:

Jogo de exemplo dos recursos do MRDX 1.1.

26/04/2011
*/

#include "mrdx.h"


//Constantes
const int ESTADO_JOGO_INICIO = 0;
const int ESTADO_JOGO_EXECUCAO = 1;
const int ESTADO_JOGO_FIM = 2;

const int VEL_ANIMAL = 6;
const int MAX_INSETOS = 50;

//definir contantes para dados de insetos
const int INSETO_DADOS_VEL_X = 0;
const int INSETO_DADOS_VEL_Y = 1;
const int INSETO_DADOS_LARGURA = 2;
const int INSETO_DADOS_ALTURA = 3;

//Dados de Animal
const int ANIMAL_DADOS_ESPELHAR = 0;


//Variáveis do tipo IMAGEM
IMAGEM imagem_fundo;
IMAGEM animal;
IMAGEM inseto;
IMAGEM insetos_clone[MAX_INSETOS];

//Identificadores de Sons e Músicas
int musica_mid;


//Variáveis Gerais
int estado_jogo = ESTADO_JOGO_INICIO;
unsigned int cont = 0;  //variavel usada para contar frames


//Protótipos de Funções
void Jogo_Inicio(void);
void Jogo_Fim(void);
void Jogo_Execucao(void);
void Processar_Animal(void);
void Processar_Insetos(void);


///////////////////////////////////////////////////////
//Função principal do jogo que é chamada várias vezes por segundo.
void Jogo_Main(void)
{
	switch(estado_jogo) {

		case ESTADO_JOGO_INICIO:
						Jogo_Inicio();
						break;

		case ESTADO_JOGO_EXECUCAO:
						Jogo_Execucao();
						break;

		case ESTADO_JOGO_FIM:
						Jogo_Fim();
						break;
	}

}

///////////////////////////////////////////////////////
void Jogo_Inicio(void)
{

		Carregar_Bitmap("background.bmp");

		//Carregar Imagem de Fundo
		Criar_Imagem(imagem_fundo,640,480,1);
		Carregar_Quadro(imagem_fundo,0,0,0);

		//Carregar Animal controlado pelo jogador
		Carregar_Bitmap("bichos.bmp");
		
		Criar_Imagem(animal,128,80,6);

		for(int i=0; i < 4; i++)
		{
			Carregar_Quadro(animal,i,i,0,true); 
		}

		//O ultimo parametro com valor 'true' indica que existe bordas ao redor da imagem
		Carregar_Quadro(animal,4,0,1,true);
		Carregar_Quadro(animal,5,1,1,true);

		//posição inicial
		animal.x = 100;
		animal.y = 400;
		
		animal.dados[ANIMAL_DADOS_ESPELHAR] = MRDX_NAO_ESPELHAR;


		//Carregar insetos
		Criar_Imagem(inseto,64,40,2);

		//os dois ultimos parametros indica a posição onde está a imagem no Bitmap
		Carregar_Quadro(inseto,0,0,0,false,440,300);
		Carregar_Quadro(inseto,1,1,0,false,440,300);

		//É armazenado na memória apenas a Imagem de um inseto.
		//Todos os outros insetos usam essa mesma Imagem fonte, devido a função Clone_Imagem()
		for(i=0; i < MAX_INSETOS; i++)
		{
			Clone_Imagem(inseto, insetos_clone[i]);

			insetos_clone[i].estado = ATIVO;


			insetos_clone[i].x = 100 + Aleatorio(0,450);
			insetos_clone[i].y = 100 + Aleatorio(0,250);

			//As linhas abaixo servem para diferenciar os insetos
			insetos_clone[i].dados[INSETO_DADOS_VEL_X] = -5 + Aleatorio(0,10); 
			insetos_clone[i].dados[INSETO_DADOS_VEL_Y] = -5 + Aleatorio(0,10); 

			insetos_clone[i].dados[INSETO_DADOS_LARGURA] = 50 + Aleatorio(0,30); 
			insetos_clone[i].dados[INSETO_DADOS_ALTURA] = 25 + Aleatorio(0,30);

			//O teste abaixo é para evitar que o inseto se move em linha reta
			if(insetos_clone[i].dados[INSETO_DADOS_VEL_X] == 0)
			{
				insetos_clone[i].dados[INSETO_DADOS_VEL_X] = 1;
			}

			if(insetos_clone[i].dados[INSETO_DADOS_VEL_Y] == 0)
			{
				insetos_clone[i].dados[INSETO_DADOS_VEL_Y] = 1;
			}
			
		}

		//carregar musica
		musica_mid = Carregar_Midi("preludio.mid");

		estado_jogo = ESTADO_JOGO_EXECUCAO;
}

///////////////////////////////////////////////////////
void Jogo_Fim(void)
{
		Transicao_Tela(VERDE);
	
		Destruir_Imagem(imagem_fundo);
		Destruir_Imagem(animal);
		Destruir_Imagem(inseto);

		Finalizar_Jogo();
}

///////////////////////////////////////////////////////
void Jogo_Execucao(void)
{
	Iniciar_Relogio();	
	Limpar_Tela();

	//tocar música
	if(!Midi_Tocando(musica_mid))
	{
		Tocar_Midi(musica_mid);
	}

	//Sair do Jogo se a tecla Esc for pressionada
	if(Testar_Tecla(DIK_ESCAPE))
	{	
		estado_jogo = ESTADO_JOGO_FIM;
		return;
	}

	Desenhar_Imagem(imagem_fundo);

	Processar_Animal();

	Processar_Insetos();

	cont++;

	Mostrar_Tela();
	Esperar_Relogio(40);
}

///////////////////////////////////////////////////////
void Processar_Animal(void)
{

	if(cont % 2 == 1)
	{
		animal.quadro_atual++;
		if(animal.quadro_atual > 5)
		{
			animal.quadro_atual = 0;
		}
		
	}

	if(Testar_Tecla(DIK_RIGHT))
	{
		if(animal.x < 640 - 128)
		{
			animal.x += VEL_ANIMAL;
		}
		
		animal.dados[ANIMAL_DADOS_ESPELHAR] = MRDX_NAO_ESPELHAR;
		
	} 
	else if(Testar_Tecla(DIK_LEFT))
	{
		if(animal.x > 0)
		{
			animal.x -= VEL_ANIMAL;
		}
		
		animal.dados[ANIMAL_DADOS_ESPELHAR] = MRDX_ESPELHAR_HOR;
	}
	else 
	{
		animal.quadro_atual = 0;
	}
		
	
	Desenhar_Imagem(animal, animal.dados[ANIMAL_DADOS_ESPELHAR]);

}

///////////////////////////////////////////////////////
void Processar_Insetos(void)
{
	
	for(int i=0; i < MAX_INSETOS; i++) 
	{
		//Se estiver INATIVO vai para o próximo Inseto.
		if(insetos_clone[i].estado == INATIVO)	continue; 
		

		insetos_clone[i].x += insetos_clone[i].dados[INSETO_DADOS_VEL_X];
		insetos_clone[i].y += insetos_clone[i].dados[INSETO_DADOS_VEL_Y];

		if((insetos_clone[i].x > 640 - 64) OU (insetos_clone[i].x < 0)  )
		{
			insetos_clone[i].dados[INSETO_DADOS_VEL_X] = - insetos_clone[i].dados[INSETO_DADOS_VEL_X];
		}

		if((insetos_clone[i].y > 480 - 40) OU (insetos_clone[i].y < 0) )
		{
			insetos_clone[i].dados[INSETO_DADOS_VEL_Y] = - insetos_clone[i].dados[INSETO_DADOS_VEL_Y];
		}

		if(cont % 5 == 1)
		{
			insetos_clone[i].quadro_atual = 1 - insetos_clone[i].quadro_atual; 
		}

		if(Colisao_Imagens(animal, insetos_clone[i]))
		{
			insetos_clone[i].estado = INATIVO;
		} 
				

		Desenhar_Imagem(insetos_clone[i],0, insetos_clone[i].dados[INSETO_DADOS_LARGURA], 
											insetos_clone[i].dados[INSETO_DADOS_ALTURA]);
		
		
	}

}


/////////////////////////////////////////////////////////////
