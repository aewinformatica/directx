// cap9_2.cpp

#include "iostream.h"

//prototipos das funcoes

void inicia_var(int &var, int valor = 0);
void inicia_var(float &var, float valor = 0.0);

void main()
{
   int var_inteira;
   float var_fracionaria;

   inicia_var(var_inteira, 5);
   cout << "\n var_inteira = " << var_inteira;

   inicia_var(var_inteira);
   cout << "\n var_inteira = " << var_inteira;

   inicia_var(var_fracionaria, 3.75);
   cout << "\n var_fracionaria = " << var_fracionaria;

}

void inicia_var(int & var, int valor)
{
   var = valor;
}

void inicia_var(float & var, float valor)
{
   var = valor;
}

