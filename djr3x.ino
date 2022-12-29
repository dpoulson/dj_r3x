#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>


#define LED_PIN    9
#define LED_COUNT 42

#define MODESWITCH 3


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

  if (lightMode == 0) 
    standardMode();
  else if (lightMode == 1)
    discoMode();

  brightness = map(analogRead(A1), 0, 1024, 0, 150);
  flashSpeed = map(analogRead(A2), 0, 890, 100, 5000);
  eyeBrightness = map(analogRead(A3), 0, 890, 100, 1000);

/*
  Serial.print(lightMode);
  Serial.print(",");
  Serial.print(brightness);
  Serial.print(",");  
  Serial.print(flashSpeed);
  Serial.print(",");
  Serial.print(eyeBrightness);
  Serial.print(",");
  Serial.print(lastChange);
  Serial.println();
  */

  strip.setBrightness(eyeBrightness);

  
}

void checkMode() {
  button1.update();
  if ( button1.pressed() ) {
    Serial.println("Button Pressed");
    // TOGGLE THE LED STATE : 
    lightMode = !lightMode; // SET ledState TO THE OPPOSITE OF ledState
  }
  Serial.println(lightMode);
  
}

void standardMode() {

  int sound = digitalRead(10);

  if (millis() > lastChange + flashSpeed || sound == 1) {
    for(int i=0; i<strip.numPixels(); i++)
    {
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
