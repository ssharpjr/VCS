/*
Arduino pins used.

    ~   ~ ~     ~  ~  ~
1 2 3 4 5 6 7 8 9 10 11 12 13 
    X X X X X X X X  X  X  X

14 15 16 17 18 19
A0 A1 A2 A3 A4 A5
   X  X  X  X  X


WiFi Shield:
Digital Pins 4, 7, 10, 11, 12, 13.
Pin 4 - SD Card (if used).
Pin 7 - Handshake between Arduino and WiFi Shield.
Pin 9 - Tied to L9 for indication.
Pin 10 - Selects the HDG104 wifi chip.
Pin 11, 12, 13 - ICSP Header.

Cam Switch:
A1-A5 - Connected to the 5 positions as digital pins 15-19.

LEDs:
Digital Pins 3, 5, 6, 8, 9
Network LED = 8
Power LED = 9 (tied to L9 on wifi shield
Shift Register Pins:
  Latch Pin: 5
  Clock Pin: 6
  Data Pin:  3

*/
