// cap12_1.cpp

#include "iostream.h"

class Ponto {
	public:
		//construtor
		Ponto(int _x = 0, int _y =0)
		{
		  x = _x;
		  y = _y;
		}
		void def_ponto(int _x, int _y)
		{
		  x = _x;
		  y = _y;
		}
		int vlr_x()
		{
		  return x;
		}
		int vlr_y()
		{
		  return y;
		}

		void imprime()
		{
		  cout <<"\n PONTO :";
		  cout <<" [ " << x << "," << y <<" ]\n";
		}
	protected:
		int x, y;
};

class Reta : public Ponto
{
	public:
		//construtor
		Reta(int xf=0, int yf=0, int xi=0, int yi=0): Ponto(xi, yi)
		{
		  x_final = xf;
		  y_final = yf;
		}

		void def_final(int xf, int yf)
		{
		  x_final = xf;
		  y_final = yf;
		}
		int vlr_x_final()
		{
		  return x_final;
		}
		int vlr_y_final()
		{
		  return y_final;
		}
		void imprime()
		{
		  cout << "\n RETA : ";
		  cout <<" [ " << x << "," << y <<" ] --- [ "
			   << x_final << "," << y_final <<" ]\n";
		}
	protected:
		int x_final, y_final;
};

void main()
{
  Ponto p1, p2(5,2);
  Reta r1, r2(8,4), r3(10, 6, -2, 1);

  cout << "\nCoordenadas do Ponto 1 :";
  p1.imprime();

  cout << "\nCoordenadas do Ponto 2 :";
  p2.imprime();

  p1.def_ponto(-3, 6);
  cout << "\nNovas coordenadas do Ponto 1 :";
  p1.imprime();

  cout <<"\n Coordenadas da Reta 1 : ";
  r1.imprime();
  cout <<"\n Coordenadas da Reta 2 : ";
  r2.imprime();
  cout <<"\n Coordenadas da Reta 3 : ";
  r3.imprime();

  r1.def_ponto(-2, -4);
  r1.def_final(7, 3);

  cout << "\n Novas coordenadas da Reta 1 :";
  r1.imprime();

}