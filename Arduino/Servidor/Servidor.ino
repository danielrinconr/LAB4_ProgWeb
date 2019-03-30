#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "ANICOR"
#define STAPSK "familiaNR213"
#endif

const char *ssid = STASSID;
const char *wf_password = STAPSK;

ESP8266WebServer server(80);

const char *LogIn = "<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><meta name='description' content='LAB 4 LogIn'><meta name='viewport' content='width=device-width,initial-scale=1,shrink-to-fit=no'><title>Login</title><!-- Bootstrap and jQuery links --><link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script><!-- END --><link href='https://danielrinconr.github.io/LAB4_ProgWeb/css/login.css' type='text/css' rel='stylesheet'></head><body class='login-background'><div class='login-left-section'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'><h2>Bienvenido a Galaga V.1</h2><p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus.</p></div><!--  START LOGIN --><div class='login-page'><div class='main-login-contain'><div class='login-form'><!-- TODO: Fix method in form --><form id='form-validation' action='/LogIn' method='POST'><h4>Iniciar sesión</h4><p class='login-title-text'>Lorem ipsum dolor sit amet, consectetuer elit.</p><div class='form-group'><input type='text' name='username' id='input-email' required> <label class='control-label' for='input-email'>Ingrese su nombre de usuario</label><i class='bar'></i></div><div class='form-group'><input type='password' name='password' id='input-password' required> <label class='control-label' for='input-password'>Contraseña</label><i class='bar'></i></div><!-- TODO: Make the forgot-password-login --><div class='goto-login' hidden><div class='forgot-password-login' hidden><a href='#'><i class='icon icon_lock'></i> ¿Olvidó su contraseña?</a></div><button type='submit' class='btn btn-login float-button-light'>Iniciar</button></div><div class='social-media-section'><div><p>Contáctenos en nuestras redes sociales:</p><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Facebook_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Twitter_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/G+_icon.png'></a></div><div class='login-bottom-text'><p>¿No tiene una cuenta?</p><p>Contáctenos para solicitar una.</p></div></div></form></div></div></div><!--  END LOGIN --></body></html>";
const char *AdminHTML = "<!DOCTYPE html><html lang='en'><head> <meta charset='utf-8'> <meta name='description' content='LAB 4 Admin'> <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'> <title>Admin</title> <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'> <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script> <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script> <script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/plugins/screenfull.js/dist/screenfull.min.js'></script> <script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/plugins/jquery-slimscroll/jquery.slimscroll.js'></script> <link rel='stylesheet' href='https://danielrinconr.github.io/LAB4_ProgWeb/assets/icons_fonts/font-awesome/css/font-awesome.min.css'/> <link href='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/css/components.min.css' type='text/css' rel='stylesheet'/> <link rel='stylesheet' href='https://danielrinconr.github.io/LAB4_ProgWeb/assets/layouts/layouts_left_menu/left_menu_layout.min.css'/> </head><body class='nav-medium'> <div class='container body'> <div class='main_container'> <div class='page-loader'> <div class='preloader loading'> <span class='slice'></span> <span class='slice'></span> <span class='slice'></span> <span class='slice'></span> <span class='slice'></span> <span class='slice'></span> </div></div><div class='col-md-3 left_color'> <div class='left_color scroll-view'> <div class='navbar nav_title'> <a href='/' class='medium-logo'> <img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'> </a> <a href='index.html' class='small-logo'> <img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'> </a> </div><div class='clearfix'></div><div id='sidebar-menu' class='main_menu_side hidden-print main_menu'> <div class='menu_section'> <h3>General</h3> <ul class='nav side-menu'> <li><a class='waves-effect waves-light' href='/'><i class='fa fa-home'></i> Dashboard</a></li><li> <a class='waves-effect waves-light' href='/LogIn'></i> Game</a> </li></ul> </div></div><div class='sidebar-footer hidden-small'> <a data-toggle='tooltip' data-placement='top' title='Settings'> <span class='fa fa-cog' aria-hidden='true'></span> </a> <a class='toggle-fullscreen' data-toggle='tooltip' data-placement='top' title='FullScreen'> <span class='fa fa-arrows-alt' aria-hidden='true'></span> </a> <a data-toggle='tooltip' data-placement='top' title='Logout' href='/'> <span class='fa fa-power-off' aria-hidden='true'></span> </a> </div></div></div><div class='top_nav'> <div class='nav_menu'> <nav> <div class='nav toggle'> <a id='menu_toggle'><i class='fa fa-bars'></i></a> <div class='responsive-logo'> <a href='index.html'> <img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'> </a> </div></div></nav> </div></div><div class='clearfix'></div><div class='container-fluid right_color'> <div class='page-main-header'> <h2 class='page-name-title'>Dashboard V1</h2> <ol class='breadcrumb'> <li><a href='#'>Home</a></li><li class='text-info'>Dashboard</li><li class='active'>Dashboard V1</li></ol> </div><div class='contain-section dashboard_v1'> <div class='row'> <div class='col-lg-3 col-md-3 col-sm-3 col-xs-12'> <div class='tile-stats bg-primary'> <div class='icon'><i class='fa fa-users'></i></div><div class='count'>3</div><h3>Usuarios Registrados</h3> <a href='javascript:' hidden> <p>View More <i class='fa fa-hand-o-right'></i></p></a> </div></div><div class='col-lg-3 col-md-3 col-sm-3 col-xs-12'> <div class='tile-stats bg-purple'> <div class='icon'><i class='fa fa-comments-o'></i></div><div class='count'>0</div><h3>Usuarios jugando</h3> <a href='javascript:' hidden> <p>View More <i class='fa fa-hand-o-right'></i></p></a> </div></div><div class='col-lg-3 col-md-3 col-sm-3 col-xs-12'> <div class='tile-stats bg-pink'> <div class='icon'><i class='fa fa-sort-amount-desc'></i></div><div class='count'>0</div><h3>Usuarios a la espera</h3> <a href='javascript:' hidden> <p>View More <i class='fa fa-hand-o-right'></i></p></a> </div></div></div><div class='row'> <div class='section-body'> <canvas id='line-basic'></canvas> </div></div></div></div><footer class='footer'> © 2019 All rights reserved. Template designed by <a class='text-primary' href='javascript:'>Prince</a> </footer> </div></div><script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/js/left-menu.min.js'></script> <script src='https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.18.1/moment.min.js'></script> <script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/plugins/chart.js/dist/Chart.min.js'></script> <script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/plugins/chart.js/samples/utils.js'></script> <script src='https://danielrinconr.github.io/LAB4_ProgWeb/assets/global/js/dashboard_v1.min.js'></script> </body></html>";
const char *GameHTML = "<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><title>Galaga</title><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script><script src='script.min.js'></script><link rel='stylesheet' href='style.min.css'></head><body><div id='background'><div id='heroes'></div><div id='missiles'></div><div id='enemies'></div><div id='missilesEnemies'></div></div><p><input id='send' type='button' value='anadir' onclick='anadir()'></p><label hidden name='resultado'></label> <textarea id='eventos' hidden></textarea></body></html>";
const char *GameCSS = "div#background{width:1200px;height:800px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/background.png)}div#hero{width:50px;height:50px;position:absolute}div#missiles{width:1200px;height:800px;position:absolute}div#missilesEnemies{width:1200px;height:800px;position:absolute}div.missile1{width:10px;height:28px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/missile1.png);position:absolute}div.missile2{width:10px;height:28px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/missile1.png);position:absolute}div#enemies{width:1200px;height:800px;position:absolute}div.enemy{width:50px;height:50px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/enemy.png);position:absolute}div.ally{width:50px;height:50px;background-image:url(https://danielrinconr.github.io/LAB4_ProgWeb/Game/assets/hero.png);position:absolute;left:575px;top:700px}textarea{width:245px;height:277px}";
const char *GameScrpt = "var heroes=[{left:200,top:700,st:1},{left:300,top:700,st:1},{left:400,top:700,st:1},{left:500,top:700,st:1},{left:600,top:700,st:1}];var missiles=[];var missilesEnemies=[];var opio=1;var limitebalasenemigas=50;var sync=true;/* var identifier=0; //Dado por el servidor*/var enemies=[{left:200,top:100,st:0},{left:300,top:100,st:0},{left:400,top:100,st:0},{left:500,top:100,st:0},{left:600,top:100,st:0},{left:700,top:100,st:0},{left:800,top:100,st:0},{left:900,top:100,st:0},{left:200,top:175,st:0},{left:300,top:175,st:0},{left:400,top:175,st:0},{left:500,top:175,st:0},{left:600,top:175,st:0},{left:700,top:175,st:0},{left:800,top:175,st:0},{left:900,top:175,st:0}];$(document).keydown(function (e){if (heroes.length==0) return; switch (e.keyCode){case 37: if (heroes[identifier].left > 10){heroes[identifier].left=heroes[identifier].left - 10; $.post('./UsAct',{u:identifier, mv:heroes[identifier].left}); writeOnMessage('heroes', identifier, 'mover izquierda');}break; case 39: if (heroes[identifier].left < 1150){heroes[identifier].left=heroes[identifier].left + 10; $.post('./UsAct',{u:identifier, mv:heroes[identifier].left}); writeOnMessage('heroes', identifier, 'mover derecha');}break; case 32: missiles.push({left: heroes[identifier].left + 20, top: heroes[identifier].top - 20}); $.post('./UsAct',{u:identifier, fr:1}); writeOnMessage('heroes', identifier, 'disparo'); drawMissiles(); break;}drawheroes();});function drawheroes(){$('#heroes')[0].innerHTML=''; for (var i=0; i < 5; i++){if(heroes[i].st) continue; $('#heroes')[0].innerHTML +=`<div class='ally' style='left:${heroes[i].left}px; top:${heroes[i].top}px'></div>`;}}function drawMissiles(){$('#missiles')[0].innerHTML=''; for (var i=0; i < missiles.length; i++){$('#missiles')[0].innerHTML +=`<div class='missile1' style='left:${missiles[i].left}px; top:${missiles[i].top}px'></div>`;}}function moveMissiles(){if (missiles.length !=0){for (var i=0; i < missiles.length; i++){missiles[i].top=missiles[i].top - 8}}}function drawEnemies(){$('#enemies')[0].innerHTML=''; for (var i=0; i < enemies.length; i++){if(enemies[i].st) continue; $('#enemies')[0].innerHTML +=`<div class='enemy' style='left:${enemies[i].left}px; top:${enemies[i].top}px'></div>`;}}function moveEnemies(){if (enemies.length==0) return; if (enemies[0].left < 10 && opio==0){opio=1;}if (enemies[0].left > 400 && opio==1){opio=0;}for (var i=0; i < enemies.length; i++){if (opio==1){enemies[i].left=enemies[i].left + 10; /*writeOnMessage('enemigos',i.toString(),'mover derecha');*/}if (opio==0){enemies[i].left=enemies[i].left - 10; /* writeOnMessage('enemigos',i.toString(),'mover izquierda');*/}}}function collisionDetection(){for (var missile=0; missile < missiles.length; missile++){for (var enemy=0; enemy < enemies.length; enemy++){if ( missiles[missile].left >=enemies[enemy].left && missiles[missile].left <=(enemies[enemy].left + 50) && missiles[missile].top <=(enemies[enemy].top + 50) && missiles[missile].top >=enemies[enemy].top ){/* enemies.splice(enemy, 1); */ enemies[enemy].st=1; missiles.splice(missile, 1);}}if (missiles[missile].top <=10){missiles.splice(missile, 1);}}}function collisionDetectionEnemie(){for (var missile=0; missile < missilesEnemies.length; missile++){for (var ally=0; ally < heroes.length; ally++){if(heroes[ally].st) continue; if ( missilesEnemies[missile].left >=heroes[ally].left && missilesEnemies[missile].left <=(heroes[ally].left + 50) && missilesEnemies[missile].top <=(heroes[ally].top + 50) && missilesEnemies[missile].top >=heroes[ally].top ){/* heroes.splice(ally, 1); */ heroes[ally].st=0; missilesEnemies.splice(missile, 1);}}if (missilesEnemies[missile].top >=700){missilesEnemies.splice(missile, 1);}}}function enemyRandomShot(){if (missilesEnemies.length < limitebalasenemigas){for (var i=0; i < enemies.length; i++){var number=1 + Math.floor(Math.random() * 100); if (number < 2){missilesEnemies.push({left: enemies[i].left + 20, top: enemies[i].top + 20}); writeOnMessage('enemigos', i, 'disparo');}}}}function drawMissilesEnemies(){if (missilesEnemies.length==0) return; $('#missilesEnemies')[0].innerHTML=''; for (var i=0; i < missilesEnemies.length; i++){$('#missilesEnemies')[0].innerHTML +=`<div class='missile2' style='left:${missilesEnemies[i].left}px; top:${missilesEnemies[i].top}px'></div>`;}}function moveMissilesEnemies(){if (missilesEnemies.length==0) return; for (var i=0; i < missilesEnemies.length; i++){missilesEnemies[i].top=missilesEnemies[i].top + 8}}function anadir(){heroes.push({left: 500, top: 700, iden: identifier, maxbullets: 50, shoot: 1});}function bullettimeout(){for (var ally=0; ally < heroes.length; ally++){if (heroes[i].shoot==1){heroes[i].maxbullets--;}if (heroes[i].maxbullets <=1){heroes[i].maxbullets=50; heroes[i].shoot==0;}}}function gameLoop(){drawheroes(); moveMissiles(); moveMissilesEnemies(); drawMissiles(); drawMissilesEnemies(); moveEnemies(); enemyRandomShot(); drawEnemies(); collisionDetection(); collisionDetectionEnemie(); victory(); Sync();}function victory(){if (enemies.length==0){$('[name=resultado]')[0].textContent='victory'; $('[name=resultado]')[0].removeAttribute('hidden');}}function writeOnMessage(entidad, numero, accion){/* $('#eventos')[0].innerHTML +=`${entidad}${numero}${accion}\\n`; $('#eventos').scrollTop($('#eventos')[0].scrollHeight); */}function Start(){$.ajax({type: 'POST', url: './NewUser', success: function (data){console.log(JSON.stringify(data)); var pSt=data.pSt; var pPs=data.pPs; for (var i=0; i < pSt.length; i++){if (pSt[i]==1) continue; heroes[i].st=pSt[i]; left/* heroes.push({id: identifier, left: pPs[i], top: 700,}); */}}, failure: function (errMsg){alert(errMsg);}});}function Sync(){if(!sync) return; $.ajax({type: 'POST', url: './Sync', success: function (data){/* console.log(JSON.stringify(data)); */ var pSt=data.pSt; var pPs=data.pPs; for (var i=0; i < pSt.length; i++){heroes[i].st=pSt[i]; if (pSt[i]==1) continue; heroes[i].left=pPs[i];}sync=true;}, failure: function (errMsg){alert(errMsg);}});}$(document).ready(function (){console.log('ready!'); setInterval(gameLoop, 100);});";

