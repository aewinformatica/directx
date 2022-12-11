/*
ARQUIVO	: CMAPA.CPP

AUTOR		: MARCOS ROMERO

E-MAIL	: ROMERO2@UOL.COM.BR

PÁGINA	: WWW.GEOCITIES.COM/PROGJOGOS

DATA		: NOVEMBRO DE 2003

COMENTÁRIOS:

				Implementacao da classe para gerenciar um mapa.
*/

#include "CMapa.h"
#include "stdio.h"


void CMapa::Carregar(void)
{
	/*
  verificar se existe o arquivo mapa.rhg, se houver carregar os 
	dados dele. Se não houver então zera todos as posicoes do mapa.
	*/

	FILE *fp;
	int cel_x,cel_y;

	//abrir arquivo em modo binário p/ leitura
	if((fp = fopen("mapa.rhg","rb"))!=NULL)
	{
			//carregar info
		for(cel_x = 0; cel_x < CMAPA_LARGURA; cel_x++)
		{
			for(cel_y = 0; cel_y < CMAPA_ALTURA; cel_y++)
			{
				mapa_base[cel_x][cel_y] = getw(fp);
				mapa_objetos[cel_x][cel_y] = getw(fp);
			}
		}

	  //fechar arquivo
	  fclose(fp);

	}
	else
	{
		//valores padroes
		for(cel_x = 0; cel_x < CMAPA_LARGURA; cel_x++)
		{
			for(cel_y = 0; cel_y < CMAPA_ALTURA; cel_y++)
			{
				mapa_base[cel_x][cel_y] = 0;
				mapa_objetos[cel_x][cel_y] = 0;
			}
		}
	}

}
/////////////////////////////
void CMapa::Salvar(void)
{
  //Salvar os dados do mapa no arquivo mapa.rhg 
	FILE *fp;
	int cel_x,cel_y;

	//abrir arquivo em modo binário p/ escrita
	if((fp = fopen("mapa.rhg","wb"))!=NULL)
	{
	  for(cel_x = 0; cel_x < CMAPA_LARGURA; cel_x++)
		{
			for(cel_y = 0; cel_y < CMAPA_ALTURA; cel_y++)
			{
			  putw(mapa_base[cel_x][cel_y], fp);
			  putw(mapa_objetos[cel_x][cel_y], fp);					
			}
	  }
		//fechar arquivo
		fclose(fp);
	}
	
}
/////////////////////////////
void CMapa::Atribuir_Imagem_Base(IMAGEM & im)
{
	//recebe uma referencia de uma IMAGEM criada externamente
	//Este representa os tiles da base

	im_base = &im;
}
/////////////////////////////
void CMapa::Atribuir_Imagem_Objetos(IMAGEM & im)
{
	//recebe uma referencia de uma IMAGEM criada externamente
	//Este representa os tiles dos objetos (camada superior)

	im_objetos = &im;
}
/////////////////////////////

void CMapa::Atribuir(int camada, int cel_x, int cel_y, int valor)
{
   //Atribui o valor a uma determinada posicao do mapa
	 // camada 0 -> Base; 1 -> Objetos;

	if(cel_x <0 || cel_x >= CMAPA_LARGURA) return;
	if(cel_y <0 || cel_y >= CMAPA_ALTURA) return;
	if(camada <0 || camada >= 2) return;
	if(valor<0 || valor >= NUM_TILES) return;

	if(camada==0) 
	{
		mapa_base[cel_x][cel_y] = valor;
	}
	else
	{
		mapa_objetos[cel_x][cel_y] = valor;
	}

}
/////////////////////////////
int CMapa::Ler(int camada, int cel_x, int cel_y)
{
	//Retorna o valor de uma determinada posicao do mapa
	if(cel_x <0 || cel_x >= CMAPA_LARGURA) return -1;
	if(cel_y <0 || cel_y >= CMAPA_ALTURA) return -1;
	if(camada <0 || camada >= 2) return -1;

	if(camada==0) 
	{
		return(mapa_base[cel_x][cel_y]);
	}
	else
	{
		return(mapa_objetos[cel_x][cel_y]);
	}

}
/////////////////////////////

void CMapa::Desenhar(int x, int y)
{
	int cel_x,cel_y;

	//desenha as duas camadas do mapa
		for(cel_x = 0; cel_x < CMAPA_LARGURA; cel_x++)
	   for(cel_y = 0; cel_y < CMAPA_ALTURA; cel_y++)
	   {	
				im_base->x = im_objetos->x = x + (cel_x * TAM_BLOCO);  
				im_base->y = im_objetos->y = y + (cel_y * TAM_BLOCO);  

				//pegar índice do quadro que deve ser desenhado. 
				im_base->quadro_atual = mapa_base[cel_x][cel_y];
				im_objetos->quadro_atual = mapa_objetos[cel_x][cel_y];

				//desenha as duas camadas da célula 
				Desenhar_Imagem(*im_base);
				Desenhar_Imagem(*im_objetos);
	   }


}
/////////////////////////////
