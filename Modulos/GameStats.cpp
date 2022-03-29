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

void GameStats::loop(){
    Timer timer;
    float freq = 60.0;
    bool game_on = false;

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

        for (int i = 0; i < 8; i++){
            std::cout << refereeStats->getDataReferee(i) << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 4; i++){
            std::cout << visionStats->getDataVision(i) << " ";
        }
        std::cout << std::endl;

        // Stop timer
        timer.stop();

        // Sleep for remainingTime
        long remainingTime = (1000 / freq) - timer.getMiliSeconds();
        std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
    }
}