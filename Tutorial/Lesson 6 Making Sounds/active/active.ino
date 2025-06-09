//www.elegoo.com
//2023.05.06

int buzzer = 12;//the pin of the active buzzer
void setup()
{
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
}
void loop()
{
  int sound_duration = 500;
  for (int i = 0; i < 10; i++)
  {
    sound_duration = 1000/(i+1);
    //activate the active buzzer
    digitalWrite(buzzer, HIGH);
    delay(sound_duration);//wait for sound_duration ms
    //deactivate the active buzzer
    digitalWrite(buzzer, LOW);
    delay(sound_duration);//wait for sound_duration ms
  }
  //activate the active buzzer
  delay(5000);//keep playing sound for 5 seconds.
}
