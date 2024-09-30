Projeto de Dashboard IoT - Monitoramento de Temperatura, Luminosidade e Umidade 

Este projeto consiste em um sistema de monitoramento de variáveis ambientais como temperatura, luminosidade e umidade, desenvolvido utilizando Python para o dashboard, uma máquina virtual para o processamento dos dados, Postman para teste de APIs e o simulador Wokwi para simulação de sensores. 

Descrição do Projeto 
O objetivo deste projeto é criar um sistema de monitoramento e visualização de dados de sensores em um ambiente de IoT. Os dados são coletados de sensores virtuais simulados pelo Wokwi, que são enviados para uma API, testada e validada com o Postman. Os dados coletados são então processados por uma máquina virtual e visualizados em um dashboard interativo desenvolvido em Python. 

Componentes do Projeto 
Wokwi (Simulador de Hardware) 
Utilizado para simular os sensores de temperatura, luminosidade e umidade. 
O Wokwi fornece dados simulados que representam os valores dos sensores em um ambiente controlado. 

Máquina Virtual 
A máquina virtual é responsável pelo processamento dos dados recebidos dos sensores. 
Pode ser configurada para hospedar um servidor, banco de dados, e interagir com os componentes do sistema. 

Postman (Teste de API) 
O Postman é utilizado para realizar o teste das APIs que recebem os dados do Wokwi. 
Garante que as requisições estão sendo feitas corretamente e que os dados estão sendo transmitidos para o servidor. 

Dashboard em Python 
Utilizando bibliotecas como Dash, Plotly e Flask, foi desenvolvido um dashboard para visualização dos dados coletados. 
O dashboard exibe gráficos em tempo real de temperatura, luminosidade e umidade, proporcionando uma visão clara das mudanças ambientais. 

Fluxo de Dados 
Simulação no Wokwi: 
Sensores de temperatura, luminosidade e umidade são simulados no Wokwi. 
Os dados dos sensores são enviados para um endpoint via HTTP. 

Recepção e Processamento dos Dados: 
A máquina virtual recebe os dados dos sensores e armazena em um banco de dados para persistência. 
O servidor na máquina virtual está preparado para processar os dados recebidos e garantir que estejam prontos para serem visualizados. 

Testes com Postman: 
O Postman é utilizado para testar e validar as requisições, verificando os pontos de integração da API que recebe os dados do Wokwi. 

Dashboard de Visualização: 
O dashboard desenvolvido em Python recebe os dados processados e os exibe em gráficos interativos. 
Cada variável (temperatura, luminosidade, umidade) é apresentada em um gráfico específico, mostrando os valores em tempo real ou de acordo com um histórico selecionado. 

Requisitos do Projeto 
Python: 3.x 
Bibliotecas Python: 
Dash e Plotly para construção do dashboard 
Flask para criação de endpoints de API 
Pandas para manipulação dos dados
Wokwi: Conta criada para simular os sensores 
Máquina Virtual: Pode ser uma instância de AWS EC2, Google Cloud VM ou uma VM local 
Postman: Para testes e validação das APIs 

Executar a Máquina Virtual: 
Configure a máquina virtual de acordo com o provedor de serviços escolhido (AWS, Google Cloud, etc.). 
Instale e configure um servidor (como Flask) para receber as requisições do Wokwi. 

Configurar o Wokwi: 
Configure os sensores no Wokwi e defina o endpoint para onde os dados devem ser enviados. 

Testar a API com o Postman: 
Importe a coleção do Postman incluída no repositório e teste as rotas. 

Funcionalidades 

Gráficos Interativos: Visualize os dados de temperatura, luminosidade e umidade em tempo real. 
Historico de Dados: Consulte os valores registrados ao longo do tempo para identificar padrões. 
Alertas Customizáveis: Defina limites para cada variável e receba alertas visuais no dashboard. 

Considerações Finais 
Este projeto é uma ótima maneira de integrar tecnologias de IoT com visualização de dados, oferecendo uma solução prática para monitoramento de variáveis ambientais. É ideal para aprendizado e desenvolvimento de soluções reais para automação residencial ou industrial. 

arquitetura do projeto



![alt text](image.png)

integrantes:
Felipe Fernandes -554598
Gustavo Martins - 556956
Henrique Ignacio - 555274