// cap11_1.cpp

#include "iostream.h"
#include "string.h"

class Aluno {
	public :
		//construtor
		Aluno(char * p_nome = "Sem nome")
		{
		   strcpy(nome, p_nome);
		   n_alunos++;
		}
		//destruidor
		~Aluno()
		{
		  n_alunos--;
		}
		int num_alunos()
		{
		  return n_alunos;
		}
		char nome[40];
	protected:
		static int n_alunos;
};
//alocar memoria p/ membro static
int Aluno::n_alunos = 0;

void fn()
{
  Aluno a4("Diana");

  cout << "\n Aluna :" << a4.nome;
  cout << "\nNumero de alunos = " << a4.num_alunos();

}

void main()
{
  Aluno a1;
  Aluno a2("Marcos");

  cout << "\n Criado alunos : " << a1.nome << " e " << a2.nome;
  cout << "\n Numero de alunos = "<< a1.num_alunos();

  Aluno a3("Andre");

  cout << "\n Criado o " << a3.nome;
  cout << "\n Numero de alunos = "<< a1.num_alunos();

  fn();

  cout << "\n Numero de alunos = "<< a1.num_alunos();

}