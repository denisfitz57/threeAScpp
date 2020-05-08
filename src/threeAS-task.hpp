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
        virtual void frameUpdate() = 0;
        virtual void keyPressed(int key) = 0;
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
    void frameUpdate() override;
    void keyPressed(int key) override;

  private:
    Framework &framework;
    bool keyPressed_{};
};
}

#endif
