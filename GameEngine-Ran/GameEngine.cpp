#include "GameEngine.h"
#include <iostream>
using namespace std;

//************GameState****************
GameState::~GameState(){} //destructor

//*********************friends with ostream:*********************************

ostream& operator<<(ostream& os, const Start& s){
    return cout << "valid command for Start: "<< endl << "1." << *s._command << endl;
}
ostream& operator<<(ostream& os, const MapLoaded& m){
    return cout << "valid command for Map Loaded: " << endl << "1." << *m._command1 << endl << "2." << *m._command2 << endl;
}
ostream& operator<<(ostream& os, const MapValidated& mv){
    return cout << "valid command for Map Validated: "<< endl << "1." << *mv._command << endl;
}
ostream& operator<<(ostream& os, const PlayersAdded& p){
    return cout << "valid command for Players Added: " << endl << "1." << *p._command1 << endl << "2." << *p._command2 << endl;
}
ostream& operator<<(ostream& os, const AssignedReinforcement& a){
    return cout << "valid command for Assigned Reinforcement: "<< endl << "1." << *a._command << endl;
}
ostream& operator<<(ostream& os, const IssueOrders& i){
    return cout << "valid command for Issue Orders: "<< endl << "1." << *i._command1 << endl << "2." << *i._command2 << endl;
}
ostream& operator<<(ostream& os, const ExcecuteOrders& e){
    return cout << "valid command for Execute Orders: "<< endl << "1." << *e._command1 << endl << "2." << *e._command2<< endl<< "3."<< *e._command3 << endl;
}
ostream& operator<<(ostream& os, const Win& w){
    return cout << "valid command for Win: "<< endl << "1." << *w._command1 << endl << "2." << *w._command2 << endl;
}

ostream& operator<<(ostream& os, const GameEngine& g){
    if(g._continue){
        return cout << "The game is still running" << endl;
    }else{
        return cout << "Game Over" << endl;
    }
}
/**********************************************************************
********************Start/Initial State:*******************************
***********************************************************************/
Start::Start(){
     _command = new string("loadmap");
}

Start::~Start(){
    delete _command;
}

void Start::transition(GameEngine* GameEngine, string input){  
    if(input == *_command){
        GameState* newState = new MapLoaded();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Loading Map..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }  
    
}

Start::Start(const Start& other){
    this->_command = new string(*(other._command));
}
Start& Start::operator = (const Start& e){
    this->_command = new string(*(e._command));
    return *this;
}

GameState* Start::clone() const{
    return new Start(*this);
}

void Start::toString(){
     cout << "We are in the Start State now.";
}

void Start::commandMessage(){
    Start s;
    cout << s;
}

/**********************************************************************
********************MapLoaded State:***********************************
***********************************************************************/
MapLoaded::MapLoaded(){
    _command1 = new string("loadmap");
    _command2 = new string("validatemap");
}

MapLoaded::~MapLoaded(){
    delete _command1;
    delete _command2;
}

void MapLoaded::transition(GameEngine* GameEngine, string input){
    if(input == *_command1){
        cout << "Loading Map..." << endl;
    }else if(input == *_command2){
        GameState* newState = new MapValidated();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Map Validated!!" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;;
    }
    
}

MapLoaded::MapLoaded(const MapLoaded& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
}
MapLoaded& MapLoaded::operator = (const MapLoaded& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    return *this;
}

GameState* MapLoaded::clone() const{
    return new MapLoaded(*this);
}

void MapLoaded::toString(){
    cout << "We are in the MapLoaded State";
}

void MapLoaded::commandMessage(){
    MapLoaded m;
    cout << m;
}

/**********************************************************************
********************MapValidated State:********************************
***********************************************************************/
MapValidated::MapValidated(){
    _command = new string("addplayer");
}

MapValidated::~MapValidated(){
    delete _command;
}

