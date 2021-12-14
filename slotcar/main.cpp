// some libraries
#include "settings.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "led.h"
#include "usb.h"
#include "motor.h"
#include "bluetooth.h"

#include "LSM9DS1.h"
#include "LSM9DS1_registers.h"

#include "wyk_stdio.h"
 

ISR(BLUETOOTH_RX_vect)
{
    uint8_t tmp = BLUETOOTH_DATA;
    usb_putc(tmp);
}

ISR(USB_RX_vect)
{
    uint8_t tmp = USB_DATA;
    bluetooth_putc(tmp);
}

int main(void)
{
    // bluetooth_servise();
    usb_init();
    bluetooth_init();
    i2c_init();
    _delay_ms(100);
    sei();

    // attributes of slotcar
    LSM9DS1 imu;
    LED led;
    Motor motor;
    

    if (!imu.begin())
    {
        usb_puts((char *) "Failed to communicate with LSM9DS1.\n"); // if the car is not connected, it sends an error message
        while (1)
            ;
    }

    imu.calibrate();// to put values to 0 in order to do measures

    while (1)
    {
        // we read the values needed after
        imu.readTemp();
        imu.readMag();
        imu.readGyro();
        imu.readAccel();
        
        // we delay the values to make it more efficient
        _delay_ms(1);

        // we take gyroscope values (only z) and adapt the speed to it 
        if ( imu.calcGyro(imu.gz) <= 40 ){ //when gyroscope is under 40 (straight line), the speed is fast (75)
            motor.forward(80);
            
			_delay_ms(0.1);
            // the leds forward are all on, the leds backward are off
            led.forward_left(true);
            led.forward_right(true);
            led.reverse_left(false);
            led.reverse_right(false);
        }    
        //when gyroscope values are more than 40 (in curves), the speed is decreased (60)
        else if ( imu.calcGyro(imu.gz) >= 40 ){
            motor.forward(65);
            
            // all leds are turned on         
            led.forward_left(true);
            led.forward_right(true);
            led.reverse_left(true);
            led.reverse_right(true);
        }   
        //when gyroscope values are over 120 (big curves), stop (or almost) the car
        else if ( imu.calcGyro(imu.gz) >= 120 ) {
            
            motor.forward(50);
            
            // all leds are turned on
            led.forward_left(true);
            led.forward_right(true);
            led.reverse_left(true);
            led.reverse_right(true);
        }    
       
       
        
        printf("deg/s: %3.0f %3.0f %3.0f  |  ", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz)); // return all gyroscope values
        printf("a [g]: %2.1f %2.1f %2.1f  |  ", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az)); // return all acceleration values
        printf("B [uT]: %4.0f %4.0f %4.0f  |  ", imu.calcMag(imu.mx) * 100, imu.calcMag(imu.my) * 100, imu.calcMag(imu.mz) * 100); // return all magnitude values
        printf("T [C]: %2.1f\r\n", 25.0 + ((double) imu.temperature) / 16.0); // return temperature values
    }
}


