#include "train.h"
void strTest(int beg, int end)
{
	if (end == std::string::npos)
		throw "Bad file arrangement";
	if ((end - beg) <= 1)
		throw "Bad file arrangement";
}
TrainType strTrainType(std::string str)
{//PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
	if (str == "PASSENGER")
		return TrainType::PASSENGER;
	else if (str == "FREIGHT")
		return TrainType::FREIGHT;
	else if (str == "HIGH_SPEED")
		return TrainType::HIGH_SPEED;
	else if (str == "SUBWAY")
		return TrainType::SUBWAY;
	else if (str == "SPECIALIZED")
		return TrainType::SPECIALIZED;
	else throw "Inappropriate Train type";
}
std::ostream& operator<<(std::ostream& out, TrainType type)
{
	if (type == TrainType::PASSENGER)
		out << "Passenger";
	else if (type == TrainType::FREIGHT)
		out << "Freight";
	else if (type == TrainType::HIGH_SPEED)
		out << "High_speed";
	else if (type == TrainType::SUBWAY)
		out << "Subway";
	else if (type == TrainType::SPECIALIZED)
		out << "Specialized";

	return out;
}
bool isDigit(const std::string& s)
{
	if (s[0] >= '0' && s[0] <= '9')
		return true;
	return false;
}
bool isInt(const std::string& s)
{
	if (s.size() > 9)
		return 0;
	if (s == "00")
		return true;
	int a = stoi(s);
	std::string reS = std::to_string(a);
	if (reS != s)
		return false;
	return true;
}

