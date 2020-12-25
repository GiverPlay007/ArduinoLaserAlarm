#define BUTTON 5
#define BUZZER 6

#define LED_ACTIVE 0
#define LED_ADJUST 1
#define LED_TRIGGER 2

#define LDR A0
#define ADJUST A1

#define FREQUENCY 9500

bool enabled = false;
bool triggered = false;
bool yetPressed = false;
bool buttonPressed = false;

unsigned int ldrLevel = 0;
unsigned int adjustLevel = 0;

void setup()
{
  pinMode(LDR, INPUT);
  pinMode(ADJUST, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ACTIVE, OUTPUT);
  pinMode(LED_ADJUST, OUTPUT);
  pinMode(LED_TRIGGER, OUTPUT);
}

void loop()
{
  checkButton();
  checkAlarm();
}

void checkButton()
{
  if(digitalRead(BUTTON) == 0)
  {
    yetPressed = false;
  }

  if(digitalRead(BUTTON) && !yetPressed)
  {
    buttonPressed = true;
  }

  if(buttonPressed)
  {
    handleButtonPress();
    buttonPressed = false;
  }
}

void checkAlarm()
{
  ldrLevel = analogRead(LDR);
  adjustLevel = analogRead(ADJUST);

  if(ldrLevel < adjustLevel)
  {
    if(enabled && !triggered)
    {
      digitalWrite(LED_TRIGGER, HIGH);
      tone(BUZZER, FREQUENCY);
      triggered = true;
    }
  }
}

void handleButtonPress()
{
  if(triggered)
  {
    digitalWrite(LED_TRIGGER, LOW);
    noTone(BUZZER);
    triggered = false;
    return;
  }

  if(enabled)
  {
    digitalWrite(LED_ACTIVE, LOW);
    enabled = false;
  }
  else
  {
    digitalWrite(LED_ACTIVE, HIGH);
    enabled = true;
  }  
}