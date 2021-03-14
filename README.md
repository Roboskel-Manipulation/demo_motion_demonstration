# Motion demonstration and replication by a UR3 cobot

## Description
This package launches the necessary nodes for a motion demonstration and replication by a UR3 cobot.

<img src="https://github.com/Roboskel-Manipulation/demo_motion_demonstration/blob/main/pipeline_git.png" />

### Human Position Tracking
The motion demonstration is based on visual input. An RGB-D camera is used for human tracking. [Openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) is used for recognising 2D human joint positions. The 3D position of the wrist is then acquired via the associated point cloud information. The 3D  coordinates are expressed in a static reference frame and then used as potential trajectory points for the control of the robot's end-effector (EE) position. This part of the pipeline is implemented in [openpose_3D_localization](https://github.com/Roboskel-Manipulation/openpose_3D_localization).

### Robot Trajectory Generation
Once the human movement onset is detected, every human (right) wrist 3D position that becomes available is first checked to avoid outliers (points that diverge over 10cm from the previous one). When the human movement end is detected, points corresponding to stagnation and could not be filtered during the movement detection procedure are further removed. The final filtered 3D human positions can be smoothed using Bezier Curves, if asked by the user. Filtered 3D human positions or the corresponding Bezier curves are translated to UR3 EE positions considering the relative position between the human wrist and the EE effector. The translated 3D EE positions are accepted by an action server, which publishes them at appropriate publishing rates according to their type. Then, the desired EE 3D position are checked in terms of robot limits to ensure that they do not lead to self-collision or over-extension of the robot arm. Valid EE positions are considered as desired positions and used for the calculation of the robot commanded velocities (see below).  This part of the pipeline is implemented in the [trajectory_process_utils](https://github.com/Roboskel-Manipulation/trajectory_process_utils) package apart from the action server which is implemented in the []() package.
 
### Robot Motion Generation
 
The desired robot positions are used as input to the [cartesian_trajectory_tracking](https://github.com/Roboskel-Manipulation/cartesian_trajectory_tracking) package which generates the commanded EE velocities published to the [CVC](https://github.com/Roboskel-Manipulation/manos/tree/updated_driver/manos_cartesian_control). The output of the CVC is fed to the UR3 robot driver.

### Pipeline demonstrations 

## Run
`roslaunch demo_motion_demonstration demo_motion_demonstration.launch`

## Arguments
Input modality
* visual_input: True if using visual input to produce the 3D keypoints either using the real camera or a rosbag. False if using already obtained 3D keypoints.
* sim: True if using visual input from a rosbag.
* live_camera: True if frames are generated by an RGB-D camera (False if they are generated by rosbags)
NOTE: sim and live_camera arguments need to be set only if visual_input is set to true.

Trajectory preprocessing
* filter: True if removing points corresponding to stagnation.
* smooth: True is smoothing the trajectory using Bezier Curves.



