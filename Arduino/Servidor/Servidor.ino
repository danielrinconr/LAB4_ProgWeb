#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "ANICOR"
#define STAPSK "familiaNR213"
#endif

const char *ssid = STASSID;
const char *wf_password = STAPSK;

ESP8266WebServer server(80);

const char *username = "admin";
const char *password = "admin";
const char *realm = "Custom Auth Realm";
const int led = 13;

const char *LogIn = "<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><meta name='description' content='LAB 4 LogIn'><meta name='viewport' content='width=device-width,initial-scale=1,shrink-to-fit=no'><title>Login</title><!-- Bootstrap and jQuery links --><link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script><!-- END --><link href='https://danielrinconr.github.io/LAB4_ProgWeb/css/login.css' type='text/css' rel='stylesheet'></head><body class='login-background'><div class='login-left-section'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'><h2>Bienvenido a Galaga V.1</h2><p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus.</p></div><!--  START LOGIN --><div class='login-page'><div class='main-login-contain'><div class='login-form'><!-- TODO: Fix method in form --><form id='form-validation' action='https://danielrinconr.github.io/LAB4_ProgWeb/Admin/index.html'><h4>Iniciar sesión</h4><p class='login-title-text'>Lorem ipsum dolor sit amet, consectetuer elit.</p><div class='form-group'><input required type='email' id='input-email'> <label class='control-label' for='input-email'>Ingrese su correo</label><i class='bar'></i></div><div class='form-group'><input required type='password' id='input-password'> <label class='control-label' for='input-password'>Contraseña</label><i class='bar'></i></div><!-- TODO: Make the forgot-password-login --><div class='goto-login' hidden><div class='forgot-password-login' hidden><a href='#'><i class='icon icon_lock'></i> ¿Olvidó su contraseña?</a></div><button type='submit' class='btn btn-login float-button-light'>Iniciar</button></div><div class='social-media-section'><div><p>Contáctenos en nuestras redes sociales:</p><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Facebook_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Twitter_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/G+_icon.png'></a></div><div class='login-bottom-text'><p>¿No tiene una cuenta?</p><p>Contáctenos para solicitar una.</p></div></div></form></div></div></div><!--  END LOGIN --></body></html>";
const char *GameHTML = "<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><title>Galaga</title><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script><script src='script.min.js'></script><link rel='stylesheet' href='style.min.css'></head><body><div id='background'><div id='hero'></div><div id='missiles'></div><div id='enemies'></div><div id='missilesEnemies'></div></div><p><input id='send' type='button' value='anadir' onclick='anadir();'></p><label hidden name='resultado'></label> <textarea id='eventos'></textarea></body></html>";
const char *GameCSS = "div#background{width:1200px;height:800px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/background.png)}div#hero{width:50px;height:50px;position:absolute}div#missiles{width:1200px;height:800px;position:absolute}div#missilesEnemies{width:1200px;height:800px;position:absolute}div.missile1{width:10px;height:28px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/missile1.png);position:absolute}div.missile2{width:10px;height:28px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/missile1.png);position:absolute}div#enemies{width:1200px;height:800px;position:absolute}div.enemy{width:50px;height:50px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/enemy.png);position:absolute}div.ally{width:50px;height:50px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/hero.png);position:absolute;left:575px;top:700px}textarea{width:245px;height:277px}";
const char *GameScrpt = "var hero=[];var missiles=[];var missilesEnemies=[];var opio=1;var enemies=[{left: 200, top: 100},{left: 300, top: 100},{left: 400, top: 100},{left: 500, top: 100},{left: 600, top: 100},{left: 700, top: 100},{left: 800, top: 100},{left: 900, top: 100},{left: 200, top: 175},{left: 300, top: 175},{left: 400, top: 175},{left: 500, top: 175},{left: 600, top: 175},{left: 700, top: 175},{left: 800, top: 175},{left: 900, top: 175}];var identifier=0;$(document).keydown(function (e){if (hero.length==0) return; switch (e.keyCode){case 37: for (var i=0; i < hero.length; i++){if (hero[i].left > 10){hero[i].left=hero[i].left - 10; writeOnMessage('heroe', hero[i].iden.toString(), 'mover izquierda');}}break; case 39: for (var i=0; i < hero.length; i++){if (hero[i].left < 1150){hero[i].left=hero[i].left + 10; writeOnMessage('heroe', hero[i].iden.toString(), 'mover derecha');}}break; case 32: for (var i=0; i < hero.length; i++){missiles.push({left: hero[i].left + 20, top: hero[i].top - 20}); writeOnMessage('heroe', hero[i].iden.toString(), 'disparo');}drawMissiles(); break;}drawHero();});function drawHero(){$('#hero')[0].innerHTML=''; for (var i=0; i < hero.length; i++){document.getElementById('hero').innerHTML +=`<div class='ally' style='left:${hero[i].left}px; top:${hero[i].top}px'></div>`;}}function drawMissiles(){$('#missiles')[0].innerHTML=''; for (var i=0; i < missiles.length; i++){document.getElementById('missiles').innerHTML +=`<div class='missile1' style='left:${missiles[i].left}px; top:${missiles[i].top}px'></div>`;}}function moveMissiles(){if (missiles.length !=0){for (var i=0; i < missiles.length; i++){missiles[i].top=missiles[i].top - 8}}}function drawEnemies(){$('#enemies')[0].innerHTML=''; for (var i=0; i < enemies.length; i++){$('#enemies')[0].innerHTML +=`<div class='enemy' style='left:${enemies[i].left}px; top:${enemies[i].top}px'></div>`;}}function moveEnemies(){if (enemies.length==0) return; if (enemies[0].left < 10 && opio==0){opio=1;}if (enemies[0].left > 400 && opio==1){opio=0;}for (var i=0; i < enemies.length; i++){if (opio==1){enemies[i].left=enemies[i].left + 10; /*writeOnMessage('enemigos',i.toString(),'mover derecha');*/}if (opio==0){enemies[i].left=enemies[i].left - 10; /* writeOnMessage('enemigos',i.toString(),'mover izquierda');*/}}}function collisionDetection(){for (var missile=0; missile < missiles.length; missile++){for (var enemy=0; enemy < enemies.length; enemy++){if ( missiles[missile].left >=enemies[enemy].left && missiles[missile].left <=(enemies[enemy].left + 50) && missiles[missile].top <=(enemies[enemy].top + 50) && missiles[missile].top >=enemies[enemy].top ){enemies.splice(enemy, 1); missiles.splice(missile, 1);}}if (missiles[missile].top <=10){missiles.splice(missile, 1);}}}function collisionDetectionEnemie(){for (var missile=0; missile < missilesEnemies.length; missile++){for (var ally=0; ally < hero.length; ally++){if ( missilesEnemies[missile].left >=hero[ally].left && missilesEnemies[missile].left <=(hero[ally].left + 50) && missilesEnemies[missile].top <=(hero[ally].top + 50) && missilesEnemies[missile].top >=hero[ally].top ){hero.splice(ally, 1); missilesEnemies.splice(missile, 1);}}if (missilesEnemies[missile].top >=700){missilesEnemies.splice(missile, 1);}}}function enemyRandomShot(){for (var i=0; i < enemies.length; i++){var number=1 + Math.floor(Math.random() * 100); if (number < 2){missilesEnemies.push({left: enemies[i].left + 20, top: enemies[i].top + 20}); writeOnMessage('enemigos', i, 'disparo');}}}function drawMissilesEnemies(){if (missilesEnemies.length==0) return; $('#missilesEnemies')[0].innerHTML=''; for (var i=0; i < missilesEnemies.length; i++){$('#missilesEnemies')[0].innerHTML +=`<div class='missile2' style='left:${missilesEnemies[i].left}px; top:${missilesEnemies[i].top}px'></div>`;}}function moveMissilesEnemies(){if (missilesEnemies.length==0) return; for (var i=0; i < missilesEnemies.length; i++){missilesEnemies[i].top=missilesEnemies[i].top + 8}}function anadir(){hero.push({left: 500, top: 700, iden: identifier});}function gameLoop(){drawHero(); setTimeout(gameLoop, 100); moveMissiles(); moveMissilesEnemies(); drawMissiles(); drawMissilesEnemies(); moveEnemies(); enemyRandomShot(); drawEnemies(); collisionDetection(); collisionDetectionEnemie(); victory();}function victory(){if (enemies.length==0){$('[name=resultado]')[0].textContent='victory'; $('[name=resultado]')[0].removeAttribute('hidden');}}function writeOnMessage(entidad, numero, accion){$('#eventos')[0].innerHTML +=`${entidad} ${numero} ${accion}\n`; $('#eventos').scrollTop($('#eventos')[0].scrollHeight);}$(document).ready(function (){console.log('ready!'); gameLoop();});";

void handleNotFound()
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void)
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wf_password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", LogIn);
  });
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/LogIn", []() {
    if (!server.authenticate(username, password)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/html", GameHTML);
  });
  server.on("/style.min.css", []() {
    server.send(200, "style", GameCSS);
  });
  server.on("/script.min.js", []() {
    server.send(200, "application/javascript", GameScrpt);
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  MDNS.update();
}
