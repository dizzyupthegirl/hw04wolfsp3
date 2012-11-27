/*
Name: Samantha Wolf
Date:November 5h, 2012
Citations: Brandon Sonoda, Nick Collins, and Matt Dwyer helped with 
reading in files(I didn't get it) and Brandon specifically showed me the pairs thing.
*/


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

static const int appHeight = 700;
static const int appWidth = 700;
static const int texture = 1024;

class hw04wolfsp3App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event);	
	void keyDown(KeyEvent event); 
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	pair<Entry*, int> getStarbucksData();
	void getCensusData();
	void displayStarbucks(Node* e, uint8_t* pixelData); 
	void createNearestMap(Node* e, uint8_t* pixelData);

private:
	
	StarbucksWolf* starbucks_;
	Surface* mySurface_;
	gl::Texture map;
	bool click;
	float circ_x, circ_y;

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

/*void hw04wolfsp3App::getCensusData() {
	int buffer;
	ifstream cen1("Census_2000.csv");

	int pop;
	double x, y;
	Entry* close;
	while(cen1.good()){
		cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
		cen1 >> pop;
		cen1.get();
		cen1 >> x;
		cen1.get();
		cen1 >> y;

		close = starbucks_->getNearest(x, y);
		//close->population = pop;
	}

	cen1.close();
}

*/
void hw04wolfsp3App::setup()

{

	//Attempts to test, but won't print to console for some dumb reason. 
	mySurface_ = new Surface(texture, texture, false);
	starbucks_ = new StarbucksWolf();
	map = gl::Texture(loadImage("usa3.png"));
	click=true;
	//Brandon Sonoda, you're a genius.
	pair<Entry*, int> smd = getStarbucksData();
	starbucks_->build(smd.first, smd.second);

	Entry* cur_entry = starbucks_->getNearest(0.0, 0.0);
	console() << "Starbucks: " << cur_entry->identifier << ", X = " << cur_entry->x << ", Y = " << cur_entry->y << std::endl;
	displayStarbucks(starbucks_->root, (*mySurface_).getData());
}

void hw04wolfsp3App::displayStarbucks(Node* root, uint8_t* pixelData) {
	
	if(root==NULL)
		return;
	 displayStarbucks(root->left, pixelData);
    
    int tempX = (int)(appWidth*(root->key->x));
    int tempY = appHeight-(int)(appHeight*(root->key->y));
    int index = 3*(tempY*texture+tempX);
    if(index>=0 && index < texture*texture*3){
        pixelData[index] = rand()%256;
        pixelData[index+1] = rand()%256;
        pixelData[index+2] = rand()%256;
    } 
    displayStarbucks(root->right, pixelData);
	
}
/*void createNearestMap(Node* root, uint8_t* pixelData) {
	
	for(int x=0; x< appWidth; x++) {
 		for(int y=0; y<appHeight; y++) {
			pixelData[y*appWidth+x] = root->r;
			pixelData[y*appWidth+x+1] = root->g;
			pixelData[y*appWidth+x+2] = root->b;
 			}
 		}
 	

	

    displayStarbucks(root->right, pixelData);


}
*/
void hw04wolfsp3App::keyDown( KeyEvent event)
{
		click=!click;
}

void hw04wolfsp3App::mouseDown( MouseEvent event )
{
	double x=1.0*event.getX()/700;
	double y=1.0-1.0*event.getY()/700;
	Entry* closestStarbucks=starbucks_->getNearest(x,y);
	circ_x=700*closestStarbucks->x;
	circ_y=700-700*closestStarbucks->y;

}



void hw04wolfsp3App::update() {
}

void hw04wolfsp3App::draw() {
	// clear out the window with black
	if(click==true) {
		gl::draw(*mySurface_); 
	
	}
	else {
	gl::draw(map, getWindowBounds());

	}
	gl::drawSolidCircle( Vec2f( circ_x, circ_y), 3.0f);

}


CINDER_APP_BASIC( hw04wolfsp3App, RendererGl )
