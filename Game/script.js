
var hero = {
    left: 575,
    top: 700
};

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


$(document).keydown(function(e) {
    if (e.keyCode === 37) {
        // Left
        hero.left = hero.left - 10;
    }
    if (e.keyCode === 39) {
        // Right
        hero.left = hero.left + 10;
    }
    if (e.keyCode === 32) {
        // Spacebar (fire)
        missiles.push({
            left: hero.left + 20,
            top: hero.top - 20
        });
        drawMissiles()
    }
    drawHero();
});


function drawHero() {
    document.getElementById('hero').style.left = hero.left + 'px';
    document.getElementById('hero').style.top = hero.top + 'px';
}

function drawMissiles() {
  if(missiles.length!=0)
  {
    document.getElementById('missiles').innerHTML = ""
    for(var i = 0 ; i < missiles.length ; i++ ) {
        document.getElementById('missiles').innerHTML += `<div class='missile1' style='left:${missiles[i].left}px; top:${missiles[i].top}px'></div>`;
    }
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
    document.getElementById('enemies').innerHTML = ""
    for(var i = 0 ; i < enemies.length ; i++ ) {
        document.getElementById('enemies').innerHTML += `<div class='enemy' style='left:${enemies[i].left}px; top:${enemies[i].top}px'></div>`;
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
        }
      if(opio == 0)
        {
          enemies[i].left = enemies[i].left - 10;
        }
    }
  }
}

function collisionDetection() {
    for (var enemy = 0; enemy < enemies.length; enemy++) {
        for (var missile = 0; missile < missiles.length; missile++) {
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
    }
}

function enemyRandomShot()
{
  for(var i = 0 ; i < enemies.length ; i++ )
  {
    var number = 1 + Math.floor(Math.random() * 10);
    if(number<3)
    {
      missiles.push({
          left: enemies[i].left + 20,
          top: enemies[i].top + 20
      });
      drawMissilesEnemies()
    }
  }
}

function drawMissilesEnemies() {
  if(missiles.length!=0)
  {
    document.getElementById('missilesEnemies').innerHTML = ""
    for(var i = 0 ; i < missiles.length ; i++ ) {
        document.getElementById('missilesEnemies').innerHTML += `<div class='missile2' style='left:${missilesEnemies[i].left}px; top:${missilesEnemies[i].top}px'></div>`;
    }
  }
}

function gameLoop() {
    setTimeout(gameLoop, 100)
    moveMissiles();
    drawMissiles();
    moveEnemies();
    drawEnemies();
    collisionDetection();
}

gameLoop()
