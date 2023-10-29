/*

Function    ESP32 pin       TFT 1       TFT 2

 MOSI         23     ->     SDA   ->    SDA     // The TFT pin may be named DIN
 SCLK         18     ->     CLK   ->    CLK     // The TFT pin may be named SCK
 TFT_DC        2     ->     DC    ->    DC      // The TFT pin may be named AO
 TFT_RST       4     ->     RST   ->    RST
 CS 1         22     ->     CS                  // Connected to TFT 1 only 
 CS 2         21                  ->    CS      // Connected to TFT 2 only 
 +3V                 ->     VCC   ->    VCC
 GND                 ->     GND   ->    GND


ESP32       Servo

 +5V        red
 GND        black
 26         signal

 */
