  // 18 February 2020
  // dbVal1 & 2 to float int
  // Batt test added
  // Radio link test added when SLM off (useful as SLM fail detect)
  // State round added

  // 4 August 2020
  // removed SDMA alarm output to Tx. - nuisance!
  // 'at risk' reading on display retained.

  // 24 August 2020
  // 5 beeps & peak detect added for test purposes.
  // this version still in use Aug. 2022
  
  #include <LiquidCrystal.h>

  #include <Wire.h>

  LiquidCrystal lcd(8,9,4,5,6,7);

  const int ALARM = 13;        // Alarm output (on-board red LED) & Alarm relay drive + buzzer + panel LED
  const int LEVEL = 12;        // High = Club rd. level (87dbA), low = State rd. level (95dbA)
  
  void setup()

 {
   
  lcd.begin(16,2);              // start lcd
  Serial.begin(9600);           // start serial
  pinMode (ALARM, OUTPUT);
  pinMode (LEVEL, INPUT);
  
 }


  void loop()

 {
   
  int SLMRead1 = 0; int SLMRead2 = 0;  float dbMax = 0;       
  float dbAVal1 = 0; float dbAVal2 = 0; float dbPeak = 0;
  float BattIn = 0; float Batt = 0; float BattVolts = 0;
  
  
  delay(10);
  
  BattIn = analogRead(A5);                     // BattIn = 12V SLA / 4 (ie, ~ 3V)
  Batt = BattIn * 4;                           // ADC value x 4
  BattVolts = Batt * 5 / 1023;                 // convert ADC value to volts DC
  
  SLMRead1 = analogRead(A1);                   // read input A1 (SLM DC) to SLMRead1
  SLMRead1 = constrain(SLMRead1, 0 , 200);     // limits val to 95dbA
  dbAVal1 = SLMRead1 / 2.03;
  delay (500);                                 // wait 0.5 sec                                                                            
  SLMRead2 = analogRead(A1);                   // take another reading, store at SLMRead2
  SLMRead2 = constrain(SLMRead2, 0, 200);      // limit value to 95dbA, as above
  dbAVal2 = SLMRead2 / 2.03;
  dbMax = max(dbAVal1, dbAVal2);
  

 if(dbMax < 10)     // SLM not connected or not working.  
 
 {
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SLM connected?");
  lcd.setCursor(0,1);
  lcd.print("ver.SLM_87dbA_71");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Batt. =  ");
  lcd.setCursor(8,0);
  lcd.print(BattVolts,2);
  lcd.setCursor(13,0);
  lcd.print("V");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Radio test...");
  digitalWrite(ALARM, HIGH);
  delay(750);
  digitalWrite(ALARM, LOW);
  delay(750);
  digitalWrite(ALARM, HIGH);
  delay(750);
  digitalWrite(ALARM, LOW);
  delay(750);
  digitalWrite(ALARM, HIGH);
  delay(750);
  digitalWrite(ALARM, LOW);
  lcd.clear();
  

 }

 if(digitalRead(LEVEL) == HIGH and (dbMax) >= 87)

 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("SDMA rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor (0,1);
  lcd.print(" *INFRINGEMENT*");
  digitalWrite(ALARM, HIGH);
  delay(4000);
  digitalWrite(ALARM, LOW);
  delay(250);
  // digitalWrite(ALARM, HIGH);
  // delay(500);
  // digitalWrite(ALARM, LOW);
  // insert peak detect here
  // delay(500);
  // digitalWrite(ALARM, HIGH);
  // delay(500);                  
  // digitalWrite(ALARM, LOW);
  // insert peak detect here
  // delay(500);                  
  // digitalWrite(ALARM, HIGH);
  // delay(500);                  
  // digitalWrite(ALARM, LOW);
  // insert peak detect here
  // delay(500);                                    
  // digitalWrite(ALARM, HIGH);
  // delay(500);                                    
  // digitalWrite(ALARM, LOW):
  // insert peak detect here
  // delay(500);                                    
  // digitalWrite(ALARM, HIGH);
  // delay(500);                                
  // digitalWrite(ALARM, LOW);
  // insert peak detect here
  // delay(900);                  
  // lcd.clear();
  // lcd.setCursor (0,0);
  // insert top row "dbPeak = xx.xdbA"
  // delay(2000);
  
  
  }

 if(digitalRead(LEVEL) == HIGH and (dbMax) >= 80 and (dbMax) <= 86)

 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("SDMA rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor (3,1);
  lcd.print("* AT RISK *");
  //digitalWrite(ALARM, HIGH);
  //delay(750);
  //digitalWrite(ALARM, LOW);
  //delay(750);
  //digitalWrite(ALARM, HIGH);
  //delay(750);
  //digitalWrite(ALARM, LOW);
  delay(250);

 }
 
  if(digitalRead(LEVEL) == HIGH and (dbMax) >= 25 and (dbMax) <= 79)

 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("SDMA rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor(0,1);
  lcd.print("<OK>");
  lcd.setCursor (5,1);
  lcd.print(dbAVal1,1);
  lcd.setCursor(11,1);
  lcd.print(dbAVal2,1);
  delay(250);

 }

 if(digitalRead(LEVEL) == LOW and (dbMax) >= 95)
 
 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("NSW rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor (0,1);
  lcd.print(" *INFRINGEMENT*");
  digitalWrite(ALARM, HIGH);
  delay(4000);
  digitalWrite(ALARM, LOW);
  delay(250);
  
 }

  if(digitalRead(LEVEL) == LOW and (dbMax) >= 88 and (dbMax) <= 94)

 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("NSW rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor (3,1);
  lcd.print("* AT RISK *");
  digitalWrite(ALARM, HIGH);
  delay(750);
  digitalWrite(ALARM, LOW);
  delay(750);
  digitalWrite(ALARM, HIGH);
  delay(750);
  digitalWrite(ALARM, LOW);
  delay(250);

 }


 if(digitalRead(LEVEL) == LOW and (dbMax) >= 25 and (dbMax) <= 87)

 {

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("NSW rd.");
  lcd.setCursor (9,0);
  lcd.print (dbMax, 1);
  lcd.setCursor (13,0);
  lcd.print("dbA");
  lcd.setCursor(0,1);
  lcd.print("<OK>");
  lcd.setCursor (5,1);
  lcd.print(dbAVal1,1);
  lcd.setCursor(11,1);
  lcd.print(dbAVal2,1);
  delay(250);
 }
 }


 
