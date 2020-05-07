#ifndef THREEAS_TASK_HPP_
#define THREEAS_TASK_HPP_

namespace three_as {
class Framework {
  public:
    virtual ~Framework() = default;
    virtual void eventLoop() = 0;
};

void runTask(Framework &);
}

#endif
