#include "include/VisionStats.h"

VisionStats::VisionStats(VisionClient *visionClient){
    this->visionClient = visionClient;

    game_on = false;
    setQtdeRobots(3);

    for (int i = 0; i < 4; i ++){
        dataVision[i] = 0;
    }

    tempoParteCampo = new double*[100];
    for (int i = 0; i < 100; i++){
        tempoParteCampo[i] = new double[100];
        for (int j = 0; j < 100; j++){
            tempoParteCampo[i][j] = 0;
        }
    }

    tempoAzul = 0;
    tempoAmarelo = 0;
    tempoEsquerdo = 0;
    tempoDireito = 0;
    tempoTotal = 0;
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
    visionPack.ball.position = Point2f(ball.x() * 1000 + tamCampo.x / 2, -ball.y() * 1000 + tamCampo.y / 2);

    for(int i = 0; i < qtdeRobots; i++){
        robotBlue[i] = objects.robots_blue(i);
        robotYellow[i] = objects.robots_yellow(i);                   

        visionPack.blueRobots[i].position = Point2f(robotBlue[i].x() * 1000 + tamCampo.x / 2, -robotBlue[i].y() * 1000 + tamCampo.y / 2);
        visionPack.blueRobots[i].psi = to180range(robotBlue[i].orientation());

        visionPack.yellowRobots[i].position = Point2f(robotYellow[i].x() * 1000 + tamCampo.x / 2, -robotYellow[i].y() * 1000 + tamCampo.y / 2);
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

void VisionStats::checkParteCampo(infoPack visionPack){
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if (visionPack.ball.position.x >= (i * tamCampo.x/100) and visionPack.ball.position.x < ((i+1) * tamCampo.x/100) and
                visionPack.ball.position.y >= (j * tamCampo.y/100) and visionPack.ball.position.y < ((j+1) * tamCampo.y/100)){
                    tempoParteCampo[i][j] += (1.0 / 60.0) * 1000.0;
            }
        }
    }

    tempoTotal += (1.0 / 60.0) * 1000.0;
}

cv::Point2f VisionStats::cvt(cv::Point2f pt){
    pt.x = pt.x / (tamCampo.x / 640.0);
    pt.y = pt.y / (tamCampo.y / 480.0);
    return pt;
}

void VisionStats::checkVision(bool game_on){
    this->game_on = game_on;

    fira_message::sim_to_ref::Environment packet =  visionClient->getLastEnvironment();
    if(packet.has_frame()){
        infoPack visionPack = vision(packet.frame());

        if (game_on){
            checkPossession(visionPack);
            checkLadoCampo(visionPack);
            checkParteCampo(visionPack);
        }
    }
}

double VisionStats::getDataVision(int data){
    return dataVision[data];
}

void VisionStats::plotMapaCalor(){
    cv::Mat img = cv::imread("campo.png");
    cv::Mat imgCopy;
    img.copyTo(imgCopy);

    double maiorTempo = 0;
    double naoZerado = 0;

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j ++){
            if (tempoParteCampo[i][j] > maiorTempo) maiorTempo = tempoParteCampo[i][j];
            if (tempoParteCampo[i][j] != 0) naoZerado++;
        }
    }

    double menorTempo = maiorTempo;
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j ++){
            if (tempoParteCampo[i][j] != 0 and tempoParteCampo[i][j] < menorTempo) menorTempo = tempoParteCampo[i][j];
        }
    }

    double mediaTempo = tempoTotal / naoZerado;

    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j ++){
                if (tempoParteCampo[i][j] != 0){
                cv::Point2f pt1 = cv::Point2f(i * tamCampo.x/100, j * tamCampo.y/100);
                cv::Point2f pt2 = cv::Point2f((i+1) * tamCampo.x/100, (j+1) * tamCampo.y/100);
                int green = 255, red = 255;                    
                
                if (tempoParteCampo[i][j] < mediaTempo){
                    red = (tempoParteCampo[i][j] - menorTempo) / (mediaTempo - menorTempo) * 255;
                } else {
                    green = (maiorTempo - tempoParteCampo[i][j]) / (maiorTempo - mediaTempo) * 255;
                }

                cv::Scalar cor = cv::Scalar(0, green, red);
                cv::rectangle(imgCopy, cvt(pt1), cvt(pt2), cor, cv::FILLED);
            }      
        }
    }

    cv::addWeighted(img, 0.6, imgCopy, 0.4, 0.0, img);

    cv::namedWindow("img");
    cv::imshow("img", img);
    cv::waitKey(1);
}