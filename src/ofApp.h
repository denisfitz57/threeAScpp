#pragma once

#include "threeAS-Timer.hpp"
#include "threeAS-SteadyClock.hpp"
#include <ofMain.h>
#include <ofxCsv.h>
#include <vector>
#include <string>
#include <array>

class ofApp : public ofBaseApp {
  public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    void keyPressed(int key) override;

  private:
    ofxCsv csv;
    ofImage pic;
    ofImage stim;
    ofImage blank;
    ofRectangle bounds;
    ofTrueTypeFont verdana14;
    three_as::SteadyClock clock;
    three_as::Timer timer{clock};
    static constexpr auto numRows{200};
    std::array<std::string, numRows> picture;
    std::array<std::string, numRows> stimulus;
    std::array<int, numRows> correctresponse;
    uint64_t stimTime;
    int actualNumRows;
    int rowCount = 0;
    bool readyForNext = true;
    bool FirstPicFlag = false;
    bool noMore = true;
    bool init = true;
};
