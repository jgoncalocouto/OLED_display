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
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
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

void loop() {
  // put your main code here, to run repeatedly:

  
  String varArr[3]={"P1","P2","REC"};
  String unitArr[3]={"[mbar]","[mbar]","[-]"};
  float valArr[3]={29.3,20.1,1.0};
  int delayTime = 100;



  for (int j=1; j<=500;j++){
      display.display();
      display.setCursor(0, 0);
      display.clearDisplay();
      
    valArr[0]=valArr[0]+j; // sensor data would appear here
    valArr[1]=valArr[1]+j*2;
    valArr[2]=valArr[2]+j*3;
    
  
  for (int i=0; i<=2;i++){
      String msg= varArr[i]+" = "+String(valArr[i],2)+" "+unitArr[i];
      display.println(msg);
    };
      display.display();
      delay(delayTime);
}
}
