#define BUTTON 5
#define BUZZER 6
#define LDR A0

#define MIN_LIGHT_LEVEL 75
#define FREQUENCY 9500

bool enabled = false;
bool triggered = false;

void setup()
{
  pinMode(LDR, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  if(digitalRead(BUTTON))
  {
    if(!enabled)
    {
      enabled = true;
    }
    else if(triggered)
    {
      triggered = false;
      enabled = false;
      noTone(BUZZER);
    }
    else if(enabled)
    {
      enabled = false;
    }

    while(digitalRead(BUTTON));
  }

  if(analogRead(LDR) < MIN_LIGHT_LEVEL)
  {
    if(enabled && !triggered)
    {
      triggered = true;
      tone(BUZZER, FREQUENCY);
    }
  }
}