#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "StarbucksWolf.h"
#include "cinder/gl/Texture.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class hw04wolfsp3App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	

private:
	
	StarbucksWolf* starbucks_;
	Surface* mySurface_;

	static const int appHeight = 600;
	static const int appWidth = 600;
	static const int texture = 1024;
};

void hw04wolfsp3App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void hw04wolfsp3App::setup()
{
	//Attemps to test, but won't print to console for some dumb reason. 
	mySurface_ = new Surface(texture, texture, false);
	starbucks_ = new StarbucksWolf();
	Entry* cur_entry = starbucks_->getNearest(0.0, 0.0);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y << std::endl;
	cur_entry = starbucks_->getNearest(0.1, 0.1);
	console() << "Starbucks:" << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y<< std::endl;
	cur_entry = starbucks_->getNearest(0.2, 0.2);
	console() << "Starbucks:" << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y<< std::endl;
	cur_entry = starbucks_->getNearest(0.3, 0.3);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y<< std::endl;
	cur_entry = starbucks_->getNearest(0.4, 0.4);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y<< std::endl;
	cur_entry = starbucks_->getNearest(0.5, 0.5);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y<< std::endl;
	
}


void hw04wolfsp3App::mouseDown( MouseEvent event )
{
}

void hw04wolfsp3App::update() {
}

void hw04wolfsp3App::draw() {
	// clear out the window with black
	gl::draw(*mySurface_); 
}


CINDER_APP_BASIC( hw04wolfsp3App, RendererGl )
