#include "threeAS-task.hpp"
#include "ofMain.h"
#include "ofApp.h"

namespace three_as {
namespace {
class OpenFrameworks : public Framework {
  public:
    void eventLoop() override { ofRunApp(new ofApp()); }
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
