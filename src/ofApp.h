#pragma once

#include "threeAS-Timer.hpp"
#include "threeAS-SteadyClock.hpp"
#include "ofMain.h"
#include "ofxCsv.h"
#include <algorithm>
#include <vector>

const int numRows = 200;

class ofApp : public ofBaseApp {
  public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    void keyPressed(int key) override;

  private:
    three_as::SteadyClock clock;
    three_as::Timer timer{clock};
    ofxCsv csv, csvtmp;
    ofImage pic, stim, blank;
    int actualNumRows;
    std::vector<int> permvec;
    string picture[numRows], stimulus[numRows];
    int correctresponse[numRows], distance[numRows], emotion[numRows],
        correct[numRows];
    char answer[numRows];
    double RT[numRows];
    int rowCount = 0;
    bool readyForNext = true;
    bool stimflag = true;
    bool FirstPicFlag = false;
    bool noMore = true;
    bool init = true;

    int bgcolor = 128; // black = 0, 128 gray, 255 white;
    char threekey =
        '3'; // changing this may require a change to instructionText below
    char fourkey = '4';
    char fivekey = '5';
    char sixkey = '6';
    ofTrueTypeFont verdana14;
    string instructionText =
        "Press the number keys 3, 4, 5, or 6 according to\n\nHOW MANY numbers "
        "you see.\n\nPress space to begin.";
    int saveTime, stimTime, respTime;
    ofRectangle bounds;
};
