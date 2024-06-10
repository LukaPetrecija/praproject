function zoomCard(card) {
    const zoomed = document.querySelector('.zoomed');
    if (zoomed) {
        zoomed.classList.remove('zoomed');
    }
    card.classList.add('zoomed');
}

function closeCard(event, button) {
    event.stopPropagation();
    const card = button.parentElement;
    card.classList.remove('zoomed');
}

function updateData() {
    document.getElementById('temperature').innerText = '26°C';
    document.getElementById('pressure').innerText = '1015 hPa';
    document.getElementById('humidity').innerText = '55%';
    document.getElementById('gas').innerText = 'Moderate';
    document.getElementById('altitude').innerText = '1520 m';
}

setTimeout(updateData, 5000);

function zoomCard(card) {
    const zoomed = document.querySelector('.zoomed');
    if (zoomed) {
        zoomed.classList.remove('zoomed');
    }
    card.classList.add('zoomed');
}

function closeCard(event, button) {
    event.stopPropagation(); 
    const card = button.parentElement;
    card.classList.remove('zoomed');
}

const options = {
    username: 'praalgebra',  
    password: 'h1sXSluD0OUMAZpv' 
};

const client = mqtt.connect('wss://praalgebra.cloud.shiftr.io:443/', options); 
client.on('connect', function () {
    console.log('Connected to MQTT broker');
    client.subscribe('outTopic');
});

client.on('message', function (topic, message) {
    const value = message.toString();
    console.log(value);
    if (topic === 'temp') {
        document.getElementById('outTopic').innerText = value + '°C';
    }

    const lines = value.split('\n');
            lines.forEach(line => {
                if (line.includes('Temperature')) {
                    document.getElementById('temperature').innerText = line.split('=')[1].trim();
                } else if (line.includes('Pressure')) {
                    document.getElementById('pressure').innerText = line.split('=')[1].trim();
                } else if (line.includes('Humidity')) {
                    document.getElementById('humidity').innerText = line.split('=')[1].trim();
                } else if (line.includes('Gas')) {
                    document.getElementById('gas').innerText = line.split('=')[1].trim();
                } else if (line.includes('Approx. Altitude')) {
                    document.getElementById('altitude').innerText = line.split('=')[1].trim();
                }
            });
        });