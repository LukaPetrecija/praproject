

// Function to zoom in on a card
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

// Function to close a zoomed card
function closeCard(event, button) {
  event.stopPropagation();
  const card = button.parentElement;
  card.classList.remove('zoomed');
  document.getElementById('overlay').classList.remove('visible');
  document.querySelectorAll('.card').forEach(c => c.classList.remove('blur'));
}

// Function to close the overlay
function closeZoomedCard() {
  const zoomed = document.querySelector('.zoomed');
  if (zoomed) {
    zoomed.classList.remove('zoomed');
    document.getElementById('overlay').classList.remove('visible');
    document.querySelectorAll('.card').forEach(c => c.classList.remove('blur'));
  }
}



const options = {
    username: 'praalgebra',  
    password: 'h1sXSluD0OUMAZpv' 
};

const client = mqtt.connect('wss://praalgebra.cloud.shiftr.io:443/', options); 
client.on('connect', function () {
    console.log('Connected to MQTT broker');
    
    client.subscribe('statsTopic');
});

client.on('message', function (topic, message) {
  const value = message.toString();
  console.log(value);
  const lines = value.split('\n');

  if (topic === 'statsTopic') {
    lines.forEach(line => {
      if (line.includes('Min Temperature')) {
        document.getElementById('minTemperature').innerText = line.split('=')[1].trim() + ' *C';
      } else if (line.includes('Max Temperature')) {
        document.getElementById('maxTemperature').innerText = line.split('=')[1].trim() + ' *C';
      } else if (line.includes('Min Pressure')) {
        document.getElementById('minPressure').innerText = line.split('=')[1].trim() + ' hPa';
      } else if (line.includes('Max Pressure')) {
        document.getElementById('maxPressure').innerText = line.split('=')[1].trim() + ' hPa';
      } else if (line.includes('Min Humidity')) {
        document.getElementById('minHumidity').innerText = line.split('=')[1].trim() + ' %';
      } else if (line.includes('Max Humidity')) {
        document.getElementById('maxHumidity').innerText = line.split('=')[1].trim() + ' %';
      } else if (line.includes('Min Gas')) {
        document.getElementById('minGas').innerText = line.split('=')[1].trim() + ' kOhms';
      } else if (line.includes('Max Gas')) {
        document.getElementById('maxGas').innerText = line.split('=')[1].trim() + ' kOhms';
      } else if (line.includes('Altitude')) {
        document.getElementById('altitude').innerText = line.split('=')[1].trim() + ' m';
      }
    });
  }
});