#pragma once
#include <string>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
using std::ofstream;

//Abstract class inherited by all classes that can be the subject of the logging mechanism
class ILoggable {
public:
	//Creates and returns a string to be outputted to the log file
	virtual ~ILoggable();
	//Creates and returns a string to be output to the log file
	virtual string stringToLog() = 0;
	friend std::ostream& operator<<(std::ostream& strm, const ILoggable& loggable);
private:
protected:
	//Constructor, protected.
	ILoggable();
	//Protected state string, update this string to reflect the current state so that stringToLog() can return it (along with some formatting).
	string* _currentState;
};

class Observer {
public:
	virtual ~Observer();
	//Update method, used to update Observers
	virtual void update(ILoggable* obj) = 0;
protected:
	Observer();

};

//Writes the game logs (using stringToLog() and Update()) to the log file (gamelog.txt by default).
class LogObserver : public Observer {
public:
	//Constructor
	LogObserver();
	//Constructor with ability to pass in a custom file name for log file
	LogObserver(string filename);
	//Copy Constructor
	LogObserver(const LogObserver& other);
	//Destructor
	virtual ~LogObserver();

	//Update method, used to update LogObserver
	void update(ILoggable* obj);

	//Assignment Operator overload
	LogObserver& operator=(const LogObserver& rhs);

	//Stream Insertion Operator overload
	friend std::ostream& operator<<(std::ostream& strm, const LogObserver& logObserver);
private:
	//Name of the log file
	string* _filename;
	//Output stream
	ofstream* _stream;
	//Print the start of the log message and timestamp of game start
	void printGameStartTime();
};

//Subject class, inherited by all Subject classes who wish to notify observers (the LogObserver).
class Subject {
public:
	//Constructor
	Subject();
	//Copy Constructor
	Subject(const Subject& other);
	//Assignment operator
	Subject& operator=(const Subject& rhs);
	//Destructor (does not destroy Observers, just the list)
	virtual ~Subject();
	//Add an Observer to the list of Observers
	virtual void attach(Observer* o);
	//Remove an Observer from the list of Observers
	virtual void detach(Observer* o);
	//Remove all Observers from the list of Observers
	virtual void detachAll();
	///<summary>Notifies all attached Observers, calling their update() method.</summary>
	///<param name='ILoggable* thisObj'>pass in 'this' as a Subject in order for your stringToLog() method to be called properly (notify(this);)</param>
	virtual void notify(ILoggable* thisObj);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& strm, const Subject& subject);
	//returns a list of attached observers.
	virtual vector<Observer*> getObservers();
private:
	//List of Observers
	vector<Observer*>* _observers;

};

