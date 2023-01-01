#include<Servo.h>
Servo ballservo;

// WHEELS AND LINE FOLLOWE**

#define rightForward 4
#define rightBackward 5 
#define leftForward 6
#define leftBackward 7
#define rightSpeed 3
#define leftSpeed 8
#define right_IR 2
#define middle_IR 11
#define left_IR 12
int Speed = 60  ;

int turning_speed = 80 ;
bool returndir = 0;

//shooting
#define shaftPos 29
#define shaftNeg  14
#define zinadPos 15
#define zinadNeg 16
#define shaftsp 13
#define zinadsp 10


//#define right_power 
#define middle_power 36 
#define left_power 9

// COLOR SENSOR STAFF*******
#define S0 26
#define S1 28
#define S2 30
#define S3 32
#define sensorOut 40

int frequency = 0;
int current_color_state = -1;
int yellow ;
int prev_s ;
int color_state = 0 ;

// IR READINGS***********


bool rightsignal ;
bool leftsignal ;
bool middlesignal ;



int sp2 = 0 ;
void shootingRed (){
// first shaft motor
// zinad pullup
digitalWrite(zinadPos,1);
digitalWrite(zinadNeg,0);
analogWrite(zinadsp,70); // different speed may change
delay(500);// different value may change

//shaft return back...
digitalWrite(shaftPos,1);
digitalWrite(shaftNeg,0);
analogWrite(shaftsp,70); // different speed may change
delay(1000);// different value may change

// catch the shaft ...
digitalWrite(zinadPos,0);
digitalWrite(zinadNeg,1);
analogWrite(zinadsp,70); // different speed may change
delay(500);// different value may change

//relase the shaft wire,,,
digitalWrite(shaftPos,0);
digitalWrite(shaftNeg,1);
analogWrite(shaftsp,70); // different speed may change
delay(2000);// different value may change

// ball download
ballservo.write(0);  // depends on where the ball is and the home position of the servo
delay(2000);
ballservo.write(90);// return the servo to the normal position...  
delay(2000);

// release the shaft from the zinad
digitalWrite(zinadPos,1);//shooting begins
digitalWrite(zinadNeg,0);
analogWrite(zinadsp,255); // different speed may change
delay(500);
}

void shootinggreen (){
// first shaft motor
// zinad pullup
digitalWrite(zinadPos,1);
digitalWrite(zinadNeg,0);
analogWrite(zinadsp,70); // different speed may change
delay(500);// different value may change

//shaft return back...
digitalWrite(shaftPos,1);
digitalWrite(shaftNeg,0);
analogWrite(shaftsp,70); // different speed may change
delay(1000);// different value may change

// catch the shaft ...
digitalWrite(zinadPos,0);
digitalWrite(zinadNeg,1);
analogWrite(zinadsp,70); // different speed may change
delay(500);// different value may change

//relase the shaft wire,,,
digitalWrite(shaftPos,0);
digitalWrite(shaftNeg,1);
analogWrite(shaftsp,70); // different speed may change
delay(2000);// different value may change

// ball download
ballservo.write(180);  // depends on where the ball is and the home position of the servo
delay(2000);
ballservo.write(0);// return the servo to the normal position...  
delay(2000);

// release the shaft from the zinad
digitalWrite(zinadPos,1);//shooting begins
digitalWrite(zinadNeg,0);
analogWrite(zinadsp,255); // different speed may change
delay(500);
}

void forward ()
{ analogWrite(rightSpeed,Speed);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);
  analogWrite(leftSpeed,Speed);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
  }

void right ()
{ analogWrite(rightSpeed,sp2);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);
  analogWrite(leftSpeed,turning_speed);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,HIGH);
      
  } 
void backright(){
  analogWrite(rightSpeed,sp2);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);
  analogWrite(leftSpeed,turning_speed);
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  }
void left ()
{analogWrite(rightSpeed,turning_speed);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,HIGH);
  analogWrite(leftSpeed,sp2);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
   
  }  
void backlift(){
  analogWrite(rightSpeed,turning_speed);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);
  analogWrite(leftSpeed,sp2);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
   
  }
void Stop ()
{analogWrite(rightSpeed,0);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);
  analogWrite(leftSpeed,0);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);}  


  void backward ()
{ analogWrite(rightSpeed,Speed);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightBackward,LOW);
  analogWrite(leftSpeed,Speed);
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftBackward,LOW);
  }
