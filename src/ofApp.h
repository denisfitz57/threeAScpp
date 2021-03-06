#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include <algorithm>
#include <vector>

const int numRows = 200;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofxCsv csv,csvtmp;
		ofImage pic, stim, blank;
		int actualNumRows;
		std::vector<int> permvec;
		string picture[numRows], stimulus[numRows];
		int correctresponse[numRows], distance[numRows], emotion[numRows], correct[numRows];
		char answer[numRows];
		double RT[numRows];
		int rowCount = 0;
		bool readyForNext=true, stimflag = true, FirstPicFlag = true, noMore = true;
		bool showPic1 = false, showStim = false, showPic2 = false, showBlank = false;
		bool init = true;

		//int pic1dur = 400;  //in msec
//int stimdur = 400;
//int pic2dur = 400;
//int endblankdur = 1300;
		uint64_t pic1dur = 24;  //in frames
		uint64_t stimdur = 24;
		uint64_t pic2dur = 24;
		uint64_t endblankdur = 78;
		int bgcolor = 128; //black = 0, 128 gray, 255 white; 
		char threekey = '3'; //changing this may require a change to instructionText below
		char fourkey = '4';
		char fivekey = '5';
		char sixkey = '6';
		ofTrueTypeFont	verdana14;
		 string instructionText = "Press the number keys 3, 4, 5, or 6 according to\n\nHOW MANY numbers you see.\n\nPress space to begin.";
		int saveTime, stimTime, respTime;
		ofRectangle bounds;
};
