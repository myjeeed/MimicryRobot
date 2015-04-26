# _Kinetic ToPoGo_
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
> - Say "Hello": the robot would shake its body and hads
> - Say "Follow": the robot tries to follow you
> - Say "Move": the robot moves in a random way

## License
