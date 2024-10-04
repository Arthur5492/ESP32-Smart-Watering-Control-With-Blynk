#ifndef _WIFI_SETUP_H_
#define _WIFI_SETUP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Preferences.h>



class wifiSetup
{
  private:
    //Blynk

    //Captive Portal
    const char* ssidCapPortal = "Configura_ESP32";
    const char* passwordCapPortal = "12345678";
    unsigned long serverStartTime;  // Variável para armazenar o tempo de início do servidor
    const unsigned long timeoutDuration = 300000;  // 5 minutos em milissegundos
    DNSServer dnsServer;
    AsyncWebServer server;
    bool isAcessPointEnabled = false;

    //NVS Memory
    Preferences wifiData;
    //Stored Wifi Data
    String ssidStored;
    String passwdStored;
    
  public:
    wifiSetup(): server(80) {};
    ~wifiSetup(){};

    bool isWifiDataStored(); //Check if there is any stored SSID and Password in NVS 
    bool connectWifi(); //Connect to the stored SSID and Password
    void startCaptivePortal(); //Start the Captive Portal
    void logoutCaptivePortal(); //Logout the Captive Portal
    void begin(); //Start the basics
    String htmlPage(); //HTML page for the Captive Portal
    void loop(); //Loop for the Captive Portal

    const char* getSsidStored() { return ssidStored.c_str(); }
    const char* getPasswdStored() { return passwdStored.c_str(); }
    bool getIsAcessPointEnabled() { return isAcessPointEnabled; }
};

extern wifiSetup acessPoint;

#endif