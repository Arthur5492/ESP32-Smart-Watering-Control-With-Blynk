#include <wifiSetup.h>

//AcessPoint Instance, is used to connect to wifi by captive portal
WifiSetup wifiSetup;

void WifiSetup::begin()
{
  isWifiDataStored = isStoredInNVS();
  if(isWifiDataStored)
    connectWifi();
  else
    startCaptivePortal();
}


bool WifiSetup::isStoredInNVS()
{ 
  wifiDataNVS.begin("wifiDataNVS",NVS_READ_ONLY);

  if(wifiDataNVS.isKey("ssid")) 
  {
    ssidStored = wifiDataNVS.getString("ssid").c_str();
    passwdStored = wifiDataNVS.getString("password").c_str();

    Serial.printf("SSID Found: %s\n",ssidStored.c_str());
    isWifiDataStored = true;
  }
  else
  {
    Serial.printf("No SSID found on NVS memory\n");
    isWifiDataStored = false;
  }

  wifiDataNVS.end();
  return isWifiDataStored;
}


void WifiSetup::startCaptivePortal()
{
  if(isCaptivePortalEnabled)
    return;
    
  if(timeoutReached)
    timeoutReached = false;

  wifiScan();


  WiFi.softAP(ssidCapPortal, passwordCapPortal);
  
  IPAddress apIP(192, 168, 4, 1);
  dnsServer.start(53, "*", apIP);

 server.onNotFound([this](AsyncWebServerRequest *request) {
  request->send(200, "text/html", htmlPage()); 
});


 //Save credentials to String variables, shut down the server and connect to the wifi
  server.on("/save", HTTP_POST, [this](AsyncWebServerRequest *request)
  {
    
    ssidStored = request->arg("ssid");
    passwdStored = request->arg("password");

    if(ssidStored == "" || passwdStored == "")
    { 
      request->send(200, "text/html", "Please, fill all labels...");
      return;
    }
    
    Serial.printf("ssid found: %s, Password found: %s\n", ssidStored, passwdStored);
    request->send(200, "text/html", "Settings saved suceffuly! Trying to connect to Wifi...");
    
    logoutCaptivePortal(); //!ERRO acho q aqui apaga o escopo e nn manda nada pro wifi
    connectWifi();
  });

  server.begin();
  isCaptivePortalEnabled = true;
  serverStartTime = millis();
  Serial.println("Captive Portal initializated\n");
}

void WifiSetup::logoutCaptivePortal()
{
  isCaptivePortalEnabled = false;
  dnsServer.stop();
  server.end();
  WiFi.softAPdisconnect(true);

  Serial.printf("Captive Portal ended\n");
}

bool WifiSetup::connectWifi()
{
  // Timeout to avoid infinite loops
  unsigned long startAttemptTime = millis();
  unsigned long wifiTimeout = 5000;

  WiFi.begin(ssidStored.c_str(),passwdStored.c_str());
  
  Serial.printf("Trying to connect to Wifi: %s\n",ssidStored.c_str());
        
  // Loop até conectar ou atingir o tempo limite
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout)
    ;
    

  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.printf("Connected to: %s \n", ssidStored.c_str());
    if(!isWifiDataStored)
      saveWifiSettingsNVS();
    return true;
  }
  else
  {
    Serial.printf("Failed connection to: %s, please try again.\n",ssidStored.c_str());
    WiFi.disconnect();
    startCaptivePortal();
    return false;
  }
}

  void WifiSetup::loop()
  {
    if(WiFi.isConnected() && !Blynk.connected())
    {
      if(blynkAttemptConnections < 5)
        if(blynkHandler.config() == false)
          blynkAttemptConnections++;
      
      return;
    }
    
    if(timeoutReached)
      return;

    if(millis() - serverStartTime >= timeoutDuration)
    {
      logoutCaptivePortal();
      timeoutReached = true;
    }

    if(isCaptivePortalEnabled)
        dnsServer.processNextRequest();
  }

void WifiSetup::wifiScan()
{ 
  Serial.println("Scanning nearby Acess Points");
  int ssidList = WiFi.scanNetworks();
  
  //0-32: Max single SSID size
  //0-25: sizeof(<option value=''></option>)
  wifiOptions.reserve(ssidList * (32+25)); 
  
  for(size_t i=0; i<ssidList;i++)
  {
    wifiOptions+= "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    // <option value=''></option> 
  }
  Serial.printf("Acess Points found: %d\n", ssidList);
  WiFi.disconnect();
}

bool WifiSetup::clearNVS() {
  
  wifiDataNVS.begin("wifiDataNVS", NVS_READ_WRITE);

  if(wifiDataNVS.clear())
  {
    Serial.println("NVS Cleared");
    wifiDataNVS.end();
    return true;
  }

  Serial.println("Error while cleaning NVS");
  wifiDataNVS.end();
  return false;
}

bool WifiSetup::saveWifiSettingsNVS()
{
  bool returnValue = false;
  wifiDataNVS.begin("wifiDataNVS",NVS_READ_WRITE);

  uint8_t checkErrorNVS = 0; //NVS putString function returns 0 if error

  checkErrorNVS = wifiDataNVS.putString("ssid", ssidStored);
  checkErrorNVS += wifiDataNVS.putString("password", passwdStored);

  if(checkErrorNVS == 0)
  {
    Serial.println("Error trying to save data in NVS\n");
    returnValue = false;
  }
  else
  {
    Serial.printf("SSID: %s saved on NVS\n",ssidStored.c_str());
    returnValue = true;
  }

  wifiDataNVS.end();
  return true;
}

String WifiSetup::htmlPage()
{
  // HTML básico para a página de configuração
  String index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Wi-Fi Configuration</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>Wi-Fi setup</h2>
  <form action="/save" method="post">
    <label for="ssid">Network Name (SSID):</label><br>
    <select id="ssid" name="ssid">
      %OPTIONS%
    </select><br><br>

    <label for="password">Password:</label><br>
    <input type="text" id="password" name="password"><br><br>

    <input type="submit" value="Save">
  </form>
</body>
</html>)rawliteral";

  // Substitui %OPTIONS% pelas opções de redes Wi-Fi descobertas
  index_html.replace("%OPTIONS%", wifiOptions);

  return index_html;
}

