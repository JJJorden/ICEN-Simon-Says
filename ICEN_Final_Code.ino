const int buzzer = 9; //buzzer to arduino pin 9
const int numPairs = 3;
const int ledPins[numPairs] = {13,12,4};
const int buttonPins[numPairs] = {2,3,11};
const int tones[numPairs] = {1000,2000,3000};// grouped the leds and buttons as an array
const int failTone = 500;// tone of for when you get it wrong
int randoo = 5;// first seed
int level = 1;// levels
void setup() {
  for(int i=0; i<numPairs; ++i)//loops the ledpins for output and buttons to input
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}
void clearLeds(int value = LOW)//turns all the leds to LOW/0 which is off
{
  for(int i=0; i<numPairs; ++i)// Sets numpairs which is the 3 numbers for button and led pins to value which is low
    digitalWrite(ledPins[i], value);
}
void setLed(int l)
{
  clearLeds();//Turns them all off but  then turns only one back on
  digitalWrite(ledPins[l], HIGH);
}
void output(int p)
{
  setLed(p);//Turns on the light and plays sound
  tone(buzzer, tones[p]);
  delay(1000);
  clearLeds();//Turns off the light and stops after second
  noTone(buzzer);
  delay(100);
}
void playSequence()
{
  randomSeed(randoo);// changes the game so it plays a different sequnce the next time your play it
  for(int i=0; i<level; ++i)
    output(random(numPairs));
}
int getInput()// gets input and returns buttons pressed 
{
  while(true)
  {
  for(int i=0; i<numPairs; ++i)// Loops through buttons to check if its pressed
    if(digitalRead(buttonPins[i]) == LOW)
    {
      delay(5); 
      if(digitalRead(buttonPins[i]) == LOW)// If the buttons pressed returns the button pressed
        return i;
    }
  }
  
}
void fail()
{
  tone(buzzer, failTone);//Plays the failtone for the buzzer
  for(int i=0; i<10; ++i)
  {// Loops for the all the leds equal to low and delays repeats for high
    clearLeds(LOW);
    delay(100);
    clearLeds(HIGH);
    delay(100);
  }
  noTone(buzzer);//resets the game
  level = 0;
  randoo = millis();// Sets it to a random sequence
  delay(2500);
  clearLeds(LOW);//Sets LEDs to low or not on
  delay(2500);
}
int getInputs()// Gets the inputs then gets the first seed
{
  randomSeed(randoo);
  for(int i=0; i<level; ++i)// Loops and gets the input in the next sequence
  {
    int n = getInput();
    int r = random(numPairs);
    if(n != r)
      fail();
    else
      output(n);
  }
}
void loop() {// Increases the level plays the sequence and gets the inputs from the player
  playSequence();
  getInputs();
  level++;
  delay(2000);
}
