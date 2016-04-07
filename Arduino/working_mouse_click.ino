int flexSensorPin = A4; //analog pin 0
int flag = 1;
int count_R = 0;
int count_L = 0;
byte byteRead;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int flexSensorReading = analogRead(A4);
  
     /*  check if data has been sent from the computer: */
  if (Serial.available()) {
  
   if (flag == 1 & flexSensorReading > 200)
  {
    if (flexSensorReading < 325)
      {
        count_L++;
        if(count_L > 3){
            Serial.write("l \n");
        }
    
        
  //      Serial.print('\n');
      }
       else if (flexSensorReading > 430)
      {
        count_R++;
        if(count_R > 3){
            Serial.write("r \n");
        }
  //      Serial.print('\n');
        
      }
       else
      {       
        if(count_L > 0 && count_L < 3){
            Serial.write("L \n");     
        }
        if(count_R > 0 && count_R < 3){  
            Serial.write("R \n"); 
        }
        count_L = 0;
        count_R = 0; 
        Serial.write("0 \n");
      }
        delay(100);
  }
   else if (flexSensorReading < 200 & flag == 0)
  {
        flag = 1;
        delay(500);
  }
   else if (flexSensorReading < 200 & flag == 1)
  {
        flag = 0;
        delay(500);
  }
   else
  {
    Serial.write("F \n");
    count_R = 0;
    count_L = 0;
    delay(100);
  }
  }

  
}
