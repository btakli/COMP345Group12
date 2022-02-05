#include "GameEngine.h"
#include <iostream>
using namespace std;

//Start:
Start& Start::getInstance(){
    static Start s;
    return s;
}

void Start::transition(Game* Game, string input){  
    if(input == "loadmap"){
        Game->setState(MapLoaded::getInstance());
        cout << "Loading Map..." << endl;
    }else
        std::cout << "ERROR: Please enter a valid command." << endl;
}


//MapLoaded:
MapLoaded& MapLoaded::getInstance(){
    static MapLoaded m;
    return m;
}

void MapLoaded::transition(Game* Game, string input){
    if(input == "loadmap"){
        Game->setState(MapLoaded::getInstance());
        cout << "Loading Map..." << endl;
    }else if(input == "validatemap"){
        Game->setState(MapValidated::getInstance());
        cout << "Map Validated!!" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;;
    }
    
}

//MapValidated:
MapValidated& MapValidated::getInstance(){
    static MapValidated mv;
    return mv;
}

void MapValidated::transition(Game* Game, string input){
    if(input == "addplayer"){
        Game->setState(PlayersAdded::getInstance());
        cout << "Adding Players..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//PlayersAdded:
PlayersAdded& PlayersAdded::getInstance(){
    static PlayersAdded p;
    return p;
}

void PlayersAdded::transition(Game* Game, string input){
    if(input == "addplayer"){
        Game->setState(PlayersAdded::getInstance()); //same state
        cout << "Adding Players..." << endl;
    }else if(input == "assigncountries"){
        Game->setState(AssignedReinforcement::getInstance());
        cout << "Assigning countries..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//AssignReinforcement:
AssignedReinforcement& AssignedReinforcement::getInstance(){
    static AssignedReinforcement a;
    return a;
}

void AssignedReinforcement::transition(Game* Game, string input){
    if(input == "issueorder"){
        Game->setState(IssueOrders::getInstance()); //same state
        cout << "Issuing orders..." << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//IssueOrders:
IssueOrders& IssueOrders::getInstance(){
    static IssueOrders i;
    return i;
}

void IssueOrders::transition(Game* Game, string input){
    if(input == "issueorder"){
        Game->setState(IssueOrders::getInstance()); //same state
        cout << "Issuing orders..." << endl;
    }else if(input == "endissueorders"){
        Game->setState(ExcecuteOrders::getInstance());
        cout << "Orders Issued!!" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//ExecuteOrders:
ExcecuteOrders& ExcecuteOrders::getInstance(){
    static ExcecuteOrders e;
    return e;
}

void ExcecuteOrders::transition(Game* Game, string input){
    if(input == "execorder"){
        Game->setState(ExcecuteOrders::getInstance()); //same state
        cout << "Executing orders..." << endl;
    }else if(input == "endexecorders"){
        Game->setState(AssignedReinforcement::getInstance());
        cout << "Orders executed!!" << endl;
    }else if(input == "win"){
        Game->setState(Win::getInstance());
        cout << "CONGRATES!! You won the game!!" << endl;
    }
    else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//Win:
Win& Win::getInstance(){
    static Win w;
    return w;
}

void Win::transition(Game* Game, string input){
    if(input == "end"){
        Game->setState(End::getInstance()); //same state
        std::cout << "**************************" << endl;
        std::cout << "*********Game Ends********" << endl;
        std::cout << "**************************" << endl;
        Game->setStatus(false); //set the _continue to false
    }else if(input == "play"){
        Game->setState(Start::getInstance());
        cout << "**********Game restarted!!**********" << endl;
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

//End:
End& End::getInstance(){
    static End e;
    return e;
}

void End::transition(Game* Game, string input){}

// Game class Initialization:
Game::Game(){
    _currentState = &Start::getInstance(); //All game begin with Start state
    _continue = true;
    std::cout << "**************************" << endl;
    std::cout << "********Game starts*******" << endl;
    std::cout << "**************************" << endl;
}

void Game::setState(GameState& newState){
    _currentState = &newState; //change state now
}

void Game::transition(string input){
    _currentState->transition(this, input);
}


/*int main(){
    string command;
    //cout << "hello world";
    Game* myGame;
    myGame = new Game();
    //cout << "hello world again";
    while(myGame->getStatus() == true){
        cout << "Please enter a command:";
        cin >> command;
        myGame->transition(command);
    }    
}*/
