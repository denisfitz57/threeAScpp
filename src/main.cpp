#include "threeAS-task.hpp"
#include "ofMain.h"
#include "ofApp.h"

namespace three_as {
namespace {
class OpenFrameworks : public Framework {
  public:
    OpenFrameworks() {
        verdana14.load("verdana.ttf", 14, true, true);
        verdana14.setLineHeight(18.0f);
        verdana14.setLetterSpacing(1.037);
    }
    void eventLoop() override { ofRunApp(new ofApp()); }

    void display(const std::string &s) override {
        const auto rect{verdana14.getStringBoundingBox(s, 0, 0)};
        verdana14.drawString(s, ofGetWidth() / 2 - rect.width / 2,
            ofGetHeight() / 2 - rect.height / 2);
    }

  private:
    ofTrueTypeFont verdana14;
};

void main() {
    OpenFrameworks framework;
    runTask(framework);
}
}
}

//========================================================================
int main() {
    ofSetupOpenGL(1920, 1080, OF_WINDOW); // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    three_as::main();
}
