from flask import Flask, render_template
import requests

app = Flask(__name__)

FIWARE_URL = "http://20.201.119.198:1026/v2/entities/ESP32Device"

@app.route('/')
def index():
    try:
        response = requests.get(FIWARE_URL)
        data = response.json()
        temperature = data['temperature']['value']
        luminosity = data['luminosity']['value']
        return render_template('dashboard.html', temperature=temperature, luminosity=luminosity)
    except Exception as e:
        return f"Error: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)
