#include "Graphics.h"
#include "Utility.h"
#include "XfileEntity.h"
#include "Camera.h"

const int kFontSize=14;

// Constructor
CGraphics::CGraphics(void) : m_d3dObject(0),m_d3dDevice(0),m_entity(0),m_displayControls(true), 
	m_entityPosition(0,0,0),m_entityYaw(0),m_entityPitch(0),m_entityRoll(0),m_font(0)
{
	m_camera=new CCamera();
}

// Destructor - clean up by deleting alloacted memory and releasing Direct3D objects
CGraphics::~CGraphics(void)
{
	if (m_entity)
	{
		delete m_entity;
		m_entity=0;
	}

	if (m_camera)
	{
		delete m_camera;
		m_camera=0;
	}

	if (m_font)
	{
		m_font->Release();
		m_font=0;
	}

	if (m_d3dDevice)
	{
		m_d3dDevice->Release();
		m_d3dDevice=0;
	}

	if (m_d3dObject)
	{
		m_d3dObject->Release();
		m_d3dObject=0;
	}
}

/*
	Initialise our graphics by setting up Direct3D
*/
bool CGraphics::Initialise(HWND hWnd)
{
	m_d3dObject=Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3dObject)
	{
		CUtility::DebugString("Could not create Direct3D object\n");
		return false;
	}

	D3DPRESENT_PARAMETERS presParams;
	memset(&presParams,0,sizeof(presParams));
	presParams.Windowed=TRUE;
	presParams.SwapEffect=D3DSWAPEFFECT_DISCARD;
	presParams.BackBufferFormat=D3DFMT_UNKNOWN;
	presParams.BackBufferCount=1;
	presParams.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT hr=m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &presParams, &m_d3dDevice);
	if (CUtility::FailedHr(hr))
	{
		// It may be that the machine cannot support vertex processing in hardware so try software instead
		hr=m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &m_d3dDevice);
		if (CUtility::FailedHr(hr))
		{
			CUtility::DebugString("Could not create Direct3D device\n");
			return false;
		}
	}

	m_d3dDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

	// Setup basic render state
	m_d3dDevice->SetRenderState( D3DRS_LIGHTING,         TRUE );
	m_d3dDevice->SetRenderState( D3DRS_DITHERENABLE,     TRUE );
	m_d3dDevice->SetRenderState( D3DRS_SPECULARENABLE,	  FALSE );
	m_d3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
	m_d3dDevice->SetRenderState( D3DRS_CULLMODE,         D3DCULL_CCW );
	m_d3dDevice->SetRenderState( D3DRS_AMBIENT,          0x99999999 );
	m_d3dDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	// Setup states effecting texture rendering:
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_CURRENT );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	m_d3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_d3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	// Set the projection matrix
	D3DXMATRIX matProj;	
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 800.0f/600.0f, 1.0f, 5000.0f );
	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	// Lighting	
	m_d3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	// Create a directional light
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	light.Diffuse.a  = 1.0f;
	light.Range      = 1000.0f;

	// Direction for our light - it must be normalized - pointing down and along z
	D3DXVECTOR3 vecDir;
	vecDir = D3DXVECTOR3(0.0f,-0.3f,0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	m_d3dDevice->SetLight( 0, &light );
	m_d3dDevice->LightEnable( 0, TRUE );

	// Plus some non directional ambient lighting
	m_d3dDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(80,80,80));
	
	// Create a font to display info on the screen
	D3DXCreateFont( m_d3dDevice, kFontSize, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );

	return true;
}

/*
	Returns the camera
	Note: I do not normally like providing access to a graphics class outside of the graphics component
	however I am doing so here just for this demo and the sake of code clarity
*/
CCamera *CGraphics::GetCamera() const
{
	assert(m_camera);
	return m_camera;
}

