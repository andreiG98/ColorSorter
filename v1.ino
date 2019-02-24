#include <Servo.h>

Servo topServo;
Servo bottomServo;

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

#define rInfGreen 220
#define rSupGreen 330
#define gInfGreen 270
#define gSupGreen 330
#define bInfGreen 320
#define bSupGreen 430

#define rInfYellow 150
#define rSupYellow 210
#define gInfYellow 200
#define gSupYellow 280
#define bInfYellow 250
#define bSupYellow 350

#define rInfPurple 250
#define rSupPurple 390
#define gInfPurple 380
#define gSupPurple 590
#define bInfPurple 340
#define bSupPurple 520

#define rInfOrange 160
#define rSupOrange 220
#define gInfOrange 340
#define gSupOrange 400
#define bInfOrange 320
#define bSupOrange 400

int frequency = 0;
int color=0;
int lastSlidePosition = 65;
int currentSlidePosition = 65;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);
  
  Serial.begin(9600);
}
void loop() {

  color = 0;
  topServo.write(100);
  delay(500);
  
  for(int i = 100; i > 50; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);

  do {
    color = readColor();
    Serial.println(color);
  }while(color == 0);
  delay (20);

  moveSlide(color);
  delay(300);
  
  for(int i = 50; i > 23; i--) {
    topServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = 23; i < 100; i++) {
    topServo.write(i);
    delay(2);
  }
  delay(200);

  /*moveSlide(1);
  delay(300);
  moveSlide(2);
  delay(300);
  moveSlide(3);
  delay(300);
  moveSlide(4);
  delay(300);*/
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing GREEN color frequency
  Serial.print("  ");
  delay(50);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing BLUE color frequency
  Serial.println("  ");
  delay(50);
  
  if (R >= rInfGreen && R <= rSupGreen && G >= gInfGreen && G <= gSupGreen && B >= bInfGreen && B <= bSupGreen) {
      color = 1; // GREEN
  }  
  else if (R >= rInfYellow && R <= rSupYellow && G >= gInfYellow && G <= gSupYellow && B >= bInfYellow && B <= bSupYellow) {
      color = 2; // YELLOW
  } 
  else if (R >= rInfPurple && R <= rSupPurple && G >= gInfPurple && G <= gSupPurple && B >= bInfPurple && B <= bSupPurple) {
      color = 3; // PURPLE
  }
  else if (R >= rInfOrange && R <= rSupOrange && G >= gInfOrange && G <= gSupOrange && B >= bInfOrange && B <= bSupOrange) {
      color = 4; // ORANGE
  }
  else {
      color = 0; //no color
  }  
  return color;  
}

void moveSlide(int color) {
  
  switch(color) {
    case 1:
      Serial.println("Green");
      currentSlidePosition = 10;
      break;
    case 2:
      Serial.println("Yellow");
      currentSlidePosition = 35;
      break;
    case 3:
      Serial.println("Purple");
      currentSlidePosition = 65;
      break;
    case 4:
      Serial.println("Orange");
      currentSlidePosition = 90;
      break;
    default:
      Serial.println("No color");
      return;    
  }
  if (lastSlidePosition == currentSlidePosition)
    return;
  if (lastSlidePosition < currentSlidePosition) {
    for(int i = lastSlidePosition; i <= currentSlidePosition; i++) {
      bottomServo.write(i);
      delay(2);
    }
  } else {
    for(int i = lastSlidePosition; i >= currentSlidePosition; i--) {
      bottomServo.write(i);
      delay(2);
    }
  }

  lastSlidePosition = currentSlidePosition;
  
}
