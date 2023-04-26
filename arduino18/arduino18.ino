#include <Servo.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#define DEBUG true
#define PIN_PHOTO_SENSOR A0
SoftwareSerial esp8266(2,3);
Servo servo1; 
float temperature = 0;
OneWire ds(8);
int LED=12;
int val=0;
int status=0;
int P=0;
const int trigPin = 7;
int avalue=0;
int aPin=A0;
const int echoPin = 6;
int pos = 0; 
int state; 
int flag=0;
int p = 3;
int itsONled[] = {0,0};
int itsONpieazo = {0,0};
void sendData(String command, const int timeout, boolean debug)
{
 esp8266.print(command);
 long int time = millis();
 while((time+timeout) > millis())
 {
 while(esp8266.available())
 {
 Serial.write(esp8266.read());
 }
 }
}
void setup(){
status = pressure.startPressure(3);
status = pressure.getPressure(P,T);
P=P*0.7500637554192,2;
pinMode(PIN_LED, OUTPUT);
int val = analogRead(PIN_PHOTO_SENSOR);
avalue=analogRead(aPin);
byte data[2];  
ds.reset();
ds.write(0xCC); 
ds.write(0x44); 
delay(1000); 
ds.reset(); 
ds.write(0xCC); 
ds.write(0xBE); 
data[0] = ds.read();
data[1] = ds.read(); 
float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
pinMode(p, OUTPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
servo1.write(0);
pinMode(LED, OUTPUT);
Serial.begin(9600);
esp8266.begin(115200);
sendData("AT+RST\r\n",2000,DEBUG);
sendData("AT+CWMODE=1\r\n",1000,DEBUG);
sendData("AT+CWJAP=\"SSID\",\”PASSWORD\"\r\n", 6000, DEBUG);
sendData("AT+CIFSR\r\n",2000,DEBUG);
sendData("AT+CIPMUX=1\r\n",1000,DEBUG);
sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
}
void loop(){
if(esp8266.available())
{
 if(esp8266.find(“+IPD,”))
 {
  int connectionId = esp8266.read()-48; 
 }
 String msg;
esp8266.find("?");
delay(100);
msg = esp8266.readStringUntil(' ');
String command1 = msg.substring(0);
String webpage = `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            background: linear-gradient(90deg, rgb(171, 229, 255, .5) 0%, rgba(145, 196, 219, 0.5) 50%);
        }

        .actions {
            margin-top: 2rem;
            display: flex;
            flex-direction: row;
            justify-content: space-between;
        }

        .actions__block {
            width: 20rem;
            height: 15rem;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            margin-left: 2rem;
            margin-right: 2rem;
            background-color: rgba(145, 233, 245, 0.75);
            border-radius: 2rem;
        }

        .actions__title {
            font-size: 1.5rem;
            font-weight: 500;
            color: white;
        }

        .btn {
            margin-top: 2rem;
            font-size: 1.25rem;
            background-color: rgb(148, 223, 241);
            width: 10rem;
            height: 2rem;
            text-align: center;
            text-decoration: none;
            color: white;
            border-radius: .5rem;
            box-shadow: 1px 1px 20px 13px rgba(96, 181, 202, 0.712);
            transition-duration: .2s;
        }

        .btn:hover {
            background-color: rgb(115, 178, 194);

        }

        .inputs__block {
            display: flex;
            margin-top: 1rem;
            margin-left: 48rem;
        }

        .inputs__input {
            width: 15rem;
        }

        .text {
            text-align: center;
        }

        .img {
            display: flex;
            margin-top: 1.5rem;
            font-size: 1.25rem;
            border: 20px, solid #20B2AA;
        }

        .img__title {
            margin-left: 1rem;
        }
    </style>
    <title>Final Project</title>
</head>
<body>
    <div class="actions">
        <div class="actions__block">
            <div class="actions__title">Открыть дверь</div>
            <a class="btn">Click</a>
        </div>
        <div class="actions__block">
            <div class="actions__title">Включить диоды</div>
            <a class="btn">Click</a>
        </div>
        <div class="actions__block">
            <div class="actions__title">Включить сигнал</div>
            <a class="btn">Click</a>
        </div>
        <div class="actions__block">
            <div class="actions__title">Вывести на экран</div>
            <a class="btn">Click</a>
        </div>
    </div>
    <div class="text">Комната А</div>
    <div class="inputs">
        <div class="inputs__block">
            <div class="imputs__title">Датчик температуры</div>
            <input type="text" name="sensor" value="`+ temperature +`"readonly id="" class="inputs__input">
          
            
        </div>
        <div class="inputs__block">
            <div class="imputs__title">Датчик влажности</div>
            <input type="text" name="sensor" value="`+ avalue +`" readonly id="" class="inputs__input">
            
        </div>
        <div class="inputs__block">
            <div class="imputs__title">Датчик освещенности</div>
            <input type="text" name="sensor" value="`+ val +`" readonly id="" class="inputs__input">
            
        </div>
        <div class="inputs__block">
            <div class="imputs__title">Датчик давления</div>
            <input type="text" name="sensor" value="`+ P +`" readonly id="" class="inputs__input">
            
        </div>
    </div>
    <div class="img">
        <img src="domu.jpg" alt="Моя картинка" width="1100" height="500">
        <div class="img__title"><p>Приветствую на сайте нашего умного дома.С помощью нашего сайта вы можете управлять своим домом сидя на диване или лежа на кровати, управлять с любого уголка вашего дома.Наш сайт имеет хороший набор функций для взаимодействия с домом:
            <p>-Открытие и закрытие двери(нажмите 1 кнопку);</p>
            <p>-Включение диодов(нажмите 2 кнопку);</p>
            <p>-Включение сигнала(нажмите 3 кнопку);</p>
            <p>-Проверка дистанции(нажмите 4 кнопку);</p>
            <p>-Вы можете увидить значение датчиков в вашей комнате(смотреть ниже кнопок);</p>
            <p>Сайт находится в стадии разработки, и со временем будут появляться новые возможности для управления вашим домом.Удачи!</p></div>
    
    </div>
    
</body>
</html>
`
if (command1 == "U"){
  if (itsONpiezo[1]== 1)
  {
    tone (p, 0);
    itsONpiezo[1]=0;
    webpage += "<p>PIEZO STATUS OFF</p>";
  }
  else{
    tone (p, 1000);
    itsONpiezo=1;
    webpage += "<p>PIEZO STATUS ON</p>";
    }
    webpage += "<a class=\"btn\"
 href=\"?U\">Click</a>
 </body></html>”;

}
if (command1 == "Y")
{
 if (itsONled[1] == 1)
 {
 digitalWrite(LED, LOW);
 itsONled[1] = 0;
 webpage += "<p>LED STATUS OFF</p>";
 }
 else
 {
 digitalWrite(LED, HIGH);
 itsONled[1] = 1;
 webpage += “<p>LED STATUS ON</p>";
 }
 webpage += “<a class=\"btn\"
 href=\”?Y\”>Click</a>
 </body></html>”;
}

 if (command1 == "T")
 {
  if(Serial.available() > 0) { state = Serial.read(); flag=0; }
  if (state == '0') { 
    myservo.write(90);  
    webpage += “<p>DOOR STATUS OPEN</p>";
    } 
    else if (state == '1') { 
      myservo.write(0); 
      webpage += “<p>DOOR STATUS CLOSE</p>";
      }
      webpage += "<a class=\"btn\"
 href=\"?T\">Click</a>
 </body></html>";
}
if (command1 == "I")
{
 long durationindigit, distanceincm;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 durationindigit = pulseIn(echoPin, HIGH);
 distanceincm = (durationindigit * 0.034)/2;
 if (distanceincm > 50) {
  tone (p, 200);
 }
 else if (distanceincm <= 50 && distanceincm > 20) {
  tone (p, 500);
 }
  else if (distanceincm <= 20 && distanceincm > 5) {
    tone (p, 1000);
  }
   webpage += "<a class=\"btn\"
 href=\"?I\">Click</a>
 </body></html>";
  }


 String cipSend = “AT+CIPSEND=”;
cipSend += connectionId;
cipSend += “,”;
cipSend +=webpage.length();
cipSend +=”\r\n”;
sendData(cipSend,200,DEBUG);
sendData(webpage,200,DEBUG);
String closeCommand = “AT+CIPCLOSE=”;
 closeCommand+=connectionId; // append connection id
 closeCommand+=”\r\n”;
 sendData(closeCommand,300,DEBUG);
