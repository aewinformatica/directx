/*
------------ PROJETO GENESIS --------------
Autor : Marcos Romero (RH Games - Beljogos)
Email : romero1978@gmail.com
Página: http://romerogames.blogspot.com
-------------------------------------------
*/

/*
ARQUIVO	: CMAPA.H

DATA		: NOVEMBRO DE 2003

COMENTÁRIOS:

				Definicao de uma classe usada para gerenciar  um 
"tile based map".
*/

#ifndef CMAPA_H
#define CMAPA_H

#include "mrdx.h"


#define CMAPA_LARGURA		14
#define CMAPA_ALTURA		14
#define TAM_BLOCO				32
#define NUM_TILES				48

class CMapa
{
	public:

		void Carregar(void);
		void Salvar(void);

		void Atribuir_Imagem_Base(IMAGEM & im);
		void Atribuir_Imagem_Objetos(IMAGEM & im);

		void Atribuir(int camada, int cel_x, int cel_y, int valor);
		int Ler(int camada, int cel_x, int cel_y);

		void Desenhar(int x, int y);


	protected:

		int mapa_base[CMAPA_LARGURA][CMAPA_ALTURA];
		int mapa_objetos[CMAPA_LARGURA][CMAPA_ALTURA];

		IMAGEM *im_base;
		IMAGEM *im_objetos;
		
};

#endif