#define MaxNumUsers 5
#define MaxNumPlayers 3

const char *username[]{"admin", "ham", "j1", "j2", "j3"};
const char *password[]{"admin", "1234", "1234", "1234", "1234"};

byte cnUsers = 0;
uint16 stPos = 500;
// Player status.
byte playerSt[] {1, 1, 1, 1, 1};
// X position of the players.
uint16 playerPos[]{0, 0, 0, 0, 0};
// Player Points.
byte playerPnts[]{0, 0, 0, 0, 0};
// Enemies status.
byte enemiesSt[16];
// Posición del enemigo superior izquierdo.
byte enmiesPos = 200;
// Id of current player.
byte userid = 0;

const int led = 13;

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

  for (byte i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void reqLogIn()
{
  bool lg = false;
  if (server.args() < 2)
  {
    server.send(400, "text/plain", "Omitió la página de LogIn");
    return;
    //return server.requestAuthentication();
  }
  char *us = const_cast<char *>(server.arg(0).c_str());
  char *ps = const_cast<char *>(server.arg(1).c_str());
  bool aut = server.authenticate(us, ps);
  // Serial.printf("Loging in: -u:%s -p:%s... %d\n", us, ps, aut);

  for (byte i = 0; i < MaxNumUsers; i++)
  {
    // Serial.printf("-ui:%s -uc:%s -pi:%s -pc:%s\n", us, username[i], ps, password[i], aut);
    if (strcmp(us, username[i]) != 0)
      continue;
    if (strcmp(ps, password[i]) != 0)
      continue;
    userid = i;
    if (playerSt[userid] == 1)
    {
      playerSt[userid] = 0;
      playerPos[userid] = stPos;
      cnUsers++;
    }
    Serial.printf("Jugador %d logeado. Num us log:%d\n", userid + 1, cnUsers);
    lg = true;
    break;
  }
  if (lg == false)
    server.send(404, "text/plain", "Fail username or password. Try again.");
  if (cnUsers <= 3)
    server.send(200, "text/html", GameHTML);
  else
    server.send(200, "text/plain", "Max number of player connected.");
}

void NewPlayer()
{
  // Allocate the JSON document
  const size_t capacity = 2*JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(5);
  DynamicJsonDocument doc(capacity);

  // Add values in the document
  doc["u"] = userid;
  JsonArray pSt = doc.createNestedArray("pSt");
  JsonArray pPs = doc.createNestedArray("pPs");
  doc["ePs"] = 200;
  JsonArray eSt = doc.createNestedArray("eSt");
  for (int i = 0; i < MaxNumUsers; i++)
  {
    pSt.add(playerSt[i]);
    pPs.add(playerPos[i]);
  }
  for (int i = 0; i < 16; i++)
    eSt.add(enemiesSt[i]);

  // Array for JSON string representation.
  char out[128];
  serializeJson(doc, out);
  server.send(200, "application/json", out);
}

void Sync()
{
  // Allocate the JSON document
  const size_t capacity = 2*JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(5);
  DynamicJsonDocument doc(capacity);

  // Add values in the document
  doc["u"] = userid;
  JsonArray pSt = doc.createNestedArray("pSt");
  JsonArray pPs = doc.createNestedArray("pPs");
  doc["ePs"] = 200;
  JsonArray eSt = doc.createNestedArray("eSt");
  for (int i = 0; i < MaxNumUsers; i++)
  {
    pSt.add(playerSt[i]);
    pPs.add(playerPos[i]);
  }
  for (int i = 0; i < 16; i++)
    eSt.add(enemiesSt[i]);

  // Array for JSON string representation.
  char out[128];
  serializeJson(doc, out);
  server.send(200, "application/json", out);
}

void UsAct()
{
  char *us = const_cast<char *>(server.arg(0).c_str());
  char *ps = const_cast<char *>(server.arg(1).c_str());
  char *act = const_cast<char *>(server.argName(1).c_str());
  // Serial.printf("{%s : %s}\n", server.argName(0).c_str(), us);
  // Serial.printf("{%s : %s}\n", act, ps);
  int id = atoi(us);
  int lf = atoi(ps);
  if(strcmp(act, "mv") == 0)
  {
    playerPos[id] = lf;
    //Serial.printf("u: %d ps:%d\n", id, lf);
  }
  else if(strcmp(act, "fr") == 0)
    //Serial.printf("u: %d Shoot\n",id);
  server.send(200);
}


void setup(void)
{
  for (byte i = 0; i < 16; i++)
  {
    enemiesSt[i] = 1;
  }
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
  server.on("/LogIn", reqLogIn);
  server.on("/style.min.css", []() {
    server.send(200, "style", GameCSS);
  });
  server.on("/script.min.js", []() {
    String _GameScrpt = "var identifier=" + String(userid);
    _GameScrpt += ";";
    _GameScrpt += GameScrpt;
    server.send(200, "application/javascript", _GameScrpt);
  });
  server.on("/Admin", []() {
    if (!server.authenticate(username[0], password[0]))
    {
      return server.requestAuthentication();
    }
    server.send(200, "text/html", AdminHTML);
  });
  server.on("/NewUser", NewPlayer);
  server.on("/Sync", Sync);
  server.on("/UsAct", UsAct);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  MDNS.update();
}
