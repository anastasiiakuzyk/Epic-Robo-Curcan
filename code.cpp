#define D1 8
#define D2 9
#define D3 10
#define D4 11
#define D5 12
#define D6 13
#define BUTTON 2
int ledArray[] = {D1, D2, D3, D4, D5, D6};

// interval at which to blink (in milliseconds)
const int INIT_INTERVAL = 1000; 
int blinkInterval = INIT_INTERVAL;

int buttonState = 0;
bool buttonClicked = false;
int numberOfClicks = 0;

// unsigned long for variables that hold time
// the current time since the Arduino started program (in milliseconds)
unsigned long currentTimestampMs = 0;
// tracks the last time the LED was updated
unsigned long lastToggledTimestampMs = 0; 
// will toggle between LOW and HIGH
int ledState = LOW; 

void setup()
{
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600); 
  pinMode(BUTTON, INPUT);
  setupOutput();
  digitalWrite(ledArray[2], HIGH);
  digitalWrite(ledArray[4], HIGH);
  digitalWrite(ledArray[5], HIGH);
}

void loop()
{
  // read the state of the pushbutton value
  buttonState = digitalRead(BUTTON);
  
  if(buttonState == HIGH){
  	buttonClicked = true;
  }
  
  // if the button is clicked and then released, change frequency
  if(buttonClicked && buttonState == LOW){
    buttonClicked = false;
    numberOfClicks += 1;
    changeFrequency();
    Serial.println(blinkInterval);
  }

  currentTimestampMs = millis();
  
  // check to see if the time between now and the last time toggled
  // the LED has exceeded blink interval. 
  // if exceeded, toggle the LED
  if (currentTimestampMs - lastToggledTimestampMs >= blinkInterval) {
    // toggle the LED
    ledState = ledState == HIGH ? LOW : HIGH; 
    // store current time as toggle time
    lastToggledTimestampMs = currentTimestampMs; 
    // output the LED state
    digitalWrite(ledArray[2], ledState); 
  } 

}

void setupOutput()
{
  int sizeLedArray = sizeof(ledArray) / sizeof(ledArray[0]);

  for(int i = 0; i < sizeLedArray; i++) { 
      pinMode(ledArray[i], OUTPUT);
  }
}

void changeFrequency()
{
  if(numberOfClicks >= 3){
    numberOfClicks = 0;
    blinkInterval = INIT_INTERVAL;
  } else {
    blinkInterval /= 2;
  }
}
