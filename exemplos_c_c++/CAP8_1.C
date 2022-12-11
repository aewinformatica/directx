/* cap8_1.c */

#include "stdio.h"

main()
{
  FILE *fp;
  int escolha, i;
  char texto[50];
  printf("\n Arquivo em modo texto \n\n\n");
  printf("\n1. Gravar Arquivo");
  printf("\n2. Ler Arquivo");
  printf("\n Opcao : ");
  scanf("%d%*c",&escolha);

  if(escolha == 1)
  {
	fp = fopen("teste.txt","w");
	printf("\nDigite um nome : ");
	gets(texto);
	for(i=0; texto[i]; i++) putc(texto[i], fp);

	fclose(fp);
	printf("\nSalvo em teste.txt");
  }
  else
  if(escolha == 2)
  {
   fp = fopen("teste.txt","r");
   if (fp == NULL) printf("\nErro ao abrir arquivo");
   else
   {
	 printf("\n Conteudo do arquivo : \n");
	 while(!feof(fp)) printf("%c", getc(fp) );
   }
  }
  else
  {
	printf("\nOpcao invalida.");
  }

}