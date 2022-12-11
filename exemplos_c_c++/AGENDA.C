/*
Nome    : agenda.c
Autor   : Marcos Romero

	Programa de exemplo da parte II
*/

#include "stdio.h"

/* valores constantes */
#define MAX_ITENS 100


typedef struct {
		char nome[30];
		char telefone[15];
		char endereco[30];
	} INFO;

INFO agenda[MAX_ITENS];

int n_itens = 0;

main()
{
  int escolha;

  printf("\n\n *** EXEMPLO DE AGENDA *** \n");

  while(1)
  {
	printf("\n\n M E N U \n");
	printf("\n 1. Entrar dados");
	printf("\n 2. Listar dados");
	printf("\n 3. Salvar");
	printf("\n 4. Carregar");
	printf("\n 5. Encerrar programa");

	printf("\n\n Escolha: ");
	scanf("%d%*c", &escolha);

	switch(escolha)
	{
	  case 1:
			Entrar_Dados();
			break;

	  case 2:
			Listar_Dados();
			break;

	  case 3:
			Salvar();
			break;

	  case 4:
			Carregar();
			break;

	  case 5:
			exit(0);
			break;

	  default: printf("\n Opcao invalida\n ");
			 break;
	}/*fim switch*/
  } /*fim while*/
}/*fim main*/

Entrar_Dados()
{
  char resp;

  do {

	if(n_itens >= MAX_ITENS)
	{
		printf("\nAgenda cheia");
		return;
	}

	printf("\n Nome : ");
	gets(agenda[n_itens].nome);
	printf("\n Telefone : ");
	gets(agenda[n_itens].telefone);
	printf("\n Endereco : ");
	gets(agenda[n_itens].endereco);

	n_itens++;

	printf("\n Continuar(s/n) : ");
	scanf("%c%*c", &resp);

  } while(resp == 's' || resp == 'S');
}

Listar_Dados()
{
	int i;

	if(n_itens == 0)
	{
	  printf("\n Agenda vazia.");
	  return;
	}

	for(i=0; i < n_itens; i++)
	{
		printf("\n %s --- %s --- %s", agenda[i].nome, agenda[i].telefone,
									  agenda[i].endereco);
	}
}

Salvar()
{
  FILE *fp;

	if(n_itens == 0)
	{
	  printf("\n Agenda vazia.");
	  return;
	}

  fp = fopen("dados.bd", "wb");

  if(fp==NULL)
  {
	printf("\n Erro ao abrir arquivo.");
	return;
  }
  //salvar o numero de itens primeiro
  putw(n_itens, fp);

  //salvar todos os dados em um unico bloco
  fwrite(agenda, sizeof(INFO), n_itens, fp);

  fclose(fp);

  printf("\n Salvo em dados.bd");
}

Carregar()
{
  FILE *fp;

  fp = fopen("dados.bd", "rb");

  if(fp==NULL)
  {
	printf("\n Erro ao abrir arquivo.");
	return;
  }
  //ler o numero de itens primeiro
  n_itens = getw(fp);

  //recuperar todos os dados em um unico bloco
  fread(agenda, sizeof(INFO), n_itens, fp);

  fclose(fp);

  printf("\n Dados recuperados.");

}
