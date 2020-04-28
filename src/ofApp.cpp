#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    string instructionText = "Press the number keys 3, 4, 5, or 6 \naccording to HOW MANY numbers you see.";

	ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
	csvtmp.load("3as.csv");
    saveTime = 1000000;
	actualNumRows = csvtmp.getNumRows()-1;
	for (int i = 0; i < actualNumRows ; i++) permvec.push_back(i);
	std::random_shuffle(permvec.begin(), permvec.end());
    csv.addRow(csvtmp.getRow(0));
    for (int i = 0; i < actualNumRows; i++) {
        csv.addRow(csvtmp.getRow(permvec[i] + 1));
    }
	for (int i = 0; i < csv.getNumRows() - 1; i++) { //-1 to account for header
		for (int j = 0; j < csv.getNumCols(i); j++) {
			picture[i] = ofTrim(csv[i+1][0]) ;
			stimulus[i] = ofTrim(csv[i+1][1]);
            correctresponse[i] = stoi(ofTrim(csv[i+1][2]));
            distance[i] = stoi(ofTrim(csv[i+1][3]));
			emotion[i] = stoi(ofTrim(csv[i+1][4]));
		}
	}
    blank.load("blank.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	if (readyForNext) {
		pic.load(picture[rowCount]);
		stim.load(stimulus[rowCount]);
        readyForNext = false;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (saveTime + pic1dur + stimdur + pic2dur + endblankdur < ofGetFrameNum()) {
        saveTime = ofGetFrameNum();
        //ofLog() << saveTime; 
        rowCount += 1;
        //ofLog() << "inc rowcount\n";
        readyForNext = true;
        FirstPicFlag = true;
        noMore = true;
        if (rowCount >= actualNumRows - 1) {
            ofExit();
        }
    }
    else if (saveTime + pic1dur + stimdur + pic2dur < ofGetFrameNum()) {
        //ofLog() << ofGetFrameNum();
        showBlank = true;
        showPic1 = false;
        showStim = false;
        showPic2 = false;
    }
    else if (saveTime + stimdur + pic1dur < ofGetFrameNum()) {
        //ofLog() << ofGetFrameNum();
        showPic2 = true;
        showBlank = false;
        showPic1 = false;
        showStim = false;
    }
    else if (saveTime + pic1dur < ofGetFrameNum()) {
        //ofLog() << ofGetFrameNum();
        showStim = true;
        showPic1 = false;
        showPic2 = false;
        showBlank = false;
        if (stimflag) {
            stimTime = ofGetSystemTimeMillis();
            stimflag = false;
        }
    }
    else if (saveTime < ofGetFrameNum()) {
        if (FirstPicFlag) {
            //ofLog() << ofGetFrameNum();
            stimflag = true;
            FirstPicFlag = false;
            showPic1 = true;
            showStim = false;
            showPic2 = false;
            showBlank = false;
        }
    }
    else {
    }

    if (showBlank) {
        blank.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
    }
    else if (showPic2) {
        pic.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
    }
    else if (showStim) {
        stim.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
    }
    else if (showPic1) {
        pic.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
    }
    if (init) {
        ofRectangle rect = verdana14.getStringBoundingBox(instructionText, 0, 0);
        //ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
        verdana14.drawString(instructionText, ofGetWidth()/2 - rect.width/2, ofGetHeight()/2 - rect.height/2);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    string mystr;
    if (key == ' ') {
        saveTime = ofGetFrameNum() + 6;
        init = false;
    }
    if (key == threekey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = threekey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] = std::to_string(correctresponse[rowCount] == 3-2);
    }
    if (key == fourkey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = fourkey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] = std::to_string(correctresponse[rowCount] == 4-2);
    }
    if (key == fivekey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = fivekey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] = std::to_string(correctresponse[rowCount] == 5-2);
    }
    if (key == sixkey && noMore) {
        noMore = false;
        respTime = ofGetSystemTimeMillis() - stimTime;
        mystr = sixkey;
        csv[rowCount + 1][5] = mystr;
        csv[rowCount + 1][6] = std::to_string(respTime);
        csv[rowCount + 1][7] = std::to_string(correctresponse[rowCount] == 6-2);
    }


}

void ofApp::exit() {
    string filetime = "AS3out" + ofGetTimestampString() + ".csv";
    csv.save(filetime);
    ofLog() << "exit";
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
