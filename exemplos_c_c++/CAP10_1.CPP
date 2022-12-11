// cap10_1.cpp

#include "iostream.h"

class retangulo {
		public :
			int altura;
			int largura;

			int area()
			{
			  return altura * largura;
			}
		};

void main()
{
   retangulo r1, r2;

   r1.altura = 5;
   r1.largura = 3;

   r2.altura = 8;
   r2.largura = 4;

   cout << "\n Area do retangulo 1 = " << r1.area();
   cout << "\n Area do retangulo 2 = " << r2.area();

}