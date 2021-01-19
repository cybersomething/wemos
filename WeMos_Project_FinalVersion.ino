//basic libraries
#include <Streaming.h>
#include <Servo.h>
#include <iomanip>
// -- OLED -------
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// OLED i2c
#define OLED_RESET -1
#define OLED_SCREEN_I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(OLED_RESET);
//timer variables
signed short minutes; 
signed short seconds;
signed short break_minutes;
signed short break_seconds;
char timeline[16];
char break_timeline[16];
//Servo variables
Servo myservo;
int pos = 0;   // variable to store the servo position

void setup()
{
Serial.begin(115200);
Serial << endl << "Hello World" << endl;
// -- OLED --------------
display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS); //displays load up screen
display.display(); //displays load-up screen
delay(2000); //display for 2 seconds
display.clearDisplay(); //clear display
display.setCursor(0,0); //set text cursor back to x,y
display.setTextSize(2); // - a line is 21 chars in this size
display.setTextColor(WHITE); //set all text colour to white
// -- Servo -------------
myservo.attach(D8); //tells the computer what pin the servo has been attached to.
myservo.write(pos=0); //tells the computer to make sure the servo is at 0 degrees.
//-- Wemos LED ----------
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  //Begin loop
  
  display.clearDisplay(); //clear display
  display.setCursor(0,0); //set cursor to x,y
  display.setTextSize(1.6); //set text size for study screen to 1.6
  display << "Study time" << endl; //Display 'Study Time on screen'
  sprintf(timeline,"%0.2d mins %0.2d secs", minutes, seconds); //used to create the timeline, with minutes and seconds
  delay(1000); //wait one second
  seconds++; //add one to seconds
  
  if (seconds == 59) //when seconds reaches 59
    {
     seconds = 0; //set seconds back to 0
     minutes++; //add one to minutes
    }
    
   display << "You have studied for" << endl; //display line saying 'you have studied for'
   display << timeline << endl; //display time studied for on next line
   display.display(); //send all display lines to output
   
   if (minutes == 10) //Once student studies for 10 minutes
   {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level
    delay(700);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(700);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level
    delay(700);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(700);
    
    for (pos = 0; pos <= 90; pos += 1) 
    { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
    }
   for (pos = 90; pos >= 0; pos -= 1) //set servo back to original position
    { // goes from 90 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
    }

    do
    {
      display.clearDisplay(); //clear display
      display.setCursor(0,0); //reset text cursor position to x,y
      display << "Time for a break!" << endl; //display 'time for a break'
      sprintf(break_timeline,"%0.2d mins %0.2d secs", break_minutes, break_seconds); //used to create break timeline, with seconds and minutes
      delay(1000); //wait one second
      break_seconds++; //add one to break seconds
      
      if (break_seconds == 59) //when break seconds reaches 59
      {
        break_seconds = 0; //set seconds back to 0
        break_minutes ++;  //add one to minutes
      } 
      
      display << "Your break started" << endl; //display your break started 
      display << break_timeline << "'s ago" << endl; //display time taken 
      display.display(); //send display lines to output
      
      if(break_minutes == 5) //when break reaches 5 minutes
      {
         display.clearDisplay(); //clear display
         display.setCursor(0,0); //reset cursor position to x,y
         display.setTextSize(2); //set text size
         display << "Resetting" << endl; //display 'resetting'
         display << "the timer!" << endl; //display 'the timer'
         display.display(); //send display lines to output
         exit(0); //end loop
      }
    }
 while (break_minutes < 5); //do while break_minutes are less than 5.
}
