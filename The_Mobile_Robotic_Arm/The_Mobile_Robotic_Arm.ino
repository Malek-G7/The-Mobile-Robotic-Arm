#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32Servo.h>
#include "Ultrasonic.h"

 
hw_timer_t * timer = NULL; // a pointer to a variable of type hw_timer_t
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //a variable of type portMUX_TYPE
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  ldr();
  portEXIT_CRITICAL_ISR(&timerMux);
 
}


Servo myservoV ;// vertical servo 
Servo myservoH; // horizontal servo
Servo myservoGrabber; // grabber servo


// dc motors
const int E1 = 25; // Right motor speed control
const int M1 = 26; // right motor direction control
const int E2 = 27; //left motor speed control
const int M2 = 14;// left motor direction control


int speed = 255; // speed of car
int pos = 0;    
int angle ;
//int sw =0;
String brightness ;
const int TEMP_PIN = 34;//34
long RangeInCentimeters;
float tempc , tempf;
int analogReading;
int trigPin =15;
int echoPin =14;
float duration_us;
float distance_cm;
int ldrStatus;
int ldrPin=2;
int ledPin= 12;

const char* ssid = "MalekiPh";
const char* password = "12345678";
String homePage = R"=====( 
 <!DOCTYPE html>
    <html>
    <head>
    <style>
    h1 {
      color: #DD1543;
      text-align: center;
    }
    h2 {
      color: #DD1543;
      text-align: center;
    }
    h3 {
      color: #DD1543;
    }
    .title{
    
    background:darkblue;
    font-size: 20px;
    
    }
    .button
    {
     background:linear-gradient(20deg, #191414,azure);;
    margin: 10px;
    padding: 10px;
    font-size: 40px;
    font-style: italic;  
    border-radius : 100px;
    width: 33%;
    text-align: center;
    }

    .flex-column{
    display: flex;
    flex-direction: column;
    background-color: darkblue;
    font-size: 20px;
    }
    .flex-row {
    display: flex;
    flex-direction: row;
    background:darkblue;
    margin: 0px;
    font-size: 20px;
    }
    .center {
  display: block;
  margin-left: auto;
  margin-right: auto;
  width: 50%;
}
    table {
      font-family: arial, sans-serif;
      border-collapse: collapse;
      width: 100%;
    }
    
    td, th {
      border: 1px solid #dddddd;
      text-align: left;
      padding: 8px;
      color : #DD1543;
    }
    
    tr:nth-child(even) {
      background-color: #dddddd;
    }
    
    
    </style>
    </head>
    
     <body>
     <div class = "title"> <H1 >The Mobile Robotic Arm Controller</H1><br>
     </div>
     <div class="flex-column">
     <h2>Car Controller</h2><br>
     <div class="flex-row">
     <Button class = "button" onclick="loadFWDL()">fwd left</Button>
     <Button class = "button" onclick="loadFWD()">fwd</Button>
     <Button class = "button" onclick="loadFWDR()">fwd right</Button>
     </div>
     <div class="flex-row">
     <button class = "button" style="visibility:hidden;" ></button>
     <Button class = "button" onclick="loadSTOP()">STOP</Button>
     <button class = "button"  style="visibility:hidden;" ></button>
     </div>
     <div class="flex-row">
    <Button class = "button" onclick="loadBACKL()">back left</Button>
    <Button class = "button" onclick="loadBACK()">back</Button>
    <Button class = "button" onclick="loadBACKR()">back right</Button>
    </div>
    <br><H2>Robotic Arm Controller</H2><br>
    <div class="flex-row">
    <Button class = "button" onclick="closeclaw()">closeclaw</Button>
    <Button class = "button" onclick="armup()">arm up</Button>
    <Button class = "button" onclick="openclaw()">openclaw</Button>
    </div>
    <div class="flex-row">
    <Button class = "button" onclick="armleft()">arm left</Button>
    <Button class = "button" onclick="armdown()">arm down</Button>
    <Button class = "button" onclick="armright()">arm right</Button>
    </div>
    <div>
    <br><H2>Sensor Readings</H2><br>
    </div>
    <div class = flex-row>
    <table>
      <tr>
        <th>Temperature (°C)</th>
        <th>Ultrasonic (cm)</th>
        
      </tr>
      <tr>
        <td id="TempDataDisplay">t</td>
        <td id="UltrasonicDataDisplay">5cm</td>
        
      </tr>
      </table>

<script>
setInterval(loadUltrasonicInfo, 1000);
function loadUltrasonicInfo() {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("UltrasonicDataDisplay").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/getUltrasonic", true);
xhttp.send();
}
</script>
<script>
setInterval(loadTempInfo, 1000);
function loadTempInfo() {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("TempDataDisplay").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/getTemp", true);
xhttp.send();
}
</script>
 <script>
function loadFWD() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/forward", true);
xhttp.send();
}
</script>
<script>
function loadFWDL() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/forwardL", true);
xhttp.send();
}
</script>
<script>
function loadFWDR() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/forwardR", true);
xhttp.send();
}
</script>
<script>
function loadSTOP() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/STOP", true);
xhttp.send();
}
</script>
<script>
function loadBACK() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/backward", true);
xhttp.send();
}
</script>
<script>
function loadBACKR() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/backwardR", true);
xhttp.send();
}
</script>
<script>
function loadBACKL() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/backwardL", true);
xhttp.send();
}
</script>
<script>
function closeclaw() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/closeclaw", true);
xhttp.send();
}
</script>
<script>
function openclaw() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/openclaw", true);
xhttp.send();
}
</script>
<script>
function armup() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/armup", true);
xhttp.send();
}
</script>
<script>
function armdown() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/armdown", true);
xhttp.send();
}
</script>
<script>
function armleft() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/armleft", true);
xhttp.send();
}
</script>
<script>
function armright() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "/armright", true);
xhttp.send();
}
</script>
    </div>
    </div>
    </body>
    </html>
  )=====";

