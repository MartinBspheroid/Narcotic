#include "cinder/app/App.h"

#include "AudioInputAnalyzer.h"


using namespace ci;
using namespace ci::app;
using namespace std;


void AudioAnalyzer::initialize()
{
	auto ctx = audio::Context::master();
	
	mInputDeviceNode = ctx->createInputDeviceNode();

	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	mMonitorSpectralNode = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

	mInputDeviceNode >> mMonitorSpectralNode;

	mInputDeviceNode->enable();

	
	auto devices = ctx->deviceManager()->getDevices();
	
	for (auto &d : devices){

		ci::app::console() << d->getName() << endl;

	}


	ci::app::console() << "DEVICE INPUT: " << mInputDeviceNode->getDevice()->getName() << endl;
	ctx->enable();

}

void AudioAnalyzer::update()
{
	spectrum = mMonitorSpectralNode->getMagSpectrum();
	audioVolume = mMonitorSpectralNode->getVolume();
	
	range1Avg = 0;
	for (int i = range1.first; i < range1.second; i++)
	{
		range1Avg += spectrum.at(i);
	}

	range1Avg /= (range1.second - range1.first);
	range1Avg *= 1000;

}

void AudioAnalyzer::draw()
{

	gl::color(Color::gray(0.25));
	gl::drawSolidRect(ci::Rectf(range1.first, 0, range1.second, 500));

	gl::color(Color::gray(0.5));
	
	int counter = 0;
	for (size_t i = 0; i < spectrum.size(); i++)
	{
		gl::drawLine(Vec2f(i, 0) , Vec2f(i, spectrum.at(i)*10000 ) );
	
	}

	

}

void AudioAnalyzer::loadRanges()
{
/// add loading from JSON
	/// use variables for now
	range1.first = 100;
	range1.second = 200;
}
