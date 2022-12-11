#include "Camera.h"

CCamera::CCamera() : m_position(0,0,0),m_yaw(0),m_pitch(0),m_roll(0)
{
	// Start with an orthagonal camera axis looking down z
	m_up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_look=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_right=D3DXVECTOR3(1.0f,0.0f,0.0f);
}

CCamera::CCamera(D3DXVECTOR3 startPos) : m_position(startPos),m_yaw(0),m_pitch(0),m_roll(0)
{
	// Start with an orthagonal camera axis looking down z
	m_up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_look=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_right=D3DXVECTOR3(1.0f,0.0f,0.0f);
}

// Sets yaw pitch and roll
void CCamera::SetYawPitchRoll(float yaw,float pitch, float roll)
{
	m_yaw=yaw;
	m_pitch=pitch;
	m_roll=roll;
}

/*
	Calculate a view matrix by rotating our axis from the default orientation (looking down z)
	via the yaw, pitch and roll member variables. Also add in any translation.
*/
void CCamera::CalculateViewMatrix(D3DXMATRIX *viewMatrix)
{
	// Start with our camera axis pointing down z
	m_up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_look=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_right=D3DXVECTOR3(1.0f,0.0f,0.0f);

	// Yaw is rotation around the y axis (m_up)
	// Create a matrix that can carry out this rotation
	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &m_up, m_yaw);
	// To apply yaw we rotate the m_look & m_right vectors about the m_up vector (using our yaw matrix)
	D3DXVec3TransformCoord(&m_look, &m_look, &yawMatrix); 
	D3DXVec3TransformCoord(&m_right, &m_right, &yawMatrix); 

	// Pitch is rotation around the x axis (m_right)
	// Create a matrix that can carry out this rotation
	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &m_right, m_pitch);
	// To apply pitch we rotate the m_look and m_up vectors about the m_right vector (using our pitch matrix)
	D3DXVec3TransformCoord(&m_look, &m_look, &pitchMatrix); 
	D3DXVec3TransformCoord(&m_up, &m_up, &pitchMatrix); 
		
	// Roll is rotation around the z axis (m_look)
	// Create a matrix that can carry out this rotation
	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &m_look, m_roll);
	// To apply roll we rotate up and right about the look vector (using our roll matrix)
	// Note: roll only really applies for things like aircraft unless you are implementing lean
	D3DXVec3TransformCoord(&m_right, &m_right, &rollMatrix); 
	D3DXVec3TransformCoord(&m_up, &m_up, &rollMatrix); 
	
	// Build the view matrix from the transformed camera axis
	D3DXMatrixIdentity(viewMatrix);

	viewMatrix->_11 = m_right.x; viewMatrix->_12 = m_up.x; viewMatrix->_13 = m_look.x;
	viewMatrix->_21 = m_right.y; viewMatrix->_22 = m_up.y; viewMatrix->_23 = m_look.y;
	viewMatrix->_31 = m_right.z; viewMatrix->_32 = m_up.z; viewMatrix->_33 = m_look.z;
	
	viewMatrix->_41 = - D3DXVec3Dot( &m_position,&m_right); 
	viewMatrix->_42 = - D3DXVec3Dot( &m_position,&m_up);
	viewMatrix->_43 = - D3DXVec3Dot( &m_position,&m_look);
}

// Yaw - rotation around y axis
void CCamera::Yaw(float amount) 
{
	m_yaw+=amount;
	m_yaw=RestrictAngleTo360Range(m_yaw);
}	

// Pitch - rotation around x axis
void CCamera::Pitch(float amount)
{
	m_pitch+=amount;
	m_pitch=RestrictAngleTo360Range(m_pitch);
}

// Roll - rotation around z axis
// Note: normally only used for aircraft type cameras rather than land based ones
void CCamera::Roll(float amount) 
{
	m_roll+=amount;
	m_roll=RestrictAngleTo360Range(m_roll);
}

// Keep the angle in the range 0 to 360 (2*PI radians)
float CCamera::RestrictAngleTo360Range(float angle) const
{
	while(angle>2*D3DX_PI)
		angle-=2*D3DX_PI;

	while(angle<0)
		angle+=2*D3DX_PI;

	return angle;
}