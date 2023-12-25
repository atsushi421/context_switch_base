#include "rclcpp/rclcpp.hpp"
#include <pmu_analyzer.hpp>

class MyTimerNode : public rclcpp::Node {
public:
  MyTimerNode() : Node("timer_node") {
    pmu_analyzer::ELAPSED_TIME_INIT(session_name);
    pmu_analyzer::PMU_INIT();

    timer_ =
        this->create_wall_timer(std::chrono::milliseconds(300),
                                std::bind(&MyTimerNode::timer_callback, this));
  }

  ~MyTimerNode() {
    pmu_analyzer::PMU_CLOSE();
    pmu_analyzer::ELAPSED_TIME_CLOSE(session_name);
  }

private:
  std::string session_name = "session";
  rclcpp::TimerBase::SharedPtr timer_;

  void timer_callback() {
    static int trace_id = 0;
    pmu_analyzer::PMU_TRACE_START(trace_id);
    pmu_analyzer::ELAPSED_TIME_TIMESTAMP(session_name, 0, true, 0);

    // Dummy work
    long long sum = 0;
    for (int i = 0; i < 50000000; i++) {
      sum += i;
    }

    pmu_analyzer::ELAPSED_TIME_TIMESTAMP(session_name, 1, false, 0);
    pmu_analyzer::PMU_TRACE_END(trace_id);
    trace_id++;
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MyTimerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
