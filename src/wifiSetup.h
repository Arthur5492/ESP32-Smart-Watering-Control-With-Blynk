/**
 * @file wifiSetup.h
 * @brief Handles Wi-Fi management with captive portal setup, NVS storage.
 * @author Arthur  Github: https://github.com/Arthur5492
 */

#ifndef _WIFI_SETUP_H_
#define _WIFI_SETUP_H_
#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Preferences.h>

#include "blynkHandler.h"
class WifiSetup
{
  public:
    WifiSetup(): server(80) {};

    void begin(); 
    void loop(); 

    /// @brief Connect to the stored SSID and Password 
    bool connectWifi(); 

    void startCaptivePortal(); 
    void logoutCaptivePortal(); 
    /// @brief Search and insert in html all wifi SSID options
    void wifiScan();
    
    /// @brief Check if there is any stored SSID and Password in NVS 
    bool isStoredInNVS();
    /// @brief Save NVS Settings
    bool saveWifiSettingsNVS();
    bool clearNVS(); 
     
    //Getters
    String get_ssidStored() { return ssidStored; };
    String get_passwdStored() { return passwdStored; };
    bool get_isCaptivePortalEnabled() { return isCaptivePortalEnabled; };
    bool get_isWifiDataStored(){return isWifiDataStored; };
    
  private:
    //Captive Portal Data
    const char* ssidCapPortal = "Configure_ESP32";
    const char* passwordCapPortal = "12345678";
    String wifiOptions = "";
    //END Captive Portal Data

    unsigned long serverStartTime = 0;
    const unsigned long timeoutDuration = 300000;
    bool timeoutReached = false;
     
    DNSServer dnsServer;
    AsyncWebServer server;
    bool isCaptivePortalEnabled = false;

    uint8_t blynkAttemptConnections = 0;

    ///NVS WIFI DATA
    Preferences wifiDataNVS;
    enum NVSReadWrite {NVS_READ_WRITE = false, NVS_READ_ONLY = true};
    bool isWifiDataStored = false;
    //Data Stored
    String ssidStored = "";  
    String passwdStored = "";
    ///END NVS WIFI DATA

    /// @brief //HTML page for the Captive Portal 
    String htmlPage(); 
};

extern WifiSetup wifiSetup;

#endif