#!/usr/bin/env bash
colcon build && source install/setup.bash
ros2 launch teleoperator main.launch.py
