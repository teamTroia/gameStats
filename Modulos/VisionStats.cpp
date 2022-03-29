#include "include/VisionStats.h"

VisionStats::VisionStats(VisionClient *visionClient){
    this->visionClient = visionClient;

    game_on = false;
    setQtdeRobots(3);

    for (int i = 0; i < 4; i ++){
        dataVision[i] = 0;
    }
}

void VisionStats::setQtdeRobots(int qtde){
    qtdeRobots = qtde;

    if (qtdeRobots == 3){
        tamCampo = Point2f(1700, 1300);
    }
    else{
        tamCampo = Point2f(2500, 1800);
    }
}

infoPack VisionStats::vision(fira_message::Frame objects){
    infoPack visionPack;

    qtdeRobots = objects.robots_blue_size();

    fira_message::Ball ball;
    fira_message::Robot robotBlue[5];
    fira_message::Robot robotYellow[5];

    ball = objects.ball();
    visionPack.ball.position = Point2f(ball.x() * 1000 + tamCampo.x / 2, ball.y() * 1000 + tamCampo.y / 2);

    for(int i = 0; i < qtdeRobots; i++){
        robotBlue[i] = objects.robots_blue(i);
        robotYellow[i] = objects.robots_yellow(i);                   

        visionPack.blueRobots[i].position = Point2f(robotBlue[i].x() * 1000 + tamCampo.x / 2, robotBlue[i].y() * 1000 + tamCampo.y / 2);
        visionPack.blueRobots[i].psi = to180range(robotBlue[i].orientation());

        visionPack.yellowRobots[i].position = Point2f(robotYellow[i].x() * 1000 + tamCampo.x / 2, robotYellow[i].y() * 1000 + tamCampo.y / 2);
        visionPack.yellowRobots[i].psi = to180range(robotYellow[i].orientation());
    }

    return visionPack;
}

void VisionStats::checkPossession(infoPack visionPack){
    double minDistAzul = dist(visionPack.blueRobots[0].position, visionPack.ball.position);
    double minDistAmarelo = dist(visionPack.yellowRobots[0].position, visionPack.ball.position);

    for (int i = 1; i < qtdeRobots; i++){
        double distAzul = dist(visionPack.blueRobots[i].position, visionPack.ball.position);
        double distAmarelo = dist(visionPack.yellowRobots[i].position, visionPack.ball.position);

        if (distAzul < minDistAzul){
            minDistAzul = distAzul;
        }
        if (distAmarelo < minDistAmarelo){
            minDistAmarelo = distAmarelo;
        }
    }

    if (minDistAzul < 300 or minDistAmarelo < 300){
        if (minDistAzul < minDistAmarelo){   // Posse azul
            tempoAzul += (1.0 / 60.0) * 1000.0;
        } else {    // Posse amarelo
            tempoAmarelo += (1.0 / 60.0) * 1000.0;
        }
    }

    dataVision[PosseAzul] = 100.0 * tempoAzul / (tempoAzul + tempoAmarelo);
    dataVision[PosseAmarelo] = 100.0 * tempoAmarelo / (tempoAzul + tempoAmarelo);
}

void VisionStats::checkLadoCampo(infoPack visionPack){
    if (visionPack.ball.position.x < tamCampo.x / 2){
        tempoEsquerdo += (1.0 / 60.0) * 1000.0;
    } else {
        tempoDireito += (1.0 / 60.0) * 1000.0;
    }

    dataVision[ladoEsquerdo] = 100.0 * tempoEsquerdo / (tempoDireito + tempoEsquerdo);
    dataVision[ladoDireito] = 100.0 * tempoDireito / (tempoDireito + tempoEsquerdo);
}

void VisionStats::checkVision(bool game_on){
    this->game_on = game_on;

    fira_message::sim_to_ref::Environment packet =  visionClient->getLastEnvironment();
    if(packet.has_frame()){
        infoPack visionPack = vision(packet.frame());

        if (game_on){
            checkPossession(visionPack);
            checkLadoCampo(visionPack);
        }
    }
}

int VisionStats::getDataVision(int data){
    return dataVision[data];
}