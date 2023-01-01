// GATE code 
 

#define c_w 5
#define c_c_w 6
#define c_w_speed 9
#define IC_pin 4

// #define c_c_w_speed 8;

#define trigpin 10 
#define echopin 13
long duration , distance ;


int speed = 255;
int speed2 = 0;

void clockwise(){
  analogWrite(c_w_speed , speed);
  digitalWrite(c_w , HIGH);
  digitalWrite(c_c_w , LOW );
}
void stop(){
  analogWrite(c_w_speed , 0);
  digitalWrite(c_w , LOW);
  digitalWrite(c_c_w , LOW );
}

void counterclockwise(){
  analogWrite(c_w_speed , speed);
  digitalWrite(c_w , LOW);
  digitalWrite(c_c_w , HIGH );
}


void setup() {
  // put your setup code here, to run once:
pinMode(trigpin , OUTPUT);
pinMode(echopin ,INPUT);
pinMode(c_w ,OUTPUT);
pinMode(c_c_w ,OUTPUT);
pinMode(IC_pin ,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(IC_pin,HIGH);
  digitalWrite(trigpin , LOW);
 delayMicroseconds(2);
  digitalWrite(trigpin , HIGH);
 delayMicroseconds(10);
 digitalWrite(trigpin,0);
  duration = pulseIn(echopin , HIGH); // pulse in returns time in which value of the pin turned from high to low or low to high depending on the setting state(HIGH or LOW)
  distance = duration * (343*0.0001  / 2) ; // m 
  Serial.println(distance);
   delay(2);

   if(distance <= 70){
     clockwise();
     delay(7000);
     stop() ;
     delay(10000);            
     counterclockwise();
     delay(7000);
   }
   
}
