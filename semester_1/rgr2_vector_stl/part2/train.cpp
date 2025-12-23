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
	int a = stoi(s);
	std::string reS = std::to_string(a);
	int dif = size(s) - size(reS);
	std::string xreS;
	for (int i = 0; i < dif; ++i)
		xreS += '0';
	xreS += reS;
	if (xreS != s && reS != s)
		return false;
	return true;
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

Train::Train() {};
void readTrainFile(std::vector<Train>& v, const std::string& fileName)
{
	std::string info;
	std::string part;
	std::string partT;
	size_t beg, begT;
	size_t end, endT;
	int hours, minutes;
	Train tr;
	std::ifstream in;
	in.open(fileName);
	if (!in.is_open())
	{
		throw "Input file error";
	}

	while (!in.eof())
	{
		getline(in, info);

		beg = 0;
		end = info.find_first_of(' ');
		strTest(beg, end);

		part = info.substr(beg, end - beg);
		if (!isInt(part))
			throw "Inappropriate TrainID";
		if (stoi(part) > 999999)
			throw "Inappropriate TrainID: limits exceeding";
		tr.id_ = stoi(part);
		beg = end+1;
		end= info.find_first_of(' ', beg);
		strTest(beg, end);


		part = info.substr(beg, end - beg);
		tr.type_=strTrainType(part);
		beg = ++end;
		end = info.find_first_of(' ', beg);
		strTest(beg, end);


		part = info.substr(beg, end - beg);
		tr.destination_ = part;
		beg = ++end;
		end = info.find_first_of(',', beg);
		strTest(beg, end);


		part = info.substr(beg, end - beg);
		tr.dispatch_time_ = timeToNumber(part);
		beg = end + 2;      //Т.к не ' ', a ", "
		end = size(info);
		strTest(beg, end);


		part = info.substr(beg, end - beg);
		tr.travelling_time_ = intervalToNumber(part);
		v.push_back(tr);
	}
	in.close();
}
void Train::myTrain()
{
	std::string ID;
	int dif = 6 - size(std::to_string(id_));
	for (int i = 0; i < dif; ++i)
		ID+='0';
	ID += std::to_string(id_);
	std::cout << ID << ' ' << std::setw(12) << type_ << ' ' << std::setw(15) << destination_ << "   ";
	PrintTime(dispatch_time_);
	int timeMinute = travelling_time_/60;
	int hours = timeMinute / 60;
	int minutes = timeMinute % 60;
	std::string stH = std::to_string(hours), stM = std::to_string(minutes);
	if (hours < 10)
		stH = '0' + stH;
	if (minutes < 10)
		stM = '0' + stM;

	std::cout << ",  " << stH << ':' << stM;

}
void sortByDispTime(std::vector<Train>& v)
{
	std::cout << "Every train sorted by its dispatch time:\n";
	int size = v.size();
	for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - i - 1; ++j)
			if (v[j].dispatch_time_ > v[j+1].dispatch_time_)
				std::swap(v[j], v[j + 1]);
	for (int i = 0; i < size; ++i)
	{
		v[i].myTrain();
		std::cout << '\n';
	}
}
void displayTrainInfo_timeInterval(std::vector<Train>& v, std::string beginning, std::string ending)
{
	std::time_t timeBeg = timeToNumber(beginning), timeEnd = timeToNumber(ending);
	std::cout << "The trains between " << beginning << " and " << ending << " dispatch time:\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].dispatch_time_ >= timeBeg && v[i].dispatch_time_ <= timeEnd)
		{
			v[i].myTrain();
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void displayTrainInfo_destination(std::vector<Train>& v, std::string dest)
{
	std::cout << "The trains to " << dest << ":\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].destination_ == dest)
		{
			v[i].myTrain();
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void displayTrainInfo_destination_type(std::vector<Train>& v, std::string dest, TrainType type)
{
	std::cout << "The "<< type <<" trains to " << dest << ":\n";
	int size = v.size();
	bool thereIs = false;
	for (int i = 0; i < size; ++i)
		if (v[i].destination_ == dest && v[i].type_ == type)
		{
			v[i].myTrain();
			std::cout << '\n';
			thereIs = true;
		}
	if (!thereIs)
		std::cout << "No such trains\n";
}
void displayFastestTrainInfo_destination(std::vector<Train>& v, std::string dest)
{
	std::cout << "The fastest train to " << dest << ":\n";
	int size = v.size();
	std::time_t minTravTime;
	int index = size;
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
		if (v[i].destination_ == dest)
			if (v[i].travelling_time_ < minTravTime)
			{
				minTravTime = v[i].travelling_time_;
				index = i;
			}

	if (thereIs)
	{
		v[index].myTrain();
		std::cout << '\n';
	}
	else
		std::cout << "No such trains\n";
}
