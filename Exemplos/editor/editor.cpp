/*
ARQUIVO	: EDITOR.CPP

AUTOR		: MARCOS ROMERO

E-MAIL	: ROMERO2@UOL.COM.BR

PÁGINA	: WWW.GEOCITIES.COM/PROGJOGOS

DATA		: NOVEMBRO DE 2003

COMENTÁRIOS:

				Este programa ilustra o uso de editores de mapas em jogos 2D. 
				Ele utiliza uma classe chamada "CMapa" que faz o gerenciamento
				do conteúdo do mapa.
*/


#include "mrdx.h"
#include "CMapa.h"


//variáveis
IMAGEM objetos;
IMAGEM base;
IMAGEM cursor;

int inicio=1;

int tile_atual=0;
int camada_atual=0;

bool control_trava=false;

CMapa mapa;

//-------------------------
//função principal do jogo
void Jogo_Main(void)
{
  //INICIALIZACAO
	if(inicio)
	{
		int ind,lin,col;

		inicio = 0;

		//criar cursor
		Carregar_Bitmap("cursor.bmp");
		Criar_Imagem(cursor,32,32,1);
		Carregar_Quadro(cursor,0,0,0);
		cursor.x = 200;
		cursor.y = 200;

		//Criar a IMAGEM que representa os objetos		
		Carregar_Bitmap("objetos.bmp");
		
		Criar_Imagem(objetos,32,32,48);

		ind=0;
		for(lin=0; lin < 8; lin++)
			for(col=0; col < 6; col++)
			{
				Carregar_Quadro(objetos,ind,col,lin);
				ind++;
			}

			//Criar a IMAGEM que representa a base		
		Carregar_Bitmap("base.bmp");
		
		Criar_Imagem(base,32,32,48);

		ind=0;
		for(lin=0; lin < 8; lin++)
			for(col=0; col < 6; col++)
			{
				Carregar_Quadro(base,ind,col,lin);
				ind++;
			}


			mapa.Atribuir_Imagem_Base(base);
			mapa.Atribuir_Imagem_Objetos(objetos);
			mapa.Carregar();

	}//fim if(inicio)

	//FINALIZACAO
	if(Testar_Tecla(DIK_ESCAPE))
	{
		Destruir_Imagem(objetos);
		Destruir_Imagem(base);
		Destruir_Imagem(cursor);
		mapa.Salvar();
		
		Finalizar_Jogo();
		return;
	}

	//CÓDIGO PRINCIPAL
	Iniciar_Relogio();
	Limpar_Tela(AZUL);

	if(Testar_Tecla(DIK_LCONTROL) )
	{
		//alterar camada
		if(!control_trava)
		{
		 camada_atual = 1 - camada_atual;
		 control_trava = true;
		}
	}
	else
	{
		control_trava = false;
	}

  //Cursor
	cursor.x += Mouse_Xvar();
	if(cursor.x <0) cursor.x = 0;
	if(cursor.x >=640) cursor.x = 639;

	cursor.y += Mouse_Yvar();
	if(cursor.y <0) cursor.y = 0;
	if(cursor.y >=480) cursor.y = 479;

	if(Mouse_Bot_Esquerdo())
	{
		if(cursor.x < 448)
		{
			if(cursor.y < 448)
			{
				//area do mapa
				mapa.Atribuir(camada_atual, cursor.x / TAM_BLOCO, 
											cursor.y / TAM_BLOCO, tile_atual);
			}
		}
		else
		{
			if(cursor.y < 256)
			{
				//area dos tiles
				tile_atual = (cursor.x - 448) / TAM_BLOCO + 
										 (cursor.y / TAM_BLOCO) * 6;
			}
		}
	}

  

	mapa.Desenhar(0,0);

	
	//desenhar os tiles a serem selecionados
	int quadro_ind=0;
	int tile_lin,tile_col;
	
	if(camada_atual==0)
	{
   for( tile_lin =0; tile_lin < 8; tile_lin++)
		for(tile_col =0; tile_col < 6; tile_col++)
		{
			base.quadro_atual = quadro_ind;
			base.x = 448 + tile_col * TAM_BLOCO;
			base.y = tile_lin * TAM_BLOCO;
			Desenhar_Imagem(base);
			quadro_ind++;
		}
	}
	else
	{
	 for( tile_lin =0; tile_lin < 8; tile_lin++)
		for(tile_col =0; tile_col < 6; tile_col++)
		{
			objetos.quadro_atual = quadro_ind;
			objetos.x = 448 + tile_col * TAM_BLOCO;
			objetos.y = tile_lin * TAM_BLOCO;
			Desenhar_Imagem(objetos);
			quadro_ind++;
		}
	}

  Desenhar_Retangulo(447,0,448,479,BRANCO);

	Escreve_Texto("EDITOR  DE  MAPAS",475,265,BRANCO);

	Escreve_Texto("TILE ATUAL :",475,300,BRANCO);
	//desenhar o tile selecionado
	if(camada_atual==0)
	{
		base.x = 580;
		base.y = 290;
		base.quadro_atual = tile_atual;
		Desenhar_Imagem(base);
	}
	else
	{
		objetos.x = 580;
		objetos.y = 290;
		objetos.quadro_atual = tile_atual;
		Desenhar_Imagem(objetos);
	}

	Escreve_Texto("COMANDOS:",475,340,BRANCO);
	Escreve_Texto("MOUSE   - EDIÇÃO",475,360,BRANCO);
	Escreve_Texto("CONTROL - CAMADAS",475,380,BRANCO);
	Escreve_Texto("E S C   - SAIR",475,400,BRANCO);

	Escreve_Texto("AS IMAGENS SÃO",475,440,BRANCO);
	Escreve_Texto("DO RPG MAKER",475,460,BRANCO);

	Escreve_Texto("DESENVOLVIDO POR MARCOS ROMERO USANDO O MRDX.",
								45,450,BRANCO);
	Escreve_Texto("WWW.GEOCITIES.COM/PROGJOGOS",100,465,BRANCO);	

	Desenhar_Imagem(cursor);
	

	Mostrar_Tela();
	Esperar_Relogio(25);//25 milisegundos -> 40 quadros por segundo

}//fim Jogo_Main

/////////////////////////////////////////



