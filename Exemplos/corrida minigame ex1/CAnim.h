/*
ARQUIVO	: CANIM.H

AUTOR		: MARCOS ROMERO

E-MAIL	: ROMERO2@UOL.COM.BR

PÁGINA	: WWW.GEOCITIES.COM/PROGJOGOS

DATA		: NOVEMBRO DE 2003

COMENTÁRIOS:

				Definicao de uma classe usada para processar sequencias de 
				animacoes.
*/


#ifndef CANIM_H
#define CANIM_H

#define MAX_ANIM 32


class CAnim
{
	public:
		
		CAnim(void);//construtor
		virtual ~CAnim(void);//destrutor - libera as animações alocadas
		int Atualizar(void); //calcula e retorna o quadro_atual
		int Quadro_Atual(void); //apenas retorna o quadro_atual
		int Atribuir_Anim_Freq(int freq);
		int Anim_Freq(void);
		int Adiciona_Anim(int num_pos, int *sequencia);//retorna o indice da anim
		int Anim_Ind(void);
		int Anim_Atual(void);
		int Atribuir_Anim_Atual(int anim, bool trava=false);
		bool Anim_Feita(void);
		void Reinicia_Anim(void);
		int Num_Anim(void);
		void Prox_Quadro(void);

	protected:
		
		int anim_cont;
		int anim_freq;
		int quadro_atual;
		int anim_ind;
		int *anim_seq[MAX_ANIM];
		int anim_atual;
		bool anim_feita;
		int num_anim;
		bool trava_ult_quadro;

};

#endif