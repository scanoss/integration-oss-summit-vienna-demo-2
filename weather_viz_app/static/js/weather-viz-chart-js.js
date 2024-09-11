// Using Chart.js (MIT License)
function createChart(labels, data) {
    const ctx = document.getElementById('temperature-chart').getContext('2d');
    new Chart(ctx, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: 'Temperature (°C)',
                data: data,
                borderColor: 'rgb(75, 192, 192)',
                tension: 0.1
            }]
        },
        options: {
            responsive: true,
            scales: {
                y: {
                    beginAtZero: false
                }
            }
        }
    });
}

let temperatureData = [];
let timeLabels = [];

function updateWeather() {
    fetch('/weather')
        .then(response => response.json())
        .then(data => {
            document.getElementById('temperature').textContent = data.temperature;
            document.getElementById('description').textContent = data.description;
            document.getElementById('timestamp').textContent = data.timestamp;

            temperatureData.push(data.temperature);
            timeLabels.push(data.timestamp);

            if (temperatureData.length > 10) {
                temperatureData.shift();
                timeLabels.shift();
            }

            createChart(timeLabels, temperatureData);
        })
        .catch(error => console.error('Error:', error));
}

updateWeather();
setInterval(updateWeather, 60000);  // Update every minute
