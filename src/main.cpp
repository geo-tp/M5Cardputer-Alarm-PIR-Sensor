#include <Arduino.h>
#include <M5Cardputer.h>
#include <FastLED.h>

#define PIN_PIR    1  // Movement Detector
#define PIN_LED    21 // Builtin
#define NUM_LEDS   1

CRGB leds[NUM_LEDS]; // init RGB LED builtin
int lastState = -1; // Save last detection state

void displayMainView() {

  // Config
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(GREEN);
  M5Cardputer.Display.setFont(&fonts::Orbitron_Light_24);
  M5Cardputer.Display.setTextSize(1);

  // Main Title
  M5Cardputer.Display.drawRoundRect(0, 0, 240, 30, 5, TFT_DARKGREY); // frame around titlte
  M5Cardputer.Display.setTextColor(TFT_LIGHTGREY);
  M5Cardputer.Display.setTextSize(0.8);
  M5Cardputer.Display.setCursor(16, 3);
  M5Cardputer.Display.printf("Movement Detector");

  // Menu
  M5Cardputer.Display.drawRoundRect(0, 108, 240, 30, 4, TFT_DARKGREY); // frame around controls
  M5Cardputer.Display.setTextSize(0.65);
  M5Cardputer.Display.setCursor(14, 112);
  M5Cardputer.Display.printf("Brightness : < >   Vol : v ");

  // Volume area
  M5Cardputer.Display.drawRoundRect(153, 40, 82, 58, 5, TFT_LIGHTGREY);
  M5Cardputer.Display.setCursor(162, 45);
  M5Cardputer.Display.setTextSize(0.5);
  M5Cardputer.Display.setTextColor(TFT_DARKGREY);
  M5Cardputer.Display.println("VOLUME");

  // Volume value
  M5Cardputer.Display.setCursor(165, 60);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setTextColor(TFT_LIGHTGREY);
  M5Cardputer.Speaker.setVolume(40);
  M5Cardputer.Display.print(M5Cardputer.Speaker.getVolume());

  // Dessiner la lettre "V" à l'envers pour volume controls
  int startX = 218;  // Position de départ X
  int startY = 119;  // Position de départ Y
  int height = 8;    // Hauteur de la lettre
  int width  = 10;   // Largeur de la lettre
  M5.Lcd.drawLine(startX, startY + height, startX + width / 2, startY, TFT_LIGHTGREY); // Ligne gauche
  M5.Lcd.drawLine(startX + width / 2, startY, startX + width, startY + height, TFT_LIGHTGREY); // Ligne droite
}

void displayVolume(uint8_t volume) {
    M5Cardputer.Display.fillRect(155, 65, 68, 25, BLACK); // reset area
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setTextColor(TFT_LIGHTGREY);
    M5Cardputer.Display.setCursor(165, 60);
    M5Cardputer.Display.print(volume);
}

void displayDetection(int state) {
    if (state == LOW) { // No move
      M5Cardputer.Display.fillRect(0, 40, 145, 58, BLACK);
      M5Cardputer.Display.drawRoundRect(5, 40, 140, 58, 5,  GREEN);
      M5Cardputer.Display.setCursor(22, 55);
      M5Cardputer.Display.setTextColor(GREEN);
      M5Cardputer.Display.setTextSize(0.9);
      M5Cardputer.Display.println("No move");
      return;
    }

    // Movement detected
    M5Cardputer.Display.fillRect(0, 40, 145, 58, BLACK); // reset area
    M5Cardputer.Display.fillRoundRect(5, 40, 140, 58, 5, RED); // frame around
    M5Cardputer.Display.setTextColor(TFT_LIGHTGREY);
    M5Cardputer.Display.setCursor(23, 48);
    M5Cardputer.Display.setTextSize(0.75);
    M5Cardputer.Display.println("Movement");
    M5Cardputer.Display.setCursor(30, 70);
    M5Cardputer.Display.println("detected");  
}

void toggleLED() {
  if (M5Cardputer.Display.getBrightness() != 0) {
    FastLED.show(); // If screen is on, led is on
  } else {
    FastLED.clear(true); // led off
  }
}

void handleKeyboard() {
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      // VOLUME UP
      if (M5Cardputer.Keyboard.isKeyPressed(';')) {
        uint8_t volume = M5Cardputer.Speaker.getVolume();
        if (volume+20 < 255) {
            volume += 20;
        } else {
          volume = 255;
        }
        displayVolume(volume);
        M5Cardputer.Speaker.setVolume(volume);
      }

      // VOLUME DOWN
      else if (M5Cardputer.Keyboard.isKeyPressed('.')) {
        uint8_t volume = M5Cardputer.Speaker.getVolume();
        if (volume-20 > 0) {
            volume -= 20;
        } else {
          volume = 0;
        }
        displayVolume(volume);
        M5Cardputer.Speaker.setVolume(volume);
      }

      // BRIGHTNESS UP
      else if (M5Cardputer.Keyboard.isKeyPressed('/')) {
        uint8_t brightness = M5Cardputer.Display.getBrightness();
        if (brightness+20 < 255) {
            brightness += 20;
        } else {
          brightness = 255;
        }
        M5Cardputer.Display.setBrightness(brightness);
      }

      // BRIGHTNESS DOWN
      else if (M5Cardputer.Keyboard.isKeyPressed(',')) {
        uint8_t brightness = M5Cardputer.Display.getBrightness();
        if (brightness-20 > 0) {
            brightness -= 20;
        } else {
          brightness = 0;
        }
        M5Cardputer.Display.setBrightness(brightness);
      }
    }
  }
}

/*
##############################################################################################
#                                                                                            #
#                                      SETUP & LOOP                                          #
#                                                                                            #
##############################################################################################
*/

void setup() {
  auto cfg = M5.config(); // M5 default config
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Speaker.setVolume(10);

  // Initialiser mvmnt detector
  pinMode(PIN_PIR, INPUT); // Configurer la broche du détecteur PIR comme entrée

  // Initialiser la LED BUILTIN à l'état éteint
  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, 1);

  // Display the main frame
  displayMainView();
}

void loop() {

  // Update state
  M5Cardputer.update();

  // Lire l'état du détecteur de mouvement
  int motionState = digitalRead(PIN_PIR);
  
  // Handle brightness/volume controls
  handleKeyboard();

  // Si une présence est détectée
  if (motionState == HIGH) {
    // Red LED
    leds[0] = CRGB::Red;
    toggleLED();

    // Set alarm
    M5Cardputer.Speaker.tone(4000, 20);
    M5Cardputer.Speaker.tone(3000, 10);

  } else {
    // Green LED
    leds[0] = CRGB::Green;
    toggleLED();
  }

  // Render only if motionState has changed
  if (lastState != motionState) {
    displayDetection(motionState);
    lastState = motionState;
  }

  delay(20);
}
