/* cap8_2.c */

#include "stdio.h"

struct heroi {
		char nome[40];
		int energia;
		int moedas;
		};

main()
{
  int escolha;
  struct heroi h1;
  FILE *fp;

  printf("\n Arquivo em modo binario \n\n\n");
  printf("\n1. Gravar Arquivo");
  printf("\n2. Ler Arquivo");
  printf("\n Opcao : ");
  scanf("%d%*c",&escolha);

  switch(escolha)
  {
	case 1:
			/* preencher informacoes do heroi */
			strcpy(h1.nome, "Mestre");
			h1.energia = 100;
			h1.moedas = 15;

			/* salvar em arquivo */
			fp = fopen("heroi.txt","wb");
			if(fp == NULL)
			{
				printf("\n erro ao abrir arquivo");
				exit(0);
			}
			else
			{
			   fwrite(&h1, sizeof(struct heroi), 1, fp);
			   fclose(fp);
			   printf("\n Salvo em heroi.txt");
			}
			break;

	case 2:
			fp = fopen("heroi.txt","rb");
			if(fp == NULL)
			{
				printf("\n erro ao abrir arquivo");
				exit(0);
			}
			else
			{
				fread(&h1, sizeof(struct heroi), 1, fp);
				fclose(fp);
				printf("\n Dados do Heroi : \n");
				printf("\n Nome : %s", h1.nome);
				printf("\n Energia : %d", h1.energia);
				printf("\n Moedas : %d", h1.moedas);
			}
			break;

	default:  printf("\nOpcao invalida");

  }
}