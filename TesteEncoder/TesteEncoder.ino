/*
 Name:		TesteEncoder.ino
 Created:	5/3/2020 1:51:52 PM
 Author:	Kalil
*/

const int encoderPinA = 2;
const int encoderPinB = 4;
const int SWITCH = 3;
#define LED_2 9

volatile int encoder0Pos;

bool dir = false, dirAnt = false;
byte mudancas = 0;

void handleEncoder()
{
    dirAnt = dir;
    if (digitalRead(encoderPinB) == digitalRead(encoderPinA))//dec
    {
        encoder0Pos--;
        dir = false;
    }
    else //inc
    {
        encoder0Pos++;
        dir = true;
    }
    if (dir != dirAnt)
        mudancas++;
}

void handleSwitch()
{
    if (digitalRead(SWITCH))
    {
        encoder0Pos = 0; 
        mudancas = 0;
    }
	
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    attachInterrupt(0, handleEncoder, CHANGE);
    attachInterrupt(1, handleSwitch, CHANGE);
    Serial.begin(9600);
    Serial.println("start");       
}

void loop()
{
    Serial.print("Pos:");
    Serial.print(encoder0Pos, DEC);
    Serial.print("\tMud:");
    Serial.print(mudancas, DEC);
    Serial.print("\tP0:");
    Serial.print(encoder0Pos, DEC);
    Serial.print("\tPin 0:");
    Serial.print(digitalRead(encoderPinA) ? "alto" : "baixo");
    Serial.print("\tPin 1:");
    Serial.println(digitalRead(encoderPinB) ? "alto" : "baixo");
    digitalWrite(LED_BUILTIN, digitalRead(encoderPinA));
    digitalWrite(LED_2, digitalRead(encoderPinB));
}