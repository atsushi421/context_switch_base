# sample_ros_app

## Setup

1. Please change the following file to match your environment:
   - [sample_app/CMakeLists.txt](./sample_app/CMakeLists.txt)
   - [pmu_analyzer/config.yaml](./pmu_analyzer/config.yaml)
2. `colcon build`

## Run

```bash
$ PMU_ANALYZER_CONFIG_FILE=/path/to/sample_app/pmu_analyzer/config.yaml ros2 run sample_app timer_node
```
