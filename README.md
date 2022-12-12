This is the repo for the Self-Balancing Bicycle senior design project at Drexel University

There are two executables you can run in this directory.

test.cpp:
run "make test" -> NOTE: since the file interactive.cpp also has a main function, make sure to comment it out before compiling
run "./test"

This program will go through and test all of the currently working aspects of the bike

interactive.cpp:
run "make interactive" -> NOTE: since the file test.cpp also has a main function, make sure to comment it out before compiling
run "./interactive"

This program is an interactive program where you can make the various parts of the bike move according to your input.

Three other things to note:
1. The GPIO class was not written by us. It is code that was provided to us from the textbook "Exploring BeagleBone 2nd Edition". If you run into any issues with this class, please refer to this textbook for additional help.
2. The code for the servo motor is based on the code in the directory ~/servoLibs/SDK_Examples. We did not change any of the comments, so if you need help understanding what is happening please refer to their documentation.
3. The bash script "setup.sh" is for setting up various features on the beaglebone. Unlike an Arduino, a lot of features like PWM and writing analog values are not enabled by default, so you need to do special configuration to set this up. All of the necessary commands should be in the file, and we recommend running them one at a time as opposed to running the script. 

Edit 12/12/2022: Repository cloned from https://github.com/pdhuddy/bike.git

