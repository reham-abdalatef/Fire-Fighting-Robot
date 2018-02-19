

const int trigPin = 36;
const int echoPin = 52;
const int trigPin1 = 41;
const int echoPin1 = 48;
const int trigPin2 =44;
const int echoPin2 = 26;
int analoginput=0;
int analogvalue;
int sum=0;
int relay=22,in1=31,in2=33,in3=35,in4=37,en1=11,en2=10;
int duration,duration1,duration2;
int distanceCm,distanceCm1,distanceCm2;

int buzzer=24;
int speedM=80;

long currenttime;
long previoustime;
int interval;
void setup() {
  // put your setup code here, to run once:
pinMode(analoginput,INPUT);
  pinMode(relay,OUTPUT);
    pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(trigPin1,OUTPUT);
pinMode(echoPin1,INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
}
void turnleft()
{
  digitalWrite(in1,1);
digitalWrite(in2,0);
digitalWrite(in3,0);
digitalWrite(in4,1);
analogWrite(en1,120);
analogWrite(en2,0); 
}
void turnright()
{
  digitalWrite(in1,0);
digitalWrite(in2,1);
digitalWrite(in3,1);
digitalWrite(in4,0);
analogWrite(en1,0);
analogWrite(en2,120); 
}
void stopcar()
{
  digitalWrite(in1,0);
digitalWrite(in2,0);
digitalWrite(in3,0);
digitalWrite(in4,0);
analogWrite(en1,0);
analogWrite(en2,0);
}
void detect()
{
  
  for(int i=0;i<10;i++)
  {
    analogvalue=analogRead(analoginput);
    sum+=analogvalue;
  }
  sum/=10;
  Serial.print("flame:");
  Serial.println(sum);
if(sum <305
)
{
 stopcar();
  digitalWrite(relay,1);
  for(int k=0;k<2;k++)
  {
    digitalWrite(buzzer,HIGH);
    delay(200);
    digitalWrite(buzzer,LOW);
    delay(200);
  }
  delay(3200);  
}
 digitalWrite(relay,0);
  }
  
void readUltrasonic(int D,int T,int trig,int echo)
{
  digitalWrite(trig, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
T = pulseIn(echo, HIGH);
// Calculating the distance
D= T*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(D);

}

void backward()
{
  digitalWrite(in1,0);
digitalWrite(in2,1);
digitalWrite(in3,0);
digitalWrite(in4,1);
analogWrite(en1,speedM);
analogWrite(en2,speedM);
}

void forward()
{
  digitalWrite(in1,1);
digitalWrite(in2,0);
digitalWrite(in3,1);
digitalWrite(in4,0);
analogWrite(en1,speedM);
analogWrite(en2,speedM); 
}

void loop() {

detect();  
forward();
delay(50);
detect();
//readUltrasonic(distanceCm,duration,trigPin,echoPin);
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration= pulseIn(echoPin, HIGH);
// Calculating the distance
distanceCm= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(duration);
detect();
if(distanceCm <= 15 && distanceCm>0 )
{
  stopcar();
delay(500);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1= pulseIn(echoPin1, HIGH);
// Calculating the distance
distanceCm1= duration1*0.034/2;

digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2= pulseIn(echoPin2, HIGH);
// Calculating the distance
distanceCm2= duration2*0.034/2;
while(distanceCm <=30 && distanceCm >0)
{
backward();
delay(5);
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration= pulseIn(echoPin, HIGH);
// Calculating the distance
distanceCm= duration*0.034/2;
}

if(distanceCm1 <=30 && distanceCm1 >0)
/*//if(distanceCm >=16 && distanceCm<=9 && distanceCm1<=30 && distanceCm2<=30 && distanceCm1 >0 && distanceCm2 >0)
{
  stopcar();
  delay(500);
}
else if(distanceCm1*/ 
//if(distanceCm1>distanceCm2)
{
  turnleft();
delay(900);
}
else
{
  turnright();
delay(1200);

}

detect();
stopcar();
digitalWrite(buzzer,1);
delay(200);
digitalWrite(buzzer,0);
delay(200);
}
}
