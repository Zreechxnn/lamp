const statusSpan = document.getElementById('status');
const bulbIcon = document.getElementById('bulbIcon');
const connectionDot = document.getElementById('connectionDot');

let currentState = 'OFF';
let isFetching = false;
let ws = null;

// Inisialisasi WebSocket
function connectWebSocket() {
  const wsUrl = `ws://${window.location.hostname}:81/`;
  ws = new WebSocket(wsUrl);

  ws.onopen = () => {
    console.log('WebSocket connected');
    connectionDot.className = 'dot online';
  };

  ws.onmessage = (event) => {
    try {
      const data = JSON.parse(event.data);
      if (data.status === 'ON' || data.status === 'OFF') {
        updateUI(data.status, true);
      }
    } catch (e) {
      console.error('Invalid JSON:', e);
    }
  };

  ws.onclose = () => {
    console.log('WebSocket disconnected, retry in 3s');
    connectionDot.className = 'dot offline';
    setTimeout(connectWebSocket, 3000);
  };

  ws.onerror = (error) => {
    console.error('WebSocket error:', error);
    ws.close();
  };
}

function updateUI(state, isConnected = true) {
    if (!isConnected) {
        connectionDot.className = 'dot offline';
        statusSpan.innerText = 'TERPUTUS';
        statusSpan.style.color = '#94a3b8';
        bulbIcon.classList.remove('nyala');
        bulbIcon.style.pointerEvents = 'none';
        document.body.classList.remove('night-mode');
        return;
    }

    connectionDot.className = 'dot online';
    bulbIcon.style.pointerEvents = 'auto';

    if (state === 'ON') {
        document.querySelector('.icon-container').classList.add('nyala');
        currentState = 'ON';
        statusSpan.innerText = 'MENYALA';
        statusSpan.style.color = '#10b981';
        bulbIcon.classList.add('nyala');
        document.body.classList.remove('night-mode');
        document.body.classList.add('day-mode');
    } else if (state === 'OFF') {
        document.querySelector('.icon-container').classList.remove('nyala');
        currentState = 'OFF';
        statusSpan.innerText = 'MATI';
        statusSpan.style.color = '#ef4444';
        bulbIcon.classList.remove('nyala');
        document.body.classList.remove('day-mode');
        document.body.classList.add('night-mode');
    }
}

async function fetchState(url) {
    try {
        isFetching = true;
        const controller = new AbortController();
        const timeoutId = setTimeout(() => controller.abort(), 3000);

        const response = await fetch(url, { signal: controller.signal });
        clearTimeout(timeoutId);

        if (response.ok) {
            const data = await response.text();
            updateUI(data.trim(), true);
        } else {
            updateUI(null, false);
        }
    } catch (error) {
        updateUI(null, false);
        console.error('Gagal menghubungi ESP32:', error);
    } finally {
        isFetching = false;
    }
}

function toggleLamp() {
    if (isFetching) return;
    const action = currentState === 'ON' ? 'off' : 'on';
    fetchState('/' + action);
}

window.onload = () => {
    fetchState('/status');
    connectWebSocket();
};