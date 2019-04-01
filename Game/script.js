var heroes = [
    { left: 500, top: 700, st: 0 },
    { left: 500, top: 700, st: 0 },
    { left: 500, top: 700, st: 0 },
    { left: 500, top: 700, st: 0 },
    { left: 500, top: 700, st: 0 }];

var missiles = [];

var missilesEnemies = [];

var opio = 1;

var limitebalasenemigas = 50;

var sync = true;

/* var identifier = 0; //Dado por el servidor*/

var enemies = [
    { left: 200, top: 100, st: 0 }, { left: 300, top: 100, st: 0 }, { left: 400, top: 100, st: 0 }, { left: 500, top: 100, st: 0 },
    { left: 600, top: 100, st: 0 }, { left: 700, top: 100, st: 0 }, { left: 800, top: 100, st: 0 }, { left: 900, top: 100, st: 0 },
    { left: 200, top: 175, st: 0 }, { left: 300, top: 175, st: 0 }, { left: 400, top: 175, st: 0 }, { left: 500, top: 175, st: 0 },
    { left: 600, top: 175, st: 0 }, { left: 700, top: 175, st: 0 }, { left: 800, top: 175, st: 0 }, { left: 900, top: 175, st: 0 }];

$(document).keyup(function (e) {
    if (heroes.length == 0)
        return;
    switch (e.keyCode) {
        case 37:
            if (heroes[identifier].left > 10) {
                heroes[identifier].left -= 10;
                writeOnMessage('heroes', identifier, 'ml');
            }
            break;
        case 39:
            if (heroes[identifier].left < 1150) {
                heroes[identifier].left += 10;
                writeOnMessage('heroes', identifier, 'mr');
            }
            break;
        case 32:
            missiles.push({
                left: heroes[identifier].left + 20,
                top: heroes[identifier].top - 20
            });
            writeOnMessage('heroes', identifier, 'fr');
            drawMissiles();
            break;
    }
    drawheroes();
});


function drawheroes() {
    $('#heroes')[0].innerHTML = '';
    for (var i = 0; i < 5; i++) {
        if (!heroes[i].st) continue;
        $('#heroes')[0].innerHTML += `<div class='ally' style='left:${heroes[i].left}px; top:${heroes[i].top}px'>${i+1}</div>`;
    }
}

function drawMissiles() {
    $('#missiles')[0].innerHTML = '';
    for (var i = 0; i < missiles.length; i++) {
        $('#missiles')[0].innerHTML += `<div class='missile1' style='left:${missiles[i].left}px; top:${missiles[i].top}px'></div>`;
    }
}

function drawEnemies() {
    $('#enemies')[0].innerHTML = '';
    for (var i = 0; i < enemies.length; i++) {
        if (!enemies[i].st) continue;
        $('#enemies')[0].innerHTML += `<div class='enemy' style='left:${enemies[i].left}px; top:${enemies[i].top}px'></div>`;
    }
}

function drawMissilesEnemies() {
    if (missilesEnemies.length == 0)
        return;
    $('#missilesEnemies')[0].innerHTML = '';
    for (var i = 0; i < missilesEnemies.length; i++) {
        $('#missilesEnemies')[0].innerHTML += `<div class='missile2' style='left:${missilesEnemies[i].left}px; top:${missilesEnemies[i].top}px'></div>`;
    }
}

function moveMissiles() {
    if (missiles.length == 0)
        return;
    for (var i = 0; i < missiles.length; i++) {
        missiles[i].top = missiles[i].top - 8
    }
}

function moveEnemies() {
    if (enemies[0].left < 10 && opio == 0) {
        opio = 1;
    }
    if (enemies[0].left > 400 && opio == 1) {
        opio = 0;
    }

    for (var i = 0; i < enemies.length; i++) {
        if (opio == 1) {
            enemies[i].left = enemies[i].left + 10;
            /*writeOnMessage('enemigos',i.toString(),'mover derecha');*/
        }
        if (opio == 0) {
            enemies[i].left = enemies[i].left - 10;
            /* writeOnMessage('enemigos',i.toString(),'mover izquierda');*/
        }
    }
}

function moveMissilesEnemies() {
    if (missilesEnemies.length == 0)
        return;
    for (var i = 0; i < missilesEnemies.length; i++) {
        missilesEnemies[i].top = missilesEnemies[i].top + 8
    }
}

