// cap11_2.cpp
#include "iostream.h"
#include "string.h"

class Cliente {
		public :
			char * nome;

			//construtor
			Cliente( char * _nome = "sem nome")
			{
			  nome = new char[ strlen(_nome) + 1 ];
			  strcpy(nome, _nome);
			}
			//destruidor
			~Cliente()
			{
			  delete[] nome;
			}
	};

void main()
{
   Cliente c1("Jonas"), c2("Mateus");

   cout << "\nCliente 1 : " << c1.nome;
   cout << "\nCliente 2 : " << c2.nome;

}
