#include <ESP8266WiFi.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
// create servo object to control a servo
// twelve servo objects can be created on most boards

// GPIO the servo is attached to
#define servo1Pin  D1
#define servo2Pin  D2
#define servo3Pin  D3
#define servo4Pin  D4
#define servo5Pin  D5 // El servo en el terminal D3

// Replace with your network credentials
const char* ssid     = "Moto";
const char* password = "12345678";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String value1String = String(5);
String value2String = String(5);
String value3String = String(5);
String value4String = String(5);
String value5String = String(5);
int pos1 = 0;
int pos2 = 0;

void setup() {
  Serial.begin(115200);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
    // attaches the servo on the servoPin to the servo object

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            
client.println("<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> ");

client.println("<title>The arm to rule'em all</title> ");

client.println("<style> body{ text-align: center; font-family: 'Trebuchet MS', 'Lucida Sans Unicode', 'Lucida Grande', 'Lucida Sans', Arial, sans-serif; margin-left: auto; margin-right: auto; } .slider{ width: 300px; } #servoSlider1{ accent-color: rgb(255, 0, 0) } #servoSlider2{ accent-color: rgb(221, 255, 0) } #servoSlider3{ accent-color: rgb(0, 42, 255) } #servoSlider4{ accent-color: rgb(255, 145, 0) } #servoSlider5{ accent-color: rgb(255, 0, 221) } </style></head> ");

client.println("<body> <h1>The arm to rule'em all</h1> <p>Dedo 1: <span id=\"servoPos1\"></span></p> <input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider1\" onchange=\"servo(this.value)\" value=\""+value1String+"\"/>"); 

client.println("<p>Dedo 2: <span id=\"servoPos2\"></span></p> <input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider2\" onchange=\"servo(this.value)\" value=\""+value2String+"\"/>"); 

client.println("<p>Dedo 3: <span id=\"servoPos3\"></span></p> <input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider3\" onchange=\"servo(this.value)\" value=\""+value3String+"\"/>"); 

client.println("<p>Dedo 4: <span id=\"servoPos4\"></span></p> <input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider4\" onchange=\"servo(this.value)\" value=\""+value4String+"\"/>"); 

client.println("<p>Dedo 5: <span id=\"servoPos5\"></span></p> <input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider5\" onchange=\"servo(this.value)\" value=\""+value5String+"\"/> </body>"); 

client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>"); 

client.println("<script> var slider1=document.getElementById(\"servoSlider1\");");

client.println("var slider2=document.getElementById(\"servoSlider2\");");

client.println("var slider3=document.getElementById(\"servoSlider3\");");

client.println("var slider4=document.getElementById(\"servoSlider4\");"); 

client.println("var slider5=document.getElementById(\"servoSlider5\");"); 

client.println("var pos1=document.getElementById(\"servoPos1\");");

client.println("var pos2=document.getElementById(\"servoPos2\");"); 

client.println("var pos3=document.getElementById(\"servoPos3\");");

client.println("var pos4=document.getElementById(\"servoPos4\");");

client.println("var pos5=document.getElementById(\"servoPos5\");");

client.println("pos1.innerHTML=slider1.value;");
client.println("pos2.innerHTML=slider2.value;");
client.println("pos3.innerHTML=slider3.value;");
client.println("pos4.innerHTML=slider4.value;");
client.println("pos5.innerHTML=slider5.value;"); 

client.println("slider1.oninput=function(){ slider1.value=this.value; pos1.innerHTML=this.value; }"); 
client.println("slider2.oninput=function(){ slider2.value=this.value; pos2.innerHTML=this.value; }");
client.println("slider3.oninput=function(){ slider3.value=this.value; pos3.innerHTML=this.value; }");
client.println("slider4.oninput=function(){ slider4.value=this.value; pos4.innerHTML=this.value; }");
client.println("slider5.oninput=function(){ slider5.value=this.value; pos5.innerHTML=this.value; }"); 

client.println("$.ajaxSetup({timeout:1000})"); 
client.println("function servo1(pos){");
 client.println("$.get(\"/?value1=\"+pos+\"&\")"); 
client.println("{Connection:close}; }"); 

client.println("function servo2(pos){"); 
client.println("$.get(\"/?value2=\"+pos+\"&\")"); 
client.println("{Connection:close}; }"); 

client.println("function servo3(pos){"); 
client.println("$.get(\"/?value3=\"+pos+\"&\")"); 
client.println("{Connection:close}; }"); 

client.println("function servo4(pos){"); 
client.println("$.get(\"/?value4=\"+pos+\"&\")"); 
client.println("{Connection:close}; }"); 

client.println("function servo5(pos){"); 
client.println("$.get(\"/?value5=\"+pos+\"&\")");
client.println("{Connection:close}; } </script> </body> </html>");
     
            
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value1=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              value1String = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              servo1.write(value1String.toInt());
              Serial.println(value1String); 
            } 
            if(header.indexOf("GET /?value2=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              value2String = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              servo2.write(value2String.toInt());
              Serial.println(value2String); 
            } 
            if(header.indexOf("GET /?value3=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              value3String = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              servo3.write(value3String.toInt());
              Serial.println(value3String); 
            } 
            if(header.indexOf("GET /?value4=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              value4String = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              servo4.write(value4String.toInt());
              Serial.println(value4String); 
            } 
            if(header.indexOf("GET /?value5=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              value5String = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              servo5.write(value5String.toInt());
              Serial.println(value5String); 
            }         
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
