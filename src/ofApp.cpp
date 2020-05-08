#include "ofApp.h"
#include <algorithm>
#include <random>

using std::literals::chrono_literals::operator""ms;

constexpr auto firstPictureDuration{400ms};
constexpr auto stimulusDuration{400ms};
constexpr auto secondPictureDuration{400ms};
constexpr auto blankDuration{1300ms};
// changing these may require a change to instructionText below
constexpr int threekey{'3'};
constexpr int fourkey{'4'};
constexpr int fivekey{'5'};
constexpr int sixkey{'6'};
constexpr auto instructionText{
    "Press the number keys 3, 4, 5, or 6 according to\n\nHOW MANY numbers "
    "you see.\n\nPress space to begin."};

void ofApp::setup() {
    ofSetFrameRate(60);
    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);

    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
    ofxCsv csvtmp;
    csvtmp.load("3as.csv");
    actualNumRows = csvtmp.getNumRows() - 1;
    std::vector<int> permvec(csvtmp.getNumRows());
    std::iota(permvec.begin(), permvec.end(), 0);
    std::shuffle(std::next(permvec.begin()), permvec.end(),
        std::mt19937(std::random_device()()));
    for (auto index : permvec)
        csv.addRow(csvtmp.getRow(index));
    for (int i = 0; i < csv.getNumRows() - 1; i++) { //-1 to account for header
        for (int j = 0; j < csv.getNumCols(i); j++) {
            picture.at(i) = ofTrim(csv.at(i + 1).at(0));
            stimulus.at(i) = ofTrim(csv.at(i + 1).at(1));
            correctresponse.at(i) = std::stoi(ofTrim(csv.at(i + 1).at(2)));
        }
    }
    blank.load("blank.png");
}

void ofApp::update() {
    if (readyForNext) {
        pic.load(picture.at(rowCount));
        stim.load(stimulus.at(rowCount));
        readyForNext = false;
    }
}

static void draw(ofImage &image) {
    image.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2,
        ofGetHeight() / 2);
}

void ofApp::draw() {
    if (init) {
        const auto rect{verdana14.getStringBoundingBox(instructionText, 0, 0)};
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

constexpr auto keyValue(int c) -> int {
    switch (c) {
    case threekey:
        return 3;
    case fourkey:
        return 4;
    case fivekey:
        return 5;
    default:
        return 6;
    }
}

void ofApp::keyPressed(int key) {
    if (key == ' ') {
        init = false;
        FirstPicFlag = true;
        ofSetBackgroundAuto(false);
    }
    if ((key == threekey || key == fourkey || key == fivekey ||
            key == sixkey) &&
        noMore) {
        noMore = false;
        csv.at(rowCount + 1).at(5) = std::to_string(key);
        csv.at(rowCount + 1).at(6) =
            std::to_string(ofGetSystemTimeMillis() - stimTime);
        csv.at(rowCount + 1).at(7) = std::to_string(static_cast<int>(
            correctresponse.at(rowCount) == keyValue(key) - 2));
    }
}

void ofApp::exit() {
    csv.save("AS3out" + ofGetTimestampString() + ".csv");
    ofLog() << "exit";
}
