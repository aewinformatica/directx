/*
ARQUIVO	: MRDX.CPP

AUTOR		: MARCOS ROMERO

E-MAIL	: MAROMERO@ZAZ.COM.BR

EMPRESA	: RH GAMES  -  WWW.GEOCITIES.COM/RHGAMES

DATA		: 26 DE ABRIL DE 2001

COMENTÁRIOS:

				O MRDX é uma biblioteca de funções criada para facilitar
				o aprendizado da programação de jogos. Ela foi criada
				baseada no livro "Tricks of the Windows Game Programming Gurus"
				de André LaMothe. Neste arquivo estão as definições das funções
				da biblioteca.

|\/\/\/|
|      |
|   0 0)
C     _)
 | ,__|				
 |   /

*/

#include "MRDX.H"		//protótipos de funções


//ESTRUTURAS /////////////////////////////////////////////

// arquivo BITMAP 
struct BITMAP_FILE
        {
        BITMAPFILEHEADER bitmapfileheader;  
        BITMAPINFOHEADER bitmapinfoheader;  
        PALETTEENTRY     palette[256];      
        unsigned char    *buffer;           
        };

// sons wave
struct pcm_sound
	{
	LPDIRECTSOUNDBUFFER dsbuffer;   
	int state;                      
	int rate;                       
	int size;                       
	int id;                         
	} ;

// MIDI 
struct MIDI
	{
	IDirectMusicSegment        *dm_segment;  
	IDirectMusicSegmentState   *dm_segstate; 
	int                        id;           
	int                        state;        
	} ;

//usado no carregador de midi
#define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP,MB_PRECOMPOSED, y,-1,x,_MAX_PATH);

// VARIÁVEIS /////////////////////////////////////////////

//Windows
HWND      id_janela_principal; // identificador da janela principal
HINSTANCE id_instancia_ap	 ; // identificador da instância da aplicação

//Direct Draw
LPDIRECTDRAW4        lpdd		= NULL;  // objeto DD
LPDIRECTDRAWSURFACE4 lpddspri	= NULL;  // superficie primaria
LPDIRECTDRAWSURFACE4 lpddssec	= NULL;  // superficie secundaria
LPDIRECTDRAWPALETTE  lpddpal    = NULL;  // palheta de cores do DD
LPDIRECTDRAWCLIPPER  lpddclipper= NULL;  // clipper
PALETTEENTRY         palheta[256];       // espaço para guardar uma palheta de cores
DDSURFACEDESC2       ddsd;                 // descrição de superfície
DDBLTFX              ddbltfx;              // usado no preenchimento
DDSCAPS2             ddscaps;              // capacidades da superficie

//Direct Input
LPDIRECTINPUT        lpdi				= NULL;       // objeto dinput 

LPDIRECTINPUTDEVICE  lpditec		= NULL;    // teclado
unsigned char				teclado_estado[256]; 

LPDIRECTINPUTDEVICE  lpdimouse = NULL;    // dinput mouse
DIMOUSESTATE				 mouse_estado;  

LPDIRECTINPUTDEVICE2 lpdijoy   = NULL;    // dinput joystick
GUID                 joystickGUID;        // guid para joystick
DIJOYSTATE					 joy_estado;
int									 joy_existe = 0;    // checa se joystick existe

//DirectSound
LPDIRECTSOUND		lpds = NULL;    // objeto dsound
DSBUFFERDESC		dsbd;           
DSCAPS				dscaps;         
HRESULT				dsresult;       
DSBCAPS				dsbcaps;        
LPDIRECTSOUNDBUFFER	lpdsbpri = NULL;   
pcm_sound			sons_wav[MAX_WAV];    

WAVEFORMATEX		pcmwf;          

//Direct Music - MIDI
IDirectMusicPerformance    *dm_perf = NULL;    
IDirectMusicLoader         *dm_loader = NULL;  

MIDI                dm_midi[MAX_MIDI];
int						 dm_id_ativo = -1;     

//outros
DWORD tempo_inicio;
BITMAP_FILE bitmap;

// FUNÇÕES //////////////////////////////////////////////

