//the three mood buttons
const int happyButton = 4;
const int sadButton = 3;
const int mysteryButton = 2;


const int potPin = A5;
const int buzzerPin = 6;


int happyNotes[] = {262, 330, 392, 523};
int sadNotes[] = {220, 262, 330, 294};
int mysteryNotes[] = {311, 370, 440, 415};


int currentMood = 0; //remembers which mood is playing
int noteIndex = 0; //remembers which note we are on
int lastFrequency = -1; //remembers the last sound played


unsigned long lastNoteTime = 0; //remembers when the note started


void setup() { //runs once when Arduino starts
  pinMode(happyButton, INPUT);
  pinMode(sadButton, INPUT);
  pinMode(mysteryButton, INPUT);
  Serial.begin(9600);
}


void loop() { 


  int potValue = analogRead(potPin);//reads the potentiometer value (0 to 1023)


  //turns the potentiometer value into a pitch change
  int pitchChange = map(potValue, 0, 1023, 33, 180);


  int mood = 0; //starts with no mood selected


  if (digitalRead(happyButton) == HIGH) { //if happy is pressed
    mood = 1; //select happy
  }
  else if (digitalRead(sadButton) == HIGH) { //if sad is pressed
    mood = 2; //select sad
  }
  else if (digitalRead(mysteryButton) == HIGH) { //if mystery is pressed
    mood = 3; //select mystery
  }
Serial.println(potValue);
  if (mood == 0) { //if no button is pressed
    noTone(buzzerPin); //then stop the sound
    currentMood = 0; //and reset the mood
    lastFrequency = -1; //forget the previous sound
    return; //start the loop again
  }


  int* melody = happyNotes; //start with the happy notes
  int noteDuration = 180; //each Happy note lasts 180 milliseconds


  if (mood == 1) { //if happy is selected
    melody = happyNotes; //use the happy notes
    noteDuration = 400; //so each note lasts 400 milliseconds
  }
  else if (mood == 2) { //if sad is selected
    melody = sadNotes; //use the sad notes
    noteDuration = 400; //make the notes slower
  }
  else if (mood == 3) { //if mystery is selected
    melody = mysteryNotes; //use the mystery notes
    noteDuration = 260; //set the note speed
  }


  if (mood != currentMood) { //if we changed to a different mood
    currentMood = mood; //remember the new mood
    noteIndex = 0; //start from the first note
    lastNoteTime = millis(); //remember the current time
    lastFrequency = -1; //get ready to play a new note
  }


  //check if it is time for the next note
  if (millis() - lastNoteTime >= noteDuration) {
    noteIndex = (noteIndex + 1) % 4; //move to the next of four notes
    lastNoteTime = millis(); //remember when this note started
  }


  //get the note and change its pitch
  int frequency = melody[noteIndex] + pitchChange;


  if (frequency != lastFrequency) { //if the sound needs to change
    tone(buzzerPin, frequency); //play the sound through the speaker
    lastFrequency = frequency; //remember the sound we played
  }
}

