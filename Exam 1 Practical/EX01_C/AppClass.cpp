#include "AppClass.h"
void Application::AddStar(void)
{
	//Check how many shapes are in the list already
	uint uCount = m_pMeshList.size();
	
	//Allocate the memory for the new shape
	MyMesh* pMesh = new MyMesh();
	pMesh->GenerateStar(uCount + 4, 0.5f, 0.25f, C_RED);
	m_pMeshList.push_back(pMesh);
}
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	AddStar();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Adjust the camera based on the number of shapes
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * (3.0f + m_pMeshList.size()), ZERO_V3, AXIS_Y);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Get some variable to position and rotate the other shapes out of the origin
	static uint uClock = m_pSystem->GenClock();
	double dDelta = m_pSystem->GetDeltaTime(uClock);
	static double dCumulative = 2.0f;
	static int startCount = 0;
	dCumulative += dDelta;
	//If the cumulative time has exceed 1 second restart and add a Star
	if (dCumulative > 1.0f)
	{
		dCumulative = 0.0;
		AddStar(); //Remove to add a star each second



	}

	//Calculate the model, view and projection matrix
	uint uCount = m_pMeshList.size();

	//Render the mesh list
	for (uint i = 0; i < uCount; i++)
	{
		m_pMeshList[i]->Render(
			m_pCameraMngr->GetProjectionMatrix(), 
			m_pCameraMngr->GetViewMatrix(), 
			ToMatrix4(m_qArcBall)* glm::translate(vector3(i, 0, 0))); //make sure to use linear combination to
			//change the position of the new stars i units from eachother
	}
	
	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	uint uCount = m_pMeshList.size();

	//Release the mesh list
	for (uint i = 0; i < uCount; i++)
	{
		SafeDelete(m_pMeshList[i]);
	}
	m_pMeshList.clear();

	//release GUI
	ShutdownGUI();
}