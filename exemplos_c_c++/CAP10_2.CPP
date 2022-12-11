// cap10_2.cpp

#include "iostream.h"

class relogio {
		public:
			relogio();
			void ajusta_hora(int h, int m=0, int s=0);
			void mostra_hora();

			int hora;
			int minuto;
			int segundo;
	};

relogio::relogio()
{
  hora = 12;
  minuto = 0;
  segundo = 0;
}

void relogio::ajusta_hora(int h, int m, int s)
{
  if(h >= 0 && h < 24) hora = h;
  if(m >=0 && m < 60) minuto = m;
  if(s >=0 && s < 60) segundo = s;
}

void relogio::mostra_hora()
{
	cout << hora << " horas, "
		 << minuto << " minutos, "
		 << segundo << " segundos.\n";
}

void main()
{
  relogio r1;
  relogio * r_ptr; //ponteiro

  cout << "\nHora definida no Construtor :";
  r1.mostra_hora();

  r1.ajusta_hora(8, 45, 30);

  cout << "\nHora no r1 :";
  r1.mostra_hora();

  r_ptr = &r1; //o ponteiro recebe o endereco de r1
  r_ptr->ajusta_hora(15, 30);

  cout << "\nHora no r_ptr : ";
  r_ptr->mostra_hora();
  cout << "\nHora no r1    : ";
  r1.mostra_hora();

}