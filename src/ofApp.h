#pragma once

#include "threeAS-Timer.hpp"
#include "threeAS-SteadyClock.hpp"
#include "ofMain.h"
#include "ofxCsv.h"
#include <vector>

class ofApp : public ofBaseApp {
  public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    void keyPressed(int key) override;

  private:
    static constexpr auto numRows{200};
    three_as::SteadyClock clock;
    three_as::Timer timer{clock};
    ofxCsv csv, csvtmp;
    ofImage pic, stim, blank;
    ofTrueTypeFont verdana14;
    std::vector<int> permvec;
    std::string picture[numRows];
    std::string stimulus[numRows];
    int actualNumRows;
    int correctresponse[numRows];
    int distance[numRows];
    int emotion[numRows];
    int rowCount = 0;
    bool readyForNext = true;
    bool FirstPicFlag = false;
    bool noMore = true;
    bool init = true;
    int stimTime;
    int respTime;
    ofRectangle bounds;
};
