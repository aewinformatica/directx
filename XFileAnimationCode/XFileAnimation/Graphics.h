#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class CXFileEntity;
class CCamera;

/*
	The CGraphics class provides all the graphics for the demo
	It has code to set up Direct3D and load x files via the CXFileEntity class
*/
class CGraphics
{
private:
	// Direct3D objects
	IDirect3D9* m_d3dObject;
	IDirect3DDevice9* m_d3dDevice;
	ID3DXFont * m_font;

	// Internal objects
	CXFileEntity *m_entity;
	CCamera *m_camera;	

	// Entity position and orientation variables
	D3DXVECTOR3 m_entityPosition;
	float m_entityYaw,m_entityPitch,m_entityRoll;

	bool m_displayControls;	
	void DisplayText() const;
public:
	CGraphics(void);
	~CGraphics(void);

	bool Initialise(HWND hWnd);
	void Update();
	bool LoadXFile(const std::string &filename,int startAnimation=0);
	CCamera *GetCamera() const;
	void ToggleControlsDisplay() {m_displayControls=!m_displayControls;}

	void YawEntity(float value){m_entityYaw+=value;}
	void PitchEntity(float value){m_entityPitch+=value;}
	void RollEntity(float value){m_entityRoll+=value;}

	void NextAnimation();
	void AnimateFaster();
	void AnimateSlower();
};
