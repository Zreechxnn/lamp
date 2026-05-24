const statusSpan = document.getElementById('status');
const bulbIcon = document.getElementById('bulbIcon');
const connectionDot = document.getElementById('connectionDot');

let currentState = 'OFF';
let isFetching = false;

function updateUI(state, isConnected = true) {
    if (!isConnected) {
        connectionDot.className = 'dot offline';
        statusSpan.innerText = 'TERPUTUS';
        statusSpan.style.color = '#94a3b8';
        bulbIcon.classList.remove('nyala');
        bulbIcon.style.pointerEvents = 'none'; // Matikan klik ikon kalau offline
        return;
    }

    connectionDot.className = 'dot online';
    bulbIcon.style.pointerEvents = 'auto'; // Aktifkan klik ikon

    if (state === 'ON') {
        currentState = 'ON';
        statusSpan.innerText = 'MENYALA';
        statusSpan.style.color = '#10b981';
        bulbIcon.classList.add('nyala');
    } else if (state === 'OFF') {
        currentState = 'OFF';
        statusSpan.innerText = 'MATI';
        statusSpan.style.color = '#ef4444';
        bulbIcon.classList.remove('nyala');
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
    if (isFetching) return; // Cegah spam klik jika ESP32 sedang memproses
    const action = currentState === 'ON' ? 'off' : 'on';
    fetchState('/' + action);
}

window.onload = () => {
    fetchState('/status');
    
    // Jangan lakukan polling jika user sedang ngeklik (isFetching)
    setInterval(() => {
        if (!isFetching) fetchState('/status');
    }, 2000);
};