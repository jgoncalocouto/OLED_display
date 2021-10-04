#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1      // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  setup_display();
}

void loop() {

  float valArr[3]={29.3,20.1,1.0};
  int delayTime = 100;
  String varArr[3][2] = {
        {"P1","[mbar]"},
        {"P2","[mbar]"},
        {"REC","[-]"},
        };


  for (int j=1; j<=500;j++){
    valArr[0]=valArr[0]+j; // sensor data would appear here
    valArr[1]=valArr[1]+j*2;
    valArr[2]=valArr[2]+j*3;

    display_sensorValues(varArr,valArr,delayTime);
    
}
}


// Auxiliary Functions
void setup_display(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display(); // display.display() refreshes the screen
  delay(100); 
  display.clearDisplay();
  display.display();
  delay(100);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void display_sensorValues(String varArr[][2], float valArr[], int delayTime){
  
  display.display();
  display.setCursor(0, 0);
  display.clearDisplay();
  int arrSize = sizeof(valArr)/sizeof(valArr[0]);
  string msg[arrSize];
  for (int i = 0; i <arrSize; i++) {
    msg[i] = varArr[i][0]+" = "+to_string(valArr[i])+" "+varArr[i][1];
    display.println(msg[i]);
  }
  display.display();
  delay(delayTime);
}