/*
	Called as often as possible from main this function calculates the time passed and 
	animates the entity. It also implements the Direct3D render loop.
*/
void CGraphics::Update()
{
	static DWORD lastTime=timeGetTime();

	// Set view matrix dependant on camera
	D3DXMATRIX matView;
	m_camera->CalculateViewMatrix(&matView);
	m_d3dDevice->SetTransform( D3DTS_VIEW, &matView );
		
	// Clear the render target and the zbuffer 
	HRESULT hr=m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	if (CUtility::FailedHr(hr))
		return;

	// Render the scene
	if(SUCCEEDED(m_d3dDevice->BeginScene()))
	{
		// Render our model
		if (m_entity)
		{
			float timeElapsed=0.001f*(timeGetTime()-lastTime);
			lastTime=timeGetTime();

			// Need to pass the high level matrix used to position and orientate the model
			// Create this from current position and rotations:
			D3DXMATRIX matRotX,matRotY,matRotZ,matTrans;
			// Calculate rotation matrix
			D3DXMatrixRotationX( &matRotX, m_entityPitch );
			D3DXMatrixRotationY( &matRotY, m_entityYaw );  
			D3DXMatrixRotationZ( &matRotZ, m_entityRoll ); 
			// Calculate a translation matrix
			D3DXMatrixTranslation(&matTrans,m_entityPosition.x,m_entityPosition.y,m_entityPosition.z);
			// Calculate our world matrix by multiplying the above (in the correct order)
			D3DXMATRIX matWorld=(matRotX*matRotY*matRotZ)*matTrans;			

			// FrameMove carries out the animation while Render just draws
			m_entity->FrameMove(timeElapsed,&matWorld);
			m_entity->Render();
		}

		DisplayText();

		m_d3dDevice->EndScene();
		m_d3dDevice->Present( NULL, NULL, NULL, NULL ); 
	}
}

/*
	Display data about the model and the controls
*/
void CGraphics::DisplayText() const
{
	static DWORD lastTime=timeGetTime();
	static int numFrames=0;
	static float fps=0;

	// Calculate frame rate every second
	numFrames++;
	DWORD timePassed=timeGetTime()-lastTime;
	if (timePassed>1000)
	{
		fps=0.001f*timePassed*numFrames;
		numFrames=0;
		lastTime=timeGetTime();
	}
	
	D3DCOLOR fontColor = D3DCOLOR_XRGB(255,255,255);    
	RECT rct;
	rct.left=kFontSize;
	rct.right=800;
	rct.top=kFontSize;
	rct.bottom=rct.top+kFontSize;

	// Show frame rate
	std::string fpsString="FPS: "+ToString(fps);
	m_font->DrawText(NULL, fpsString.c_str(), -1, &rct, 0, fontColor );
	rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;

	if (m_entity)
	{
		std::string fnameString="Current File: "+m_entity->GetFilename();
		m_font->DrawText(NULL,fnameString.c_str(), -1, &rct, 0, fontColor );
		
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;		
		std::string animString="Current Animation Set: ("+ToString(m_entity->GetCurrentAnimationSet())+") "+
			m_entity->GetAnimationSetName(m_entity->GetCurrentAnimationSet());
		m_font->DrawText(NULL,animString.c_str(), -1, &rct, 0, fontColor );
	}
	else
	{
		m_font->DrawText(NULL,"No file loaded. Press L to load a file", -1, &rct, 0, fontColor );
	}
	
	if (m_displayControls)
	{
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "CONTROLS", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Space bar: switch to next animation set", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Numpad plus and minus: change animation speed", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Left and right arrows: translate camera left and right", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Up and down arrows: translate camera forward and back", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Home and End keys: translate camera up and down", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Numpad 4 and 6: rotate entity about y (yaw)", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Numpad 8 and 2: rotate entity about x (pitch)", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "Numpad 7 and 9: rotate entity about z (roll)", -1, &rct, 0, fontColor );
		rct.top+=kFontSize;rct.bottom=rct.top+kFontSize;
		m_font->DrawText(NULL, "F1: toggle the display of these controls", -1, &rct, 0, fontColor );
	}
}

/*
	This function attempts to load the requested .x file from filename
	If it fails (probably cannot find the file) it returns false
	The startAnimation optionally allows the first animation to play to be set
*/
bool CGraphics::LoadXFile(const std::string &filename,int startAnimation)
{
	// We only support one entity so if it already exists delete it
	if (m_entity)
	{
		delete m_entity;
		m_entity=0;
	}

	// Create the entity
	m_entity=new CXFileEntity(m_d3dDevice);
	if (!m_entity->Load(filename))
	{
		delete m_entity;
		m_entity=0;
		return false;
	}

	m_entity->SetAnimationSet(startAnimation);

	// Set the camera so it is looking at the entity
	D3DXVECTOR3 pos=m_entity->GetInitialCameraPosition();
	m_camera->SetPosition(pos);
	m_camera->SetYawPitchRoll(0,0,0);

	return true;
}

// Select the next animation set
void CGraphics::NextAnimation()
{
	if (m_entity)
		m_entity->NextAnimation();
}

// Make it animate faster
void CGraphics::AnimateFaster()
{
	if (m_entity)
		m_entity->AnimateFaster();
}

// Make it animate slower
void CGraphics::AnimateSlower()
{
	if (m_entity)
		m_entity->AnimateSlower();
}
