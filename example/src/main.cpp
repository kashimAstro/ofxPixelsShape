#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxPixelsShape.h"

class ImgThread : public ofThread  /* example thread */
{
	public:
	ofPixels pix;
	ofxPixelsShape shape;

	void threadedFunction() 
	{
		ofLoadImage(pix,"pedoni.png");
		shape.create_font( "letter32x32", 32 );

        	while(isThreadRunning()) 
		{
			static unsigned int counter = 0;
		
			shape.draw_rectangle(pix, ofRectangle(200,75,80,15), ofColor::black, true);
			shape.draw_string(pix, "person", ofPoint(200,75), 12);
			shape.draw_rectangle(pix, ofRectangle(200,90,100,200), ofColor::orange, false);

			shape.draw_rectangle(pix, ofRectangle(310,75,80,15), ofColor::black, true);
			shape.draw_string(pix, "person", ofPoint(310,75), 12);
			shape.draw_rectangle(pix, ofRectangle(310,90,100,200), ofColor::violet, false);

			shape.draw_rectangle(pix, ofRectangle(550,65,80,15), ofColor::black, true);
			shape.draw_string(pix, "person", ofPoint(550,65), 12);
			shape.draw_rectangle(pix, ofRectangle(550,80,100,210), ofColor::blue, false);

			shape.draw_rectangle(pix, ofRectangle(600,75,80,15), ofColor::black, true);
			shape.draw_string(pix, "person", ofPoint(600,75), 12);
			shape.draw_rectangle(pix, ofRectangle(600,90,100,210), ofColor::green, false);

			ofSaveImage(pix,"thread_"+getThreadName()+"_"+to_string(counter)+".jpg",OF_IMAGE_QUALITY_BEST);
			cout << "Save image in Thread: "<<"thread_"<<getThreadName()<<"_"<<to_string(counter)<<".jpg" << endl;

			ofSleepMillis(2500);
			counter++;
		}
	}
};

class ofApp : public ofBaseApp /* example ofAppNoWindow */
{
	public:
	ImgThread imgth;

	ofImage img;
	ofPixels pix;
	ofxPixelsShape shape;
	float startTime;
        float endTime;

	void setup()
	{
		ofSetVerticalSync(false);
		shape.create_font( "letter32x32" );

		startTime = ofGetElapsedTimeMillis();
		endTime   = 2000;

		imgth.startThread(false);
	}

	void update()
	{
		float timer = ofGetElapsedTimeMillis() - startTime;
		if(timer >= endTime) 
		{
			static unsigned int counter = 0;
			pix.allocate(800,600,OF_IMAGE_COLOR);
			pix.setColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));

			shape.draw_line(pix,      ofPoint(10, 10), ofPoint(200, 10), 		     ofColor::red);
			shape.draw_rectangle(pix, ofRectangle(300,30,100,100),       		     ofColor::blue);
			shape.draw_rectangle(pix, ofRectangle(100,50,110,150),  		     ofColor::orange, false);
			shape.draw_circle(pix,    ofPoint(400, 250), 60, 	     		     ofColor::red);
			shape.draw_circle(pix,    ofPoint(100, 350), 100, 	     		     ofColor::violet, false);
			shape.draw_point(pix,     ofPoint(320, 50), 		    		     ofColor::yellow);
			shape.draw_triangle(pix,  ofPoint(50,150), ofPoint(150,150), ofPoint(50,50), ofColor::cyan);
			shape.draw_triangle(pix,  ofPoint(400,350), ofPoint(300,350), ofPoint(200,460), ofColor::green, false);
			shape.draw_char(pix,   'A', ofPoint(350,100));
			shape.draw_string(pix, "openframeworks", ofPoint(400,200), 12);

			ofSaveImage(pix,"main_"+to_string(counter)+".jpg",OF_IMAGE_QUALITY_BEST);
			cout << "Save image in ofMain: "<<"main_"<<to_string(counter)<<".jpg" << endl;
			startTime = ofGetElapsedTimeMillis();
			endTime   = 2000;
			counter++;
		}
	}

	void exit()
	{
		imgth.stopThread();
		ofExit(0);
	}
};

int main(int argc, char ** argv)
{
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);
	ofRunApp( new ofApp());
}
