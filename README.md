# BBot Arduino Sketch
This is simple Arduino sketch for BBot skid-steering base.

The sketch have following basic implementations:
* motor PWM and direction control
* motor angular velocity control
* motor stall detection with motor disabling
* wheel encoder odometry with pose and velocity
* battery voltage measurement
* serial datagram transport level protocol with error detection
* application level protocol with control timeout detection

The sketch was designed for and tested on following configuration:
* Arduino DUE (because we need 4 interrupt pins for encoders and fast enough interrupt execution)
* 2 cheap dual H-bridges (pins: PWM, ENA, ENB per motor)
* 12V motors with gearbox (530 RPM output) and 2-channel encoders (about 500 ticks per revolution, pins: CHA, CHB)
* battery voltage probe with 100 kOhm : 1 MOhm voltage divider (analog pin BAT)
* control algorithms are executed with 20 Hz frequency

## Usage
0. Clone sketch and one it with Arduino IDE (you may need to install Arduino DUE libraries)
1. Set right pins and adjust parameters in bbot_arduino.ino file.
> Note: if your platform's parameters are different, you may want to create new sketch and add classes one by one and use Serial.print for debug.
2. ???????
3. PROFIT

## Documentation
The code is pretty self-explanatory, you may even find some comments in it. Following file descriptions will help you find out where to start:
* bbot_arduino.ino - the main file with all parameters
* battery.h/cpp - battery voltage measurement, provides battery voltage
* drivecontroller.h/cpp - drive controller, uses linear and angular target velocity and provides target EI (Encoder Increment per period) for motor controller
* encoder.h/cpp - encoder, provides current EI
* motor.h/cpp - motor, uses signed PWM to control motor
* motorcontroller.h/cpp - motor controller, uses target EI and provides PWM for motor, checks if motor stalls and disables it 
* odometry.h/cpp - odometry, provides pose and velocity, uses current EI
* period.h/cpp - utility class for executing code with specified period
* protocol.h/cpp - application level protocol on top of serial datagram transport protocol
* serialdatagram.h/cpp - serial datagram library, provides datagram protocol over serial protocol (such as UART) with error detection using CRC-8
