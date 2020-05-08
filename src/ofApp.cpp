#include "ofApp.h"
#include <algorithm>
#include <random>

using std::literals::chrono_literals::operator""ms;

constexpr auto firstPictureDuration{400ms};
constexpr auto stimulusDuration{400ms};
constexpr auto secondPictureDuration{400ms};
constexpr auto blankDuration{1300ms};
constexpr auto threekey =
    '3'; // changing this may require a change to instructionText below
constexpr auto fourkey = '4';
constexpr auto fivekey = '5';
constexpr auto sixkey = '6';
constexpr auto instructionText =
    "Press the number keys 3, 4, 5, or 6 according to\n\nHOW MANY numbers "
    "you see.\n\nPress space to begin.";

void ofApp::setup() {
    ofSetFrameRate(60);
    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);

    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
    csvtmp.load("3as.csv");
    actualNumRows = csvtmp.getNumRows() - 1;
    for (int i = 0; i < actualNumRows; i++)
        permvec.push_back(i);
    std::shuffle(
        permvec.begin(), permvec.end(), std::mt19937(std::random_device()()));
    csv.addRow(csvtmp.getRow(0));
    for (int i = 0; i < actualNumRows; i++) {
        csv.addRow(csvtmp.getRow(permvec[i] + 1));
    }
    for (int i = 0; i < csv.getNumRows() - 1; i++) { //-1 to account for header
        for (int j = 0; j < csv.getNumCols(i); j++) {
            picture[i] = ofTrim(csv[i + 1][0]);
            stimulus[i] = ofTrim(csv[i + 1][1]);
            correctresponse[i] = stoi(ofTrim(csv[i + 1][2]));
            distance[i] = stoi(ofTrim(csv[i + 1][3]));
            emotion[i] = stoi(ofTrim(csv[i + 1][4]));
        }
    }
    blank.load("blank.png");
}

void ofApp::update() {
    if (readyForNext) {
        pic.load(picture[rowCount]);
        stim.load(stimulus[rowCount]);
        readyForNext = false;
    }
}

static void draw(ofImage &image) {
    image.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2,
        ofGetHeight() / 2);
}

void ofApp::draw() {
    if (init) {
        ofRectangle rect =
            verdana14.getStringBoundingBox(instructionText, 0, 0);
        verdana14.drawString(instructionText, ofGetWidth() / 2 - rect.width / 2,
            ofGetHeight() / 2 - rect.height / 2);
    } else if (FirstPicFlag) {
        FirstPicFlag = false;
        timer.invokeAfter(0ms, [&]() {
            ::draw(pic);
            timer.invokeAfter(firstPictureDuration, [&]() {
                stimTime = ofGetSystemTimeMillis();
                ::draw(stim);
                timer.invokeAfter(stimulusDuration, [&]() {
                    ::draw(pic);
                    timer.invokeAfter(secondPictureDuration, [&]() {
                        ::draw(blank);
                        timer.invokeAfter(blankDuration, [&]() {
                            rowCount += 1;
                            readyForNext = true;
                            FirstPicFlag = true;
                            noMore = true;
                            if (rowCount >= actualNumRows - 1) {
                                ofExit();
                            }
                        });
                    });
                });
            });
        });
    }
    timer.check();
}

void ofApp::keyPressed(int key) {
    string mystr;
    if (key == ' ') {
        init = false;
        FirstPicFlag = true;
        ofSetBackgroundAuto(false);
    }
    if (key == threekey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = threekey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] =
            std::to_string(correctresponse[rowCount] == 3 - 2);
    }
    if (key == fourkey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = fourkey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] =
            std::to_string(correctresponse[rowCount] == 4 - 2);
    }
    if (key == fivekey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = fivekey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] =
            std::to_string(correctresponse[rowCount] == 5 - 2);
    }
    if (key == sixkey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = sixkey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] =
            std::to_string(correctresponse[rowCount] == 6 - 2);
    }
}

void ofApp::exit() {
    string filetime = "AS3out" + ofGetTimestampString() + ".csv";
    csv.save(filetime);
    ofLog() << "exit";
}
