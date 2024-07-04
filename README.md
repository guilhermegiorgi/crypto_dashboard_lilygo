# A Lilygo Crypto Dashboard

## Arduino Crypto Monitor

This project implements a cryptocurrency monitoring system using Arduino, TFT display, and WiFi connectivity. It fetches real-time data from the Gate.io API and displays it on the screen in a user-friendly manner. The system supports dynamic updating of cryptocurrency pairs via a web interface.

*Este projeto implementa um sistema de monitoramento de criptomoedas usando Arduino, display TFT e conectividade WiFi. Ele obtém dados em tempo real da API Gate.io e os exibe na tela de forma amigável ao usuário. O sistema suporta atualização dinâmica de pares de criptomoedas via interface web.*

<img src="https://github.com/guilhermegiorgi/crypto_dashboard_lilygo/blob/main/lilygo_dashboard1.jpg?raw=true" width="450"><img src="https://github.com/guilhermegiorgi/crypto_dashboard_lilygo/blob/main/lilygo_dashboard2.jpg?raw=true" width="450">

### Características/Features

- *Exibe preços em tempo real e mudanças percentuais para pares de criptomoedas selecionados.*
- Displays real-time prices and percentage changes for selected cryptocurrency pairs.

- *Suporta conectividade com múltiplas redes WiFi para operação robusta.*
- Supports connectivity to multiple WiFi networks for robust operation.

- *Oferece uma interface web para usuários atualizarem dinamicamente os pares de criptomoedas.*
- Provides a web interface for users to dynamically update cryptocurrency pairs.

- *Inclui funcionalidade de tela de apresentação na inicialização para exibir informações essenciais.*
- Includes splash screen functionality at startup to display essential information.

### Componentes usados/Components Used

- **Placa Arduino:** ESP32 S3 ou placas compatíveis
- **Arduino board:** ESP32 S3 or compatible boards

- **Display TFT:** Biblioteca TFT_eSPI utilizada para funcionalidades de display
- **TFT Display:** TFT_eSPI library used for display functionalities

- **Módulo WiFi:** Biblioteca WiFi.h para conectividade de rede
- **WiFi Module:** WiFi.h library for network connectivity

- **Servidor Web:** Biblioteca ESPAsyncWebServer para manipulação da interface web
- **Web Server:** ESPAsyncWebServer library for handling web interface


### Setup Instructions

#### Configuração de Hardware/Hardware Setup

- *Conecte o display TFT e verifique a fiação correta com a placa Arduino.*
- Connect the TFT display and ensure proper wiring with the Arduino board.

#### Dependências/Dependencies

- *Instale as bibliotecas necessárias usando o Gerenciador de Bibliotecas do Arduino:*
- Install necessary libraries using Arduino Library Manager:

- TFT_eSPI
- Arduino_JSON
- ESPAsyncWebServer
- NTPClient
- WiFi

#### Configuração/Configuration

1. *Modifique os arrays `ssidList` e `passwordList` com suas credenciais WiFi.*
1. Modify `ssidList` and `passwordList` arrays with your WiFi credentials.

#### Upload do Código/Upload Code

- *Carregue o sketch para sua placa Arduino usando o IDE do Arduino ou software compatível.*
- Upload the sketch to your Arduino board using the Arduino IDE or compatible software.

#### Acesso/Access

- *Após implantado, acesse a interface de monitoramento via endereço IP exibido na tela TFT.*
- Once deployed, access the monitoring interface via the IP address displayed on the TFT screen.

### Uso/Usage

- *Na inicialização, o sistema se conecta às redes WiFi disponíveis. A tela TFT exibe dados de criptomoedas em tempo real de forma rotativa através de três telas. Os usuários podem modificar os pares de criptomoedas exibidos através da interface web acessível pelo endereço IP exibido na tela.*
- Upon startup, the system connects to available WiFi networks. The TFT screen displays real-time cryptocurrency data in a rotating fashion across three screens. Users can modify the displayed cryptocurrency pairs via the web interface accessible through the IP address displayed on the screen.

### Contribuições/Contributing

- *Contribuições são bem-vindas! Sinta-se à vontade para fazer um fork do repositório, realizar suas alterações e enviar um pull request.*
  - Contributions are welcome! Feel free to fork the repository, make your changes, and submit a pull request.


- *Considere fazer uma doação para apoiar o desenvolvimento deste projeto.*
  - *Consider donating to support the ongoing development of this project.* 


  - EVM: 0x288656d7812bfb22317b18a1e3b23d3fc904ee70
  - TRC20: TT65xcZRsM8Ym4egt9PFdp5pu9AqWMUAiU   
  - BTC: bc1qep3syuc4f9lkj24c42w9pgyx3krfe2v5kepr2s

### Licença/License

- *Este projeto está licenciado sob a Licença MIT.*
- This project is licensed under the MIT License 
