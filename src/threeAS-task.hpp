#ifndef THREEAS_TASK_HPP_
#define THREEAS_TASK_HPP_

#include <string>

namespace three_as {
constexpr auto instructions{
    "Press the number keys 3, 4, 5, or 6 according to\n\nHOW MANY numbers "
    "you see.\n\nPress space to begin."};

class Framework {
  public:
    class Listener {
      public:
        virtual ~Listener() = default;
    };
    virtual ~Framework() = default;
    virtual void subscribe(Listener *) = 0;
    virtual void eventLoop() = 0;
    virtual void display(const std::string &) = 0;
};

class Task : public Framework::Listener {
  public:
    explicit Task(Framework &);
    void run();
    void frameUpdate();
    void keyPressed(int key);

  private:
    Framework &framework;
    bool keyPressed_{};
};
}

#endif
