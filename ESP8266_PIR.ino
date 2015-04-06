//Change values in lines 5-7 and 98-101!

//WiFi Settings

// Set up macros for wifi and connection.
#define SSID "YOUR WIFI SSID"		// SSID
#define PASS "YOUR WIFI PASS"      // Network Password
#define HOST "YOUR DOMAIN eg: google.com"  // Webhost
//-------------------------------

//PIR Settings

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;       
int  interval = 1000; // Wait between dumps

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int nPIR_detect;
boolean noMotion = true;
int motion = 2;

int minSecsBetweenUpdates = 300; // 5 minutes
long lastSend = -minSecsBetweenUpdates * 1000l;
//-------------------------------

// Begin Setup
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
   nPIR_detect = 0;  

  // Test ESP8266 module.
  Serial.println("AT");
  delay(5000);
  if(Serial.find("OK")){
    connectWiFi();
  }
}

void loop(){
  // if you get a connection, report back via serial:
  {
  long now = millis();
  if (digitalRead(pirPin) == HIGH)
    {
      if (now > (lastSend + minSecsBetweenUpdates * 1000l) || noMotion == true)
        {
          int motion = 1;
          lastSend = now;
          noMotion = false;
          Serial.println("Motion");
          sendData(String(motion)); 
        } 
      else
        {
        //Serial.println("Too soon motion");
        }
    }
  else 
    {
      if (now > (lastSend + minSecsBetweenUpdates * 2000l))
        {
          int motion = 0;
          lastSend = now;
          noMotion = true;
          Serial.println("No motion");
          sendData(String(motion)); 
        }         
       else
        {
        //Serial.println("Too soon no motion");
      } 
      }  
  }   
  delay(interval);
}

void sendData(String motion){
  // Set up TCP connection.
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += HOST;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);

  // Send data.
  cmd = "GET /arduino/add_data.php"; //Place the link to your PHP script here
  cmd += "?motionornot=";            //first selector
  cmd += motion;                     //value (1 or 0)
  cmd += " HTTP/1.1\r\nHost: www.google.com\r\n\r\n\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")){
    Serial.print(cmd);
  }
  
}

boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  if(Serial.find("OK")){
    Serial.println("Connection");
    return true;
  }
  else{
    Serial.println("No Connection");
    return false;
  }
}