int color_check(){
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
 
  frequency = pulseIn(sensorOut, LOW);
//
  Serial.print("R= ");
 Serial.print(frequency);
  int red = frequency ;
  Serial.print("  ");
  delay(100);

    digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
 
  frequency = pulseIn(sensorOut, LOW);
  
  Serial.print("B= ");
  Serial.print(frequency);
  int blue = frequency ;
  Serial.print("  ");
   delay(100);

   
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  frequency = pulseIn(sensorOut, LOW);
 
  Serial.print("G= ");
 Serial.print(frequency);
int green = frequency ;
  
  Serial.println("  ");
  delay(100);

  
  if (green > 35 )
  {
    if (blue > red )
    {
      Serial.println(" I read RED " );
    //  color_state = 1 ;
      return 1;
      }
    else if(red> blue)
    {
          Serial.println(" I read Black " );  
         // color_state = 500 ;
          return 500;    
      }
  }
  
  else if(green<35)
  {
    if(red>=blue-1 && blue >23)
    {
            Serial.println(" I read Green " );
            //color_state = 10 ;  
            return 10;
      }
    else if (1&& blue > 22)//blue > red-1 
    {      Serial.println(" I read YELLOW " );
    //color_state = "yellow" ;  
    //color_state = 3 ;
    return 3;
      }  

      else
      {      Serial.println(" I read WHITE " );
      //color_state = "white" ; 
       //color_state = 0 ;
       return 0;
      }
 
    }
    Serial.println(color_state);
  } 
void line_follow(){
  rightsignal = digitalRead(right_IR);


leftsignal = digitalRead(left_IR);

middlesignal = digitalRead(middle_IR);  // low for black , high for white



  
  if(rightsignal == LOW && leftsignal==LOW ) // low for white , high for black   must contain the three ir readings 
  
  {forward();}
  
  else if(rightsignal == LOW && middlesignal == LOW && leftsignal==LOW) // white black white    there is a differens between the condition and the ccomments
  
  { forward();} 
     
  else if(rightsignal == LOW && middlesignal == HIGH && leftsignal==HIGH) //  white white black       there is a differens between the condition and the ccomments
  
  {left();}
  
  else if(rightsignal == HIGH && middlesignal == HIGH && leftsignal==LOW) // black white white       there is a differens between the condition and the ccomments
  
  
  {right();}
  
  else if (rightsignal == HIGH  && middlesignal == LOW && leftsignal == LOW) // black black white        there is a differens between the condition and the ccomments
  
  
  {
    right();
    returndir = 2;
  delay(450);
    
    }
  
  else if (rightsignal == LOW && middlesignal == LOW && leftsignal == HIGH ) //white black black     there is a differens between the condition and the ccomments
  
  {
    left();
  returndir =1;
  delay(450); }
  
  }


 

void setup() {
  // put your setup code here, to run once:
for ( int i = 3 ; i<11 ; i++)
{pinMode(i,OUTPUT);}

pinMode(2,INPUT);
//shooting motor pins...
for(int i= 13; i<18;i++){
  pinMode(i,OUTPUT);
}
pinMode(29,OUTPUT);
pinMode(10,OUTPUT);
//*********************



pinMode(50,OUTPUT);
//pinMode(50,OUTPUT);  REPEATED
pinMode(12,INPUT);
pinMode(11,INPUT);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(middle_power, HIGH) ;
  
  digitalWrite(left_power, HIGH) ;

  
//  digitalWrite(right_power, HIGH) ;
  
  
  //Serial.begin(9600);
  
    digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);

//digitalWrite(right_power, HIGH);
//digitalWrite(left_power, HIGH);
}
void loop() {
  
while(true){
//color_check() ;
current_color_state = color_check() ; 
//Serial.println(current_color_state);
//if (current_color_state !=1 || current_color_state !=10 || current_color_state != 3)
//
// {line_follow();}

line_follow();

if ( current_color_state ==1)
{
  Stop();
  shootingRed();          // the code of the shooting has its own delay...
  backward();       //must be very specific to return back on the line...
 delay(3000);
  if(returndir == 1){
    backlift();
    delay(450);
    line_follow();
    }
   else if (returndir==2){
    
    backright();
      delay(450);
    line_follow();
    }
  } 
if ( current_color_state ==10)
{
  Stop();
  shootinggreen();      // same as  1
  backward();      //must be very specific to return back on the line...
   delay(3000);
    if(returndir == 1){
    backlift();
    delay(450);
    line_follow();
    }
   else if (returndir==2){
    
    backright();
      delay(450);
    line_follow();
    }
  }  
}
}
