  /* | ESP32 Pin | TB6612FNG Pin |
| --------- | ------------- |
| 18        | PWMA          |
| 19        | STBY          |
| 22        | AIN2          |
| 23        | AIN1          |
| 32        | PWMB          |
| 13        | BIN1          |
| 12        | BIN2          |
*/
#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "ESP32-Car";
const char* password = "88888888";
WebServer server(80);
int pwma = 18;
int pwmb = 32;
int stby = 19;
int ain1 = 23;
int ain2 = 22;
int bin1 = 13;
int bin2 = 12;
int speed = 200;
bool movingForward = false;
bool turningR = false;
bool turningL = false; 

void forward(int speed) {
  ledcWrite(pwma, speed);
  ledcWrite(pwmb, speed);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, HIGH);
}

void stop() {
  ledcWrite(pwma, 0);
  ledcWrite(pwmb, 0);
}

void reverse(int speed) {
  ledcWrite(pwma, 200);
  ledcWrite(pwmb, 200);
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);
}

void rightturn(int speed) {
  ledcWrite(pwma, speed);
  ledcWrite(pwmb, speed);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, HIGH);
  turningR = true;
  turningL = false;
}

void leftturn(int speed) {
  ledcWrite(pwma, speed);
  ledcWrite(pwmb, speed);
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, HIGH);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, HIGH);
  turningL = true;
  turningR = false;
}

void doForward() {
    forward(speed);
    movingForward = true;
    server.send(200, "text/plain", "Forward");
}

void doLeft() {
    leftturn(speed);
    server.send(200, "text/plain", "Left");
}

void doRight() {
    rightturn(speed);
    server.send(200, "text/plain", "Right");
}

void doBrake() {
  if (movingForward == true || turningR == true || turningL == true) {
    speed -= 200;
    forward(speed);
    Serial.println(speed);

      if (speed <= 0) {
  stop();
  movingForward = false;
  turningR = false;
  turningL = false;
  speed = 500;
  }
}
    server.send(200, "text/plain", "Brake");
}

void doStop() {
    stop();
    movingForward = false;
    turningR = false;
    turningL = false;
    speed = 500;
    server.send(200, "text/plain", "Stop");
}

void doReverse(){
  if (movingForward == false) {
    reverse(300);
}
    server.send(200, "text/plain", "Reverse");
}

void doAccelerate(){
  speed += 25;
      if (turningR == false && turningL == false && movingForward == true) {
        forward(speed);
      Serial.println(speed);
    }

      if (turningR == true && turningL == false && movingForward == true) {
        rightturn(speed);
      }

      if (turningR == false && turningL == true && movingForward == true) {
        leftturn(speed);
      }
}

void setup() {
Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println(ssid);
  Serial.println(password);
  Serial.println("IP adress: ");
  Serial.println(WiFi.softAPIP());

  server.on("/forward", doForward);
  server.on("/left", doLeft);
  server.on("/right", doRight);
  server.on("/brake", doBrake);
  server.on("/stop", doStop);
  server.on("/reverse", doReverse);
  server.on("/accelerate", doAccelerate);
  server.begin();

  pinMode(pwma, OUTPUT);
  ledcAttach(pwma, 1000, 10);
  ledcAttach(pwmb, 1000, 10);
  pinMode(stby, OUTPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(stby, OUTPUT);

  digitalWrite(stby, HIGH);
 
}

void loop() {
server.handleClient();
if (Serial.available()) {
  char command = Serial.read();

  if (command == 'w') {
    forward(speed);
    movingForward = true;
  }

  if (command == 'q') {
    stop();
    movingForward = false;
    turningL = false;
    turningR = false;
    speed = 500;
  }

  if (command == 'r' && movingForward == false) {
    reverse(300);
  }

  if (command == 'd') {
    rightturn(speed);
  }

  if (command == 'a') {
    leftturn(speed);
  }

  if (command == 'e' && movingForward == true) {
      speed += 25;
      if (turningR == false && turningL == false && movingForward == true) {
        forward(speed);
      Serial.println(speed);
    }

      if (turningR == true && turningL == false && movingForward == true) {
        rightturn(speed);
      }

      if (turningR == false && turningL == true && movingForward == true) {
        leftturn(speed);
      }

  }

  if (command == 's' && (movingForward == true || turningR == true || turningL == true)) {
    speed -= 200;
    forward(speed);
    Serial.println(speed);

      if (speed <= 0) {
  stop();
  movingForward = false;
  turningR = false;
  turningL = false;
  speed = 500;
  }
  }

}
}
