# ZED-Rover
This project uses the ```zed-ros2-wrapper```. To initiliaze after cloning,
use rosdep for packages, and then build with ```colcon build --symlink-install --cmake-args=-DCMAKE_BUILD_TYPE=Release --parallel-workers $(nproc)```

some commands: 
```ros2 launch zed_wrapper zed_camera.launch.py camera_model:=zed```