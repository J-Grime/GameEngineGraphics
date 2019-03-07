////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_ModelX = 0;
	m_ModelY = 0;
	m_ModelZ = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -40.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 5.0f, 1.0f);
	m_Light->SetDirection(1.0f,0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 5.0f, 1.0f);
	m_Light->SetSpecularPower(50.0f);

	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/fish.txt", L"../Engine/data/fish.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}
	// Create the model object.
	m_ModelX = new ModelClass;
	if (!m_Model1)
	{
		return false;
	}
	// Create the model object.
	m_ModelY = new ModelClass;
	if (!m_ModelY)
	{
		return false;
	}

	// Initialize the model object.
	result = m_ModelY->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/floor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model object.
	result = m_ModelX->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/backwall.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/fish.txt", L"../Engine/data/fish.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}


	// Create the model object.
	m_ModelSUB = new ModelClass;
	if (!m_ModelSUB)
	{
		return false;
	}

	// Initialize the model object.
	result = m_ModelSUB->Initialize(m_D3D->GetDevice(), "../Engine/data/SUB.txt", L"../Engine/data/sub.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/bush.txt", L"../Engine/data/seagrass.dds", 
								  L"../Engine/data/seagrass.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	return true;


}




void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if(m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if(m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}
	if (m_ModelX)
	{
		m_ModelX->Shutdown();
		delete m_ModelX;
		m_ModelX = 0;
	}
	if (m_ModelY)
	{
		m_ModelY->Shutdown();
		delete m_ModelY;
		m_ModelY = 0;
	}
	if (m_ModelZ)
	{
		m_ModelZ->Shutdown();
		delete m_ModelZ;
		m_ModelZ = 0;
	}
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
		
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ,mouseX,mouseY;
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix,ScaleMatrix, rotationMatrix,okay;
	bool result;
	XMVECTOR originMatrix;
	static float rotation = 0.2f;
	float x;
	float y;
	float up = -100.0f;
	
	
	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the first model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixScaling(0.5f,0.5f,0.5f) ;
	translateMatrix = XMMatrixTranslation(4.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	
	//positioning factors
	XMVECTOR myAxis;
	myAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix,XMMatrixRotationAxis(myAxis,rotation));
	
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 1.0f, 0.0f));
	okay = worldMatrix;

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}
	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0), XMMatrixScaling(110.0f, 100.0f, 0.0f));
	translateMatrix = XMMatrixTranslation(-2.0f, 25.0f, 100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render model using the texture shader.
	m_ModelX->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelX->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelX->GetTexture());
	if (!result)
	{
		return false;
	}
	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0.0F), XMMatrixScaling(100.0f, 0.1f, 100.0f));
	translateMatrix = XMMatrixTranslation(0.0f, -2.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_ModelY->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelY->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelY->GetTexture());
	if (!result)
	{
		return false;
	}
	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0.0f), XMMatrixScaling(0.0f, 100.0f, 100.0f));
	translateMatrix = XMMatrixTranslation(-100.0f, 25.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_ModelX->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelX->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelX->GetTexture());
	if (!result)
	{
		return false;
	}
	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0.0f), XMMatrixScaling(100.0f, 100.0f, 00.0f));
	translateMatrix = XMMatrixTranslation(0.0f, 25.0f, -100.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_ModelX->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelX->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelX->GetTexture());
	if (!result)
	{
		return false;
	}
	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0.0f), XMMatrixScaling(00.0f, 100.0f, 100.0f));
	translateMatrix = XMMatrixTranslation(100.0f, 25.0f, 00.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_ModelX->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelX->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelX->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of a model.
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixMultiply(XMMatrixRotationY(rotation*0.0f), XMMatrixScaling(00.01f, 00.01f, 00.01f));
	translateMatrix = XMMatrixTranslation(-100.0f + (rotation*6.0f), 10.0f, 50.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	// Render the first model using the texture shader.
	m_ModelSUB->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_ModelSUB->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ModelSUB->GetTexture());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);
	
	rotationMatrix = XMMatrixRotationY(XMConvertToRadians(rotation));
	worldMatrix = XMMatrixScaling(0.5f, 0.5f,0.5f);
	translateMatrix = XMMatrixTranslation(4.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//positioning factors
	myAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(myAxis, rotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix,okay);

	

	// Render the second model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the third model.
	
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(XMMatrixRotationX(rotation*0.0f),XMMatrixScaling(0.05f, 0.05f, 0.05f)) ;
	translateMatrix = XMMatrixTranslation(3.5f, -2.0f, 10.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(), 
												  m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(XMMatrixRotationX(rotation*0.0f), XMMatrixScaling(0.05f, 0.05f, 0.05f));
	translateMatrix = XMMatrixTranslation(0.5f, -2.0f, 10.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(XMMatrixRotationX(rotation*0.0f), XMMatrixScaling(0.1f, 0.1f, 0.1f));
	translateMatrix = XMMatrixTranslation(-5.5f, -2.0f, 20.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}