#include "threeAS-Task.hpp"
#include "ofMain.h"
#include "ofApp.h"

namespace three_as {
namespace {
class OpenFrameworks : public Framework {
  public:
    OpenFrameworks() {
        ofSetupOpenGL(1920, 1080, OF_WINDOW);
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

    void subscribe(Listener *s) override { listener = s; }

  private:
    ofTrueTypeFont verdana14;
    Listener *listener{};
};

void main() {
    OpenFrameworks framework;
    Task task{framework};
    task.run();
}
}
}

int main() { three_as::main(); }
