/**
   @file flying.ino
   @author Your-Name-Here (you@domain.com)
   @brief Logic for experiment My-Cool-Experiment
   @version 0.1
   @date 2023-07-15

*/

#include "Quest_Flight.h"
#include "Quest_CLI.h"
#include "SparkFunISL29125.h"

//////////////////////////////////////////////////////////////////////////
//    this defines the timers used to control flight operations
//////////////////////////////////////////////////////////////////////////
#define one_sec   1000                         //one second = 1000 millis
#define one_min   60*one_sec                   // one minute of time
#define one_hour  60*one_min                   // one hour of time
#define one_day  24*one_hour                   // one hour of time
//
#define eventTime0  one_day                 //this event every day - photo, pump broth
#define eventTime1  one_day*10              //this event every 10 days - pump antibiotic
#define eventTime2  one_min*3              //this event every 3 mins - read sensor
///////////////////////////////////////////////////////////////////////////
/**
   @brief Flying function is used to capture all logic of an experiment during flight.
*/
//************************************************************************
//   Beginning of the flight program setup
//
int fileNum = 0;
char txtBuffer[20];
SFE_ISL29125 RGB_sensor;
void Flying() {
    // Initialize the ISL29125 and verify its presence
  if (RGB_sensor.init())
  {
    Serial.println("Sensor Initialization Successful\n\r");
  } else {
    Serial.println("Sensor Initialization Unsuccessful?");
  }

  Serial.println("Here to Run flight program, not done yet 20230718");
  Serial.println(" 20230718 working on it");

  uint32_t event0timer = millis();              //set event zero timer
  uint32_t event1timer = millis();              //set event one timer
  uint32_t event2timer = millis();              //set event two timer

  //
  uint32_t one_secTimer = millis();             //set happens every second
  uint32_t sec60Timer = millis();               //set minute timer

  //*****************************************************************
  //   Here to set up flight conditions i/o pins, atod, and other special condition
  //   of your program
  //
  pinMode(pin1, OUTPUT);  //nutrient pump
  pinMode(pin2, OUTPUT);  //antibiotic pump
  //camera leds
  pinMode(pin3, OUTPUT); // LED 1
  pinMode(pin4, OUTPUT); // LED 2
  pinMode(pin5, OUTPUT); // LED 3
  pinMode(pin6, OUTPUT); // LED 4
  //
  //******************************************************************
  // all / most delays are subject to change
  //------------ flying -----------------------

  Serial.println("Flying NOW  -  x=abort");                 //terminal output for abort back to test
  Serial.println("Terminal must be reset after abort");     //terminal reset requirement upon soft reset

  missionMillis = millis();     //Set mission clock millis, you just entered flight conditions
  //
  //
  /////////////////////////////////////////////////////
  //----- Here to start a flight from a reset ---------
  /////////////////////////////////////////////////////
  //
  DateTime now = rtc.now();                   //get time now
  currentunix = (now.unixtime());             //get current unix time, don't count time not flying
  writelongfram(currentunix, PreviousUnix);   //set fram Mission time start now counting seconds unix time
  //
  //***********************************************************************
  //***********************************************************************
  //  All Flight conditions are now set up,  NOW to enter flight operations
  //
  //
  delay(1000); // 24 hr wait 
  while (1) {
    //
    //----------- Test for terminal abort command from flying ----------------------
    //
    while (Serial.available()) {      //Abort flight program progress
      byte x = Serial.read();         //get the input byte
      if (x == 'x') {                 //check the byte for an abort x
        return  ;                     //return back to poeration sellection
      }                               //end check
    }                                 //end abort check
    //-------------------------------------------------------------------
    //  this test if eventTime0 time has come
    //  See above for eventTime0 settings between this event
    //
    if ((millis() - event0timer) > eventTime0) {  //camera and broth event 
      event0timer = millis();                    //yes is time now reset event0timer
      Serial.println();                          //
      Serial.println(millis());                  //
      //
      //***** Build the User Text buffer here
      //***** additions to the user text buffer can be added anytime between photo events
      //
      strcat(user_text_buf0, ("User Buffer space here, millis = "));    //put this in user buffer
      itoa(millis(), text_buf, 10);                                     //put millis time in user buffer
      strcat(user_text_buf0, (text_buf));               //append the just created text_buf to user buffer
      //
      //  Take a photo using the serial c329 camera and place file name in Queue
      //
      digitalWrite(pin3, HIGH);                  //turns on LED 1
      digitalWrite(pin4, HIGH);                  //turns on LED 2
      digitalWrite(pin5, HIGH);                  //turns on LED 3
      digitalWrite(pin6, HIGH);                  //turns on LED 4

      cmd_takeSphoto();                          //Take photo and send it
      delay(100);

      digitalWrite(pin3, LOW);                   //turns off LED 1
      digitalWrite(pin4, LOW);                   //turns off LED 2
      digitalWrite(pin5, LOW);                   //turns off LED 3
      digitalWrite(pin6, LOW);                   //turns off LED 4

      delay(1000);

      digitalWrite(pin1, HIGH);                   // pumps antibiotic
      delay(1000);
      digitalWrite(pin1, LOW);                    // turns pump off
      delay(5000);
      // Call the freeMemory function and print the result
      // cmd_stackandheap();                          //enable to know stack and heap after photo time
      //
      // logit_string();                            //log the event
    }                                               //end of eventTime0
    //----------------------------------------------------------------------
    //  This test if eventTime1 time has come
    //  See above for eventTime1 settings between this event
    //
    if ((millis() - event1timer) > eventTime1) { //antibiotic event 
      event1timer = millis();                    //reset event1timer
      Serial.println();
      Serial.println(millis());
      //
      //  Build the User Text buffer here
      //
      //         strcat(user_text_buf0,("User Buffer space here, millis = "));
      //         itoa(millis(),text_buf,10);
      //         strcat(user_text_buf0,(text_buf));
      //
      //  Take a photo using the SPI c329 camera
      //
      digitalWrite(pin2, HIGH); //pumps antibiotic
      delay(1000);
      digitalWrite(pin2, LOW); //turns pump off
      delay(5000);      

    }
    if ((millis() - event2timer) > eventTime2) { //color sensor event
      event2timer = millis();                    //reset event2timer
      Serial.println();
      Serial.println(millis());
      unsigned int red = RGB_sensor.readRed();
      unsigned int green = RGB_sensor.readGreen();
      unsigned int blue = RGB_sensor.readBlue();      

      String(red, DEC);
      String(green, DEC);
      String(blue, DEC);

      logit_myFile(red, green, blue, "sensorReadings");
      
      
      //
      //  Build the User Text buffer here
      //
      //         strcat(user_text_buf0,("User Buffer space here, millis = "));
      //         itoa(millis(),text_buf,10);
      //         strcat(user_text_buf0,(text_buf));
      //
      //  Take a photo using the SPI c329 camera
      //
      

    }
    //------------------------------------------------------------------
    //------------  Here one sec timer  ------ -every second ------
    //
    if ((millis() - one_secTimer) > one_sec) {
      one_secTimer = millis();
      DotStarYellow();                              //Blink Yellow when flying
      Serial.write('+');                            //Send to terminal
      //
      //-------------------------------
      // DO NOT TOUCH THIS CODE IT IS NECESARY FOR PROPER MISSION CLOCK OPERATIONS
      //    Mission clock timer
      //    FRAM keep track of cunlitive power on time
      //    and RTC with unix seconds
      //-------------------------------
      //
      DateTime now = rtc.now();                           //get the time time,don't know how long away
      currentunix = (now.unixtime());                     //get current unix time
      Serial.print(currentunix); Serial.print("  ");      //testing print unix clock
      uint32_t framdeltaunix = (currentunix - readlongFromfram(PreviousUnix)); //get delta sec of unix time
      uint32_t cumunix = readlongFromfram(CumUnix);       //Get cumulative unix mission clock
      writelongfram((cumunix + framdeltaunix), CumUnix);  //add and Save cumulative unix time Mission
      writelongfram(currentunix, PreviousUnix);           //reset PreviousUnix to current for next time
      //
      Serial.print("--- Fram Mission Clock = ");      //testing print mission clock
      Serial.print(readlongFromfram(CumUnix));        //mission clock
      Serial.print("  =>   ");                        //spacer
      //
      //------Output the terminal  days hours min sec
      //
      getmissionclk();
      Serial.print(xd); Serial.print(" Days   ");
      Serial.print(xh); Serial.print(" Hours  ");
      Serial.print(xm); Serial.print(" Min  ");
      Serial.print(xs); Serial.println(" Sec");
      //
      //
      //
      //------------ print time once a min -------------------
      //
      if ((millis() - sec60Timer) > (60 * one_sec)) {
        sec60Timer = millis();
        Serial.println();
        cmd_time();
      }
      DotStarOff();
    }
  }
}

void logit_myFile(String  r, String  g, String  b, String myFile) {
  fileNum++; //adds num to end of file
  itoa(fileNum, txtBuffer, 10);
  Logfile = SD.open(strcat(strcat(myFile, txtBuffer), ".txt"), FILE_WRITE);  //open new myFile;
  txtBuffer[0] = "/0"; 
  if (Logfile) {  
  //with logfile is open
    Logfile.write(xd); Logfile.write(" Days   ");
    Logfile.write(xh); Logfile.write(" Hours  ");
    Logfile.write(xm); Logfile.write(" Min  ");
    Logfile.write(xs); Logfile.write(" Sec");
    Logfile.write(strcat("red: ", r));                         //write the string to file
    Logfile.write(strcat("green: ", g)); 
    Logfile.write(strcat("blue: ", b)); 
  } else {                                        //if not open say error
    Serial.println("\r\nlogit error");  
  }  
  Logfile.close();    
}
 
