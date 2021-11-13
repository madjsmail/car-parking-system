#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Servo myservo;



#define ir_car1 8
#define ir_car2 9
#define ir_car3 10
#define ir_car4 11
#define ir_car5 12
#define ir_car6 13



int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;

int allSpace = 6;  
int validID = 0;
int count = 0;
int red = 5 , grean = 4;
char c;
String id;
int pos = 0; // variable to store the servo position

void setup(){
Serial.begin(9600);
 myservo.attach(3);
 myservo.write(pos);
digitalWrite(red, HIGH);

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);
pinMode(ir_car5, INPUT);
pinMode(ir_car6, INPUT);
pinMode(red, OUTPUT);
pinMode(grean, OUTPUT);

Serial.println("Please scan your RFID TAG");

lcd.begin(20, 4);  
lcd.setCursor (0,1);
lcd.print("    Car  parking  ");
lcd.setCursor (0,2);
lcd.print("       System     ");
delay (500);
lcd.clear();  


Read_Sensor();

}


void loop(){
RFID() ;
Read_Sensor();
lcd.clear(); 
lcd.setCursor (0,0);
if(total_slot() == 6){

  lcd.print("Parking is Full");  
  delay(500);
}else{


  lcd.print(allSpace-total_slot());
  lcd.print(" free space         "); 
 
}




lcd.setCursor (0,1);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:free");}

lcd.setCursor (10,1);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:free");}

lcd.setCursor (0,2);
if(S3==1){lcd.print("S3:Fill ");}
     else{lcd.print("S3:free");}

lcd.setCursor (10,2);
if(S4==1){lcd.print("S4:Fill ");}
     else{lcd.print("S4:free");}

 lcd.setCursor (0,3);
if(S5==1){lcd.print("S5:Fill ");}
     else{lcd.print("S5:free");}

lcd.setCursor (10,3);
if(S6==1){lcd.print("S6:Fill ");}
     else{lcd.print("S6:free");}    


delay (500);




      digitalWrite(grean, LOW);
      digitalWrite(red, HIGH);

}




void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;

if(digitalRead(ir_car1) == 1){S1=1;}
if(digitalRead(ir_car2) == 1){S2=1;}
if(digitalRead(ir_car3) == 1){S3=1;}
if(digitalRead(ir_car4) == 1){S4=1;}
if(digitalRead(ir_car5) == 1){S5=1;}
if(digitalRead(ir_car6) == 1){S6=1;}  
}


int total_slot(){
  Read_Sensor();
    return S1+S2+S3+S4+S5+S6 ;
  }





void RFID()
{
 while(Serial.available()>0)
  {
    c = Serial.read();
   count++;
   id += c;
   if(count == 12)  
    {
      Serial.print(id);
      Serial.println(" is ") ;
      //break;
     //AB123456789B
      if(id=="AB123456789A")
      {
        Serial.println("Valid ");
        digitalWrite(grean, HIGH);
        digitalWrite(red, LOW);
         openGate();

  
        
      }
      else
      {
  
      Serial.println("Invalid");
      digitalWrite(grean, LOW);
      digitalWrite(red, HIGH);
      closeGate();
      }
    }
  }

  count = 0;
  id="";
  delay(500);



  
}

void openGate(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                                       // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 20 ms for the servo to reach the position
  }

  
}

void closeGate(){
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10 ms for the servo to reach the position
  }
}








  
