int triggerPin = 7; //triggering on pin 7
int echoPin = 8;    //echo on pin 8
int LED = 13; //led pin
int info = 0;//variable for the information comming from the bluetooth module
int state = 0;//simple variable for displaying the state

void setup() { //we will be combinig both setups from the codes
  
  Serial.begin(9600);  //we'll start serial comunication, so we can see the distance on the serial monitor
  
  pinMode(triggerPin, OUTPUT); //defining pins
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);    //defining LED pin
  digitalWrite(LED, LOW);  //once the programm starts, it's going to turn of the led, as it can be missleading.
  
}

void loop(){ //here we combine both codes to work in the loop
  bluetooth();
  sensor();
}


void bluetooth() { //loop from the bluetooth code is renamed to "bluetooth" void
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

void sensor() { //loop from the sensor code is renamed to the "sensor" void
  
  int duration, distance;    //Adding duration and distance
  
  digitalWrite(triggerPin, HIGH); //triggering the wave(like blinking an LED)
  delay(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
  distance = (duration/2) / 29.1; //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number
  
  Serial.print(distance);    //printing the numbers
  Serial.print("cm");       //and the unit
  Serial.println(" ");      //just printing to a new line
  
  //adding for mesuring distance where the led will turn off, even if we tell it to turn off when we chose so in the app
  
  if(distance <= 20){  //if we get too close, the LED will turn off, that's the method with my RC car, if it gets too close, it turns off, but that will be in the next instructable :)
    digitalWrite(LED, LOW);
    Serial.println("TOO CLOSE!!!");
    delay(2000); //so the stopping is visabl
  }
}
