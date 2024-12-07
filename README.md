# Sistema de Irrigação para Horta Medicinal

Este projeto tem como objetivo o desenvolvimento de um protótipo de automatização de uma Horta Medicinal localizada nas dependências da UFSC - Campus Araranguá. O trabalho foi desenvolvido como parte da disciplina **Projeto Integrador I** por:
- **Arthur Rodrigues**
- **Fernando Moretti**
- **Lucas Schemes**
- **Pedro Magnavita**

# Descrição do Projeto

O sistema utiliza um sensor **FC28** para monitorar a umidade do solo e um **DHT11** para monitorar a temperatura do ar. Caso a umidade esteja abaixo do esperado, uma bomba d'água é acionada, irrigando a horta.  
Também há o controle do sistema de tanque de água, que utiliza dois sensores de nível de água verticais para medir o nível de água do tanque. Caso ele esteja baixo, uma válvula solenoide conectada ao encanamento é acionada via relé.

---
# Funcionalidades

## Detalhes Gerais
- **Gerenciamento de Conexão à Internet:**  
  Conecta o ESP32 à internet remotamente, armazenando o ID e a senha do WiFi na memória para reconexões automáticas.
- **Envio de Dados Otimizado:**  
  Envia informações ao Blynk com intervalos controlados para evitar sobrecarga na comunicação.
- **Redução de Consumo de Energia:**  
  Implementa intervalos de tempo para leitura de sensores e lógica, otimizando o consumo de energia do ESP32.
- **Botão de Reset de Conexão:**  
  Utiliza o botão "boot" para reiniciar a conexão do ESP32 com a internet em caso de falhas.
### Tanque de Água
- **Monitoramento de Nível:**  
  Detecta os estados de cheio, médio, vazio ou erro no tanque de água.
- **Proteção Contra Vazamentos:**  
  Monitora o tempo de operação e os níveis de água para evitar transbordamentos ou vazamentos.
- **Relatório de Enchimento:**  
  Informa o tempo necessário para completar o enchimento do tanque.
### Irrigação- 
- **Gerenciamento Integrado do Sistema de Irrigação:**  
  Controla a ativação da bomba d'água com base nos dados coletados do sensor de humidade de solo, tendo garantia contra temperaturas extremas utilizando os dados do DHT11
- **Configuração de Limites:**  
  Implementa thresholds ajustáveis para umidade do solo, temperatura e umidade relativa para otimização do consumo de água.
- **Gestão de Erros:**  
  Identifica falhas críticas, como sensores fora de operação ou timeouts, e aplica lógica de fallback para evitar danos ao sistema.
- **Modo Manual e Testes:**  
  Oferece operação forçada via comando remoto para manutenção ou testes do sistema(experimental).
---
## Esquema Geral do Sistema
![Irrigação drawio (1)](https://github.com/user-attachments/assets/a1357d2c-8834-49f1-b013-14b51f24a0bd)

## Esquema de Conexão
![Conexões drawio (2)](https://github.com/user-attachments/assets/87d00905-9c92-4b0c-a60f-a35893415945)

