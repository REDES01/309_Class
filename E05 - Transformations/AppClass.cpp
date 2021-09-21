#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	m_uMeshCount = 46;		// Count
	for (uint i = 0;i < m_uMeshCount;i++)
	{
		m_pMesh = new MyMesh();
		m_pMesh->GenerateCube(1.0f, C_BLACK);
		meshList.push_back(m_pMesh);
	}


		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	static float value = 0;
	matrix4 origin = IDENTITY_M4 * glm::translate(vector3(value, 0, -20));
	value += 0.1;


	float row1[] = {3,4,6,7};
	int i = 0;
	for (;i < 4;i++)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin,vector3(row1[i],0,0)));
	}


	float row2[] = { 0,2,8,10 };
	for (;i < 8;i++)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin, vector3(row2[i-4], 1, 0)));
	}

	float row3[] = { 0,2,3,4,5,6,7,8,10 };
	for (;i < 17;i++)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin, vector3(row3[i-8], 2, 0)));
	}
	for (uint count = 0; count < 11; ++count)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin, vector3(count, 3.0f, 0.0f))); ++i;
	}

	float row4[] = { 1,2,4,5,6,8,9 };
	for (;i < 35;i++)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin, vector3(row4[i-28], 4, 0)));
	}
	for (uint count = 2; count < 9; ++count)
	{
		meshList[i]->Render(m4Projection, m4View, glm::translate(origin, vector3(count, 5.0f, 0.0f))); ++i;
	}
	meshList[42]->Render(m4Projection, m4View, glm::translate(origin, vector3(3, 6.0f, 0.0f)));
	meshList[43]->Render(m4Projection, m4View, glm::translate(origin, vector3(7, 6.0f, 0.0f)));

	meshList[44]->Render(m4Projection, m4View, glm::translate(origin, vector3(2, 7.0f, 0.0f)));
	meshList[45]->Render(m4Projection, m4View, glm::translate(origin, vector3(8, 7.0f, 0.0f)));
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
	//Release meshes
	for (int i = 0;i < m_uMeshCount;i++)
	{
		if (meshList[i] != nullptr)
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	//release GUI
	ShutdownGUI();
}