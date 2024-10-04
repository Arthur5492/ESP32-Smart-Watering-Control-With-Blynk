#include <wifiSetup.h>

wifiSetup acessPoint;

void wifiSetup::begin()
{
  wifiData.begin("wifiData",true);//Acess Read Only NVS memory

  // Tenta conectar ao WiFi se os dados estiverem armazenados, caso contrário inicia o Captive Portal
  if (!isWifiDataStored() || !connectWifi()) {
      startCaptivePortal();
  }

  wifiData.end();
}

bool wifiSetup::isWifiDataStored()
{
  String isDataStored = wifiData.getString("ssid");

  if(isDataStored != 0) 
  {
    ssidStored = wifiData.getString("ssid").c_str();
    passwdStored = wifiData.getString("password").c_str();

    wifiData.end();

    Serial.printf("SSID Encontrado: %s\n",ssidStored.c_str());
    return true;
  }

  Serial.printf("Nenhum SSID encontrado no NVS\n");
  return false; 
}

void wifiSetup::startCaptivePortal()
{
  if(isAcessPointEnabled)
    return;
  
  WiFi.softAP(ssidCapPortal, passwordCapPortal);
  IPAddress apIP(192, 168, 4, 1);
  dnsServer.start(53, "*", apIP);
  
 server.onNotFound([this](AsyncWebServerRequest *request) {
  request->send(200, "text/html", htmlPage());  // Redireciona para a página de configuração para todas as rotas
});


 //Save credentials to String variables, shut down the server and connect to the wifi
  server.on("/save", HTTP_POST, [this](AsyncWebServerRequest *request)
  {
    ssidStored = request->arg("ssid");
    passwdStored = request->arg("password");

    serverStartTime = millis(); //Reinicia o timer de quando o Acess Point foi iniciado

    request->send(200, "text/html", "Configurações salvas! Tentando conectar ao Wifi...");
    
    logoutCaptivePortal();
    connectWifi();
  });

  server.begin();
  isAcessPointEnabled = true;
  Serial.printf("%s server started",ssidCapPortal);
}

void wifiSetup::logoutCaptivePortal()
{
  isAcessPointEnabled = false;
  dnsServer.stop();
  server.end();
  WiFi.softAPdisconnect(true);
}

bool wifiSetup::connectWifi()
{
  WiFi.begin(ssidStored.c_str(),passwdStored.c_str());
  
    Serial.printf("Tentando conectar ao Wifi %s",ssidStored.c_str());
    delay(1000);
    while(WiFi.status() == WL_IDLE_STATUS)
    {
      Serial.print(".");
      delay(1000);
    }
    if(WiFi.status() == WL_CONNECTED)
    {
      Serial.printf("Conectado ao Wifi %s", ssidStored.c_str());
      wifiData.begin("wifiData",false);//Acess Read Write NVS memory
      wifiData.putString("ssid", ssidStored);
      wifiData.putString("password", passwdStored);
      wifiData.end();
      Serial.printf("SSID: %s salvo no NVS\n",ssidStored.c_str());
      return true;
    }
    else
    {
      Serial.printf("Falha ao conectar ao Wifi %s, erro: %d",ssidStored.c_str(),WiFi.status());
      startCaptivePortal();
      return false;
    }
}

void wifiSetup::loop()
{
  if(isAcessPointEnabled && millis() - serverStartTime < timeoutDuration)
      dnsServer.processNextRequest();
}

String wifiSetup::htmlPage()
{
  // HTML básico para a página de configuração
 String index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Configuracao do Wi-Fi</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>Configurar Wi-Fi</h2>
  <form action="/save" method="post">
    <label for="ssid">Nome da Rede (SSID):</label><br>
    <input type="text" id="ssid" name="ssid"><br><br>
    <label for="password">Senha:</label><br>
    <input type="text" id="password" name="password"><br><br>
    <input type="submit" value="Salvar">
  </form>
</body>
</html>)rawliteral";

return index_html;
}

