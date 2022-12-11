//banco.cpp
//Programa exemplo da parte III
//Autor : Marcos Romero

#include "iostream.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

//prototipos
void Criar_Conta();
void Acessar_Conta();

class Conta
{
 public:
  Conta(int num, char * _cliente)
  {
	 conta_num = num;
	 strcpy(cliente, _cliente);
	 saldo = 0.0;
	 contador++; //acompanha quantas contas estao abertas
  }
  int Conta_Num()
  {
   return conta_num;
  }
  float Saldo()
  {
   return saldo;
  }
  static int Quant_Contas()
  {
   return contador;
  }
  void Deposito(float valor)
  {
   if(valor > 0.0) saldo += valor;
  }

  virtual void Retirada(float valor) = 0;

  void Exibir()
  {
   cout << "\nConta : " << conta_num
		<< " --- "	<< cliente
		<< " --- Tipo : " << tipo;
  }
 protected:

  int conta_num;
  float saldo;
  char cliente[50];
  char tipo[20];

  static int contador;

};

//alocar variavel estatica
int Conta::contador = 0;

class Corrente : public Conta
{
 public:
  Corrente(int num, char * _cliente):Conta(num, _cliente)
  {
	strcpy(tipo, "Corrente");
  }
  // sobrecarregar funcao virtual pura
  virtual void Retirada(float valor)
  {
	if (saldo < valor)
	{
		cout << "\nInsuficiencia de fundos: saldo = " << saldo ;
	}
	else
	{
	  saldo -= valor;
	  // se saldo baixo, cobrar taxa de servico
	  if (saldo < 500.00)
	  {
	   saldo -= 0.20;
	  }
	}

  }

};

class Poupanca : public Conta
{
 public:
  Poupanca(int num, char * _cliente):Conta(num, _cliente)
  {
	strcpy(tipo, "Poupanca");
  }

  virtual void Retirada(float valor)
  {
	 if (saldo < valor)
	 {
	  cout << "Insuficiencia de fundos: saldo = " << saldo;
	 }
	 else
	 {
	  saldo -= valor;
	  saldo -= 5.00; //taxa de retirada da poupanca
	}
  }
};

const int MAX_CONTAS = 100;

Conta * conta_lista[MAX_CONTAS];


void main()
{
  int escolha;

  cout << "\n\n *** CONTROLE DE CONTAS EM UM BANCO *** \n";

  while(1)
  {
	cout << "\n\n M E N U \n"
		 << "\n 1. Criar nova conta"
		 << "\n 2. Acessar conta"
		 << "\n 3. Encerrar programa"
		 << "\n\n Escolha: ";
	cin >> escolha;

	switch(escolha)
	{
	  case 1:
			Criar_Conta();
			break;

	  case 2:
			Acessar_Conta();
			break;

	  case 3:
			//limpar memoria das contas
			int n_contas = Conta::Quant_Contas();
			for(int i=0; i < n_contas; i++)
			{
			  delete conta_lista[i];
			}

			exit(0);
			break;

	  default: cout <<"\n Opcao invalida\n ";
			 break;
	}/*fim switch*/
  } /*fim while*/

}

void Criar_Conta()
{
  int novo_num;
  char novo_cliente[50];
  float dep_inicial;
  int novo_tipo;

  cout << "\n Criando nova conta : \n";

  cout << "\n Digite o numero da nova conta: ";
  cin >> novo_num;

  cout << "\n Digite o nome do cliente: ";
  gets(novo_cliente);

  do {
  cout << "\n 1. Corrente"
	   << "\n 2. Poupanca"
	   << "\n Digite o tipo da nova conta: ";
  cin >> novo_tipo;
  } while (novo_tipo != 1 && novo_tipo !=2);

  cout << "\n Digite o valor do deposito inicial: ";
  cin >> dep_inicial;

  int posicao = Conta::Quant_Contas();

  if(novo_tipo == 1)
  {
	conta_lista[posicao] = new Corrente(novo_num, novo_cliente);
	conta_lista[posicao]->Deposito(dep_inicial);
  }
  else
  {
	conta_lista[posicao] = new Poupanca(novo_num, novo_cliente);
	conta_lista[posicao]->Deposito(dep_inicial);
  }
  cout << "\nConta criada : \n";
  conta_lista[posicao]->Exibir();

}

void Acessar_Conta()
{

	int n_contas = Conta::Quant_Contas();
	if(n_contas == 0)
	{
	  cout << "Nao existe contas";
	  return;
	}

	cout << "\n\nContas Existentes : ";
	for(int i=0; i < n_contas; i++)
	{
	  conta_lista[i]->Exibir();
	}

	int num, id=-1;
	do {
		cout << "\n Numero da conta : ";
		cin >> num;
		for(i=0; i < n_contas; i++)
		{
		  if(num == conta_lista[i]->Conta_Num())
		  {
			id = i;
			break;
		  }
		}
		if(id == -1) cout << "\nNumero invalido.";

	} while (id == -1);

   conta_lista[i]->Exibir();
   cout.precision(2);
   cout << "\n Saldo = " << conta_lista[i]->Saldo();

   cout << "\n\n Transacoes : ";
   float vlr;
   do {
	   cout << "\n\n Digite um valor positivo p/ deposito,\n"
			<< " negativo p/ retirada e 0 p/ sair.";
	   cout << "\n Valor : " ;
	   cin >> vlr;

	   if(vlr > 0.0) conta_lista[i]->Deposito(vlr);
	   else if(vlr < 0.0) conta_lista[i]->Retirada(-vlr);

	   cout <<"\n Saldo atual : " << conta_lista[i]->Saldo();

   } while(vlr != 0.0);

}


