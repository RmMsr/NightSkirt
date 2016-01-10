Overview
--------

Extra layer of fabric containing the electronics. Get's sewed above the inner
skirt layer. So electronics are hidden, but LEDs shine through.

    +------------------------------------------------+
    |                                                |
    |                                     Battery    |
    |                                                |
    |                 Microcontroller                |
    |                                                |
    |     LED Driver A       :     LED Driver B      |
    |                        :                       |
    | *   *   *   *   *   *  :*   *   *   *   *   *  |  Line 2
    |   *   *   *   *   *   *:  *   *   *   *   *   *|  Line 1
    | *   *   *   *   *   *  :*   *   *   *   *   *  |  Line 0
    |                        :                       |
    +------------------------------------------------+
    Back        Left      Front       Right       Back

Fabric
------

A dark trapezoid piece light and still robust cloth.

  * Lines: 3
  * LEDs per Line: 12
  * Max width: 119 cm
  * Max height: 65 cm

LED distribution:

  * Line 2: 45 cm from bottom 114.0 cm long, LED each 9.5 cm, left offset 2,4 cm
  * Line 1: 30 cm from bottom 116.0 cm long, LED each 9.7 cm, left offset 7.3 cm
  * Line 0: 15 cm from bottom 118.0 cm long, LED each 9.8 cm, left offset 2,5 cm

LEDs
----

36 x cold white LED 20 mA (3.2 V drop)
2 x I2C LED Drivers SN3218

Microcontroller
---------------

Arduino Lilypad USB

As Arduino has only 1 pair of I2C pins for SCL (clock) and SDA (data) we use
a software I2C library to control the 2nd LED driver.

Battery
-------

A lightweight USB 2000 mAh Powerbank (5.2 V, 55 g, USB A connector)

Connections
-----------

In order to keep the fabric soft all connections are made of eigther 
conductive thread or thin isolated wires. The thread is sewed and knotted 
the wire sewed and soldered.

