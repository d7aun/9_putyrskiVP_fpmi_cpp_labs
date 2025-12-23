#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "time_utility.h"
#include <iomanip>

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
    friend void readTrainFile(std::vector<Train>& v, const std::string& fileName);
    friend void sortByDispTime(std::vector<Train>& v);
    friend void displayTrainInfo_timeInterval(std::vector<Train>& v, std::string beginning_, std::string ending_);
    friend void displayTrainInfo_destination(std::vector<Train>& v, std::string destination_);
    friend void displayTrainInfo_destination_type(std::vector<Train>& v, std::string destination_, TrainType type_);
    friend void displayFastestTrainInfo_destination(std::vector<Train>& v, std::string destination_);
    void myTrain();
};
