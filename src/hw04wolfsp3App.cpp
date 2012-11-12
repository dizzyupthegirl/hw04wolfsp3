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
	pair<Entry*, int> getStarbucksData();
	

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

//Brandon Shenanigan's
pair<Entry*, int> hw04wolfsp3App::getStarbucksData() {
	ifstream in("Starbucks_2006.csv");
	vector <Entry> stored_v;
	string line;
	double i_;
	double j_;
	char separator;
	int x = 0;

	//I was so lost on this part, I'm still not sure exactly how this reads in the code...
	while(in.good()) {
		Entry* e = new Entry();
		stored_v.push_back(*e);
		getline(in, line, ',');

		stored_v[x].identifier = line;
		in >> i_;
		stored_v[x].x = i_;
		in >> separator;//Sam, this is a comma....
		in >> j_;
		stored_v[x].y = j_;
		x++;
	}
	Entry* stored_a = new Entry[stored_v.size()];

	for(int i = 0; i < stored_v.size(); i++)
		stored_a[i] = stored_v[i];
	return std::make_pair(stored_a, x);
}

void hw04wolfsp3App::setup()

{

	//Attempts to test, but won't print to console for some dumb reason. 
	mySurface_ = new Surface(texture, texture, false);
	starbucks_ = new StarbucksWolf();

	//Brandon Sonoda, you're a genius.
	pair<Entry*, int> smd = getStarbucksData();
	starbucks_->build(smd.first, smd.second);

	Entry* cur_entry = starbucks_->getNearest(0.0, 0.0);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y << std::endl;
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
