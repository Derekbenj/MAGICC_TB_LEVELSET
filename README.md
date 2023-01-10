For controlling the turtlebot via ROS 1 (Noetic on my computer, Kinetic on the Turtlebots). The difference in ROS versions shouldn't matter since we're only passing
geometry_msg/Twist messages to the turtlebots currently

All that needs to be done to create a catkin workspace for further ROS development is to pull this code, and then move into the workspace titled "control_testing" and type "catkin_make". An extra folder exists alongside the catkin workspace folder only because all arduino code must be held in it's own folder. Because the arduino code relies on a custom message defined in our catkin project titled "keys", you must source the catkin workspace using "source /devel/setup.bash" prior to running the arduino code. If you forget to do this, you'll likely see an error from ROS telling you it's failing to communicate with the Arduino.

Current State:
    1) Arduino code works and can be uploaded for measurements. Doesn't measure lux, but scales so every arduino should be roughly equally sensitive to light.
    2) Code for experimenting with ROS interfacing written in C++ and Python (C++ code simply listens for simple keypresses and is unrelated to the controller project, while the python code interfaces with the arduino to change it's state in the state machine and listen for measurements).
    3) I haven't figured out how to write the arduino interface with ROS 2 yet...
    4) Controller code written for interfacing with the turtlebot node.

Useful Notes:
    1) Don't eat up too much of the dynamic memory in the Arduino code if you modify it. Any code using 75% or more starts warning me that the arduino may malfunction, and often it does.
    2) The control testing code should be run with the simulation.py module (which will open a ROS node) and will pause until the turtlesim_node is up and running if started first.

Beta Feature in the works: Connecting Optitrack Cameras and Connecting the Turtlebots
On the optitrack computer, start ROSCORE, then start the node by typing rosrun optitrack_vrpn node _host:=192.168.1.3
Tell my lab computer to use another ros computer as the core. That's done by changing the environmental variable ROS_MASTER_URI=http://192.168.1.0.254 (maybe it's 192.168.1.3 but Jake thinks that's for the modem)
The node I'm going to want to subscribe to is a pose variable called /raph_ned or /raph_enu... these both use a geometry_msgs/PoseStamped message