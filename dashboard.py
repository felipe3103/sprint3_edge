import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go
import requests
import json

# Inicializando o app Dash
app = dash.Dash(__name__)

# Layout do dashboard
app.layout = html.Div([
    html.H1("Monitoramento de Variáveis ESP32"),
    dcc.Graph(id='temperature-graph'),
    dcc.Graph(id='humidity-graph'),
    dcc.Graph(id='luminosity-graph'),
    dcc.Interval(id='interval-component', interval=10*1000, n_intervals=0)  # Atualiza a cada 10 segundos
])

# Função para coletar os dados do FIWARE
def get_fiware_data():
    url = "http://FIWARE_ENDPOINT/v2/entities/ESP32Device"  # Substitua pelo seu URL do FIWARE
    headers = {'Content-Type': 'application/json'}
    response = requests.get(url, headers=headers)
    
    if response.status_code == 200:
        data = json.loads(response.text)
        temperature = data['temperature']['value']
        humidity = data['humidity']['value']
        luminosity = data['luminosity']['value']
        return temperature, humidity, luminosity
    else:
        return None, None, None

# Callback para atualizar os gráficos
@app.callback(
    [Output('temperature-graph', 'figure'),
     Output('humidity-graph', 'figure'),
     Output('luminosity-graph', 'figure')],
    [Input('interval-component', 'n_intervals')]
)
def update_graphs(n):
    temperature, humidity, luminosity = get_fiware_data()

    # Gráfico de temperatura
    temp_fig = go.Figure(go.Indicator(
        mode="gauge+number",
        value=temperature,
        title={'text': "Temperatura (°C)"}
    ))

    # Gráfico de umidade
    hum_fig = go.Figure(go.Indicator(
        mode="gauge+number",
        value=humidity,
        title={'text': "Umidade (%)"}
    ))

    # Gráfico de luminosidade
    lum_fig = go.Figure(go.Indicator(
        mode="gauge+number",
        value=luminosity,
        title={'text': "Luminosidade"}
    ))

    return temp_fig, hum_fig, lum_fig

# Executando o servidor
if __name__ == '__main__':
    app.run_server(debug=True)
