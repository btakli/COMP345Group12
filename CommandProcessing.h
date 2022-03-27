//To prevent mutiple inclusion:
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include "GameEngine.h"
#include <string>
#include <list>

class GameEngine;
//Command class:
class Command
{
    public:
    Command();
    ~Command();
    Command(std::string command);
    void saveEffect(string nextState);
    std::string getCommandName();
    std::string getEffect();

    //copy constructor:
    Command(const Command &c);
    //assignment operator:
    Command& operator = (const Command& c);

    private:
    std::string* _command;
    std::string* _effect;
};

//CommandProcessor:
/*
 * The CommandProcessor class.
 * This is the Target class. 
*/
class CommandProcessor
{
    public:
    CommandProcessor();
    virtual ~CommandProcessor();
    std::list<Command>* getCommand();
    bool validate(GameEngine* myGame, Command* command);

    protected:
    virtual void readCommand();
    void saveCommand();
    std::string* command_in;
    std::list<Command>* commands_ptr;
};

//FileLineReader
/*
 * The FileLineReader class.
 * This is the Adaptee class.
*/
class FileLineReader
{
    public:
    FileLineReader();
    FileLineReader(std::string path);
    ~FileLineReader();
    std::string readLineFromFile();
    std::string getPath();

    private:
    std::string* _path;
};

//FileCommandProcessorAdapter:
/*
 * The FileCommandProcessorAdaptor class.
 * This is the adapter class.
 * It adapts a CommandProcessor to a FileLineReader. 
 * Its interface is CommandProcessor.
*/
class FileCommandProcessorAdapter : public CommandProcessor
{
    public:
    FileCommandProcessorAdapter();
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(std::string pathIn);

    protected:
    void readCommand();
    FileLineReader* flr;
    std::string* _pathIn;
};



#endif