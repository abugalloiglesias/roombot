#include "ServerManager.h"

ServerManager::ServerManager(int port, Roomba *roomba)
    : server(port)
{
    this->roomba = roomba;

    server.on("/", [this]() {
        this->handleRoot();
    });
    server.on("/startsafe", [this]() {
        this->handleStartSafe();
    });
    server.on("/startfull", [this]() {
        this->handleStartFull();
    });
    server.on("/oistop", [this]() {
        this->handleOIStop();
    });
    server.on("/poweroff", [this]() {
        this->handlePowerOff();
    });
    server.on("/drive", [this]() {
        this->handleDrive();
    });
    server.on("/stop", [this]() {
        this->handleStop();
    });
    server.on("/song", [this]() {
        this->handleSong();
    });
}

void ServerManager::begin()
{
    server.begin();
}

void ServerManager::handleClient(){
    server.handleClient();
}

void ServerManager::handleOIStop()
{
    roomba->stop();
    Serial.println("Open Interface stopped");
    server.send(200, "text/html", "Open Interface stop command executed");
}

void ServerManager::handleStartSafe()
{
    roomba->startSafe();
    roomba->setPowerLED(128, 255);
    Serial.println("Open Interface started in safe mode");
    server.send(200, "text/html", "Start in safe mode command executed");
}

void ServerManager::handleStartFull()
{
    roomba->startFull();
    Serial.println("Open Interface started in full mode");
    server.send(200, "text/html", "Start in full mode command executed");
}

void ServerManager::handlePowerOff()
{
    roomba->powerOff();
    Serial.println("Turned off");
    server.send(200, "text/html", "Power off command executed");
}

void ServerManager::handleDrive()
{
    roomba->driveWheels(server.arg("speedLeft").toInt(), server.arg("speedRight").toInt());
    server.send(200, "text/html", "Drive command executed");
}

void ServerManager::handleStop()
{
    roomba->driveStop();
    Serial.println("Stopped");
    server.send(200, "text/html", "Stop command executed");
}

void ServerManager::handleSong()
{
    roomba->playSound(2);
    Serial.println("Playing song");
    server.send(200, "text/html", "Playing sound command executed");
}

void ServerManager::handleRoot()
{
    server.send(200, "text/html", "<!DOCTYPE html><html><head><link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css'integrity='sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk' crossorigin='anonymous'><style>body {text-align: center;}#h_joystick {position: relative;box-sizing: content-box;margin-top: 100px;}#v_joystick {position: relative;box-sizing: content-box;margin-top: 100px;}</style><meta charset='utf-8' /><script src='https://yoannmoi.net/nipplejs/javascripts/nipplejs.js'></script><script type='text/javascript'>function init() {ip = '" + WiFi.localIP().toString() + "';x_component = 0; y_component = 0; speedLeft = 0; speedRight = 0; h_manager = nipplejs.create({ zone: document.getElementById('h_joystick'), threshold: 0.1, position: { left: '50%', top: '50%' }, mode: 'static', size: 150, color: '#000000', lockX: true }); h_manager.on('move', function (event, nipple) { x_component = nipple.distance * Math.cos(nipple.angle.radian) / 75; }); h_manager.on('end', function () { x_component = 0; }); v_manager = nipplejs.create({ zone: document.getElementById('v_joystick'), threshold: 0.1, position: { left: '50%', top: '50%' }, mode: 'static', size: 150, color: '#000000', lockY: true }); v_manager.on('move', function (event, nipple) { y_component = nipple.distance * Math.sin(nipple.angle.radian) / 75; }); v_manager.on('end', function () { y_component = 0; }); timer = setInterval(function () { move(x_component, y_component); }, 100); move = function (x_component, y_component) { $('#x_component').text(x_component); $('#y_component').text(y_component); new_speedLeft = 500 * y_component * (1 - x_component); if (y_component >= 0 && new_speedLeft > 500 * y_component || y_component <= 0 && new_speedLeft < 500 * y_component) { new_speedLeft = 500 * y_component; } new_speedRight = 500 * y_component * (1 + x_component); if (y_component >= 0 && new_speedRight > 500 * y_component || y_component <= 0 && new_speedRight < 500 * y_component) { new_speedRight = 500 * y_component; } if (Math.round(new_speedLeft) != speedLeft || Math.round(new_speedRight) != speedRight) { speedLeft = Math.round(new_speedLeft); speedRight = Math.round(new_speedRight); $('#speed_left').text(speedLeft); $('#speed_right').text(speedRight); fetch('http://' + ip + '/drive?speedLeft=' + speedLeft + '&speedRight=' + speedRight); } } } window.onload = function () { $('#oistop').click(function () { fetch('http://' + ip + '/oistop'); }); $('#startsafe').click(function () { fetch('http://' + ip + '/startsafe'); }); $('#startfull').click(function () { fetch('http://' + ip + '/startfull'); }); $('#poweroff').click(function () { fetch('http://' + ip + '/poweroff'); }); $('#song').click(function () { fetch('http://' + ip + '/song'); }); init(); }</script></head><body><div class='container'><h1>Roombot</h1><button id='startsafe'>Start in Safe Mode</button><button id='startfull'>Start in Full Mode</button><button id='oistop'>OIStop</button><button id='poweroff'>Power off</button><buttonid='song'>Play Song</button><div class='row'><div id='h_joystick' class='col-sm'><p id='x_component'></p><p id='speed_left'></p></div><div id='v_joystick' class='col-sm'><p id='y_component'></p><p id='speed_right'></p></div></div></div><script src='https://code.jquery.com/jquery-3.5.1.slim.min.js'integrity='sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj'crossorigin='anonymous'></script><script src='https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js'integrity='sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo'crossorigin='anonymous'></script><script src='https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js'integrity='sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI'crossorigin='anonymous'></script></body></html>");
}