Train::Train() {};
void Train::readTrainFile(std::vector<Train>& v, const std::string& fileName)
{
	std::ifstream in;
	in.open(fileName);
	if (!in)
	{
		throw "Input file error";
	}
	std::string info;
	std::string part;
	std::string partT;
	size_t beg, begT;
	size_t end, endT;
	int hours, minutes;
	Train tr;
	while (!in.eof())
	{
		getline(in, info);
		try
		{
			beg = 0;
			end = info.find_first_of(' ');
			strTest(beg, end);

			part = info.substr(beg, end - beg);
			if (!isInt(part))
				throw "Inappropriate TrainID";
			if (stoi(part) > 999999)
				throw "Inappropriate TrainID: limits exceeding";
			tr.id_ = stoi(part);
			beg = ++end;
			end= info.find_first_of(beg, ' ');
			strTest(beg, end);


			part = info.substr(beg, end - beg);
			tr.type_=strTrainType(part);
			beg = ++end;
			end = info.find_first_of(beg, ' ');
			strTest(beg, end);


			part = info.substr(beg, end - beg);
			tr.destination_ = part;
			beg = ++end;
			end = info.find_first_of(beg, ' ');
			strTest(beg, end);


			part = info.substr(beg, end - beg);
			endT= info.find_first_of(beg, ':');
			strTest(beg, end);
			partT= info.substr(beg, endT - beg);
			if (!isInt(partT))
				throw "Inappropriate dispatch hours";
			hours = stoi(partT);
			if (hours > MAX_HOUR_NUMBER_PER_DAY)
				throw "Inappropriate dispatch hours";

			begT = ++endT;
			strTest(beg, end);
			partT = info.substr(begT, end - begT);
			if (!isInt(partT))
				throw "Inappropriate dispatch minutes";
			minutes = stoi(partT);
			if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
				throw "Inappropriate dispatch minutes";

			tr.dispatch_time_ = SetTime(hours, minutes);
			beg = endT + 2;      //Т.к не ' ', a ", "
			end = size(info) - 1;
			strTest(beg, end);


			part = info.substr(beg, end - beg);
			endT = info.find_first_of(beg, ':');
			strTest(beg, end);
			partT = info.substr(beg, endT - beg);
			if (!isInt(partT))
				throw "Inappropriate dispatch hours";
			hours = stoi(partT);

			begT = ++endT;
			strTest(beg, end);
			partT = info.substr(begT, end - begT);
			if (!isInt(partT))
				throw "Inappropriate dispatch minutes";
			minutes = stoi(partT);
			if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
				throw "Inappropriate dispatch minutes";

			tr.travelling_time_ = (hours * 60 + minutes) * 60;
		}
		catch (const char* c)
		{
			std::cerr << c << '\n';
		}
	}
	in.close();
}
std::time_t timeToNumber(std::string time)
{
	if (size(time) > 5)
		throw "Inappropriate interval entry";

	int hours, minutes;
	std::string tmp;
	tmp = time.substr(0, 2);
	if (!isInt(tmp))
		throw "Inappropriate dispatch hours";
	hours = stoi(tmp);
	if (hours > MAX_HOUR_NUMBER_PER_DAY)
		throw "Inappropriate dispatch hours";

	tmp = time.substr(3, 2);
	if (!isInt(tmp))
		throw "Inappropriate dispatch minutes";
	minutes = stoi(tmp);
	if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
		throw "Inappropriate dispatch minutes";

	return SetTime(hours, minutes);
}
std::time_t intervalToNumber(std::string interval)
{
	int hours, minutes;
	int colon;
	std::string tmp;
	colon = interval.find_first_of(':');
	tmp = interval.substr(0, colon);
	if (!isInt(tmp))
		throw "Inappropriate dispatch hours";
	hours = stoi(tmp);

	tmp = interval.substr(colon + 1);
	if (!isInt(tmp))
		throw "Inappropriate dispatch minutes";
	minutes = stoi(tmp);
	if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
		throw "Inappropriate dispatch minutes";

	return (hours * 60 + minutes) * 60;
}
void Train::myTrain(const Train& tr)
{
	std::cout << tr.id_ << ' ' << tr.type_ << ' ' << tr.destination_ << ' ';
	PrintTime(tr.dispatch_time_);
	int timeMinute = tr.travelling_time_/60;
	int hours = timeMinute / 60;
	int minutes = timeMinute % 60;
	std::cout << ", " << hours << ':' << minutes;
}
void Train::sortByDispTime(std::vector<Train>& v)
{
	std::cout << "Every train sorted by its dispatch time:\n";
	int size = v.size();
	for (int i = 0; i < size - 1; ++i)
		for (int j = i + 1; j < size - 1; ++j)
			if (v[i].dispatch_time_ < v[i + 1].dispatch_time_)
				std::swap(v[i], v[i + 1]);
	for (int i = 0; i < size - 1; ++i)
	{
		myTrain(v[i]);
		std::cout << '\n';
	}
}
void Train::displayTrainInfo_timeInterval(std::vector<Train>& v, std::string beginning, std::string ending)
{
	std::time_t timeBeg = timeToNumber(beginning), timeEnd = timeToNumber(ending);
	std::cout << "The trains between " << beginning << " and " << ending << ":\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].dispatch_time_ >= timeBeg && v[i].dispatch_time_ <= timeEnd)
		{
			myTrain(v[i]);
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void Train::displayTrainInfo_destination(std::vector<Train>& v, std::string dest)
{
	std::cout << "The trains to " << dest << ":\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].destination_ == dest)
		{
			myTrain(v[i]);
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void Train::displayTrainInfo_destination_type(std::vector<Train>& v, std::string dest, TrainType type)
{
	std::cout << "The "<< type <<" trains to " << dest << ":\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].destination_ == dest && v[i].type_ == type)
		{
			myTrain(v[i]);
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void Train::displayFastestTrainInfo_destination(std::vector<Train>& v, std::string dest)
{
	std::cout << "The fastest train to " << dest << ":\n";
	int size = v.size();
	std::time_t minTravTime;
	int index = 0;
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
	{
		if (v[i].destination_ == dest)
		{
			thereIs = true;
		}
		if (thereIs)
		{
			minTravTime = v[i].travelling_time_;
			index = i;
			break;
		}
	}
	for (int i = index + 1; i < size; ++i)
		if (v[i].travelling_time_<minTravTime)
		{
			minTravTime = v[i].travelling_time_;
			index = i;
		}

	if (thereIs)
		myTrain(v[index]);
	else
		std::cout << "No such trains\n";
}