void MapValidated::transition(GameEngine* GameEngine, string input){
    if(input == *_command){
        GameState* newState = new PlayersAdded();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Adding Players..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

MapValidated::MapValidated(const MapValidated& other){
    this->_command = new string(*(other._command));
}
MapValidated& MapValidated::operator = (const MapValidated& e){
    this->_command = new string(*(e._command));
    return *this;
}

GameState* MapValidated::clone() const{
    return new MapValidated(*this);
}

void MapValidated::toString(){
    cout << "We are in the MapValidated State";
}
void MapValidated::commandMessage(){
    MapValidated mv;
    cout << mv;
}

/**********************************************************************
********************PlayersAdded State:********************************
***********************************************************************/
PlayersAdded::PlayersAdded(){
    _command1 = new string("addplayer");
    _command2 = new string("assigncountries");
}

PlayersAdded::~PlayersAdded(){
    delete _command1;
    delete _command2;
}

void PlayersAdded::transition(GameEngine* GameEngine, string input){
    if(input == *_command1){
        cout << "Adding Players..." << endl;
    }else if(input == *_command2){
        GameState* newState = new AssignedReinforcement();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Assigning countries..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

PlayersAdded::PlayersAdded(const PlayersAdded& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
}
PlayersAdded& PlayersAdded::operator = (const PlayersAdded& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    return *this;
}

GameState* PlayersAdded::clone() const{
    return new PlayersAdded(*this);
}

void PlayersAdded::toString(){
    cout << "We are in the Players Added State.";
}

void PlayersAdded::commandMessage(){
    PlayersAdded p;
    cout << p;
}
/**********************************************************************
****************AssignedReinforcement State:***************************
***********************************************************************/
AssignedReinforcement::AssignedReinforcement(){
    _command = new string("issueorder");
}

AssignedReinforcement::~AssignedReinforcement(){
    delete _command;
}

void AssignedReinforcement::transition(GameEngine* GameEngine, string input){
    if(input == *_command){
        GameState* newState = new IssueOrders();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Issuing orders..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

AssignedReinforcement::AssignedReinforcement(const AssignedReinforcement& other){
    this->_command = new string(*(other._command));
}
AssignedReinforcement& AssignedReinforcement::operator = (const AssignedReinforcement& e){
    this->_command = new string(*(e._command));
    return *this;
};

GameState* AssignedReinforcement::clone() const{
    return new AssignedReinforcement(*this);
}

void AssignedReinforcement::toString(){
    cout << "We are in the Assigned Reinforcement State";
}

void AssignedReinforcement::commandMessage(){
    AssignedReinforcement a;
    cout << a;
}
/**********************************************************************
******************Issue Orders State:**********************************
***********************************************************************/
IssueOrders::IssueOrders(){
    _command1 = new string("issueorder");
    _command2 = new string("endissueorders");
}

IssueOrders::~IssueOrders(){
    delete _command1;
    delete _command2;
}

void IssueOrders::transition(GameEngine* GameEngine, string input){
    if(input == *_command1){
        cout << "Issuing orders..." << endl;
    }else if(input == "endissueorders"){
        GameState* newState = new ExcecuteOrders();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState);
        cout << "Orders Issued!!" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

IssueOrders::IssueOrders(const IssueOrders& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
}
IssueOrders& IssueOrders::operator = (const IssueOrders& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    return *this;
}

GameState* IssueOrders::clone() const{
    return new IssueOrders(*this);
}

void IssueOrders::toString(){
    cout << "We are in the Issue Orders State";
}

void IssueOrders::commandMessage(){
    IssueOrders i;
    cout << i;
}
/**********************************************************************
******************Execute Orders State:********************************
***********************************************************************/
ExcecuteOrders::ExcecuteOrders(){
    _command1 = new string("execorder");
    _command2 = new string("endexecorders");
    _command3 = new string("win");
}

ExcecuteOrders::~ExcecuteOrders(){
    delete _command1;
    delete _command2;
    delete _command3;
}

void ExcecuteOrders::transition(GameEngine* GameEngine, string input){
    if(input == *_command1){
        cout << "Executing orders..." << endl;
    }else if(input == *_command2){
        GameState* newState_assign = new AssignedReinforcement();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState_assign);
        cout << "Orders executed!!" << endl;
    }else if(input == *_command3){
        GameState* newState_win = new Win();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState_win);
        cout << "CONGRATES!! You won the game!!" << endl;
    }
    else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

ExcecuteOrders::ExcecuteOrders(const ExcecuteOrders& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
    this->_command3 = new string(*(other._command3));
}

ExcecuteOrders& ExcecuteOrders::operator = (const ExcecuteOrders& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    this->_command3 = new string(*(e._command3));
    return *this;
}

GameState* ExcecuteOrders::clone() const{
    return new ExcecuteOrders(*this);
}

void ExcecuteOrders::toString(){
    cout << "We are in the Execute Orders State";
}

void ExcecuteOrders::commandMessage(){
    ExcecuteOrders e;
    cout << e;
}
/**********************************************************************
*************************Win State:************************************
***********************************************************************/
Win::Win(){
    _command1 = new string("play");
    _command2 = new string("end");
}

Win::~Win(){
    delete _command1;
    delete _command2;
}

void Win::transition(GameEngine* GameEngine, string input){
    if(input == *_command2){
        GameState* newState_end = new End();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState_end);
        std::cout << "**************************" << endl;
        std::cout << "*********Game Ends********" << endl;
        std::cout << "**************************" << endl;
        GameEngine->setStatus(false); //set the _continue to false
    }else if(input == *_command1){
        GameState* newState_start = new Start();
        delete GameEngine->getCurrentState();
        GameEngine->setState(newState_start);
        cout << "**********Game restarted!!**********" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

Win::Win(const Win& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
}
Win& Win::operator = (const Win& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    return *this;
}

GameState* Win::clone() const{
    return new Win(*this);
}

void Win::toString(){
    cout << "We are in the Win State";
}

void Win::commandMessage(){
    Win w;
    cout << w;
}
/**********************************************************************
*************************End State:************************************
***********************************************************************/
End::End(){}

End::~End(){}

void End::transition(GameEngine* GameEngine, string input){
    delete GameEngine->getCurrentState(); //delete the last object to prevent memeory leak
}

End::End(const End& other){};
End& End::operator = (const End& e){return *this; }

GameState* End::clone() const{
    return new End(*this);
}

void End::toString(){
    cout << "We are in the End State.";
}

void End::commandMessage(){
    cout << "NO COMMANDS ACCEPTED ANYMORE!!";
}
/**********************************************************************
*************************GameEngine Class:*****************************
***********************************************************************/
GameEngine::GameEngine(){
    _currentState = new Start(); //All game begin with Start state
    _continue = true;
    std::cout << "**************************" << endl;
    std::cout << "********Game starts*******" << endl;
    std::cout << "**************************" << endl;
}

GameEngine::~GameEngine(){
    delete _currentState;
}

GameState* GameEngine::getCurrentState() const{
    return _currentState;
}

void GameEngine::setStatus(bool b){
     _continue = b;
}

bool GameEngine::getStatus(){
    return _continue;
}

//function setState receives a pointer to the current state
//and assign the new state to the current state
void GameEngine::setState(GameState* newState){
    _currentState = newState; //change state now
}

//function transit receives a string (the user input)
//then triggers the transition() funtion of the current state
void GameEngine::transit(string input){
    _currentState->transition(this, input); //transit to next state
}

//Copy Constructor of GameEngine:
GameEngine::GameEngine(const GameEngine& other){
    //called the virtual function clone to perform deep copy:
    this->_currentState = other._currentState->clone(); 
    this->setStatus(other._continue);
}

GameEngine& GameEngine::operator = (const GameEngine& e){
    this->_currentState = e._currentState->clone();
    this->setStatus(e._continue);
    return *this;
}

