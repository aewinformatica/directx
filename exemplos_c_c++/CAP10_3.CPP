// cap10_3.cpp

#include "iostream.h"

class empregado {
		friend void aumentar_salario(empregado & e, int valor);

		public:
			empregado()
			{
				salario = 100;
			}
			int vlr_salario()
			{
			   return salario;
			}
		protected:
			int salario;
};

void aumentar_salario(empregado & e, int valor)
{
  //o acesso a variavel salario e permitido aqui
  //por que esta funcao e friend da classe empregado

  e.salario += valor;
}

void main()
{
  empregado emp;

  //a linha seguinte iria gerar um erro :
  // emp.salario = 1500;

  cout << "\n Salario = " << emp.vlr_salario();
  aumentar_salario(emp, 200);
  cout << "\n Novo salario = " << emp.vlr_salario();

}

