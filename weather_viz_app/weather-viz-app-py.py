from flask import Flask, render_template, jsonify
import requests
from datetime import datetime

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/weather')
def get_weather():
    api_key = "YOUR_OPENWEATHERMAP_API_KEY"
    city = "London"
    url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}&units=metric"
    
    response = requests.get(url)
    data = response.json()
    
    if response.status_code == 200:
        weather_data = {
            "temperature": data["main"]["temp"],
            "description": data["weather"][0]["description"],
            "icon": data["weather"][0]["icon"],
            "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        }
        return jsonify(weather_data)
    else:
        return jsonify({"error": "Unable to fetch weather data"}), 500

if __name__ == '__main__':
    app.run(debug=True)
