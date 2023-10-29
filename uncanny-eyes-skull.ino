// An adaption of the "UncannyEyes" sketch (see eye_functions tab)
// for the TFT_eSPI library but adapted for two 240x240 px displays.

// For wiring see the wiring folder.

// Configuration settings for the eye, eye style, display count,
// chip selects and x offsets can be defined in the sketch "config.h" tab.

// To increase performance DMA should stay enabled.
// Two 240x240 px displays run at 32 FPS.
#define USE_DMA

// Load TFT driver library
// Use the predefined user setup Setup46_GC9A01_ESP32 of the TFT_eSPI library.
// Either select via library/TFT_eSPI/User_Setup_Select.h or as you like.
// An update of the library will overwrite the file above.
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft;

#define BUFFER_SIZE 1024

#ifdef USE_DMA
  #define BUFFERS 2
#else
  #define BUFFERS 1
#endif

uint16_t pbuffer[BUFFERS][BUFFER_SIZE];
bool dmaBuf = 0;

typedef struct {
  int8_t  select;       // pin numbers for each eye's screen select line
  int8_t  wink;         // and wink button (or -1 if none) specified there,
  uint8_t rotation;     // also display rotation and the x offset
  int16_t xposition;    // position of eye on the screen
} eyeInfo_t;

#include "config.h"     // ****** CONFIGURATION IS DONE IN HERE ******

 // functions in the user*.cpp files, please enable one
extern void user_setup(void);
extern void user_loop(void);

#define SCREEN_X_START 0
#define SCREEN_X_END   SCREEN_WIDTH   // Badly named, actually the "eye" width!
#define SCREEN_Y_START 0
#define SCREEN_Y_END   SCREEN_HEIGHT  // Actually "eye" height

// A simple state machine is used to control eye blinks/winks:
#define NOBLINK 0       // Not currently engaged in a blink
#define ENBLINK 1       // Eyelid is currently closing
#define DEBLINK 2       // Eyelid is currently opening
typedef struct {
  uint8_t state;        // NOBLINK/ENBLINK/DEBLINK
  uint32_t duration;    // Duration of blink state (micros)
  uint32_t startTime;   // Time (micros) of last state change
} eyeBlink;

struct {                // One-per-eye structure
  int16_t tft_cs;       // Chip select pin for each display
  eyeBlink blink;       // Current blink/wink state
  int16_t xposition;    // x position of eye image
} eye[NUM_EYES];

uint32_t startTime;  // For FPS indicator

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect
  }  Serial.println("starting");

#if defined(DISPLAY_BACKLIGHT) && (DISPLAY_BACKLIGHT >= 0)
  // enable backlight pin, initially off
  Serial.println("backlight turned off");
  pinMode(DISPLAY_BACKLIGHT, OUTPUT);
  digitalWrite(DISPLAY_BACKLIGHT, LOW);
#endif

  user_setup();
  initEyes();

  Serial.println("initialising displays");
  tft.init();

#ifdef USE_DMA
  tft.initDMA();
#endif

  // raise chip select(s) so that displays can be individually configured
  digitalWrite(eye[0].tft_cs, HIGH);
  if (NUM_EYES > 1) digitalWrite(eye[1].tft_cs, HIGH);

  for (uint8_t e = 0; e < NUM_EYES; e++) {
    digitalWrite(eye[e].tft_cs, LOW);
    tft.setRotation(eyeInfo[e].rotation);
    tft.fillScreen(TFT_BLACK);
    digitalWrite(eye[e].tft_cs, HIGH);
  }

#if defined(DISPLAY_BACKLIGHT) && (DISPLAY_BACKLIGHT >= 0)
  Serial.println("backlight on");
  analogWrite(DISPLAY_BACKLIGHT, BACKLIGHT_MAX);
#endif

  startTime = millis();
}

void loop() {
  updateEye();
  // use user_loop, do not add things here
}
