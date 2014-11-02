#pragma once
#include "Visual1.h"


using namespace ci;
using namespace ci::app;
using namespace std;

void VisualOne::draw()
{
	cam = CameraPersp(800, 600, fov, nearPlane, farPlane);
	gl::pushMatrices();
	gl::setMatrices(cam);
	gl::drawCube(cubePos, Vec3f::one());
	gl::drawSolidRect(Rectf(posX, 10, 50, 50));
	gl::popMatrices();
}

void VisualOne::update()
{
	posX++;
}

void VisualOne::initialize()
{
	posX = 10;
	nearPlane = 1;
	farPlane = 0; 
	fov = 120;
	cubePos = Vec3f::one();
	cubeSize = 10;
}

void VisualOne::Drawgui()
{
	ImGui::SliderFloat("fov", &fov, 0, 180);
	ImGui::SliderFloat("nearPlane", &nearPlane, -180, 180);
	ImGui::SliderFloat("farPlnae", &farPlane, -180, 180);
	ImGui::Spacing();
	ImGui::SliderFloat("cube X", &cubePos.x, -1000, 1000);
	ImGui::SliderFloat("cube Y", &cubePos.y, -1000, 1000);
	ImGui::SliderFloat("cube Z", &cubePos.z, -1000, 1000);
	ImGui::SliderFloat("cubeSize", &cubeSize, 1, 1000);
}
