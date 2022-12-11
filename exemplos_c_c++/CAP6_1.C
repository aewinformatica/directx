/* cap6_1.c */

main()
{
  int x;
  int *pont;

  printf("\nEstudo dos ponteiros\n");

  printf("\nDigite um valor para X: ");
  scanf("%d", &x);

  pont = &x;  /* o ponteiro recebe o endereco de x*/

  printf("\nx = %d",x);
  printf("\nEndereco de memoria de X = %p", &x);
  printf("\nConteudo de pont = %p", pont);
  printf("\nValor que esta no endereco apontado por pont = %d", *pont);

  /*alterar o conteudo de x atraves do ponteiro */
  *pont += 10;

  printf("\nX alterado pelo ponteiro = %d", x);

}