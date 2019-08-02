int LED = 13; //led pin
int info = 0;//variable for the information comming from the bluetooth module
int state = 0;//simple variable for displaying the state
void setup() {
  Serial.begin(9600); //making serial connection
  pinMode(LED, OUTPUT);    //defining LED pin
  digitalWrite(LED, LOW);  //once the programm starts, it's going to turn of the led, as it can be missleading.
}
void loop() {
  if(Serial.available() > 0){  //if there is any information comming from the serial lines...
    info = Serial.read();   
    state = 0;   //...than store it into the "info" variable
  }
  if(info == '1'){                //if it gets the number 1(stored in the info variable...
    digitalWrite(LED, HIGH);    //it's gonna turn the led on(the on board one)
    if(state == 0){              //if the flag is 0, than display that the LED is on and than set that value to 1
      Serial.println("LED ON");  //^^that will prevent the arduino sending words LED ON all the time, only when you change the state
      state = 1;
    }
   }
  else if(info == '0'){
    digitalWrite(LED, LOW);      //else, it's going to turn it off
    if(state == 0){
      Serial.println("LED OFF");//display that the LED is off
      state = 1;
     }
  }
}
