/**
 * 
 *                 20231110 Version 1.0
   @file flying.ino
   @author howell ivy
   @brief Logic for experiment My-Cool-Experiment
   @version 1.0
   @date 2023-07-15

  20231120 CLI_V1.0 Required to make a complete program - this file, CLI_V1.0,Quest_CLI.h, Quest_Flight.h,Quest_flight.cpp
                  cmd_takeSphot , cmd_takeSpiphoto, nophotophoto, nophoto30K --,clean up code for understanding.
                  
*/

#include "Quest_Flight.h"
#include "Quest_CLI.h"
#include "SparkFunISL29125.h"

#define TCAADDR 0x70 // I2C for multiplexer



//////////////////////////////////////////////////////////////////////////
//    this defines the timers used to control flight operations
//////////////////////////////////////////////////////////////////////////
//  Fast clock --- 1 hour = 5 min = 1/12 of an  hour
//     one millie -- 1ms
//
#define SpeedFactor 30    // = times faster
//
//
//////////////////////////////////////////////////////////////////////////
//

#define one_sec   1000                         //one second = 1000 millis
#define one_min   60*one_sec                   // one minute of time
#define one_hour  60*one_min                   // one hour of time
#define one_day  24*one_hour                   // one hour of time
//

#define TimeEvent1_time     ((one_day * 4) / SpeedFactor)      //pump broth TBD
#define TimeEvent2_time     ((one_day * 10) / SpeedFactor)       //antibioti: this event on day 2, 4, 10, 12
#define TimeEvent3_time     ((one_hour * 12) / SpeedFactor)      //take a photo 
// aka one_day <-- wait time + ( 2 * one_day) || (4 * one_day) || (10 * one_day) || (12*one_day);
#define Sensor1time         ((one_min * 2)/ SpeedFactor)      //Time to make Sensor1 readings -- both color sensor readings 

//
  int pumpState1 = 0;     //used to differentiate first time pumping vs the rest 
  int pumpState2 = 0;     //used to differentiate first time pumping vs the rest 
  int State =   0;          //FOR TESTING ONLY WILL SWITCH FROM SPI CAMERA TO SERIAL CAMERA EVERY TimeEvent1_time!!!!!
//

///////////////////////////////////////////////////////////////////////////
/**
   @brief Flying function is used to capture all logic of an experiment during flight.
*/
//************************************************************************
//   Beginning of the flight program setup
//


//char txtBuffer[20] = "----------";

// color sensor declaration

