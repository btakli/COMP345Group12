#include "LoggingObserver.h"
#include <chrono>
#include <ctime>
#include <iostream>

ILoggable::~ILoggable()
{
	//delete _currentState;
}

ILoggable::ILoggable()
{
	_currentState = new string("ILoggable: State not set");
}

Observer::~Observer()
{
}

Observer::Observer()
{
}

LogObserver::LogObserver(): LogObserver("gamelog.txt")
{

}

LogObserver::LogObserver(string filename)
{

	_filename = new string(filename);
	_stream = new ofstream();
	_stream->open(*_filename);
	printGameStartTime();

	if (!(*_stream)) {
		std::cerr << "An error has occured when trying to open the file " << filename << "... Ensure you have appropriate permissions to use it!" << std::endl;
		std::cerr << "Exiting the program..." << std::endl;
		exit(0);
	}
}

LogObserver::LogObserver(const LogObserver& other)
{
	this->_filename = new string(*(other._filename));
	_stream = new ofstream(*_filename, std::ofstream::out); //Output mode
}

LogObserver::~LogObserver()
{
	delete _filename;
	_stream->close();
	delete _stream;
}

LogObserver& LogObserver::operator=(const LogObserver& rhs)
{
	delete _filename;
	_stream->close();
	delete _stream;

	this->_filename = new string(*rhs._filename);
	this->_stream = new ofstream(*_filename, std::ofstream::out);
	return *this;

}

void LogObserver::printGameStartTime()
{

#ifndef __APPLE__
	//Get time (DOES NOT WORK ON MACS, SO USING PREPROCESSOR DIRECTIVE)
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	char tmBuff[30];
	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
	*_stream << "~~~~ Gamelog for game starting on: " << tmBuff << std::endl;
#else
	//This should work on MacOS
	auto now = std::chrono::system_clock::now();
	std::time_t date = std::chrono::system_clock::to_time_t(now);
	*_stream << "~~~~ Gamelog for game starting on: " << std::ctime(&date) << std::endl;
#endif
}

void LogObserver::update(ILoggable* obj) {
	*_stream << obj->stringToLog() << std::endl; //Write the log to the file.
}

std::ostream& operator<<(std::ostream& strm, const ILoggable& loggable)
{
	strm << "Current state: " << *loggable._currentState;
	return strm;
}

std::ostream& operator<<(std::ostream& strm, const LogObserver& logObserver)
{
	strm << "logObserver writing to file: " << *logObserver._filename << std::endl;;
	string status = (logObserver._stream->is_open()) ? "Open" : "Closed";
	strm << "Status of stream: " << status;
	return strm;
}

std::ostream& operator<<(std::ostream& strm, const Subject& subject)
{
	vector<Observer*>* list = subject._observers;
	strm << "Subject has " << list->size() << " Observers attached, here are their details: " << std::endl;
	for (int i = 0; i < list->size(); i++)
		strm << list->at(i) << std::endl;
	return strm;

}

Subject::Subject()
{
	_observers = new vector<Observer*>();
}

Subject::Subject(const Subject& other)
{
	_observers = new vector<Observer*>();
	vector<Observer*>* otherList = other._observers;

	for (int i = 0; i < otherList->size(); i++)
		_observers->push_back(otherList->at(i));

}

Subject& Subject::operator=(const Subject& rhs)
{
	_observers->clear();
	vector<Observer*>* otherList = rhs._observers;

	for (int i = 0; i < otherList->size(); i++)
		_observers->push_back(otherList->at(i));
	return *this;
}

Subject::~Subject()
{
	//WILL NOT TAKE CARE OF DELETING OBSERVERS! That would be bad
	_observers->clear();
	delete _observers;
}

void Subject::attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::detach(Observer* o)
{
	for (int i = 0; i < _observers->size(); i++)
	{
		if (o == _observers->at(i)) //They point to the same thing
			_observers->erase(_observers->begin() + i); //Remove the Observer from the list
	}

}

void Subject::detachAll()
{
	_observers->clear();
}

void Subject::notify(ILoggable* thisObj)
{
	for (int i = 0; i < _observers->size(); i++) {
		Observer* observer = _observers->at(i);
		observer->update(thisObj);
	}

}
