#include <wifiSetup.h>

wifiSetup acessPoint;

void wifiSetup::begin()
{
  wifiDataNVS.begin("wifiDataNVS",true);//Acess Read Only NVS memory

  // Tenta conectar ao WiFi se os dados estiverem armazenados, caso contrário inicia o Captive Portal
  if (!isWifiDataStored() || !connectWifi()) {
      wifiScan();//Procura redes wifi para colocar no portal de acesso
      startCaptivePortal();
  }

  wifiDataNVS.end();
}

bool wifiSetup::isWifiDataStored()
{
  String isDataStored = wifiDataNVS.getString("ssid");

  if(isDataStored != 0) 
  {
    ssidStored = wifiDataNVS.getString("ssid").c_str();
    passwdStored = wifiDataNVS.getString("password").c_str();

    wifiDataNVS.end();

    Serial.printf("SSID Encontrado: %s\n",ssidStored.c_str());
    return true;
  }

  Serial.printf("Nenhum SSID encontrado no NVS\n");
  return false; 
}

void wifiSetup::startCaptivePortal()
{

  if(isAcessPointEnabled == true)
    {
      Serial.print("Acess Point ja esta ativado");
      return;
    }

  //?If WiFi is connected wait for disconnect
  while(WiFi.status() == WL_CONNECTED)
  {
    WiFi.disconnect();
    delay(100);
  }

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
    
    // Timeout para evitar loops infinitos
    unsigned long startAttemptTime = millis();
    
    // Loop até conectar ou atingir o tempo limite
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      Serial.print(".");
      delay(1000); // Espera entre tentativas
    }


    if(WiFi.status() == WL_CONNECTED)
    {
      Serial.printf("Conectado ao Wifi %s", ssidStored.c_str());
      wifiDataNVS.begin("wifiDataNVS",false);//Acess Read Write NVS memory
      wifiDataNVS.putString("ssid", ssidStored);
      wifiDataNVS.putString("password", passwdStored);
      wifiDataNVS.end();
      Serial.printf("SSID: %s salvo no NVS\n",ssidStored.c_str());
      return true;
    }
    else
    {
      Serial.printf("Falha ao conectar ao Wifi %s, erro: %d",ssidStored.c_str(),WiFi.status());
      isAcessPointEnabled = false;
      startCaptivePortal();
      return false;
    }
}

void wifiSetup::loop()
{
  if(isAcessPointEnabled && millis() - serverStartTime < timeoutDuration)
      dnsServer.processNextRequest();
  
}

void wifiSetup::clearNVS() {
    wifiDataNVS.begin("wifiDataNVS", false);
    wifiDataNVS.clear();
    wifiDataNVS.end();
    Serial.println("NVS limpo");
}

void wifiSetup::wifiScan()
{
  WiFi.mode(WIFI_STA); // Modo Station para escanear redes Wi-Fi
  WiFi.disconnect(); // Certifique-se de que não está conectado a outra rede
  delay(200); // Pequeno delay para garantir que o modo foi ativado

  int ssidList = WiFi.scanNetworks();
  
  for(size_t i=0; i<ssidList;i++)
  {
    wifiOptions+= "<option value='"+WiFi.SSID(i)+"'>" + WiFi.SSID(i) + "</option>";
  }

  Serial.printf("Wifi options before: %s \n", wifiOptions.c_str());
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
    <select id="ssid" name="ssid">
      %OPTIONS%
    </select><br><br>

    <label for="password">Senha:</label><br>
    <input type="text" id="password" name="password"><br><br>
    
    <label for="local_ip">Endereco IP local:</label><br>
    <input type="text" id="local_ip" name="local_ip" placeholder="Digite o IP aqui"><br><br>

    <input type="submit" value="Salvar">
  </form>
</body>
</html>)rawliteral";

  // Substitui %OPTIONS% pelas opções de redes Wi-Fi descobertas
  index_html.replace("%OPTIONS%", wifiOptions);

  return index_html;
}

