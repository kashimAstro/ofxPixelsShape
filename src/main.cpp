#include "ofMain.h"
#include "ofPixelsShape.h"

class ofApp : public ofBaseApp
{
	public:
	ofImage img;
	ofPixels pix;
	ofPixelsShape shape;

	void setup()
	{
		ofSetVerticalSync(false);
		pix.allocate(800,600,OF_IMAGE_COLOR);
		pix.setColor(ofColor::grey);

		shape.create_font( "letter32x32" );

		shape.draw_line(pix,      ofPoint(10, 10), ofPoint(200, 10), 		     ofColor::red);
		shape.draw_rectangle(pix, ofRectangle(300,30,100,100),       		     ofColor::blue);
		shape.draw_rectangle(pix, ofRectangle(100,50,110,150),  		     ofColor::orange, false);
		shape.draw_circle(pix,    ofPoint(400, 250), 60, 	     		     ofColor::red);
		shape.draw_circle(pix,    ofPoint(100, 350), 100, 	     		     ofColor::violet, false);
		shape.draw_point(pix,     ofPoint(320, 50), 		    		     ofColor::yellow);
		shape.draw_triangle(pix,  ofPoint(50,150), ofPoint(150,150), ofPoint(50,50), ofColor::cyan);

		//BUG:  no fill for triangle
		//shape.draw_triangle(pix, ofPoint(100,250), ofPoint(450,250), ofPoint(300,50), ofColor::cyan,false);
		shape.draw_char(pix,   'A', ofPoint(350,100));
		shape.draw_string(pix, "openframeworks", ofPoint(400,200), 12);

		img = pix;
	}

	void draw()
	{
		ofSetWindowTitle(to_string(ofGetFrameRate()));
		img.draw(0,0);
	}

	void keyPressed(int key)
	{
		if(key == ' ')
		{
			ofSaveImage(pix,"draw.jpg",OF_IMAGE_QUALITY_BEST);
		}
	}
};

int main(int argc, char ** argv)
{
	ofSetupOpenGL(800,600, OF_WINDOW);
	ofRunApp( new ofApp());
}
