
var hero = [];

var missiles = [];

var missilesEnemies = [];

var opio=1;

var enemies = [
    { left: 200, top: 100 },
    { left: 300, top: 100 },
    { left: 400, top: 100 },
    { left: 500, top: 100 },
    { left: 600, top: 100 },
    { left: 700, top: 100 },
    { left: 800, top: 100 },
    { left: 900, top: 100 },
    { left: 200, top: 175 },
    { left: 300, top: 175 },
    { left: 400, top: 175 },
    { left: 500, top: 175 },
    { left: 600, top: 175 },
    { left: 700, top: 175 },
    { left: 800, top: 175 },
    { left: 900, top: 175 }
];

var identifier=0;

$(document).keydown(function(e) {
  if(hero.length!=0){
    if (e.keyCode === 37) {
        // Left
        for(var i = 0 ; i < hero.length ; i++ )
        {
          if(hero[i].left>10){
              hero[i].left = hero[i].left - 10;
              writeOnMessage("heroe",hero[i].iden.toString(),"mover izquierda");
            }
        }
      }
    if (e.keyCode === 39) {
        // Left
        for(var i = 0 ; i < hero.length ; i++ ){
          if(hero[i].left<1150){
            hero[i].left = hero[i].left + 10;
            writeOnMessage("heroe",hero[i].iden.toString(),"mover derecha");
          }
        }
    }
    if (e.keyCode === 32) {
        // Spacebar (fire)
        for(var i = 0 ; i < hero.length ; i++ ){
          missiles.push({
              left: hero[i].left + 20,
              top: hero[i].top - 20
          });
        writeOnMessage("heroe",hero[i].iden.toString(),"disparo");
        }
        drawMissiles()
        }
    drawHero();
    }
});


function drawHero() {

    $('#hero')[0].innerHTML = "";
    for(var i = 0 ; i < hero.length ; i++ ) {
        document.getElementById('hero').innerHTML += `<div class='ally' style='left:${hero[i].left}px; top:${hero[i].top}px'></div>`;
    }

}

function drawMissiles() {
    $('#missiles')[0].innerHTML = ""
    for(var i = 0 ; i < missiles.length ; i++ ) {
        document.getElementById('missiles').innerHTML += `<div class='missile1' style='left:${missiles[i].left}px; top:${missiles[i].top}px'></div>`;
    }
  }

function moveMissiles() {
  if(missiles.length!=0)
  {
    for(var i = 0 ; i < missiles.length ; i++ ) {
        missiles[i].top = missiles[i].top - 8
    }
  }
}

function drawEnemies() {
    $('#enemies')[0].innerHTML = "";
    for(var i = 0 ; i < enemies.length ; i++ ) {
        $('#enemies')[0].innerHTML += `<div class='enemy' style='left:${enemies[i].left}px; top:${enemies[i].top}px'></div>`;
    }
}

function moveEnemies() {
  if(enemies.length!=0)
  {
    if(enemies[0].left < 10 && opio==0)
    {
      opio = 1;
    }
    if (enemies[0].left>400 && opio==1)
    {
      opio = 0;
    }

    for(var i = 0 ; i < enemies.length ; i++ )
    {
      if(opio == 1)
        {
          enemies[i].left = enemies[i].left + 10;
          writeOnMessage("enemigos",i.toString(),"mover derecha");
        }
      if(opio == 0)
        {
          enemies[i].left = enemies[i].left - 10;
          writeOnMessage("enemigos",i.toString(),"mover izquierda");
        }
    }
  }
}

function collisionDetection() {
    for (var missile = 0; missile < missiles.length; missile++) {
        for (var enemy = 0; enemy < enemies.length; enemy++){
            if (
                missiles[missile].left >= enemies[enemy].left  &&
                missiles[missile].left <= (enemies[enemy].left + 50)  &&
                missiles[missile].top <= (enemies[enemy].top + 50)  &&
                missiles[missile].top >= enemies[enemy].top
            ) {
                enemies.splice(enemy, 1);
                missiles.splice(missile, 1);
            }

        }
        if (missiles[missile].top <= 10) {
          missiles.splice(missile, 1);
        }
    }
}

function collisionDetectionEnemie() {
    for (var missile = 0; missile < missilesEnemies.length; missile++) {
        for (var ally = 0; ally < hero.length; ally++){
            if (
                missilesEnemies[missile].left >= hero[ally].left  &&
                missilesEnemies[missile].left <= (hero[ally].left + 50)  &&
                missilesEnemies[missile].top <= (hero[ally].top + 50)  &&
                missilesEnemies[missile].top >= hero[ally].top
            ) {
                hero.splice(ally, 1);
                missilesEnemies.splice(missile, 1);
            }
        }
        if (missilesEnemies[missile].top >= 700) {
          missilesEnemies.splice(missile, 1);
        }
    }
}

function enemyRandomShot(){
  for(var i = 0 ; i < enemies.length ; i++ ){
    var number = 1 + Math.floor(Math.random() * 100);
    if(number<2){
      missilesEnemies.push({
          left: enemies[i].left + 20,
          top: enemies[i].top + 20
      });
      writeOnMessage("enemigos",i,"disparo");
    }
  }
}

function drawMissilesEnemies() {
  if(missilesEnemies.length!=0)
  {
    $('#missilesEnemies')[0].innerHTML = ""
    for(var i = 0 ; i < missilesEnemies.length ; i++ ) {
        $('#missilesEnemies')[0].innerHTML += `<div class='missile2' style='left:${missilesEnemies[i].left}px; top:${missilesEnemies[i].top}px'></div>`;
    }
  }
}

function moveMissilesEnemies() {
  if(missilesEnemies.length!=0)
  {
    for(var i = 0 ; i < missilesEnemies.length ; i++ ) {
        missilesEnemies[i].top = missilesEnemies[i].top + 8
    }
  }
}

function anadir(){
  hero.push({
      left: 500,
      top: 700,
      iden: identifier
  });
}

function gameLoop() {
    drawHero();
    setTimeout(gameLoop, 100)
    moveMissiles();
    moveMissilesEnemies();
    drawMissiles();
    drawMissilesEnemies();
    moveEnemies();
    enemyRandomShot();
    drawEnemies();
    collisionDetection();
    collisionDetectionEnemie();
    victory();
}

function victory() {
  if(enemies.length==0){
    $("[name=resultado]")[0].textContent="victory";
    $("[name=resultado]")[0].removeAttribute("hidden");
  }
}

function writeOnMessage(entidad,numero,accion)
{
  $('#eventos')[0].innerHTML += entidad+" "+numero+" "+accion+"\n";
  $('#eventos').scrollTop($('#eventos')[0].scrollHeight);
}


$( document ).ready(function() {
    console.log( "ready!" );
    gameLoop();
});