void Flying() {

  Serial.println("Here to Run flight program, not done yet 20230718");
  Serial.println(" 20230718 working on it");

  uint32_t TimeEvent1 = millis();               //set event one timer -- pump lb broth event 
  uint32_t TimeEvent2 = millis();              //set event two timer -- pump antibiotic 
  uint32_t TimeEvent3 = millis();              //set event three timer -- camera
  //

  uint32_t Sensor1Timer = millis();             //clear sensor1Timer to effective 0
  uint32_t Sensor2Deadmillis = millis();        //clear mills for difference

  //
  uint32_t one_secTimer = millis();             //set happens every second
  uint32_t sec60Timer = millis();               //set minute timer

  //*****************************************************************
  //   Here to set up flight conditions i/o pins, atod, and other special condition
  //   of your program
  //
  //
  //
  //******************************************************************

  //refer to component test
  pinMode(IO1, OUTPUT); // half of right pump (antibiotic) - first time pumping: 23.49 rest: 14.59
  pinMode(IO2, OUTPUT); // half of right pump
  pinMode(IO3, OUTPUT); // half of left pump (broth) low - on
  pinMode(IO4, OUTPUT); // half of left pump low - on first time pumping: 22 seconds rest: 17.18
  pinMode(IO5, OUTPUT); // oscillater 
  pinMode(IO6, OUTPUT); // BLUE leds
  pinMode(IO7, OUTPUT); // WHITE leds
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
  //***********************************************************************
  //***********************************************************************
  //

  delay(one_day / SpeedFactor ); //24 hr wait 

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
//------------------------------------------------------------------
//
//*********** Timed Event 1 test ***************************************
// 
    //-------------------------------------------------------------------
    //  this test if TimeEvent1 time has come
    //  See above for TimeEvent1_time settings between this event
    //
    if ((millis() - TimeEvent1) > TimeEvent1_time) { // broth pump event 
      TimeEvent1 = millis();                    //yes is time now reset TimeEvent1 

      // Pump LB Broth

      digitalWrite(IO5, HIGH); //turns oscillator on
      digitalWrite(IO5, HIGH);      
      Serial.println("oscillator turned on");

      delay(30 * one_sec); //leaves on for 30 seconds

      digitalWrite(IO5, LOW); //turns oscillator off
      digitalWrite(IO5, LOW);  
      Serial.println("oscillator turned off");

      digitalWrite(IO3, LOW);
      digitalWrite(IO4, LOW); // turns broth pump on      
      Serial.println("broth pumped turned on");
      if (pumpState1 == 0) {
        delay(23480); //delay first pump by 22 seconds
        pumpState1++;
      } else {
        delay(14590); //time it takes for pump to run
      }
      
      digitalWrite(IO3, HIGH);
      digitalWrite(IO4, HIGH); // turns pump 2 off
      Serial.println("broth pumped turned off");
      //end of TimeEvent1_time
      }

    //------------------------------------------------------------------
    //
    //  This test if TimeEvent2_time time has come
    //  See above for TimeEvent2_time settings between this event
    //
    if (millis() == ((one_day + (2 * one_day)) / SpeedFactor) 
      || millis() == ((one_day + (4 * one_day)) / SpeedFactor)
      || millis() == ((one_day + (10 * one_day)) / SpeedFactor)
      || millis() == (one_day + (12 * one_day)) / SpeedFactor) {  //antibiotic event 
      //TimeEvent2 = millis();                    //reset TimeEvent2
      Serial.println();
      Serial.println(millis());
      //
      //  Build the User Text buffer here
      //
      //         strcat(user_text_buf0,("User Buffer space here, millis = "));
      //         itoa(millis(),text_buf,10);
      //         strcat(user_text_buf0,(text_buf));
      //


      digitalWrite(IO5, HIGH); //turns oscillator on
      digitalWrite(IO5, HIGH);      
      Serial.println("oscillator turned on");

      delay(30 * one_sec); //leaves on for 30 seconds

      digitalWrite(IO5, LOW); //turns oscillator off
      digitalWrite(IO5, LOW);      
      Serial.println("oscillator turned off");

      digitalWrite(IO1, LOW);
      digitalWrite(IO2, LOW); // turns pump 2 on
      Serial.println("antibiotic pump turned on");

      if (pumpState2 == 0) {
        delay(22 * one_sec); //delay first pump by 22 seconds
        pumpState2++;
      } else {
        delay(17800); //time it takes for pump to run
      }

      digitalWrite(IO1, HIGH);
      digitalWrite(IO2, HIGH); // turns pump 2 off
      Serial.println("antibiotic pump turned off");

    }

    //continue
    if ((millis() - TimeEvent3) > TimeEvent3_time) { //ccamera event
      TimeEvent3 = millis();                    //reset TimeEvent3
      Serial.println();
      Serial.println(millis());
      digitalWrite(IO5, HIGH); //turns blue LEDS off
      digitalWrite(IO7, LOW); // turns white LEDS on
      delay(1000);   
      cmd_takeSphoto();            //Take serial photo and send it
      delay(one_min);             // more than enough time for camera to take pic
      digitalWrite(IO7, HIGH); // turns white LEDS off    
      digitalWrite(IO5, LOW); //turns blue LEDS on
      delay(5000);
    }
//*******************************************************************************
//*********** One second counter timer will trigger every second ****************
//*******************************************************************************
    //  Here one sec timer - every second
    //
    if ((millis() - one_secTimer) > one_sec) {      //one sec counter
      one_secTimer = millis();                      //reset one second timer
      DotStarYellow();                              //turn on Yellow DotStar to Blink for running
      //
//****************** NO_NO_NO_NO_NO_NO_NO_NO_NO_NO_NO_ *************************
// DO NOT TOUCH THIS CODE IT IS NECESARY FOR PROPER MISSION CLOCK OPERATIONS
//    Mission clock timer
//    FRAM keep track of cunlitive power on time
//    and RTC with unix seconds
//------------------------------------------------------------------------------
      DateTime now = rtc.now();                           //get the time time,don't know how long away
      currentunix = (now.unixtime());                     //get current unix time
      Serial.print(currentunix); Serial.print("  ");      //testing print unix clock
      uint32_t framdeltaunix = (currentunix - readlongFromfram(PreviousUnix)); //get delta sec of unix time
      uint32_t cumunix = readlongFromfram(CumUnix);       //Get cumulative unix mission clock
      writelongfram((cumunix + framdeltaunix), CumUnix);  //add and Save cumulative unix time Mission
      writelongfram(currentunix, PreviousUnix);           //reset PreviousUnix to current for next time
//
//********* END_NO_END_NO_END_NO_END_NO_END_NO_END_NO_ **************************
      //
      //  This part prints out every second
      //
      Serial.print(": Mission Clock = ");      //testing print mission clock
      Serial.print(readlongFromfram(CumUnix));        //mission clock
      Serial.print(" is ");                        //spacer
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
      DotStarOff();
    } // end of one second routine
//**********************************************************************
//*********** Read Sensor1 Event read and add to text buffer************
//**********************************************************************
    //update based on multiplexer
    //
    if ((millis() - Sensor1Timer) > Sensor1time) {    //Is it time to read?
      Sensor1Timer = millis();                        //Yes, lets read the sensor1

      tcaselect(2);
      
      unsigned int red0 = RGB_sensor0.readRed();
      unsigned int green0 = RGB_sensor0.readGreen();
      unsigned int blue0 = RGB_sensor0.readBlue();

      delay(2000);    
      tcaselect(3);

      unsigned int red1 = RGB_sensor1.readRed();
      unsigned int green1 = RGB_sensor1.readGreen();
      unsigned int blue1 = RGB_sensor1.readBlue();

      cmd_writeTextFile(1, red0, green0, blue0, 2, red1, green1, blue1);
      //    
    }     // End of Sensor1 time event
    //

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//    This is a function to adds three values to the user_text_buffer
//    Written specificy for 2023-2024 Team F, Team B,
//    Enter the function with "add2text(1st interger value, 2nd intergre value, 3rd intergervalue);
//    the " - value1 " text can be changed to lable the value or removed to same space
//    ", value2 " and ", value 3 " masy also be removed or changed to a lable.
//    Space availiable is 1024 bytes, Note- - each Data line has a ncarrage return and a line feed
//
//example of calling routine:
//       //
//      int value1 = 55;
//      int value2 = 55000;
//      int value3 = 14;
//      add2text(value1, value2, value3);
//      //
//EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE     
//
   }
}
void add2text(int value1,unsigned int value2,unsigned int value3,unsigned int value4){ //Add value to text file
        if (strlen(user_text_buf0) >= (sizeof(user_text_buf0)-100)){    //Check for full
          Serial.println("text buffer full");                           //yes, say so
          return;                                                       //back to calling
        }
        char temp[11];                  // Maximum number of digits for a 32-bit integer 
        int index = 10;                 //Start from the end of the temperary buffer  
        char str[12];                   //digits + null terminator   
//--------- get time and convert to str for entry into text buffer ----
        DateTime now = rtc.now();                   //get time of entry
        uint32_t value = now.unixtime();            //get unix time from entry
        do {
            temp[index--] = '0' + (value % 10);     // Convert the least significant digit to ASCII
            value /= 10;                            // Move to the next digit
        } while (value != 0);
        strcpy(str, temp + index +1);               // Copy the result to the output string
//---------- end of time conversion uni time is now in str -------------       
        strcat(user_text_buf0, (str));              //write unix time
        //
        // unit time finish entry into this data line
        //
        strcat(user_text_buf0, (" - count= "));            // seperator
        strcat(user_text_buf0, (itoa(value1, ascii, 10)));
        strcat(user_text_buf0, (", red= "));
        strcat(user_text_buf0, (itoa(value2, ascii, 10)));
        strcat(user_text_buf0, (", green= "));
        strcat(user_text_buf0, (itoa(value3,  ascii, 10)));
        strcat(user_text_buf0, (", blue= "));
        strcat(user_text_buf0, (itoa(value4,  ascii, 10)));
        strcat(user_text_buf0, ("\r\n"));

        //Serial.println(strlen(user_text_buf0));  //for testing
}
 //------end of Function to add to user text buffer ------       