//Manipulador de Eventos que processa as mensagens
//recebidas pela sua aplicação
LRESULT CALLBACK WindowProc(HWND hwnd, 
														UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{

	PAINTSTRUCT		ps;		// usado em WM_PAINT
	HDC				hdc;	// identificador para um Contexto de Dispositivo


	// Qual é a mensagem 
	switch(msg)
	{	
	case WM_CREATE: 
     {
				// fazer inicializações aqui
        // retornar
				return(0);
		} break;
   
	case WM_PAINT: 
		{
		//isto é necessário porquê o Windows sempre manda a mensagem
		//quando há alguma alteração na janela de sua aplicação,
		//e solicita que a janela seja desenhada de novo.

		//No caso do jogo, isto ocorrerá sempre, mas a tela estará
		//sendo constantemente redesenhada, então deve-se informar ao
		// Windows que a janela já foi redesenhada. 

		// apenas validar a janela 
   	    hdc = BeginPaint(hwnd,&ps);	 
        
        // finalizar PAINT
        EndPaint(hwnd,&ps);

        // retornar
		return(0);
   		} break;

	case WM_DESTROY: 
		{

		// Acabar com a aplicação.Isto manda uma mensagem WM_QUIT 
		PostQuitMessage(0);

        // retornar
		return(0);
		} break;

	default:break;

    } // fim switch

	// processamento padrão de qualquer outra mensagem recebida 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // fim WinProc


//////////////////////////////////////////////////
// função principal do Windows. É o equivalente ao main() do C padrão.
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

	WNDCLASSEX winclasse; // guarda a classe que iremos criar para a nossa janela
	HWND	   hwnd;	 // identificador  para janela 
	MSG		   msg;		 // mensagem


	// Criar e preencher  as informações da classe window
	// a partir da qual será criada a nossa janela principal
	winclasse.cbSize         = sizeof(WNDCLASSEX);
	winclasse.style			= CS_OWNDC;                          
	winclasse.lpfnWndProc	= WindowProc; //nome do manipulador de eventos
	winclasse.cbClsExtra		= 0;
	winclasse.cbWndExtra		= 0;
	winclasse.hInstance		= hinstance;
	winclasse.hIcon			= LoadIcon(NULL, IDI_APPLICATION);//ícone padrão
	winclasse.hCursor		= LoadCursor(NULL, IDC_ARROW); //cursor padrão
	winclasse.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclasse.lpszMenuName	= NULL;
	winclasse.lpszClassName	= "WINCLASSE1";
	winclasse.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

	// salvar hinstance na variável global id_instancia_ap 
	id_instancia_ap = hinstance;

	// registrar a classe window 
	if (!RegisterClassEx(&winclasse))
		return(0);

	// criar a janela 
	if (!(hwnd = CreateWindowEx(NULL,                  // estilos estendidos
                            "WINCLASSE1",     // classe
						    "MRDX", // título
						    WS_POPUP | WS_VISIBLE,//estilo da janela
					 	    0,0,	  // x,y inicial
						    400,300,  // largura e altura iniciais
						    NULL,	  // identificador da janela Pai
						    NULL,	  // identificador do Menu
						    hinstance,// identificador da instância desta aplicação
						    NULL)))	// parâmetros extras de criação de janela
	return(0);

	// salvar o identificador da janela principal na variável global
	id_janela_principal = hwnd;

	//inicializar directX
	Directx_Iniciar();


	// entrar no laço principal de eventos
	while(TRUE)
	{
    // test if there is a message in queue, if so get it
	//testa se há uma mensagem na fila, se tiver então a retira
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	   { 
			// testa se é uma saída (WM_QUIT)
       if (msg.message == WM_QUIT)
           break;
	
			 // traduz teclas aceleradoras
			TranslateMessage(&msg);

			// manda a mensagem para o manipulador de evento (WindowProc)
			DispatchMessage(&msg);
	   } // fim if

		//atualizar dispositivos de entrada
		Atualizar_Teclado();
		Atualizar_Mouse();
		Atualizar_Joystick();

    //Processamento principal do jogo
		Jogo_Main();
       
	} // fim while


	//Encerrar DirectX
	Directx_Encerrar();

	// retornar para o Windows
	return(msg.wParam);

} // fim WinMain

//////////////////////////////////////////////

int Directx_Iniciar(void)
{
	// Esta função inicializa os componentes do directX:
	// DirectDraw, DirectInput, DirectSound, DirectMusic

	// Iniciar Direct Draw /////

	// esconder mouse
	ShowCursor(FALSE);

	// iniciar o gerador de números aleatórios
	srand(GetTickCount());

	LPDIRECTDRAW lpdd_temp = NULL; // usado para pegar directdraw1

	// criar IDirectDraw interface 1.0 
	if (FAILED(DirectDrawCreate(NULL,&lpdd_temp,NULL)))
		return(0);

	// requisitar por IDirectDraw4, a última versão
	if (FAILED(lpdd_temp->QueryInterface(IID_IDirectDraw4,
                               (LPVOID *)&lpdd)))
		return(0);

	// especificar modo de cooperação com o Windows
	if (FAILED(lpdd->SetCooperativeLevel(id_janela_principal,
           DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
		return(0);

	// especificar modo de video
	if (FAILED(lpdd->SetDisplayMode(640,480,8,0,0)))
		return(0);

	// Superfície primária
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;

	//indica que é uma formação complexa que contém superfícies 
	// primária e secundária
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

	//existe apenas uma superfície secundária
	ddsd.dwBackBufferCount = 1;

	// criar a Superfície primária
	lpdd->CreateSurface(&ddsd,&lpddspri,NULL);

	// superfície secundária
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	if (FAILED(lpddspri->GetAttachedSurface(&ddscaps,&lpddssec)))
		return(0);


	// criar palheta de cores

	// limpar palheta
	memset(palheta,0,256*sizeof(PALETTEENTRY));
	
	for (int i=0; i < 256; i++)
    {
		// não permitir que o Windows altere a palheta
		palheta[i].peFlags = PC_NOCOLLAPSE;
    } // fim for 

	Cores_Basicas();
	
	// criar o objeto palheta
	if (FAILED(lpdd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE | DDPCAPS_ALLOW256,
                               palheta,&lpddpal,NULL)))
		return(0);

	// anexar a palheta na superfície primária
	if (FAILED(lpddspri->SetPalette(lpddpal)))
		return(0);
	

	//limpar superfícies 
	Limpar_Tela();
	Mostrar_Tela();
	Limpar_Tela();

	//criar o clipper que corta as partes da imagem
	//que estiver fora da tela
	Anexar_Clipper();

	//DIRECT INPUT
	if (FAILED(DirectInputCreate(id_instancia_ap,DIRECTINPUT_VERSION,&lpdi,NULL)))
   return(0);

	// criar o teclado
	if (FAILED(lpdi->CreateDevice(GUID_SysKeyboard, &lpditec, NULL)))
   return(0);

	// Modo de cooperação
	if (FAILED(lpditec->SetCooperativeLevel(id_janela_principal, 
                 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
    return(0);

	// formato dos dados
	if (FAILED(lpditec->SetDataFormat(&c_dfDIKeyboard)))
   return(0);

	// adquirir o teclado
	if (FAILED(lpditec->Acquire()))
   return(0);

	//criar mouse
	if (FAILED(lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL)))
		 return(0);

	// Modo de cooperação
	if (FAILED(lpdimouse->SetCooperativeLevel(id_janela_principal, 
                       DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		 return(0);

	// formato dos dados
	if (FAILED(lpdimouse->SetDataFormat(&c_dfDIMouse)))
		 return(0);

	// adquirir o mouse
	if (FAILED(lpdimouse->Acquire()))
		 return(0);

	Inicia_Joystick();

	//iniciar DirectSound

	memset(sons_wav,0,sizeof(pcm_sound)*MAX_WAV);
		
	// criar objeto dsound
	if (FAILED(DirectSoundCreate(NULL, &lpds, NULL)))
		return(0);

	// modo de cooperação
	if (FAILED(lpds->SetCooperativeLevel((HWND)id_janela_principal,DSSCL_NORMAL)))
		return(0);

	// inicia matriz de sons
	for (i=0; i<MAX_WAV; i++)
	{
		sons_wav[i].state = 0;
		sons_wav[i].id    = i;

	} 

	//MIDI - DirectMusic

	// inicia COM
	if (FAILED(CoInitialize(NULL)))
   {    
   return(0);
   }   

	// criar a perfomance
	if (FAILED(CoCreateInstance(CLSID_DirectMusicPerformance,
                            NULL,
                            CLSCTX_INPROC,
                            IID_IDirectMusicPerformance,
                            (void**)&dm_perf)))    
   {
   return(0);
   }

	//inicia a performance
	if (FAILED(dm_perf->Init(NULL, lpds, id_janela_principal)))
   {
   return(0);
   }  

	if (FAILED(dm_perf->AddPort(NULL)))
   {    
   return(0);
   } 

	// criar o loader
	if (FAILED(CoCreateInstance(
          CLSID_DirectMusicLoader,
          NULL,
          CLSCTX_INPROC, 
          IID_IDirectMusicLoader,
          (void**)&dm_loader)))
   {
   return(0);
   } 

	//iniciar dados	
	for (i = 0; i < MAX_MIDI; i++)
    {
    dm_midi[i].dm_segment  = NULL;  
    dm_midi[i].dm_segstate = NULL;  
    dm_midi[i].state       = 0;
    dm_midi[i].id          = i;
    } 

	dm_id_ativo = -1;

	//retornar com sucesso
	return(1);

} //fim Directx_Iniciar()

//////////////////////////////////////////////

int Directx_Encerrar(void)
{
	//liberar memória

	int i;

	//Dmusic
	if (dm_perf)
   dm_perf->Stop(NULL, NULL, 0, 0 ); 

	// apagar todos os midis
	for (i = 0; i < MAX_MIDI; i++)
    {
    
    if (dm_midi[i].dm_segment)
       {
       dm_midi[i].dm_segment->SetParam(GUID_Unload, -1, 0, 0, (void*)dm_perf); 

       dm_midi[i].dm_segment->Release(); 
       dm_midi[i].dm_segment  = NULL;
       dm_midi[i].dm_segstate = NULL;
       dm_midi[i].state       = 0;
       } 
    } 

	if (dm_perf)
   {
   dm_perf->CloseDown();
   dm_perf->Release();     
   } 

	
	if (dm_loader)
   dm_loader->Release();     
	
	CoUninitialize(); 

	//dsound
	
	Parar_Todos_Wav();

	for (i=0; i<MAX_WAV; i++)
		if (sons_wav[i].dsbuffer)
			sons_wav[i].dsbuffer->Release();

	// liberar objeto dsound 
	lpds->Release();

	//joystick
	if (lpdijoy)
    {    
    lpdijoy->Unacquire();
    lpdijoy->Release();
    } 

	//mouse
	if (lpdimouse)
    {    
    lpdimouse->Unacquire();
    lpdimouse->Release();
    }

	//teclado
	if (lpditec)
    {
    lpditec->Unacquire();
    lpditec->Release();
    } 

	//direct input
	if (lpdi)
   lpdi->Release();

	//bitmap
	if (bitmap.buffer)
   {
   free(bitmap.buffer);
   bitmap.buffer = NULL;
   }

	// clipper
	if (lpddclipper)
		lpddclipper->Release();

	// palheta
	if (lpddpal)
		lpddpal->Release();

	// superficie secundária
	if (lpddssec)
		lpddssec->Release();

	// superfície primária
	if (lpddspri)
		lpddspri->Release();

	//objeto DD principal
	if (lpdd)
		lpdd->Release();

	// mostrar mouse
	ShowCursor(TRUE);

	//retornar com sucesso
	return(1);
}

//////////////////////////////////////////////

int Mostrar_Tela(void)
{

	//esta função troca a superfície primária com a secundária

	//espera canhão de elétrons chegar na base da tela
	lpdd->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN,0);

	// troca
	while(FAILED(lpddspri->Flip(NULL, DDFLIP_WAIT)));


	// retornar
	return(1);

} // fim Troca_Superf(void)

///////////////////////////////////////////////////////////   

int Limpar_Tela(int cor)
{
	//preenche a tela com uma cor especificada

	//estrutura para o blitter
	DDBLTFX ddbltfx; 

	// limpar a estrutura 
	memset(&ddbltfx,0,sizeof(ddbltfx)); 

	//informar o tamanho
	ddbltfx.dwSize=sizeof(ddbltfx); 

	// definir cor de preenchimento
	ddbltfx.dwFillColor = cor; 

	// preencher superfície secundária
	lpddssec->Blt(	NULL,       
					NULL,       
					NULL,       
					DDBLT_COLORFILL | DDBLT_WAIT,   
					&ddbltfx);  

	// retornar 
	return(1);

} // fim Limpar_Tela()

//////////////////////////////////////////////

int Iniciar_Relogio(void)
{
	//função usada em conjunto com Esperar_Relogio()
	tempo_inicio = GetTickCount();

	return(1);

}
//////////////////////////////////////////////

int Esperar_Relogio(unsigned int tempo_espera)
{
	//permanece no laço até atingir tempo_espera desde
	//a última chamada de Iniciar_Relogio()

	while((GetTickCount() - tempo_inicio) < tempo_espera);

	return(1);

}
//////////////////////////////////////////////
int	Desenhar_Retangulo(int x1, int y1, int x2, int y2, int cor)
{
	// desenha um retangulo cheio

	DDBLTFX ddbltfx; // info para o blitter
	RECT area;  // estrutura de retangulo

	// limpar a estrutura 
	memset(&ddbltfx,0,sizeof(ddbltfx)); 

	//informar o tamanho
	ddbltfx.dwSize=sizeof(ddbltfx); 

	// definir cor
	ddbltfx.dwFillColor = cor; 

	// area do retangulo
	area.top    = y1;
	area.left   = x1;
	area.bottom = y2+1;
	area.right  = x2+1;

	// desenha
	lpddssec->Blt(	&area, 
					NULL,  
					NULL,  
					DDBLT_COLORFILL | DDBLT_WAIT,   
					&ddbltfx);  

	
	return(1);

} // fim Desenha_Retangulo()

//////////////////////////////////////////////

int Anexar_Clipper(void)
{
	//retangulo  correspondente a tela
	RECT tela = {0,0,640,480};

	// esta função cria um clipper para a tela

	//ponteiro para dados da regiao do clipper
	LPRGNDATA dados_regiao;             

	// criar o clipper
	if (FAILED(lpdd->CreateClipper(0,&lpddclipper,NULL)))
		 return(NULL);


	// alocar memória para dados da regiao
	dados_regiao = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+ sizeof(RECT));

	//copiar retangulo para os dados da regiao
	memcpy(dados_regiao->Buffer, &tela, sizeof(RECT));

	// definir campos do cabeçalho da regiao
	dados_regiao->rdh.dwSize          = sizeof(RGNDATAHEADER);
	dados_regiao->rdh.iType           = RDH_RECTANGLES;
	dados_regiao->rdh.nCount          = 1;
	dados_regiao->rdh.nRgnSize        = sizeof(RECT);

	dados_regiao->rdh.rcBound.left    =  0;
	dados_regiao->rdh.rcBound.top     =  0;
	dados_regiao->rdh.rcBound.right   = 640;
	dados_regiao->rdh.rcBound.bottom  = 480;


	//definir a lista do clipper
	if (FAILED(lpddclipper->SetClipList(dados_regiao, 0)))
   {
		 // liberar memória e retornar erro
		free(dados_regiao);
		return(0);
   } // fim if

	// anexar clipper à superfície
	if (FAILED(lpddssec->SetClipper(lpddclipper)))
	{
			// liberar memória e retornar erro
		free(dados_regiao);
		return(0);
	} // fim if

	// tudo ocorreu bem. liberar memória e retornar OK
	free(dados_regiao);
	return(1);

} // fim Anexar_Clipper

//////////////////////////////////////////////

int Carregar_Bitmap(char *nome_arq)
{
	//esta função carrega um arquivo bitmap

	int id_arq,  // identificador de arquivo
		  i;        // variável de laço

	OFSTRUCT dados_arq;          // dados do arquivo

	// abre o arquivo se existir
	if ((id_arq = OpenFile(nome_arq,&dados_arq,OF_READ))==-1)
		 return(0);

	//carregar o cabeçalho do arquivo
	_lread(id_arq, &bitmap.bitmapfileheader,sizeof(BITMAPFILEHEADER));

	// testar se é um arquivo bitmap
	if (bitmap.bitmapfileheader.bfType!=0x4D42)
   {
			// fechar arquivo
			_lclose(id_arq);

			// retornar erro
			return(0);
   } // fim if


	//ler infoheader
	_lread(id_arq, &bitmap.bitmapinfoheader,sizeof(BITMAPINFOHEADER));

	// ler palheta
	if (bitmap.bitmapinfoheader.biBitCount == 8)
  {
		 _lread(id_arq, &bitmap.palette,256*sizeof(PALETTEENTRY));

   //endireitar o formato
   for (i=0; i < 256; i++)
   {
		   //inverter os campos vermelho e azul
       int temp_cor              = bitmap.palette[i].peRed;
       bitmap.palette[i].peRed  = bitmap.palette[i].peBlue;
       bitmap.palette[i].peBlue = temp_cor;
       
       // não deixar o windos mexer na palheta
       bitmap.palette[i].peFlags = PC_NOCOLLAPSE;
   } // fim for i

    } // end if

		//copiar palheta do bitmap para o sistema
		memcpy(palheta, bitmap.palette,256*sizeof(PALETTEENTRY));

		//preservar cores básicas do sistema
		Cores_Basicas();

	//definir palheta do sistema
	if(FAILED(lpddpal->SetEntries(0,0,256,palheta)));


	//dados da imagem
	_lseek(id_arq,-(int)(bitmap.bitmapinfoheader.biSizeImage),SEEK_END);

	// ler imagem se for 8bit
	if (bitmap.bitmapinfoheader.biBitCount==8) 
   {
			// apagar a imagem anterior
			if (bitmap.buffer)
				 free(bitmap.buffer);

			//alocar a memória para a imagem
			if (!(bitmap.buffer = (unsigned char *)malloc(bitmap.bitmapinfoheader.biSizeImage)))
      {
				
				//fechar arquivo
				_lclose(id_arq);

				// retornar erro
				return(0);
      } // fim if

			
			//ler os dados
			_lread(id_arq,bitmap.buffer,bitmap.bitmapinfoheader.biSizeImage);

   } // fim if
	 else
   {
			// problema
			return(0);
   } // fim else

	// fechar arquivo
	_lclose(id_arq);

	// inverter o bitmap
	Inverter_Bitmap(bitmap.buffer, 
								bitmap.bitmapinfoheader.biWidth, 
								bitmap.bitmapinfoheader.biHeight);

	// retornar sucesso
	return(1);

} // fim Carregar_Bitmap()

//////////////////////////////////////////////
int Inverter_Bitmap(unsigned char *dados, int largura, int altura)
{
	//função utilizada no Carregar_Bitmap()

	unsigned char *buffer; 

	//buffer temporário
	if (!(buffer = (unsigned char *)malloc(largura*altura)))
   return(0);

	// copiar imagem
	memcpy(buffer,dados,largura*altura);

	// inverter verticalmente
	for (int i=0; i < altura; i++)
    memcpy(&dados[((altura-1) - i)*largura],
           &buffer[i*largura], largura);

	//liberar memória
	free(buffer);

	// retornar sucesso
	return(1);

} // fim Inverter_Bitmap()


//////////////////////////////////////////////
int Cores_Basicas(void)
{
	
	//definir cores básicas da biblioteca
	palheta[PRETO].peRed			= 0;
	palheta[PRETO].peGreen		= 0;
	palheta[PRETO].peBlue		= 0;

	palheta[BRANCO].peRed			= 240;
	palheta[BRANCO].peGreen		= 240;
	palheta[BRANCO].peBlue		= 240;

	palheta[VERDE].peRed		= 20;
	palheta[VERDE].peGreen	= 200;
	palheta[VERDE].peBlue		= 20;

	palheta[AZUL].peRed			= 20;
	palheta[AZUL].peGreen		= 20;
	palheta[AZUL].peBlue		= 200;

	palheta[VERMELHO].peRed		= 200;
	palheta[VERMELHO].peGreen	= 20;
	palheta[VERMELHO].peBlue	= 20;

	palheta[AMARELO].peRed		= 240;
	palheta[AMARELO].peGreen	= 240;
	palheta[AMARELO].peBlue	= 20;

	palheta[CINZA].peRed			= 100;
	palheta[CINZA].peGreen		= 100;
	palheta[CINZA].peBlue		= 100;

	palheta[ROXO].peRed			= 150;
	palheta[ROXO].peGreen		= 20;
	palheta[ROXO].peBlue		= 150;
	

	return(1);
}
//////////////////////////////////////////////
int Testar_Tecla(int dik_cod)
{
		return(teclado_estado[dik_cod] & 0x80);
}
//////////////////////////////////////////////
int Escreve_Texto(char *texto, int x, int y, int cor)
{

	HDC xdc; // contexto de dispositivo

	// pegar contexto da superfície
	if (FAILED(lpddssec->GetDC(&xdc)))
		 return(0);

	//escolher fonte padrão
	SelectObject(xdc, GetStockObject(ANSI_FIXED_FONT));

	//definir cor do texto
	SetTextColor(xdc,RGB(palheta[cor].peRed,palheta[cor].peGreen,palheta[cor].peBlue) );
	

	// modo do background
	SetBkMode(xdc, TRANSPARENT);

	// desenha o texto
	TextOut(xdc,x,y,texto,strlen(texto));

	// libera o dispositivo
	lpddssec->ReleaseDC(xdc);

	// retornar OK
	return(1);

} // fim Escreve_Texto()

//////////////////////////////////////////////
int Criar_Imagem(IMAGEM &imagem,int largura, int altura, int num_quadros)

{
	int i; //indice

	//cria o objeto IMAGEM e todas as suas superfícies

	DDSURFACEDESC2 ddsd; // descrição de superfície

	//definir atributos
	imagem.x = 0;
	imagem.y = 0;
	imagem.largura = largura;
	imagem.altura = altura;
	imagem.num_quadros = num_quadros;
	imagem.quadro_atual = 0;
	imagem.estado = ATIVO;

	for (i=0; i<MAX_DADOS; i++)
    imagem.dados[i] = 0;


	// iniciar todas imagens em NULL
	for (i=0; i<MAX_QUADROS; i++)
    imagem.quadros[i] = NULL;


	// criar cada superfície
	for (i=0; i < imagem.num_quadros; i++)
    {
    
    memset(&ddsd,0,sizeof(ddsd));
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

    ddsd.dwWidth  = imagem.largura;
    ddsd.dwHeight = imagem.altura;

    // fora da tela
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

    // criar a superfície
    if (FAILED(lpdd->CreateSurface(&ddsd,&(imagem.quadros[i]),NULL)))
        return(0);

    // transparência para cor 0
    DDCOLORKEY color_key; 
    color_key.dwColorSpaceLowValue  = 0;
    color_key.dwColorSpaceHighValue = 0;

    (imagem.quadros[i])->SetColorKey(DDCKEY_SRCBLT, &color_key);
    
    } //fim for


		return(1);

} // fim criar imagem


//////////////////////////////////////////////
int Destruir_Imagem(IMAGEM &imagem)
{
	//liberar toda a memória alocada para a IMAGEM
 
		//destruir cada superfície
    for (int i=0; i<imagem.num_quadros; i++)
            (imagem.quadros[i])->Release();   

	  return(1);

} // fim Destruir_Imagem()

//////////////////////////////////////////////

int Desenhar_Imagem(IMAGEM &imagem)
{

	RECT ret_dest,   //retangulo destino
		   ret_font; //retangulo fonte


		// preencher retangulo destino
	ret_dest.left   = imagem.x;
	ret_dest.top    = imagem.y;
	ret_dest.right  = imagem.x + imagem.largura;
	ret_dest.bottom = imagem.y + imagem.altura;

	// preencher retangulo fonte
	ret_font.left    = 0;
	ret_font.top     = 0;
	ret_font.right   = imagem.largura;
	ret_font.bottom  = imagem.altura;

	
	//desenhar 
	 if (FAILED(lpddssec->Blt(&ret_dest, imagem.quadros[imagem.quadro_atual],
          &ret_font,(DDBLT_WAIT | DDBLT_KEYSRC),
          NULL)))
    return(0);

	
	return(1);

} // fim Desenhar_Imagem()

//////////////////////////////////////////////

int Carregar_Quadro(IMAGEM &imagem, int quadro, int cx, int cy)
{
	// extrai um quadro de um bitmap

	unsigned char *ptr_font,   
							*ptr_dest;

	DDSURFACEDESC2 ddsd;  

   //converte coordenadas
   cx = cx* imagem.largura;
   cy = cy* imagem.altura;
   

	// extrair dados do bitmap
	ptr_font = bitmap.buffer + cy*bitmap.bitmapinfoheader.biWidth+cx;
	
	ddsd.dwSize = sizeof(ddsd);

	
	(imagem.quadros[quadro])->Lock(NULL,
                           &ddsd,
                           DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
                           NULL);

	
	ptr_dest = (unsigned char *)ddsd.lpSurface;

	// copiar bitmap
	for (int ind_y=0; ind_y< imagem.altura; ind_y++)
    {
    
    memcpy(ptr_dest, ptr_font,imagem.largura);

    
    ptr_dest   += imagem.largura;
    ptr_font += bitmap.bitmapinfoheader.biWidth;

    } 

	
	(imagem.quadros[quadro])->Unlock(NULL);

	return(1);

} // fim Carregar_Quadro

//////////////////////////////////////////////

int Colisao_Imagens(IMAGEM &imagem1, IMAGEM &imagem2)
{
	
	// pegar o raio de cada retangulo
	int largura1  = (imagem1.largura>>1) - (imagem1.largura>>3);
	int altura1 = (imagem1.altura>>1) - (imagem1.altura>>3);

	int largura2  = (imagem2.largura>>1) - (imagem2.largura>>3);
	int altura2 = (imagem2.altura>>1) - (imagem2.altura>>3);

	// achar centro de cada retangulo
	int cx1 = imagem1.x + largura1;
	int cy1 = imagem1.y + altura1;

	int cx2 = imagem2.x + largura2;
	int cy2 = imagem2.y + altura2;

	// achar deltas
	int dx = abs(cx2 - cx1);
	int dy = abs(cy2 - cy1);

	// testar colisão
	if (dx < (largura1+largura2) && dy < (altura1+altura2))
		 return(1);
	else
	// else sem colisão
	return(0);

} // fim Colisao_Imagens()

//////////////////////////////////////////////

int Finalizar_Jogo(void)
{
	//envia mensagem para o Windows solicitando
	//o fim da aplicação
	SendMessage(id_janela_principal,WM_DESTROY,0,0);
	return(1);
}

//////////////////////////////////////////////
int Aleatorio(int min, int max)
{
	//retorna um número entre min e max inclusivo
	return(min + (rand()%(max-min+1)));
}
//////////////////////////////////////////////

int Atualizar_Teclado(void)
{	

	if (lpditec)
    {
    if (FAILED(lpditec->GetDeviceState(256, (LPVOID)teclado_estado)))
       return(0);
    }
	else
    {
    // problema. zerar estados
    memset(teclado_estado,0,sizeof(teclado_estado));

    // retornar erro
    return(0);
    } 

	// retornar sucesso
	return(1);

} // fim Atualizar_Teclado

//////////////////////////////////////////////
int Atualizar_Mouse(void)
{

	if (lpdimouse)    
    {
    if (FAILED(lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_estado)))
			    return(0);
    }
	else
    {
    // problema. zerar dados
    memset(&mouse_estado,0,sizeof(mouse_estado));

    // retornar erro
    return(0);
    } 

	// retornar OK
	return(1);

} // fim Atualizar_Mouse

//////////////////////////////////////////////
int	Mouse_Xvar(void)
{
	//retorna a variação da posição do mouse no eixo X

	return(mouse_estado.lX);
}
//////////////////////////////////////////////
int	Mouse_Yvar(void)
{
	//retorna a variação da posição do mouse no eixo Y

	return(mouse_estado.lY);
}
//////////////////////////////////////////////
int Mouse_Bot_Esquerdo(void)
{
	//retorna se botão esquerdo foi pressionado
	return(mouse_estado.rgbButtons[0] & 0x80);
}
//////////////////////////////////////////////
int Mouse_Bot_Direito(void)
{
	//retorna se botão direito foi pressionado
	return(mouse_estado.rgbButtons[1] & 0x80);
}

//////////////////////////////////////////////
BOOL CALLBACK Enum_Joystick(LPCDIDEVICEINSTANCE lpddi,
								LPVOID guid_ptr) 
{
	//pega info do joytick encontrado
	*(GUID*)guid_ptr = lpddi->guidInstance; 

	// para enumeração depois de encontrar o primeiro
	return(DIENUM_STOP);

} // fim Enum_Joystick()

//////////////////////////////////////////////
int Inicia_Joystick(void)
{

	// pegar GUID
	lpdi->EnumDevices(DIDEVTYPE_JOYSTICK, 
								    Enum_Joystick, 
									  &joystickGUID, 
										DIEDFL_ATTACHEDONLY); 

	// interface temporária, para pegar versão atual
	LPDIRECTINPUTDEVICE lpdijoy_temp = NULL;

	if (FAILED(lpdi->CreateDevice(joystickGUID, &lpdijoy_temp, NULL)))
		 return(0);

	lpdijoy_temp->QueryInterface(IID_IDirectInputDevice2, 
                            (void **) &lpdijoy); 

	// Liberar versão antiga
	lpdijoy_temp->Release();

	// modo de cooperação
	if (FAILED(lpdijoy->SetCooperativeLevel(id_janela_principal, 
	                 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
   return(0);

	// formato dos dados
	if (FAILED(lpdijoy->SetDataFormat(&c_dfDIJoystick)))
		 return(0);

	// área do joystick
	DIPROPRANGE joy_eixo_area;

	// eixo X
	joy_eixo_area.lMin = -10;
	joy_eixo_area.lMax = 10;

	joy_eixo_area.diph.dwSize       = sizeof(DIPROPRANGE); 
	joy_eixo_area.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	joy_eixo_area.diph.dwObj        = DIJOFS_X;
	joy_eixo_area.diph.dwHow        = DIPH_BYOFFSET;

	lpdijoy->SetProperty(DIPROP_RANGE,&joy_eixo_area.diph);

	// eixo Y
	joy_eixo_area.lMin = -10;
	joy_eixo_area.lMax = 10;

	joy_eixo_area.diph.dwSize       = sizeof(DIPROPRANGE); 
	joy_eixo_area.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	joy_eixo_area.diph.dwObj        = DIJOFS_Y;
	joy_eixo_area.diph.dwHow        = DIPH_BYOFFSET;

	lpdijoy->SetProperty(DIPROP_RANGE,&joy_eixo_area.diph);

	// adquirir o  joystick
	if (FAILED(lpdijoy->Acquire()))
		 return(0);

	// joystick existe
	joy_existe = 1;

	// retornar OK
	return(1);

} // fim Inicia_Joystick()

//////////////////////////////////////////////
int Atualizar_Joystick(void)
{

	// testa se existe 
	if (!joy_existe)
		 return(0);

	if (lpdijoy)
    {
    
    if (FAILED(lpdijoy->Poll()))
        return(0);

    if (FAILED(lpdijoy->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&joy_estado)))
        return(0);
    }
	else
    {
    // problema. zera estados
    memset(&joy_estado,0,sizeof(joy_estado));

    // retornar erro
    return(0);
    } 

	// retornar OK
	return(1);

} // fim Atualizar_Joystick
//////////////////////////////////////////////
int Joy_Existe(void)
{
	//retornar verdadeiro se existir um joystick
	return(joy_existe);
}
//////////////////////////////////////////////
int Joy_Cima(void)
{
		// testa se existe 
	if (!joy_existe)
		 return(0);

	if(joy_estado.lY  < -3) return(1);
	else return(0);

}
//////////////////////////////////////////////
int Joy_Baixo(void)
{
		// testa se existe 
	if (!joy_existe)
		 return(0);

	if(joy_estado.lY  > 3) return(1);
	else return(0);

}

//////////////////////////////////////////////
int Joy_Esquerda(void)
{
		// testa se existe 
	if (!joy_existe)
		 return(0);

	if(joy_estado.lX  < -3) return(1);
	else return(0);

}

//////////////////////////////////////////////
int Joy_Direita(void)
{
		// testa se existe 
	if (!joy_existe)
		 return(0);

	if(joy_estado.lX  > 3) return(1);
	else return(0);

}

//////////////////////////////////////////////
int Joy_Bot(int bot)
{
	// testa se existe 
	if (!joy_existe)
		 return(0);

	if((bot<0) || (bot>=32))
		return(0);

	return(joy_estado.rgbButtons[bot] & 0x80);

}
//////////////////////////////////////////////
int Carregar_Wav(char *nome_arq)
{
	//carrega um arquivo wav e retorna um id do som
	//retorna -1 se ocorrer erro

	HMMIO 			hwav;    
	MMCKINFO		parent,  
                child;   
	WAVEFORMATEX    wfmtx;   

	int	som_id = -1,       // id do som a ser carregado
			i;               

	UCHAR *snd_buffer,      
		    *audio_ptr_1=NULL,
			  *audio_ptr_2=NULL; 

	DWORD audio_length_1=0,  
		  audio_length_2=0;  
			
	// procurar por som livre
	for (i=0; i < MAX_WAV; i++)
	{	
    
	if (sons_wav[i].state==0)
	   {
	   som_id = i;
	   break;
	   } 
	} 

	// testar se encontrou
	if (som_id==-1)
		return(-1);

	
	parent.ckid 	    = (FOURCC)0;
	parent.cksize 	    = 0;
	parent.fccType	    = (FOURCC)0;
	parent.dwDataOffset = 0;
	parent.dwFlags		= 0;

	
	child = parent;

	// abrir arquivo wav
	if ((hwav = mmioOpen(nome_arq, NULL, MMIO_READ | MMIO_ALLOCBUF))==NULL)
    return(-1);


	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	if (mmioDescend(hwav, &parent, NULL, MMIO_FINDRIFF))
    {
    // fechar arquivo
    mmioClose(hwav, 0);

    // retornar erro
    return(-1); 	
    } 

	
	child.ckid = mmioFOURCC('f', 'm', 't', ' ');

	if (mmioDescend(hwav, &child, &parent, 0))
    {
      // fechar arquivo
    mmioClose(hwav, 0);

    // retornar erro
    return(-1); 	
    } 

	// info do wav
	if (mmioRead(hwav, (char *)&wfmtx, sizeof(wfmtx)) != sizeof(wfmtx))
    {
    // fechar arquivo
    mmioClose(hwav, 0);

    // retornar erro
    return(-1); 
    } 

	// testar se é formato PCM
	if (wfmtx.wFormatTag != WAVE_FORMAT_PCM)
    {
    
    mmioClose(hwav, 0);
    
    return(-1); 
    } 

	
	if (mmioAscend(hwav, &child, 0))
   {  
   mmioClose(hwav, 0);

   return(-1); 	
   } // end if

	
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (mmioDescend(hwav, &child, &parent, MMIO_FINDCHUNK))
    {
  
    mmioClose(hwav, 0);

    return(-1); 	
    } 

	
	// copiar dados para o dsound buffer

	// alocar memória
	snd_buffer = (unsigned char*)malloc(child.cksize);

	 
	mmioRead(hwav, (char *)snd_buffer, child.cksize);

	
	mmioClose(hwav, 0);

	
	sons_wav[som_id].rate  = wfmtx.nSamplesPerSec;
	sons_wav[som_id].size  = child.cksize;
	sons_wav[som_id].state = 1;

	
	memset(&pcmwf, 0, sizeof(WAVEFORMATEX));

	pcmwf.wFormatTag	  = WAVE_FORMAT_PCM;  
	pcmwf.nChannels		  = 1;                
	pcmwf.nSamplesPerSec  = 11025;          
	pcmwf.nBlockAlign	  = 1;                
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample  = 8;
	pcmwf.cbSize		  = 0;


	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	dsbd.dwBufferBytes	= child.cksize;
	dsbd.lpwfxFormat	= &pcmwf;

	
	if (FAILED(lpds->CreateSoundBuffer(&dsbd,&sons_wav[som_id].dsbuffer,NULL)))
   {
  
   free(snd_buffer);

   return(-1);
   } 

	
	if (FAILED(sons_wav[som_id].dsbuffer->Lock(0,					 
								      child.cksize,			
								      (void **) &audio_ptr_1, 
								      &audio_length_1,
								      (void **)&audio_ptr_2, 
								      &audio_length_2,
								      DSBLOCK_FROMWRITECURSOR)))
								 return(0);

	
	memcpy(audio_ptr_1, snd_buffer, audio_length_1);

	memcpy(audio_ptr_2, (snd_buffer+audio_length_1),audio_length_2);

	
	if (FAILED(sons_wav[som_id].dsbuffer->Unlock(audio_ptr_1, 
									    audio_length_1, 
									    audio_ptr_2, 
									    audio_length_2)))
 							     return(0);

	
	free(snd_buffer);

	// retornar id
	return(som_id);

} // fim Carregar_Wav

//////////////////////////////////////////////
int Tocar_Wav(int id,int modo)
{
// Toca o som wav.  modo pode ser REPETIR 

	if (sons_wav[id].dsbuffer)
	{
	
		if (FAILED(sons_wav[id].dsbuffer->SetCurrentPosition(0)))
			return(0);
	
	
		if(modo == REPETIR)
		{
			if (FAILED(sons_wav[id].dsbuffer->Play(0,0,DSBPLAY_LOOPING)))
				return(0);
		}
		else
		{
			if (FAILED(sons_wav[id].dsbuffer->Play(0,0,0)))
				return(0);
		}
	} 


return(1);

} // fim Tocar_Wav

//////////////////////////////////////////////
int Parar_Wav(int id)
{
	
	if (sons_wav[id].dsbuffer)
   {
   sons_wav[id].dsbuffer->Stop();
   sons_wav[id].dsbuffer->SetCurrentPosition(0);
   } 

	
	return(1);

} // fim Parar_Wav

//////////////////////////////////////////////
int Parar_Todos_Wav(void)
{
	for (int i=0; i<MAX_WAV; i++)
		Parar_Wav(i);	

	return(1);

} // fim Parar_Todos_Wav();

//////////////////////////////////////////////
int Wav_Tocando(int id)
{
	// retornar 1 se o wav estiver tocando
	if (sons_wav[id].dsbuffer)
	{
		unsigned long status; 
	
		sons_wav[id].dsbuffer->GetStatus(&status);

		if (status & (DSBSTATUS_LOOPING | DSBSTATUS_PLAYING))
		{
			return(1);
		}
		else
		{
			return(0);
		}
	} // end if
	else 
		return(0);

} // end DSound_Status_Sound

//////////////////////////////////////////////
int Carregar_Midi(char *nome_arq)
{
		//carrega um arquivo midi e retorna um id do som
	//retorna -1 se ocorrer erro

	
	DMUS_OBJECTDESC ObjDesc; 
	HRESULT hr;
	IDirectMusicSegment* pSegment = NULL;

	int i; 
 

	int id = -1;

	for (i = 0; i < MAX_MIDI; i++)
    {
    //testar se está livre
    if (dm_midi[i].state == 0)
       {
       id = i;
       break;
       }
    } 

	// id válido?
	if (id==-1)
   return(-1);

	
	char szDir[_MAX_PATH];
	WCHAR wszDir[_MAX_PATH]; 

	if(_getcwd( szDir, _MAX_PATH ) == NULL)
  {
		return(-1);
  } 

	MULTI_TO_WIDE(wszDir, szDir);

	hr = dm_loader->SetSearchDirectory(GUID_DirectMusicAllTypes,wszDir, FALSE);

	if (FAILED(hr)) 
   {
		return (-1);
   } 

	WCHAR wfilename[_MAX_PATH]; 
	MULTI_TO_WIDE(wfilename, nome_arq);
 
	memset(&ObjDesc,0,sizeof(ObjDesc)); 
	ObjDesc.dwSize=sizeof(ObjDesc);

	ObjDesc.guidClass = CLSID_DirectMusicSegment;
	wcscpy(ObjDesc.wszFileName, wfilename );
	ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;
 
	hr = dm_loader->GetObject(&ObjDesc,IID_IDirectMusicSegment, (void**) &pSegment);

	if (FAILED(hr))
   return(-1);
 
	hr = pSegment->SetParam(GUID_StandardMIDIFile,-1, 0, 0, (void*)dm_perf);

	if (FAILED(hr))
   return(-1);
  
	hr = pSegment->SetParam(GUID_Download, -1, 0, 0, (void*)dm_perf);

	if (FAILED(hr))
   return(-1);


	dm_midi[id].dm_segment  = pSegment;
	dm_midi[id].dm_segstate = NULL;
	dm_midi[id].state       = 1;
 
	// retornar id
	return(id);
 
} // fim Carregar_Midi()

//////////////////////////////////////////////
int Tocar_Midi(int id)
{

	if (dm_midi[id].dm_segment && dm_midi[id].state!=0)
   {
   // se houver um midi ativo então pára
   if (dm_id_ativo!=-1)
       Parar_Midi(dm_id_ativo);

   dm_perf->PlaySegment(dm_midi[id].dm_segment, 0, 0, &dm_midi[id].dm_segstate); 
   
   dm_id_ativo = id;
   return(1);
   }  
	 else
    return(0);

} // fim Tocar_Midi

//////////////////////////////////////////////
int Parar_Midi(int id)
{
	
	if (dm_midi[id].dm_segment && dm_midi[id].state!=0)
   {
   
   dm_perf->Stop(dm_midi[id].dm_segment, NULL, 0, 0);
   
   dm_id_ativo = -1;

   return(1);
   }  
	else
    return(0);

} // fim Parar_Midi

//////////////////////////////////////////////

int Midi_Tocando(int id)
{

	if (dm_midi[id].dm_segment && dm_midi[id].state !=0)
   {
   
   if (dm_perf->IsPlaying(dm_midi[id].dm_segment,NULL) == S_OK) 
      return(1);
   else
      return(0);
   } 
else
   return(0);

} // fim Midi_Tocando
