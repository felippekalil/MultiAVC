/*
 Name:		TesteEncoder.ino
 Created:	5/3/2020 1:51:52 PM
 Author:	Kalil
*/

#define ENCODER_PIN_A  2 
#define ENCODER_PIN_B  3 
#define LED_2 9 
#define SWITCH 

volatile int encoder0Pos;
volatile int encoder1Pos;


void doEncoder0()
{
    if(digitalRead(ENCODER_PIN_B) == digitalRead(ENCODER_PIN_A))
    {
        encoder0Pos++;
    }
    else
    {
        encoder0Pos--;
    }
}

void doEncoder1()
{
    if(digitalRead(ENCODER_PIN_B) == digitalRead(ENCODER_PIN_A))
    {
        encoder1Pos++;
    }
    else
    {
        encoder1Pos--;
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(ENCODER_PIN_A, INPUT);
    digitalWrite(ENCODER_PIN_A, HIGH); 
    pinMode(ENCODER_PIN_B, INPUT);
    digitalWrite(ENCODER_PIN_B, HIGH);  
    attachInterrupt(0, doEncoder0, CHANGE); 
    attachInterrupt(1, doEncoder1, CHANGE);
    Serial.begin(9600);
    Serial.println("start");       
}

void loop()
{
    Serial.print("Pos:");
    Serial.print(encoder0Pos + encoder1Pos, DEC);
    Serial.print("\tP0:");
    Serial.print(encoder0Pos, DEC);
    Serial.print("\tP1:");
    Serial.print(encoder1Pos, DEC);
    Serial.print("\tPin 0:");
    Serial.print(digitalRead(ENCODER_PIN_A) ? "alto" : "baixo");
    Serial.print("\tPin 1:");
    Serial.println(digitalRead(ENCODER_PIN_B) ? "alto" : "baixo");
    digitalWrite(LED_BUILTIN, digitalRead(ENCODER_PIN_A));
    digitalWrite(LED_2, digitalRead(ENCODER_PIN_B));
}