//
//=============================================================================
//
////FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//  Function to write into a 30K databuffer
//    char databuffer[30000];         // Create a character buffer with a size of 2KB
//    int databufferLength = 0;       // Initialize the buffer length
//  Append data to the large data buffer buffer always enter unit time of data added
//  enter: void dataappend(int counts, int ampli, int SiPM, int Deadtime) (4 values)
//


void dataappend(int value1,unsigned int value2,unsigned int value3,unsigned int value4) {          //entry, add line with values to databuffer
  //----- get and set time to entry -----
  DateTime now = rtc.now();                                               //get time of entry
  String stringValue = String(now.unixtime());                            //convert unix time to string
  const char* charValue = stringValue.c_str();                            //convert to a C string value
  //appendToBuffer(charValue);                                              //Sent unix time to databuffer
  //----- add formated string to buffer -----
  String results = "Sensor num: " + String(value1) + "\n" + " Red " + String(value2) + " Blue: " + String(value3) + " Green: " + String (value4) + "\r\n";  //format databuffer entry
  const char* charValue1 = results.c_str();                               //convert to a C string value
  appendToBuffer(charValue1);                                             //Send formated string to databuff
  //
  //  Serial.println(databufferLength);                                   //print buffer length for testing only
}

//-----------------------                                               //end dataappend
//----- sub part od dataappend -- append to Buffer -----
//-----------------------
void appendToBuffer(const char* data) {                                   //enter with charator string to append
  int dataLength = strlen(data);                                          //define the length of data to append
      // ----- Check if there is enough space in the buffer                           //enough space?
  if (databufferLength + dataLength < sizeof(user_text_buf0)) {               //enouth space left in buffer
      // ----- Append the data to the buffer
    strcat(user_text_buf0, data);                                             //yes enough space, add data to end of buffer
    databufferLength += dataLength;                                       //change to length of the buffer
  } else {
    Serial.println("Buffer is full. Data not appended.");                 //Not enough space, say so on terminal
  }       //end not enough space
}         //end appendToBuffer


void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
// old method to create text file from sensor data 
// void logit_myFile(unsigned int r, unsigned int  g, unsigned int b, char* myFile) {
//   fileNum++; //adds num to end of file
//   itoa(fileNum, txtBuffer, 10);
//   Logfile = SD.open(strcat(strcat(myFile, txtBuffer) , (".txt")), FILE_WRITE);  //open new myFile;
//   txtBuffer[0] = '\0'; 
//   if (Logfile) {  
//   //with logfile is open
//     Logfile.write(xd); Logfile.write(" Days   ");
//     Logfile.write(xh); Logfile.write(" Hours  ");
//     Logfile.write(xm); Logfile.write(" Min  ");
//     Logfile.write(xs); Logfile.write(" Sec");
//     char red[] = "red";
//     Logfile.write(red + r);                         //write the string to file
//     Logfile.write("green: " + g); 
//     Logfile.write("blue: " + b); 
//   } else {                                        //if not open say error
//     Serial.println("\r\nlogit error");  
//   }  
//   Logfile.close();    
// }
