# 🌱 Sistema de Irrigação para Horta Medicinal🌱

Este projeto busca desenvolver um protótipo automatizado para o gerenciamento de uma Horta Medicinal, localizada nas dependências da UFSC - Campus Araranguá.  
O trabalho foi realizado como parte da disciplina **Projeto Integrador I**, com a colaboração de:
- **Arthur Rodrigues**
- **Fernando Moretti**
- **Lucas Schemes**
- **Pedro Magnavita**

---

## 📋 Descrição do Projeto

> O sistema utiliza um sensor **FC28** para monitorar a umidade do solo e um **DHT11** para monitorar a temperatura e umidade do ar. Caso a umidade esteja abaixo do esperado, uma bomba d'água é automaticamente acionada, garantindo a irrigação adequada da horta.  
> Além disso, o sistema gerencia o tanque de água utilizando dois sensores verticais para monitorar o nível do reservatório. Quando o nível está baixo, uma válvula solenóide conectada ao encanamento é ativada via relé, assegurando o reabastecimento automático.

---

## 🖼 Visão Geral do Sistema

Abaixo, você pode conferir os esquemas que detalham a organização geral do sistema e suas conexões. Esses diagramas ilustram como os componentes interagem para tornar o sistema funcional e eficiente.

### **Esquema Geral do Sistema**
![Irrigação drawio (1)](https://github.com/user-attachments/assets/a1357d2c-8834-49f1-b013-14b51f24a0bd)  
*Este esquema representa a visão completa do sistema, incluindo sensores, atuadores e o microcontrolador ESP32.*

### **Esquema de Conexão**
![Conexões drawio (2)](https://github.com/user-attachments/assets/87d00905-9c92-4b0c-a60f-a35893415945)  
*Aqui estão as conexões detalhadas entre os componentes, mostrando como os sensores, atuadores e o ESP32 se comunicam.*

---

## ⚙️ Funcionalidades

### 🌐 **Conexão e Gerenciamento Inteligente**
- **Gerenciamento de Conexão à Internet:**  
  O ESP32 conecta-se à internet automaticamente, salvando ID e senha para facilitar reconexões.  
- **Envio de Dados Otimizado:**  
  Envia dados para o Blynk em intervalos controlados para garantir comunicação eficiente.  
- **Redução de Consumo de Energia:**  
  Lógica otimizada para leituras periódicas, reduzindo o consumo do ESP32.  
- **Botão de Reset de Conexão:**  
  Um simples toque no botão "boot" reinicia a conexão em caso de falha.

---

### 💧 **Controle do Tanque de Água**
- **Monitoramento Completo do Nível:**  
  Detecta os estados de cheio, médio, vazio ou erro no tanque.  
- **Proteção Contra Vazamentos:**  
  Monitora o tempo de operação e níveis para evitar transbordamentos.  
- **Relatório de Enchimento:**  
  Calcula e exibe o tempo necessário para encher o tanque.

---

### 🌿 **Irrigação Automática**
- **Gerenciamento Integrado:**  
  A bomba d'água é acionada com base nos dados de umidade do solo. O sistema também usa informações de temperatura e umidade do DHT11 para evitar condições extremas.  
- **Configuração de Limites:**  
  Permite ajuste de thresholds para otimização do consumo de água.  
- **Gestão de Erros:**  
  Detecta falhas de sensores, timeouts ou condições adversas, aplicando lógica de fallback.  
- **Modo Manual e Testes:**  
  Oferece operação forçada para ajustes ou manutenção, ideal para experimentação.
