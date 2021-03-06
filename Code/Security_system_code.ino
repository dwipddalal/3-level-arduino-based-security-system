// Team: "The Mechaneers"
// Names: "Dwip Dalal" and "Dhairya Shah"

// Importing required Libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Activating Servo motor variables
Servo gate1;
Servo gate3R;
Servo gate2;

//Defining all the Variables
int pos=0; 
String InPut = "";
String s = "";
Servo gate3L;
int IR_Pin = 13;
int pirState = LOW;
int a = 0;
int val ;   
int p = 0;
int g = 0;
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
// Variables of Keypad
const byte rows=4;
const byte cols=3;
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={0,2,3,4};
byte colPins[cols]={5,6,7};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="8980";
char* password2 = "109#*";
int currentposition=0;
int redled=10;
int greenled=11;
int buzz=8;
int invalidcount=12;
//Setting status of the variables
void setup()
{
displayscreen();
Serial.begin(9600);
pinMode(redled, OUTPUT);
pinMode(greenled, OUTPUT);
pinMode(buzz, OUTPUT);
pinMode(IR_Pin, INPUT);
gate3L.attach(12, 500, 2500);
gate1.attach(9); //SERVO ATTACHED//
gate3R.attach(10);//SERVO ATTACHED//
gate2.attach(11);//SERVO ATTACHED//
lcd.begin(16,2);
}

//Main void loop to open gates
void loop()
{
while (p == 0)
{
  if( currentposition==0)
  {
    displayscreen();
  }
  //Entering password for Gate 1
  int l ;
  char code=keypad.getKey();
  if(code!=NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
    for(l=0;l<=currentposition;++l)
    {
      lcd.print("*");
    }
    if (code==password[currentposition])
    {
      ++currentposition;
      if(currentposition==4)
      {
        unlockdoor();
        currentposition=0;
        p = 1;
      }
    }
    else
    {
       ++invalidcount;
       incorrect();
       currentposition=0;
    }
  }
}

//Entering password for Gate 2
while(p == 1)
{
  if(currentposition==0)
  {
    displayscreen();
  }
  int d ;
  char code2=keypad.getKey();
  if(code2!=NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
    for(d=0;d<=currentposition;++d)
    {
       lcd.print("*");
    }
    if (code2==password2[currentposition])
    {
      ++currentposition;
      if(currentposition==5)
      {
         unlockdoor2();
         currentposition=0;
         p = 2;
      } 
     }
    else
    {
      ++invalidcount;
      incorrect();
      currentposition=0;
    }
   }
}
while(p == 2)
{ 
  g = g + 1;
  //The bait for the gate 3 using serial monitor
  if (g == 1)
  {Serial.println("SINCE YOU HAVE SOLVE FIRST AND SECOND LAYER SO WE OPENED UP RIGHT GATE FOR YOUR EXIT. PLEASE TYPE YES OR NO!");
  }
   while (Serial.available() == 0)   
  {}
   s = Serial.readString();

  if (s == "YES")
  {
    while(a == 0)
    {
      val = digitalRead(IR_Pin);
      if (val == HIGH)
      { 
        digitalWrite(buzz, HIGH);  
        if (pirState == LOW) 
        { 
           Serial.println("Motion detected!");
           Serial.println("YOU ARE OVER BABE");
           pirState = HIGH;
           a = 1;
        }
      } 
      else 
      {
        digitalWrite(buzz, LOW); 
        if (pirState == HIGH)
        {
          Serial.println("Motion ended!");
          pirState = LOW;
        }
      }
    }
    while(1){}
  }
  
  //If thief is smart to ignore the bait 
  else if (s == "NO")
  {
    Serial.println("Enter combination(ALL CAPS)");  
    while (Serial.available() == 0)   
    {}  
    InPut = Serial.readString();
    if ( InPut == "LEFT")
    {
    Serial.println("Make good use of treasure");
    for (pos = 90; pos >=0; pos -= 1) 
    { gate3L.write(pos);
      delay(15);
    }
     while(1) {}
    }
    else
    {
     digitalWrite(buzz, HIGH);
     Serial.println("You are Over");
     while(1) {}
    }
  }
} 
// Loop ends
} 

//OPEN THE DOOR FUNCTION
void unlockdoor()
{
delay(900);
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("WALKS ON SAND");
lcd.setCursor(1,1);
lcd.println("FLOATS IN SKY#*");
for(pos = 90; pos>=0; pos-=1) // goes from 180 degrees to 0 degrees
{
gate1.write(pos); // tell servo to go to position in variable 'pos'
delay(5); // waits 15ms for the servo to reach the position
}
delay(500);
for(pos = 90; pos>=0; pos-=1) // goes from 90 degrees to 0 degrees
{
gate3R.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
delay(3000);
counterbeep();
delay(1000);
for(pos = 0; pos <= 90; pos +=5) // goes from 0 degrees to 180 degrees
{ // in steps of 1 degree
gate1.write(pos); // tell servo to go to position in variable 'pos'
delay(15);
currentposition=0;
lcd.clear();
displayscreen();
}
}

// Opening Gate 2 
void unlockdoor2()
{
delay(900);
lcd.setCursor(0,0);
lcd.print(" LET THE EAGLE ");
lcd.setCursor(0,1);
lcd.println("      FLY       ");
for(pos = 90; pos>=0; pos-=1) // goes from 90 degrees to 0 degrees
{
gate2.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
delay(2000);
delay(1000);
counterbeep2();
for(pos = 0; pos <= 90; pos +=5) // goes from 0 degrees to 90 degrees
{ // in steps of 1 degree
gate2.write(pos);
  // tell servo to go to position in variable 'pos'
delay(15);
currentposition=0;
lcd.clear();
displayscreen();
}
}

//Wrong password function
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("GET AWAY!!!");
lcd.setCursor(13,1);
digitalWrite(redled, HIGH);
digitalWrite(buzz, HIGH);
delay(3000);
lcd.clear();
digitalWrite(redled, LOW);
digitalWrite(buzz,LOW);
displayscreen();
}

//Clearing the screen function
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//Displaying screen Function
void displayscreen()
{
 
lcd.setCursor(0,0);
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
}

//Servo arm function
void armservo()
{
 
for (pos=180;pos<=180;pos+=50)
{
gate1.write(pos);
delay(5);
}
delay(5000);
for(pos=180;pos>=0;pos-=50)
{
gate1.write(pos);
}
}

//Counter beep function
void counterbeep()
{
delay(1200);
lcd.clear();
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("SUM IT UP");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("SUM IT UP");
delay(1000);
//2
lcd.setCursor(2,0);
lcd.println("SUM IT UP");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//3
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//4
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//5
lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");
delay(1000);
//6
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}
void counterbeep2()
{
delay(1200);
lcd.clear();
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//3
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//4
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
//5
lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");
delay(1000);
//6
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}
