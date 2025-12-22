#pragma once

#include <string>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    //ID would be 1 to 999999
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train();
    void readTrainFile(std::vector<Train>& v, const std::string& fileName);
    void sortByDispTime(std::vector<Train>& v);
    void displayTrainInfo_timeInterval(std::vector<Train>& v, std::string beginning_, std::string ending_);
    void displayTrainInfo_destination(std::vector<Train>& v, std::string destination_);
    void displayTrainInfo_destination_type(std::vector<Train>& v, std::string destination_, TrainType type_);
    void displayFastestTrainInfo_destination(std::vector<Train>& v, std::string destination_);
    void myTrain(const Train& tr);
};
