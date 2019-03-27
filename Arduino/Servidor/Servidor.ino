#include <ESP8266WiFi.h>
//
//const char* ssid = "Red 2";
//const char* password = "79966208";

const char* ssid = "Hamana";
const char* password = "12345678";

WiFiServer server(80);
int id = 2;
int red = 16;
int green = 5;
int blue = 4;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  delay(500);
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  if (request == "GET / HTTP/1.1")
    client.println("<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><meta name='description' content='LAB 4 LogIn'><meta name='viewport' content='width=device-width,initial-scale=1,shrink-to-fit=no'><title>Login</title><!-- Bootstrap and jQuery links --><link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script><!-- END --><link href='https://danielrinconr.github.io/LAB4_ProgWeb/css/login.css' type='text/css' rel='stylesheet'></head><body class='login-background'><div class='login-left-section'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/logo.png' alt='logo-image'><h2>Bienvenido a Galaga V.1</h2><p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus.</p></div><!--  START LOGIN --><div class='login-page'><div class='main-login-contain'><div class='login-form'><!-- TODO: Fix method in form --><form id='form-validation' action='https://danielrinconr.github.io/LAB4_ProgWeb/Admin'><h4>Iniciar sesión</h4><p class='login-title-text'>Lorem ipsum dolor sit amet, consectetuer elit.</p><div class='form-group'><input required type='email' id='input-email'> <label class='control-label' for='input-email'>Ingrese su correo</label><i class='bar'></i></div><div class='form-group'><input required type='password' id='input-password'> <label class='control-label' for='input-password'>Contraseña</label><i class='bar'></i></div><!-- TODO: Make the forgot-password-login --><div class='goto-login' hidden><div class='forgot-password-login' hidden><a href='#'><i class='icon icon_lock'></i> ¿Olvidó su contraseña?</a></div><button type='submit' class='btn btn-login float-button-light'>Iniciar</button></div><div class='social-media-section'><div><p>Contáctenos en nuestras redes sociales:</p><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Facebook_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/Twitter_icon.png'> </a><a class='social-hexagon'><img src='https://danielrinconr.github.io/LAB4_ProgWeb/Imgs/G+_icon.png'></a></div><div class='login-bottom-text'><p>¿No tiene una cuenta?</p><p>Contáctenos para solicitar una.</p></div></div></form></div></div></div><!--  END LOGIN --></body></html>");
  else if (request == "GET /main.css HTTP/1.1")
  {
    client.println("fieldset {width:30%;margin-left:auto;margin-right:auto;}input[type='text']{background-color:white;background-image:url(data:image/ico;base64,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);/*background-image:url(trans.ico);*/background-repeat:no-repeat;background-size:contain;text-align:center;}input[type='button']{border-top-right-radius:10px;border:none;float:left;font-size:16px;}");
  }
  else if (request == "GET /trans.ico HTTP/1.1")
  {
    client.println("data:image/ico;base64,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");
  }
  else if (request == "GET /scripts.js HTTP/1.1")
  {
    client.println("window.setInterval(leer,800);function check(id,btn){var xhttp =new XMLHttpRequest();xhttp.onreadystatechange =function (){};const msg ='l'+id;xhttp.open('POST',msg,true);xhttp.send();if (btn.style.backgroundColor =='red'||btn.style.backgroundColor =='green'||btn.style.backgroundColor =='blue'){btn.style.backgroundColor ='rgb(240,240,240)';return;}var color ='';switch (id){case 1:color ='red';break;case 2:color ='green';break;case 3:color ='blue';break;default:break;}btn.style.backgroundColor =color;}function leer(){var xhr =new XMLHttpRequest();xhr.open('GET','/server',true);xhr.responseType ='text';xhr.onload =function (){if (xhr.readyState ===xhr.DONE){if (xhr.status ===200){var lect =document.getElementsByName('inpSens');lect[0].value =xhr.responseText;}}};xhr.send(null);}");
  }
  else if (request == "GET /server HTTP/1.1")
  {
    int analogValue = analogRead(A0);
    float millivolts = (analogValue / 1024.0) * 3300; //3300 is the voltage provided by NodeMCU
    float celsius = millivolts / 10;
    client.println(celsius);
  }
  else if (request == "POST /l1 HTTP/1.1")
    digitalWrite(red, !digitalRead(red));
  else if (request == "POST /l2 HTTP/1.1")
    digitalWrite(green, !digitalRead(green));
  else if (request == "POST /l3 HTTP/1.1")
    digitalWrite(blue, !digitalRead(blue));


  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
