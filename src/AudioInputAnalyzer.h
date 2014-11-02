#include "cinder/audio/Context.h"
#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"
#include "ImGuiCinder.h"
#include "cinder/gl/gl.h"

typedef std::pair<int, int> audioRange;

class AudioAnalyzer{
public:
	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;

	void initialize();
	void update();
	void draw();
	void loadRanges();
	bool showSpectrum;
	std::vector<float> spectrum;
	float audioVolume;

	float range1Avg;
	
	audioRange range1;
};
