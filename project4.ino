const int IR_LED_PIN = 7;   // IR LED pin
const int IR_RECEIVER_PIN = A5;  // IR receiver pin
const int BUZZER_PIN = 8;  // Buzzer pin
const int DEBOUNCE_DELAY = 50; // Debounce delay in milliseconds
const int led_red = 50;
const int led_green = 51;
const int led_yellow = 52;
int led_delay = 70;


int check = false;
int check1 = false;
int check2= false;
int check_state_servo = false;
int check3 =false;
  
#include <Servo.h>
Servo myservo; //ประกาศตัวแปรแทน Servo
Servo myservo2;

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28};
byte colPins[COLS] = {30, 32, 34, 36};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int log_password= 368;
int password = 0;

#include <LCD_I2C.h>
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

int debounceAnalogRead(int pin) {
  int val = analogRead(pin);
  delay(DEBOUNCE_DELAY);
  int newVal = analogRead(pin);
  if (abs(val - newVal) < 10) {
    return newVal;
  } else {
    return val;
  }
}

int respond_led1(int delays){
  digitalWrite(led_red,1);
  delay(delays);
  digitalWrite(led_green,1);
  delay(delays);
  digitalWrite(led_yellow,1);
  delay(delays);
  digitalWrite(led_red,0);
  delay(delays);
  digitalWrite(led_green,0);
  delay(delays);
  digitalWrite(led_yellow,0);
  
  }

int respond_led2(int delays){
  digitalWrite(led_red,1);
  delay(delays);
  digitalWrite(led_red,0);
  delay(delays);
  digitalWrite(led_green,1);
  delay(delays);
  digitalWrite(led_green,0);
  delay(delays);
  digitalWrite(led_yellow,1);
  delay(delays);
  digitalWrite(led_yellow,0);
  delay(delays);
  }

void setup() {
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  
  Serial.begin(9600);
  lcd.begin(); 
  lcd.backlight();
  myservo.attach(2); // กำหนดขา 9 ควบคุม Servo
  myservo2.attach(3);
}

void loop() {
  
  if(digitalRead(BUZZER_PIN) or check){
    respond_led2(led_delay);
    if(check1==false){
    lcd.setCursor(0,0);
    lcd.print("INSERT PASSWORD:))");
    }
    check = true;
    check1 = true;
    char key = keypad.getKey();
    if (key != NO_KEY and check2==false) {
      lcd.setCursor(1,0);
      lcd.print("INSERT PASSWORD :");
      lcd.setCursor(1,1);
      lcd.print(">>>>>>>");
      lcd.setCursor(8,1);
      lcd.print(key);
      lcd.setCursor(9,1);
      lcd.print("<<<<<<<");
      delay(1500);
      lcd.clear();

      password += int(key);
      if(password == log_password){
        check2=true;
        }
      Serial.println(password);
    }

    if(check2 == true and check3==false){ 
      lcd.setCursor(3,0);
      lcd.print("Success !!");
      delay(1000);
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("WELCOME :)");
      delay(1000); 
      lcd.clear();
      check_state_servo = true;
      }

   if(check_state_servo==true){
    for (int i = 180; i > 0; i--) {
    myservo.write(i);
    myservo2.write(i);                         
    delay(10);                     
  }
    check_state_servo = false;
    check3 =true;
    }
  
    
  digitalWrite(BUZZER_PIN, LOW);
//    
  }
 
  
  if(check == false){
    respond_led1(led_delay);
    lcd.setCursor(2,0);
    lcd.print("Secure Door :))");
    delay(1000);
    lcd.clear();    
    
    Serial.println(analogRead(IR_RECEIVER_PIN));
    digitalWrite(IR_LED_PIN, HIGH);
    delayMicroseconds(100);  // Replace with your desired IR signal timing
    digitalWrite(IR_LED_PIN, LOW);
    delay(10);  // Wait for receiver to settle
  
    // Read status of IR receiver with debouncing
    int receiverValue = debounceAnalogRead(IR_RECEIVER_PIN);
  
    // If the receiver value is high, turn on the buzzer
    if (receiverValue > 500) {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer ON");
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("Buzzer OFF");
    }
    
    delay(100);  // Replace with your desired loop delay
  }
}
