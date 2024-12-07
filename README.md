Sistema de Irrigação para Horta Medicinal

Este projeto tem como objetivo o desenvolvimento de um protótipo de automatização de uma Horta Medicinal localizada nas dependências da UFSC - Campus Araranguá. O trabalho foi desenvolvido como parte da disciplina **Projeto Integrador I** por:
- **Arthur Rodrigues**
- **Fernando Moretti**
- **Lucas Schemes**
- **Pedro Magnavita**

## Descrição do Projeto
O sistema utiliza um sensor **FC28** para monitorar a umidade do solo e um **DHT11** para monitorar a temperatura do ar. Caso a umidade esteja abaixo do esperado, uma bomba d'água é acionada, irrigando a horta.  
Também há o controle do sistema de tanque de água, que utiliza dois sensores de nível de água verticais para medir o nível de água do tanque. Caso ele esteja baixo, uma válvula solenoide conectada ao encanamento é acionada via relé.


## Funcionalidades

### Detalhes Gerais
- **Conecta ESP32 à internet remotamente, salvando id e senha do WiFi na memória**
- **Envio de dados para o Blynk com intervalo de tempo para não sobrecarregar a comunicação**
- **Intervalo de tempo de leitura e lógica para reduzir o consumo do ESP32**
- **Botão boot para resetar a conexão com a internet**

### Tanque de Água
- **Detecta se está cheio/médio/vazio/erro**
- **Proteção contra vazamento checando tempo limite e nível de água**
- **Informa o tempo percorrido para enchimento do tanque**

### Irrigação- 
- **Gerenciamento Integrado do Sistema de Irrigação:**  
  Controla a ativação da bomba d'água com base nos dados coletados do sensor de humidade de solo, tendo garantia contra temperaturas extremas utilizando os dados do DHT11
- **Configuração de Limites:**  
  Implementa thresholds ajustáveis para umidade do solo, temperatura e umidade relativa para otimização do consumo de água.
- **Gestão de Erros:**  
  Identifica falhas críticas, como sensores fora de operação ou timeouts, e aplica lógica de fallback para evitar danos ao sistema.
- **Modo Manual e Testes:**  
  Oferece operação forçada via comando remoto para manutenção ou testes do sistema(experimental).
## Esquema Geral do Sistema
![Irrigação drawio (1)](https://github.com/user-attachments/assets/a1357d2c-8834-49f1-b013-14b51f24a0bd)

## Esquema de Conexão
![Conexões drawio (2)](https://github.com/user-attachments/assets/87d00905-9c92-4b0c-a60f-a35893415945)

