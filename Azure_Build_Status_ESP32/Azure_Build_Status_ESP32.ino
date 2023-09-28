#include "WiFi.h"
#include <WiFiClientSecure.h>
#include "Arduino.h"

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

short buildStatusOk = 1;

WiFiClientSecure client;

String serverName  = "fa-wrkshpz-build-status.azurewebsites.net";
String serverPath = "/api/GetBuildStatus?code=941XPEOOtaXZ76KBLNheLMkozIVZKjv74lTwYov47bPCAzFugOU6vw==";

const int serverPort = 443;

void SetLightToGreen() {
  Serial.println("Set light green");
  digitalWrite(2, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void SetLightToOrange() {
  Serial.println("Set light orange");
  digitalWrite(2, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void SetLightToRed() {
  Serial.println("Set light red");
  digitalWrite(2, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void SetLightToBlue() {
  Serial.println("Set light blue");
  digitalWrite(2, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void SetLightToOff() {
  Serial.println("Set light off");
  digitalWrite(2, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void IRAM_ATTR resetBuildStatus()
{
  Serial.println("Reset build status...");
  buildStatusOk = true;
  SetLightToOrange();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(3, INPUT);

  attachInterrupt(3, resetBuildStatus, RISING);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    SetLightToOff();
    delay(500);
    SetLightToBlue();
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  SetLightToGreen();
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  GetAzureDevopsBuildStatus();

  if (buildStatusOk == 0) {
    SetLightToRed();
  } else {
    Serial.println("Build status seems ok");
  }

  delay(15000);            // waits for 15 seconds
}

void GetAzureDevopsBuildStatus() {
  // https://fa-wrkshpz-build-status.azurewebsites.net/api/GetBuildStatus?code=941XPEOOtaXZ76KBLNheLMkozIVZKjv74lTwYov47bPCAzFugOU6vw==

  String getAll;
  String getBody;
  
  client.setInsecure(); // DO NOT DO THIS IN PRODUCTION SCENARIOS

  if (client.connect(serverName.c_str(), serverPort)) {
    Serial.println("Connection successful!");    
  
    client.println("GET " + serverPath + " HTTP/1.1");
    client.println("Host: " + serverName);
    client.println();
      
    int timoutTimer = 10000;
    long startTimer = millis();
    boolean state = false;
    
    while ((startTimer + timoutTimer) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (getAll.length()==0) { state=true; }
          getAll = "";
        }
        else if (c != '\r') { getAll += String(c); }
        if (state==true) { getBody += String(c); }
        startTimer = millis();
      }
      if (getBody.length()>0) { break; }
    }

    client.stop();
    
    Serial.println("Build status: " + String(buildStatusOk));

    if (String(getBody).indexOf("NOK") > 0) {
      buildStatusOk = 0;
    } else {
      buildStatusOk = 1;
    }

    Serial.println("Build status: "+ String(buildStatusOk));
  }
}

