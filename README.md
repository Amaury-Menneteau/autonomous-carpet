# Digital electronics 2 final project : Autonomous-car



## Project objectives :

The project has for goal to implement a code in C language on an ATmega328PB in a small car in order to make the car autonomous on tracks.

Here is the flowchart of our project :



## Hardware components :

* ATmega328PB : microcontroller
* CP2102/9 : a bus between UART and USB (for putty results)
* LSM9DS1 : inertial module that combine gyroscope, accellerometer and magnetometer
* TLE5206 : driver for motors
* A car


Here is the schema :


![arcarr](https://user-images.githubusercontent.com/91128744/145998473-1d193036-aa4d-477d-938d-53b1a619df0c.png)


## Code description

In our code, we included libraries that were used to bring function needed in the slotcar. 
You can find the main.cpp here : [main](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711577/main.txt)


List of librairies :

* bluetooth.h : the bluetooth doesn't work
* i2c.h : For bluetooth too
* [led.h](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711662/led.txt) : turn on or off the leds of the slotcar
* [LSMD9DS1.h](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711667/LSMD9DS1.txt),
* [LSMD9DS1 - types.h](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711669/LSMD9DS1.-.types.txt)
* [LSMD9DS1 - registers.h](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711672/LSMD9DS1.-.registers.txt)
: library used for the gyroscope, accelerometer and magnetometer (get values, calibrate)
* [motor.txt](https://github.com/Amaury-Menneteau/autonomous-carpet/files/7711675/motor.txt)
: library for motor settings (direction, power)

&nbsp;

The table of the functions used in this project:
|    FUNCTION NAME   |  PARAMETERS  |     RETURN   | APPLICATION                                                                                                                                                                                                                       |
|:------------------:|:------------:|:------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|      imu.calcgyro(...)     |     x,y and z values     |     values of x, y and z     | take values of gyroscope and return them.                                                                                                               |
|   imu.calibrate()   |     none     |     none     | set values of gyroscope to 0   |
|     led.forward_left(...),led.forward_left(...),led.reverse_left(...),led.reverse_right(...)    |     boolean true or false     |     none     | use to activate or desactivate leds of the car  |
|    motor.forward(...)   | uint8_t | none | set the power of the machine |

&nbsp;


## Video of our project (making and results)

