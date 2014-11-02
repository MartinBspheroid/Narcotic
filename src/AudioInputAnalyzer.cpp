#include "AudioInputAnalyzer.h"

using namespace ci;
using namespace ci::app;
using namespace std;
#include "cinder/app/App.h"

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
	
}

void AudioAnalyzer::draw()
{
	gl::color(Color::white());
	
	int counter = 0;
	for (size_t i = 0; i < spectrum.size(); i++)
	{
		gl::drawLine(Vec2f(i, 0) , Vec2f(i, spectrum.at(i)*100000 ) );
	
	}



}
