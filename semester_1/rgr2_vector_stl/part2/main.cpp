#include "time_utility.h"
#include "train.h"
#include <windows.h>

#include <iostream>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    }
    catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);
    std::cout << '\n';

    std::cout << "t2: ";
    PrintTime(t2);
    std::cout << '\n';

    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';

    
    std::string inputFile = "trains.txt";
    std::vector<Train> Poezda;
    try
    {
        readTrainFile(Poezda, inputFile);
    }
    catch (const char* er)
    {
        std::cerr << er << '\n';
    }

    std::cout << "\nTimetable:\n";
    for (int i = 0; i < Poezda.size(); ++i)
    {
        Poezda[i].myTrain();
        std::cout << '\n';
    }
    std::cout << "\n";

    sortByDispTime(Poezda);
    std::cout << '\n';

    displayTrainInfo_timeInterval(Poezda, "03:00", "10:00");
    displayTrainInfo_timeInterval(Poezda, "18:00", "23:59");
    std::cout << '\n';

    displayTrainInfo_destination(Poezda, "MOSCOW");
    displayTrainInfo_destination(Poezda, "LUNINETS");
    displayTrainInfo_destination(Poezda, "WARSAW");
    std::cout << '\n';

    displayTrainInfo_destination_type(Poezda, "SUBWAY", TrainType::HIGH_SPEED);
    displayTrainInfo_destination_type(Poezda, "LUNINETS", TrainType::FREIGHT);
    displayTrainInfo_destination_type(Poezda, "KHABAROVSK", TrainType::HIGH_SPEED);
    std::cout << '\n';

    displayFastestTrainInfo_destination(Poezda, "MOSCOW");
    displayFastestTrainInfo_destination(Poezda, "LUNINETS");
    displayFastestTrainInfo_destination(Poezda, "WARSAW");
    std::cout << '\n';


    return EXIT_SUCCESS;
}
