#include "include/GameStats.h"

GameStats::GameStats(){
    visionClient = new VisionClient("224.0.0.1", 10002);
    refereeClient = new RefereeClient("224.5.23.2", 10003);

    refereeStats = new RefereeStats(refereeClient);
    visionStats = new VisionStats(visionClient);
}

GameStats::~GameStats(){
    visionClient->close();
    refereeClient->close();
}

std::string GameStats::to_string_with_precision(const float a_value, const int n){
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

void GameStats::plotData(int imgMode){
    cv::Mat dataPainel = cv::Mat::zeros(cv::Size(640,280),CV_8UC3);

    cv::Scalar azul = cv::Scalar(255, 127, 0);
    cv::Scalar amarelo = cv::Scalar(0, 255, 255);
    cv::Scalar branco = cv::Scalar(255, 255, 255);

    cv::putText(dataPainel, "Blue Team", cv::Point(74, 30), 4, 0.5, azul);
    cv::putText(dataPainel, "Yellow Team", cv::Point(469, 30), 4, 0.5, amarelo);
    
    cv::putText(dataPainel, "Posse de Bola", cv::Point(260, 60), 4, 0.5, branco);
    cv::putText(dataPainel, to_string_with_precision(visionStats->getDataVision(PosseAzul)) + "%", cv::Point(100, 60), 4, 0.5, azul);
    cv::putText(dataPainel, to_string_with_precision(visionStats->getDataVision(PosseAmarelo)) + "%", cv::Point(510, 60), 4, 0.5, amarelo);

    cv::putText(dataPainel, "Tempo no Ataque", cv::Point(243, 90), 4, 0.5, branco);
    cv::putText(dataPainel, to_string_with_precision(visionStats->getDataVision(ladoDireito)) + "%", cv::Point(100, 90), 4, 0.5, azul);
    cv::putText(dataPainel, to_string_with_precision(visionStats->getDataVision(ladoEsquerdo)) + "%", cv::Point(510, 90), 4, 0.5, amarelo);

    cv::putText(dataPainel, "Penalty Kicks", cv::Point(260, 120), 4, 0.5, branco);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(PenaltiAzul)), cv::Point(110, 120), 4, 0.5, azul);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(PenaltiAmarelo)), cv::Point(520, 120), 4, 0.5, amarelo);

    cv::putText(dataPainel, "Goal Kicks", cv::Point(272, 150), 4, 0.5, branco);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(GoalkickAzul)), cv::Point(110, 150), 4, 0.5, azul);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(GoalkickAmarelo)), cv::Point(520, 150), 4, 0.5, amarelo);

    cv::putText(dataPainel, "Free Balls", cv::Point(276, 200), 4, 0.5, branco);

    cv::putText(dataPainel, "Quadrant 1", cv::Point(340, 230), 4, 0.5, branco);
    cv::putText(dataPainel, "Quadrant 2", cv::Point(200, 230), 4, 0.5, branco);
    cv::putText(dataPainel, "Quadrant 3", cv::Point(200, 260), 4, 0.5, branco);
    cv::putText(dataPainel, "Quadrant 4", cv::Point(340, 260), 4, 0.5, branco);

    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(FreeballQ1)), cv::Point(460, 230), 4, 0.5, branco);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(FreeballQ2)), cv::Point(170, 230), 4, 0.5, branco);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(FreeballQ3)), cv::Point(170, 260), 4, 0.5, branco);
    cv::putText(dataPainel, std::to_string(refereeStats->getDataReferee(FreeballQ4)), cv::Point(460, 260), 4, 0.5, branco);

    cv::imshow("GameStats", dataPainel);
    cv::waitKey(1);

    visionStats->plotMapaCalor(imgMode);
}

void GameStats::loop(){
    Timer timer;
    float freq = 60.0;
    bool game_on = false;
    int imgMode = 0;

    cv::namedWindow("GameStats");
    cv::namedWindow("GameStatsImage");
    cv::createTrackbar("imgMode", "GameStatsImage", &imgMode, 6);

    while(1) {
        // Start timer
        timer.start();

        // Running vision and referee clients
        visionClient->run();
        refereeClient->run();

        if (refereeClient->getLastFoul() != VSSRef::Foul::GAME_ON){
            game_on = false;
        } else {
            game_on = true;
        }

        refereeStats->checkReferee();
        visionStats->checkVision(game_on);
        plotData(imgMode);

        // Stop timer
        timer.stop();

        // Sleep for remainingTime
        long remainingTime = (1000 / freq) - timer.getMiliSeconds();
        std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
    }
}