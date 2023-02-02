# EMG controlled vehicle
An electromyography (EMG) controlled vehicle is intended for people with disabilities and/or decreased muscle control. It consists of EMG sensors that pick up nerve signals from the user and is used to control a mobility device. As part of prototyping, this vehicle was simulated in a virtual environment using the Gazebo simulator.

Four separate sensors were used, and each of these were mounted on different muscle groups for optimal sensor input. Sensor data was then sent to an Arduino Nano that performed signal processing. Finally, the Nano passed a signal to the virtual environment through a computer where the vehicle could be controlled.
