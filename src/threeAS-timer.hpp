#ifndef THREEAS_TIMER_HPP_
#define THREEAS_TIMER_HPP_

namespace three_as {
class Screen {
  public:
    class Listener {
      public:
        virtual ~Listener() = default;
    };
    virtual ~Screen() = default;
    virtual void subscribe(Listener *) = 0;
};

class Timer : public Screen::Listener {
  public:
    explicit Timer(Screen &screen) { screen.subscribe(this); }
};
}

#endif
