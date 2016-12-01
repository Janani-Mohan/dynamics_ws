# dynamics_ws

WPI RBE-500 Dynamics_Project_2016 :

Contributors

Ankur Agrawal

Janani Mohan

Praneeta Mallela

Sathya Narayanan

Project Goal : Accurate BGA chip placement on a PCB using ABB IRB 120 Industrial robot

Simulation: The entire simulation is in Gazebo. The ROS packages irb120 and irb120_perception executes the trajectory planning and the image processing of the entire robot.A vacuum suction pump is attached onto the end effector and it is activated during pick operation and deactivated during place operation. Currently the detection of BGA chips at zero degree orientation is picked up and placed at the same orientation on the PCB. Future Goal : To work on different sizes of BGAs and different orientations of BGAs.

Dependent Packages to be installed:

ros-indigo

gazebo2 / also works in gazebo7

ros-controllers

sudo apt-get install ros-indigo-gazebo-ros-pkgs ros-indigo-gazebo-ros-control

eigen library

Link : http://eigen.tuxfamily.org/index.php?title=Main_Page

ros-gazebo-pkgs for vaccum gripper plugins

Link : https://github.com/ros-simulation/gazebo_ros_pkgs

Usage:

Build Workspace : catkin_make
source devel/setup.bash
Launch gazebo : roslaunch irb120-gazebo irb120_gazebo.launch
Run the Node for trajectory planning :rosrun irb120 irb120_node
Run the Node for image processing: rosrun irb120_perception irb120_perception_node