WebServer server(80); // server object

void handleRoot() {
  Serial.println("Sending home page");
  server.send(200, "text/html", homePage);
}
void getTheUltrasonic() {
  Serial.println("Sending Ultrasonic data:");
  server.send(200, "text/plain", UltrasonicS());
}
void getTheTemp() {
  Serial.println("Sending Temp data:");
  server.send(200, "text/plain", temp());
}
void moveForward() {
  Serial.println("Got the forward command");
  server.send(200, "text/plain", "Moving forward!");
  Forward(speed);
}
void moveForwardL() {
  Serial.println("Got the forward left command");
  server.send(200, "text/plain", "Moving forward left!");
  forwardLeft(speed);
}
void moveForwardR() {
  Serial.println("Got the forward right command");
  server.send(200, "text/plain", "Moving forward right!");
  forwardRight(speed);
}
void STOP() {
  Serial.println("Got the stop command");
  server.send(200, "text/plain", "stopping!");
  Forward(0);
}
void moveBackward() {
  Serial.println("Got the backward command");
  server.send(200, "text/plain", "moving backward!");
  Backward(speed);
}
void moveBackwardL() {
  Serial.println("Got the backward left command");
  server.send(200, "text/plain", "moving backward left!");
  backwardLeft(speed);
}
void moveBackwardR() {
  Serial.println("Got the backward right command");
  server.send(200, "text/plain", "moving backward right!");
  backwardRight(speed);
}
void closeClaw() {
  Serial.println("Got the close claw command");
  server.send(200, "text/plain", "moving backward right!");
  closeGrabber();
}
void openClaw() {
  Serial.println("Got the open claw command");
  server.send(200, "text/plain", "moving backward right!");
  openGrabber();
}
void armUp() {
  Serial.println("Got the arm up command");
  server.send(200, "text/plain", "moving backward right!");
  ArmUp();
}
void armDown() {
  Serial.println("Got the arm down command");
  server.send(200, "text/plain", "moving backward right!");
  ArmDown();
}
void armLeft() {
  Serial.println("Got the arm left command");
  server.send(200, "text/plain", "moving backward right!");
  ArmLeft();
}
void armRight() {
  Serial.println("Got the arm right command");
  server.send(200, "text/plain", "moving backward right!");
  ArmRight();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
  message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
}
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
   // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

 if (MDNS.begin("esp32")) {
Serial.println("MDNS responder started");
}
  
  server.on("/", handleRoot);
  server.on("/forward", moveForward);
  server.on("/forwardR", moveForwardR);
  server.on("/forwardL", moveForwardL);
  server.on("/STOP", STOP);
  server.on("/backward", moveBackward);
  server.on("/backwardL", moveBackwardL);
  server.on("/backwardR", moveBackwardR);
  server.on("/openclaw", openClaw);
  server.on("/closeclaw", closeClaw);
  server.on("/armup", armUp);
  server.on("/armdown", armDown);
  server.on("/armleft", armLeft);
  server.on("/armright", armRight);
  server.on("/getUltrasonic", getTheUltrasonic);
  server.on("/getTemp", getTheTemp);
  server.on("/inline", []() {
  server.send(200, "text/plain", "this works as well");
});

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  timer = timerBegin(0, 80, true); // timer 0 , prescaler=80 clock is 80MHZ counter will be incremented at each microsecond , count up = true
  timerAttachInterrupt(timer, &onTimer, true);//handling function, which will be executed when the interrupt is generated
  timerAlarmWrite(timer, 5000000, true); // second argument specifies the counter value in which the timer interrupt is generated , in this case 5000000 microseconds , true to reload couner
  timerAlarmEnable(timer);
  myservoV.attach(32);
  myservoGrabber.attach(4);
  myservoH.attach(5);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop(void) {
  server.handleClient();
}
