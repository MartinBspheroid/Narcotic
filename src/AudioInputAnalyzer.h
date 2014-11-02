#include "cinder/audio/Context.h"
#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"
#include "ImGuiCinder.h"
#include "cinder/gl/gl.h"

class AudioAnalyzer{
public:
	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;

	void initialize();
	void update();
	void draw();

	std::vector<float> spectrum;
};