function collisionDetection() {
    for (var missile = 0; missile < missiles.length; missile++) {
        for (var enemy = 0; enemy < enemies.length; enemy++) {
            if (!enemies[enemy].st) continue;
            if (
                missiles[missile].left >= enemies[enemy].left &&
                missiles[missile].left <= (enemies[enemy].left + 50) &&
                missiles[missile].top <= (enemies[enemy].top + 50) &&
                missiles[missile].top >= enemies[enemy].top
            ) {
                /* enemies.splice(enemy, 1); */
                enemies[enemy].st = 0;
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
        for (var ally = 0; ally < heroes.length; ally++) {
            if (!heroes[ally].st) continue;
            if (
                missilesEnemies[missile].left >= heroes[ally].left &&
                missilesEnemies[missile].left <= (heroes[ally].left + 50) &&
                missilesEnemies[missile].top <= (heroes[ally].top + 50) &&
                missilesEnemies[missile].top >= heroes[ally].top
            ) {
                /* heroes.splice(ally, 1); */
                heroes[ally].st = 0;
                missilesEnemies.splice(missile, 1);
            }
        }
        if (missilesEnemies[missile].top >= 700) {
            missilesEnemies.splice(missile, 1);
        }
    }
}

function enemyRandomShot() {
    if (missilesEnemies.length >= limitebalasenemigas)
        return;
    for (var i = 0; i < enemies.length; i++) {
        if (!enemies[i].st) continue;
        var number = 1 + Math.floor(Math.random() * 100);
        if (number < 2) {
            missilesEnemies.push({
                left: enemies[i].left + 20,
                top: enemies[i].top + 20
            });
            /* writeOnMessage('enemigos', i, 'disparo'); */
        }
    }
}

function anadir() {
    heroes.push({
        left: 500,
        top: 700,
        iden: identifier,
        maxbullets: 50,
        shoot: 1
    });
}

function bullettimeout() {
    for (var ally = 0; ally < heroes.length; ally++) {
        if (heroes[i].shoot == 1) {
            heroes[i].maxbullets--;
        }
        if (heroes[i].maxbullets <= 1) {
            heroes[i].maxbullets = 50;
            heroes[i].shoot == 0;
        }
    }
}

function gameLoop() {
    drawheroes();
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
    Sync();
}

function victory() {
    if (enemies.length == 0) {
        $('[name=resultado]')[0].textContent = 'victory';
        $('[name=resultado]')[0].removeAttribute('hidden');
    }
}

function writeOnMessage(ent, num, act) {
    /* $('#eventos')[0].innerHTML += `${entidad} ${numero} ${accion}\\n`;
    $('#eventos').scrollTop($('#eventos')[0].scrollHeight); */
    var _url = (ent == 'heroes') ? './UsAct' : './MchAct';
    var _act = (act == 'fr') ? -1 : heroes[num].left;
    $.ajax({
        type: 'POST',
        url: _url,
        dataType: 'json',
        contentType: 'application/json',
        data: JSON.stringify({ u: num, mv: _act }),
        success: function (data) {
        },
        failure: function (errMsg) {
            alert(errMsg);
        }
    });

}

/* function Start() {
    $.ajax({
        type: 'POST',
        url: './NewUser',
        success: function (data) {
            console.log(JSON.stringify(data));
            var pSt = data.pSt;
            var pPs = data.pPs;
            for (var i = 0; i < pSt.length; i++) {
                if (pSt[i] == 1) continue;
                heroes[i].st = pSt[i];
            }
        },
        failure: function (errMsg) {
            alert(errMsg);
        }
    });
} */

function Sync() {
    if (!sync) return;
    sync = false;
    $.ajax({
        type: 'POST',
        url: './Sync',
        success: function (data) {
            /* console.log(JSON.stringify(data)); */
            var pSt = data.pSt;
            var pPs = data.pPs;
            for (var i = 0; i < pSt.length; i++) {
                heroes[i].st = pSt[i];
                if (!pSt[i]) continue;
                if (i == identifier) continue;
                heroes[i].left = pPs[i];
            }
            sync = true;
        },

        failure: function (errMsg) {
            alert(errMsg);
        }
    });
}

$(document).ready(function () {
    console.log('ready!');
    setInterval(gameLoop, 100);
});
