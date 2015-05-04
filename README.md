# _Kinetic ToPoGo_

Robot website: http://cmsc838f-s15.wikispaces.com/kinetic-topogo
Youtube video: https://www.youtube.com/watch?v=IuHxXKFdOlw

_Description: Control your robot, differently_
The C# code tries to read the exact position of each joint using a Microsoft Kinect so that it could calculate and send our hands movements to the arduino.
Commands are sent through a SerialPort communication between the computer that runs the C# program and the Arduino.
The arduino code translates the commands received from its Serial Port into PWM analog voltages that would set the position of each servo motor.

## Project Setup:

_Materials Used_ 

1. Microsoft Kinect V1 x 1
2. Servo Motors x 6
3. Arduino Uno
4. Cardboards
5. Wires, glue and other misc material

_Examples of common tasks_

> e.g.
> 
> - Say "sit down": the robot would sit down and start mimicing your hand gestures
> - Say "Follow": the robot tries to walk by following your body movements
> - Say "Shake": the robot will shake its butt ┍㋛┛
> - Say "Move": the robot moves in a random way
> - Say "Crawl": the robot would simply crawl
