


/* include library */
#include <ESP8266WiFi.h>
#include <Servo.h>

Servo myservo; 

/* define port */
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "krishna";
const char* password = "krishna123";

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */
/*int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
/*int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
/*int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
/*int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
/*int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
/*int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */
int pos = 90;
void setup()
{
  /* initialize motor control pins as output */
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(D5, OUTPUT); 
  pinMode(D6, OUTPUT);
  myservo.attach(D7); 
  /* start server communication */
  Serial.begin(115200);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Connecting to WIFI");
  WiFi.begin("saiteja", "saitej123");
  while ((!(WiFi.status() == WL_CONNECTED))) 
  {
    delay(500);
    Serial.print("..");
  } 
  Serial.println("I am Connected");
  Serial.println("My Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();

  for (  pos = 0 ; pos >= 90 ; pos = pos + 1) 
   {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1);                       // waits 15ms for the servo to reach the position
  }

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "Forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if (data == "Down") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "Left") TurnLeft();
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "Right") TurnRight();
    /* If the incoming data is "stop", run the "MotorStop" function */
    else if (data == "Stop") MotorStop();

    
    else if (data == "RotateRight") RotateRight();

    else if (data == "RotateLeft") RotateLeft();
    
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
  
  analogWrite(D0,255);
  analogWrite(D1,0);
  analogWrite(D2,255);
  analogWrite(D3,0);
  delay(500);
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
  Serial.println("forward");
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  
  analogWrite(D0,0);
  analogWrite(D1,255);
  analogWrite(D2,0);
  analogWrite(D3,255);
  delay(500);
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
   Serial.println("backward");
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  analogWrite(D0,255);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,255);
  delay(500);
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
   Serial.println("left");
}


/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  analogWrite(D0,0);
  analogWrite(D1,255);
  analogWrite(D2,255);
  analogWrite(D3,0);
  delay(500);
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);

 Serial.println("right");}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
  delay(500);
  analogWrite(D0,0);
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
 Serial.println("stop");
}

void RotateRight(void)
{
  
  int right = pos;
  for (  ; right <= pos + 9 ; right += 1) 
   {
    myservo.write(right);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   pos = right;
 Serial.println("rotateright");
}

void RotateLeft(void)
{
  
  int left = pos;
  for (  ; left >= pos - 9 ; left = left-1) 
   {
    myservo.write(left);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   pos = left;
  Serial.println("rotateleft");
}


  
 /* for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}*/

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
