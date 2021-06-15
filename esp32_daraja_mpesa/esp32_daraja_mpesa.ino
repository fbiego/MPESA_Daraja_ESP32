#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <MpesaSTK.h>

char * WIFI_SSID = "__ssid__";
char * WIFI_PASS = "__password__";

//get your credentials from https://developer.safaricom.co.ke/user/me/apps
String consumer_key = "__consumer_key__";
String consumer_secret = "__consumer_secret__";
//https://developer.safaricom.co.ke/test_credentials
String pass_key = "__pass_key__";
int business_code = 174379;

WiFiMulti wifiMulti;
MpesaSTK mpesa(consumer_key, consumer_secret, pass_key, SANDBOX);

String number = "2547XXXX__";
int amount = 100;

void setup() {

  Serial.begin(115200);

  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  wifiMulti.addAP(WIFI_SSID, WIFI_PASS);

  Serial.print("Waiting for WiFi to connect...");
  while ((wifiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

  
  mpesa.begin(business_code, PAYBILL, "http://mycallbackurl.com/checkout.php");
  
  
  String result = mpesa.pay(number, amount, "Arduino", "Test");

  Serial.println(result);

}


void loop() {
  // nothing here

}
