#include "ImGuiCinder.h"

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "Visual1.h"
#include "AudioInputAnalyzer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Narcotic : public AppNative {
public:
	void setup();

	void initializeWindows();
	void initializeMidi();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
	void drawImGui();
	void keyUp(KeyEvent event);
	void drawGui();
	void narcoticQuit();

	gl::Fbo fboProjection;
	VisualOne v1;

	AudioAnalyzer audioIn;
	app::WindowRef guiWindow, projectionWindow;
	bool isQuit;
};

void Narcotic::setup()
{
	audioIn.initialize();
	isQuit = false;
	initializeWindows();
	fboProjection = gl::Fbo(1024, 768, false);
	v1.initialize();

}

void Narcotic::mouseDown(MouseEvent event)
{
}

void Narcotic::update()
{
	if (isQuit)
	{
		narcoticQuit();
	}
	audioIn.update();
	v1.update();
}

void Narcotic::draw()
{
	
	gl::clear();
	fboProjection.bindFramebuffer();
	gl::clear(Color::gray(0.25));
	v1.draw();
	fboProjection.unbindFramebuffer();
	gl::draw(fboProjection.getTexture(), Rectf(projectionWindow->getBounds()));
	//fboProjection.unbindTexture();
}

void Narcotic::initializeWindows()
{
	guiWindow = app::getWindow();
	projectionWindow = createWindow(Window::Format().size(400, 400));

// FIX THIS 
	guiWindow->getSignalPostDraw().connect([this]{drawGui(); });

	projectionWindow->setTitle("Narcotic Visuals Projection");
	projectionWindow->setAlwaysOnTop(true);
	

	Vec2f projectionPos;
	projectionPos.x = guiWindow->getPos().x + guiWindow->getSize().x;
	projectionPos.y = 50;
	projectionWindow->setPos(projectionPos);
	guiWindow->getSignalClose().connect([=]{isQuit = true; });
	guiWindow->setTitle("Narcotic visuals GUI");

	guiWindow->setPos(10, 50);

	int uniqueId = getNumWindows();
	/*newWindow->getSignalClose().connect(
		[uniqueId, this] { this->console() << "You closed window #" << uniqueId << std::endl; }
		);*/
	ImGui::setWindow(guiWindow);
	//connect close to other windows.
	// download midi
}

void Narcotic::drawGui()
{
	gl::clear(Color::black());
	audioIn.draw();
	drawImGui();
}

void Narcotic::drawImGui()
{
	ImGui::NewFrame();
	
	v1.Drawgui();
	static float f = 0.1f;
	static bool displayTestWindow = false;

	static bool isKinectConnected = false;
	static bool isArduinoConnected = false;

	// add some text. the %.xf allows to specify float precision
	ImGui::Text("Average FPS %.0f", getAverageFps());
	// add a slider from 0 to 1
	ImGui::SliderFloat("Background", &f, 0.0f, 1.0f);

	ImGui::Checkbox("Kinect Connected", &isKinectConnected);
	ImGui::Checkbox("Arduino Connected", &isArduinoConnected);
	ImGui::SliderInt("V1 val", &v1.posX, 0, 30);

	ImGui::Render();
}

void Narcotic::keyUp(KeyEvent event)
{
	if (event.isControlDown() && event.getCode() == KeyEvent::KEY_q)
	{
		isQuit = true;
	}
}

void Narcotic::narcoticQuit()
{
// close all devices 
	//save all preferences
	if (isQuit)
	{
		quit();
	}
	else
	{
		isQuit = true;
	}
	
}

CINDER_APP_NATIVE(Narcotic, RendererGl)
