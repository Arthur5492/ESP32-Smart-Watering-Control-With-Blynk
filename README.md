Sistema de Irrigação para Horta Medicinal

Este projeto tem como objetivo o desenvolvimento de um protótipo de automatização de uma Horta Medicinal localizada nas dependências da UFSC - Campus Araranguá. O trabalho foi desenvolvido como parte da disciplina **Projeto Integrador I** por:
- **Arthur Rodrigues**
- **Fernando Moretti**
- **Lucas Schemes**
- **Pedro Magnavita**

## Descrição do Projeto
O sistema utiliza um sensor FC28 para monitorar a umidade do solo e um DHT11 para monitorar a temperatura do ar, caso a humidade esteja abaixo do esperado, uma bomba d'água é acionada, irrigando a horta,
Também há o controle do sistema de tanque de água, que utiliza dois sensores de nível de água verticais para medir o nível de água do tanque, caso ele esteja baixo, uma valvula solenoide conectada ao encanamento é acionada via relé.

## Funcionalidades:
<details>
  <summary>Detalhes gerais</summary>
  <ul>
    <li><strong>Conectar dispositivo à internet remotamente, salvando na memória do ESP</strong></li>
    <li><strong>Envio de dados para o Blynk com intervalo de tempo para não sobrecarregar a comunicação</strong></li>
    <li><strong>Intervalo de tempo de leitura e lógica para reduzir o consumo do ESP32</strong></li>
    <li><strong>Botão para reiniciar a conexão com o ESP</strong></li>
  </ul>
</details>
<details>
  <summary>Tanque de Água</summary>
  <ul>
    <li><strong>Detecta se está cheio/médio/vazio</strong></li>
    <li><strong>Proteção contra vazamento checando tempo limite e nível de água</strong></li>
    <li><strong>Informa a duração da irrigação</strong></li>
  </ul>
</details>
<details>
  <summary>Irrigação</summary>
  <ul>
    <li><strong>Detecta umidade do solo da horta</strong></li>
    <li><strong>Calcula quando irrigar baseado na temperatura atual e umidade do solo</strong></li>
    <li><strong>Precaução caso o tanque de água esteja em nível baixo, liga o tanque de água e irriga simultaneamente</strong></li>
    <li><strong>Precaução caso haja erro de sensor de nível de água</strong></li>
    <li><strong>Timeout caso o sensor de umidade falhe</strong></li>
  </ul>
</details>


## Esquema Geral do Sistema
![Irrigação drawio (1)](https://github.com/user-attachments/assets/a1357d2c-8834-49f1-b013-14b51f24a0bd)

## Esquema de Conexão
![Conexões drawio (2)](https://github.com/user-attachments/assets/87d00905-9c92-4b0c-a60f-a35893415945)

