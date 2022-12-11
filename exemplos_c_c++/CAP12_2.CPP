// cap12_2.cpp

#include "iostream.h"

//classe abstrata
class Forma2d {
		public:
			virtual float area()
			{
				return 0.0;
			}
			virtual void mostra_nome() = 0;
};

class Retangulo : public Forma2d
{
	public :
		//construtor
		Retangulo(float larg = 0.0, float alt = 0.0)
		{
		  largura = larg;
		  altura = alt;
		}

		virtual float area()
		{
		  return largura * altura;
		}

		virtual void mostra_nome()
		{
		  cout << "\n Retangulo ";
		}
	protected:
		float largura, altura;
};

class Circulo : public Forma2d
{
  public:
		Circulo( float r = 0.0)
		{
		  raio = r;
		}
		virtual float area()
		{
		  return 3.1416 * raio * raio;
		}

		virtual void mostra_nome()
		{
		  cout << "\n Circulo ";
		}
  protected:
		float raio;
};

void main()
{
   Retangulo r1(5,3), r2(10, 8);
   Circulo c1(4);

   Forma2d * formas[3];

   formas[0] = &r1;
   formas[1] = &r2;
   formas[2] = &c1;

   //ajustar a saida para mostrar duas casas decimais
   cout.precision(2);

   for(int i=0; i < 3; i++)
   {
	 formas[i]->mostra_nome();
	 cout << "\n Area = " << formas[i]->area() << endl;
   }
}
