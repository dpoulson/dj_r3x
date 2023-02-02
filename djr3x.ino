#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>


#define LED_PIN    9
#define LED_COUNT 42
#define EYE_PIN   10

#define MODESWITCH 3

#define SOUND_PIN 10
// #define ENABLE_SOUND


int flashSpeed = 100;
int brightness = 50;
int eyeBrightness = 50;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Bounce2::Button button1 = Bounce2::Button();

int lightMode = LOW;
unsigned long lastChange;

uint32_t colour = strip.Color(255,255,255);


void setup() {

  Serial.begin(115200);
  pinMode(A7, INPUT_PULLUP);
  pinMode(SOUND_PIN, INPUT);
  
  button1.attach( MODESWITCH, INPUT_PULLUP ); // USE EXTERNAL PULL-UP

  // DEBOUNCE INTERVAL IN MILLISECONDS
  button1.interval(5); 

  // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  button1.setPressedState(LOW); 

  strip.begin();
  strip.show();
  strip.setBrightness(20);

}

void loop() {

  checkMode();
  standardMode();

  brightness = map(analogRead(A1), 0, 1024, 0, 150);
  flashSpeed = map(analogRead(A2), 0, 890, 0, 3000);
  eyeBrightness = map(analogRead(A3), 0, 890, 0, 250);
/*
  Serial.print(analogRead(A1));
  Serial.print(",");
  Serial.print(analogRead(A2));
  Serial.print(",");  
  Serial.print(analogRead(A3));
  Serial.print(",");
  Serial.print(eyeBrightness);
  Serial.print(",");
  Serial.print(lightMode);
  Serial.print(",");
  Serial.print(brightness);
  Serial.print(",");  
  Serial.print(flashSpeed);
  Serial.print(",");
  Serial.print(eyeBrightness);
  Serial.print(",");
  Serial.print(lastChange);
  Serial.print(",");
  Serial.print(digitalRead(10));
  Serial.println();
  */

  strip.setBrightness(brightness);

  // Set eye brightness
  analogWrite(EYE_PIN, eyeBrightness);

  
}

void checkMode() {
  button1.update();
  if ( button1.pressed() ) {
    Serial.println("Button Pressed");
    // TOGGLE THE LED STATE : 
    lightMode = !lightMode; // SET ledState TO THE OPPOSITE OF ledState
  }
  
}

void standardMode() {

  int sound = 0;

  #ifdef ENABLE_SOUND
    int soundValue = analogRead(A5);
    Serial.print(soundValue);
    Serial.print(","); 
    Serial.println();
    
    if (soundValue > analogRead(A3)) {
      sound = 1;
    } else {
      sound = 0;
    }
  #endif

  if (millis() > lastChange + flashSpeed || sound == 1) {
    for(int i=0; i<strip.numPixels(); i++)
    {
      if (lightMode) {
        colour = strip.Color(random(255),random(255),random(255));
      } else {
        colour = strip.Color(255,255,255);
      }
      int chance = random(1,100);
      if (chance > 50) 
      {

         strip.setPixelColor(i, colour);
              
      } else {
        strip.setPixelColor(i, strip.Color(0,0,0));
      }
      strip.show();
    }
    lastChange = millis();
  }

}

void discoMode() {
  
}
