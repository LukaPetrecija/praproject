function zoomCard(card) {
    const zoomed = document.querySelector('.zoomed');
    if (zoomed) {
        zoomed.classList.remove('zoomed');
        document.querySelectorAll('.card').forEach(c => c.classList.remove('blur'));
    }
    card.classList.add('zoomed');
    document.getElementById('overlay').classList.add('visible');
    document.querySelectorAll('.card').forEach(c => {
        if (c !== card) {
            c.classList.add('blur');
        }
    });
}

function closeCard(event, button) {
    event.stopPropagation();
    const card = button.parentElement;
    card.classList.remove('zoomed');
    document.getElementById('overlay').classList.remove('visible');
    document.querySelectorAll('.card').forEach(c => c.classList.remove('blur'));
}

function closeZoomedCard() {
    const zoomed = document.querySelector('.zoomed');
    if (zoomed) {
        zoomed.classList.remove('zoomed');
    }
    document.getElementById('overlay').classList.remove('visible');
    document.querySelectorAll('.card').forEach(c => c.classList.remove('blur'));
}


function updateData() {
    document.getElementById('temperature').innerText = '/ *C';
    document.getElementById('pressure').innerText = '/ hPa';
    document.getElementById('humidity').innerText = '/ %';
    document.getElementById('gas').innerText = '/ kOhms';
    document.getElementById('altitude').innerText = '/ m';
}

setTimeout(updateData, 5000);

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
