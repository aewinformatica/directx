/* cap7_3.c */

main()
{
  int x =0;

  por_valor(x);
  printf("\nChamada por valor. x = %d", x );

  por_referencia(&x);
  printf("\nChamada por referencia. x = %d", x );

}

por_valor(int a)
{
	a = 10;
}

por_referencia( int * a)
{
  *a = 10;
}