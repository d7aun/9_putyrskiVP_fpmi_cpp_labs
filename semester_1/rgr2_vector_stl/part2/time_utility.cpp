#include "time_utility.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <iomanip>

namespace time_utility {

std::time_t SetTime(size_t hours, size_t minutes)
	{
		if (hours > MAX_HOUR_NUMBER_PER_DAY)
			throw std::out_of_range("Wrong value of hours! (must be from 0 to 23)");

		if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
			throw std::out_of_range("Wrong value of minutes! (must be from 0 to 59)");

		std::time_t now = time(NULL);
		int dayInSec = 60 * 60 * 24;
		now -= (now % dayInSec);
		//now += (hours * 60 + minutes) * 60; - Неверно
		//Т.к время в Беларуси - GMT+3, то мы должны из кол-ва часов вычесть эти самые 3 часика. т.е 3 * 3600сек
		//Это всё из-за локалТайма в выводе))
		now -= 3 * 3600;
		now += (hours * 60 + minutes) * 60;
		return now;
	}

std::time_t GenerateRandomTime(std::mt19937& generator) {
    std::uniform_int_distribution<size_t> hour_randomizer(0, MAX_HOUR_NUMBER_PER_DAY);
    std::uniform_int_distribution<size_t> minute_randomizer(0, MAX_MINUTE_NUMBER_PER_HOUR);

    size_t hours = hour_randomizer(generator);
    size_t minutes = minute_randomizer(generator);

    std::time_t generated_time = SetTime(hours, minutes);
    return generated_time;
}

void PrintTime(const std::time_t& time_to_print)
	{
		char* tmp = std::asctime(std::localtime(&time_to_print));
		int size = sizeof(tmp) / sizeof(char);
		std::string forOut(tmp);
		forOut.pop_back();
		std::cout<< forOut;
	}

}  // namespace time_utility
