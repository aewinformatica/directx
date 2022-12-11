/*
ARQUIVO	: LUTADOR.CPP

AUTOR		: MARCOS ROMERO

E-MAIL	: ROMERO2@UOL.COM.BR

PÁGINA	: WWW.GEOCITIES.COM/PROGJOGOS

DATA		: NOVEMBRO DE 2003

COMENTÁRIOS:

				Este programa ilustra o uso de animacao em jogos 2D. 
				Ele utiliza uma classe chamada "CAnim" que faz o processamento
				da animacao.
*/


#include "mrdx.h"
#include "CAnim.h"


#define POS_VER		220
#define VEL_HOR		4


//variáveis
IMAGEM lutador;
IMAGEM fundo;

int inicio=1;

int vel_vertical, pulo_vel_hor;

int anim_parado, anim_andando, anim_recuando, anim_soco, anim_chute,
		anim_abaixar, anim_soco_baixo, anim_chute_baixo, anim_pulo;

bool atacando=false, pulando=false;

int ANIM_PARADO[] = { 0,1,2,3,4,5,4,3,2,1 };
int ANIM_ANDANDO[] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
int ANIM_RECUANDO[] = {21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6};
int ANIM_SOCO[] = {34,35,36,36,35,34};
int ANIM_CHUTE[] = {37,38,39,39,38,37};
int ANIM_ABAIXAR[] = {22,23,24};
int ANIM_SOCO_BAIXO[] = {42,40,41,41,40,42};
int ANIM_CHUTE_BAIXO[] = {42,43,44,44,43,42};
int ANIM_PULO[] = {25,26,27,28,29,29,30,31,32,33};

CAnim anim;

//-------------------------
//função principal do jogo
void Jogo_Main(void)
{
  //INICIALIZACAO
	if(inicio)
	{
		inicio = 0;
				
		Carregar_Bitmap("lutador.bmp");
		
		Criar_Imagem(lutador,104,124,45);

		int ind=0;
		for(int lin=0; lin < 5; lin++)
			for(int col=0; col < 9; col++)
			{
				Carregar_Quadro(lutador,ind,col,lin);
				ind++;
			}

			lutador.y = POS_VER;
			lutador.x = 50;

			//Carregar as animacoes
			anim_parado = anim.Adiciona_Anim(10, ANIM_PARADO);
			anim_andando = anim.Adiciona_Anim(16, ANIM_ANDANDO);
			anim_recuando = anim.Adiciona_Anim(16, ANIM_RECUANDO);
			anim_soco = anim.Adiciona_Anim(6, ANIM_SOCO);
			anim_chute = anim.Adiciona_Anim(6, ANIM_CHUTE);
			anim_abaixar = anim.Adiciona_Anim(3, ANIM_ABAIXAR);
			anim_soco_baixo = anim.Adiciona_Anim(6, ANIM_SOCO_BAIXO);
			anim_chute_baixo = anim.Adiciona_Anim(6, ANIM_CHUTE_BAIXO);
			anim_pulo = anim.Adiciona_Anim(10, ANIM_PULO);

		//imagem de fundo
		Carregar_Bitmap("fundo.bmp");

		Criar_Imagem(fundo,640,400,1);
		Carregar_Quadro(fundo,0,0,0);


	}//fim if(inicio)

	//FINALIZACAO
	if(Testar_Tecla(DIK_ESCAPE))
	{
		Destruir_Imagem(lutador);
		Destruir_Imagem(fundo);
		
		Finalizar_Jogo();
		return;
	}

	//CÓDIGO PRINCIPAL
	Iniciar_Relogio();
		
	Limpar_Tela(AZUL);

	if(pulando)
	{
		lutador.y += vel_vertical;
		vel_vertical++;

		lutador.x += pulo_vel_hor;
		//testar os limites da tela
		if(lutador.x < VEL_HOR  || lutador.x > (640 - lutador.largura))
		{
			pulo_vel_hor = 0;
		}
		

		//testar fim de pulo
		if(lutador.y >= POS_VER)
		{
			lutador.y = POS_VER;
			pulando=false;
			anim.Atribuir_Anim_Atual(anim_parado);
		}
	}
	else
	if(atacando)
	{
		if(anim.Anim_Feita())
		{
			atacando = false;		
		}
	}
  else 
	{
	 if(Testar_Tecla(DIK_LSHIFT))
	 {
	  if(Testar_Tecla(DIK_DOWN)) 
		{
		 anim.Atribuir_Anim_Atual(anim_soco_baixo);
		}
		else
		{
		 anim.Atribuir_Anim_Atual(anim_soco);
		}
		
		atacando = true;
	 }
	 else
	 if(Testar_Tecla(DIK_LCONTROL))
	 {
		if(Testar_Tecla(DIK_DOWN)) 
		{
		 anim.Atribuir_Anim_Atual(anim_chute_baixo);
		}
		else
		{
		 anim.Atribuir_Anim_Atual(anim_chute);
		}

		atacando = true;
	 }
	 else
	 if(Testar_Tecla(DIK_UP))
	 {
		//o 'true' no final indica que a animacao deve
		//parar no ultimo quadro ao inves de reiniciar.
		anim.Atribuir_Anim_Atual(anim_pulo,true);

		pulando = true;
		vel_vertical = -15;

		if(Testar_Tecla(DIK_LEFT)) pulo_vel_hor = - VEL_HOR;
		else
		if(Testar_Tecla(DIK_RIGHT)) pulo_vel_hor = VEL_HOR;
		else pulo_vel_hor = 0;

	 }
	 else
	 if(Testar_Tecla(DIK_DOWN))
	 {
		//o 'true' no final indica que a animacao deve
		//parar no ultimo quadro ao inves de reiniciar.
		anim.Atribuir_Anim_Atual(anim_abaixar,true);
	 }
	 else
	 if(Testar_Tecla(DIK_LEFT))
	 {
		anim.Atribuir_Anim_Atual(anim_recuando);

		if(lutador.x > VEL_HOR)
		{
		  lutador.x -= VEL_HOR;
		}
	 }
	 else
   if(Testar_Tecla(DIK_RIGHT))
	 {
		anim.Atribuir_Anim_Atual(anim_andando);

		if(lutador.x < (640 - lutador.largura))
		{
		  lutador.x += VEL_HOR;
		}
	 }
	 else
	 {
		anim.Atribuir_Anim_Atual(anim_parado);
	 }
	}//else - if(atacando)

	lutador.quadro_atual = anim.Atualizar();

	Desenhar_Imagem(fundo);
	Desenhar_Imagem(lutador);

	Escreve_Texto("ESTE PROGRAMA ILUSTRA O USO DE ANIMAÇÃO EM JOGOS 2D.",
								10,410,BRANCO);

	Escreve_Texto("COMANDOS: SETAS - MOVIMENTOS   SHIFT - SOCO  \
CONTROL - CHUTE   ESC - SAIR", 10,428,BRANCO);

	Escreve_Texto("A IMAGEM DO LUTADOR FOI OBTIDA NO PROGRAMA MUGEN E O \
CENÁRIO É DO RPG MAKER.", 10,446,BRANCO);

	Escreve_Texto("DESENVOLVIDO POR MARCOS ROMERO USANDO O MRDX.    \
WWW.GEOCITIES.COM/PROGJOGOS",	10,464,BRANCO);
	
	Mostrar_Tela();
	Esperar_Relogio(25);//25 milisegundos -> 40 quadros por segundo

}//fim Jogo_Main

/////////////////////////////////////////



