#pragma once
#include "AbstractVisual.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include "ImGuiCinder.h"

class VisualOne : public AbstractVisual
{
public:
	void draw();
	void update();
	void initialize();
	
	void Drawgui();
	int posX;
	float nearPlane, farPlane, fov;
	float cubeSize;
	ci::Vec3f cubePos;
private:
	
	ci::CameraPersp cam;

};

