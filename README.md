# Uncanny eyes Halloween skull

Build a Halloween skull with living eyes and moving jaw.

Full instruction: https://www.instructables.com/Uncanny-Eyes-Halloween-Skull-Animatronic/

The eyes are inspired by [Adafruit’s uncanny eyes](https://github.com/adafruit/Uncanny_Eyes/). The code was adopted is an adaption of the [TFT_eSPI example](https://github.com/Bodmer/TFT_eSPI/).

It contains 240px eyes instead of 128px to run on two round 1.28" TFT GC9A01 display modules with 240x240 resolution.

software prerequisits
- [Arduino IDE](https://www.arduino.cc/en/software)
- [TFT_eSPI library](https://www.arduino.cc/reference/en/libraries/tft_espi/)
- [ESP32Servo library](https://www.arduino.cc/reference/en/libraries/esp32servo/)

hardware required
- 1x ESP32 (e.g. Expressif ESP32-WROOM-32D) ([example](https://www.aliexpress.com/item/4000535213799.html))
- 2x 1.28" TFT LCD Display Module Round RGB 240*240, GC9A01 driver ([example](https://www.aliexpress.com/item/1005004340894235.html))
- realistic human skull ([example](https://www.aliexpress.com/item/32953218173.html))

you will also need
- jumper wires to connect everything, optionally a breadboard to test
- cables, female wire connector and crimping tool (to create Y-cables)
- a rotary tool, ideally with flex shaft, to open the skull and make space for the displays
- a power supply and USB cable

for a moving jaw you need
- small servo (9g)
- soldering iron
- to say goodbye to your USB cable mentioned above

## wiring

### display
| ESP32 pin | TFT 1 | TFT 2 |
|-----------|-------|-------|
| 23        | SDA   | SDA   |
| 18        | SCL   | SCL   |
| 2         | DC    | DC    |
| 4         | RST   | RST   |
| 22        | CS    |       |
| 21        |       | CS    |
| +3V       | VCC   | VCC   |
| GND       | GND   | GND   |

### servo

| ESP32 pin | Servo  | USB cable |
|-----------|--------|-----------|
| 26        | signal |           |
| GND       | black  |           |
|           | red    | red*      |

You could connect the servo’s red wire to the 5V pin, but…don’t.
The displays will flicker during movement.
Yes, you could add a capacitor to compensate this.
It worked with 5000 μF to remove the flickering, but I decided to do it right.

The final solution will require you to cut open the USB cable and connect the red wire,
if it is +5V, with the servo directly before it gets into the ESP32.

I used a jumper wire with one male side (to be plugged into the servo),
ripped off the other side and soldered it to the USB cable.

## build steps
### test setup

1. connect ESP32 and displays using a breadboard
2. compile and upload code to the ESP32 board

### after successful run of two eyes

1. replace breadboard connection with Y-cables, female-to-double-female and test
2. open the skull
3. remove inner skull’s eye parts using the rotary tool to make space for the displays

Try to fit the displays with the connectors on top.
You will need to remove less and it saves space for the servo.
Repeat until the two displays fit.
Once done…

1. Fixate the displays in their final position, e.g. by using play dough
2. Apply hot glue to fixate the displays
3. Drill a hole at the skull’s back to be able to connect the USB cable

### adding movable jaw (optional)

1. drill a hole through the left mental foramen hole in the jaw
2. imagine a line between the drilled hole and a servo arm inside the skull, cut it open
3. glue the servo into the skull, plenty of hot glue will do
4. connect a rigid wire
   - to the servo
   - to jaw
5. move the servo to the closed position and connect both wires
6. check and adjust angles

### final steps

1. secure the cables with hot glue if needed, so that only USB power supply exits the skull
2. tidy up so that the wires do not interfere with the servo arm
3. close the skull