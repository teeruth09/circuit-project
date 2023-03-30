//int check = 1;
int input_status_led = A5;
int buzzer = 8;

int check = 1;

void setup()
{
  pinMode(input_status_led, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

}
void loop()
{
  Serial.println(analogRead(input_status_led));
  if (check == 1 and (analogRead(input_status_led)>30)) 
  {
    digitalWrite(buzzer, HIGH);
    delay(100); // หน่วงเวลา 1000ms
    check = 0;
  }
  else
  {
    digitalWrite(buzzer, LOW);
    check = 1;
  }
  Serial.print("buzzer:");
  Serial.println(digitalRead(buzzer));
  Serial.print("check:");
  Serial.println(check);
  delay(1000); // หน่วงเวลา 1000ms

}
