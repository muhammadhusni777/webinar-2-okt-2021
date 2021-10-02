#include<avr/wdt.h>
#include<EEPROM.h>

int red = 13;
int yellow = 12;
int green = 11;
int cycle = 0;
int red_cycle = 10000;
int yellow_cycle = 3000;
int green_cycle = 10000;

int cycle_memory = 0;
unsigned long Time;
unsigned long time_prev;

//count time per loop
unsigned long time_now;
unsigned long time_now_prev;
unsigned long time_per_loop;

int hang_pin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(hang_pin, INPUT_PULLUP);
  wdt_enable(WDTO_1S);
 // cycle = EEPROM.read(cycle_memory);
  
}

void loop()
{
  time_now = millis();
  //Serial.println(time);
  Serial.println(cycle);
 
  if (cycle == 0){
  Time = millis() - time_prev;
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
    if (Time > red_cycle) {
    cycle = 1;
    time_prev = millis();
    }
  }
  
  if (cycle == 1){
  Time = millis() - time_prev;
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
    if (Time > yellow_cycle) {
    cycle = 2;
    time_prev = millis();
    }
  }
  
  if (cycle == 2){
  Time = millis() - time_prev; 
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);

  
  
    if (Time > green_cycle) {
    cycle = 0;
    time_prev = millis();
    }
  }


  //hang condition
  if (digitalRead(hang_pin) == 0){
  while(1){}
  }

  time_per_loop = time_now - time_now_prev;
  Serial.print("t/loop : ");
  Serial.println(time_per_loop);
  time_now_prev = time_now;
 // EEPROM.update(cycle_memory, cycle);
  wdt_reset();
}
