#include "GameEngine.h"
#include <iostream>
#include <random>
#include <set>


using std::vector;
using std::shuffle;
using std::begin;
using std::end; 
#define LOADMAP "loadmap"
#define VALIDATE_MAP "validatemap"
#define ADD_PLAYER "addplayer"
#define GAME_START "gamestart"
#define ISSUE_ORDER "issueorder"

#define ASSIGN_COUNTRIES "assigncountries"
#define GAME_START "gamestart"

#define LOG(str)  std::cout << "\n>> " << str << std::endl;
#define INPUT() std::cout << "> " << std::endl;

//************GameState****************
GameState::~GameState(){} //destructor


Territory* territory_picker(Player& player) {
    int count = 0;
    cout << "Please choose a territory to deploy troops to: " << endl;
    for (Territory* t : player.get_territories()) {
        cout << "\n" << to_string(count) << ": " << t->get_name() << "[" << t->get_stationed_army() << "]";
        count++;
    }
    cout << "> ";

    int option;

    do {
        INPUT()
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            option = -1;
        }

        if (option > count - 1 || option < 0)
            cout << "Please enter a number between 0 and " << count - 1 << endl;

    } while (option > count - 1 || option < 0);


    return player.get_territories()[option];
}

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
ostream& operator<<(ostream& os, const ExecuteOrders& e){
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
     _command = new string(LOADMAP);
}

Start::~Start(){
    delete _command;
}



void Start::transition(GameEngine* engine, string input){

    if(input == *_command){
        engine->map_picker();
        engine->change_state(new MapLoaded());
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

bool Start::validate(string command){
    if(command == *_command){
        return true;
    }
    return false;
}

string Start::getName(){
    return "Start";
}

/**********************************************************************
********************MapLoaded State:***********************************
***********************************************************************/
MapLoaded::MapLoaded(){
    _command1 = new string(LOADMAP);
    _command2 = new string(VALIDATE_MAP);
}

MapLoaded::~MapLoaded(){
    delete _command1;
    delete _command2;
}

void MapLoaded::transition(GameEngine* engine, string input){

    if(input == *_command1){ // Load a new map
        
        engine->map_picker();

    }else if(input == *_command2){ // Validate Map

        engine->validateMap();
            
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

bool MapLoaded::validate(string command){
    if(command == *_command1 || command == *_command2){
        return true;
    }
        return false;
}

string MapLoaded::getName(){
    return "MapLoaded";
}
/**********************************************************************
********************MapValidated State:********************************
***********************************************************************/
MapValidated::MapValidated(){
    _command = new string(ADD_PLAYER);
}

MapValidated::~MapValidated(){
    delete _command;
}

void MapValidated::transition(GameEngine* engine, string input){

    if(input == *_command){

        engine->add_new_player();

        engine->change_state(new PlayersAdded());

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

bool MapValidated::validate(string command){
    if(command == *_command){
        return true;
    }
    return false;
}

string MapValidated::getName(){
    return "MapValidated";
}

/**********************************************************************
********************PlayersAdded State:********************************
***********************************************************************/
PlayersAdded::PlayersAdded(){
    _command1 = new string(ADD_PLAYER);
    _command2 = new string(ASSIGN_COUNTRIES);
    _commandGame = new string (GAME_START);
}

PlayersAdded::~PlayersAdded(){
    delete _command1;
    delete _command2;
    delete _commandGame;
}

void PlayersAdded::transition(GameEngine* engine, string input){


    if(input == *_command1){

        engine->add_new_player();


    }else if(input == *_command2 || input == *_commandGame){

        int player_size = engine->get_players().size();

        if (player_size < 2) {
            std::cout << "ERROR: Need at least 2 players to play." << endl;
        }
        else if (player_size > 6) {
            std::cout << "ERROR: Max 6 players. Currently at " << player_size << " players." << endl;
        }
        else {

            engine->change_state(new AssignedReinforcement());
            
            engine->assign_territories();
            engine->order_of_play();
            engine->give_initial_armies();
            engine->draw_initial_cards();
            engine->popConqBool();

            engine->getCurrentState() ->transition(engine, "");

        }
    }else{
        std::cout << "ERROR: Please enter a valid command." << endl;
    }
}

PlayersAdded::PlayersAdded(const PlayersAdded& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
    this->_commandGame = new string(*(other._commandGame));
}
PlayersAdded& PlayersAdded::operator = (const PlayersAdded& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    this->_commandGame = new string(*(e._commandGame));
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

bool PlayersAdded::validate(string command){
    if(command == *_command1 || command == *_commandGame){
        return true;
    }
        return false;
}

string PlayersAdded::getName(){
    return "PlayersAdded";
}
/**********************************************************************
****************AssignedReinforcement State:***************************
***********************************************************************/
AssignedReinforcement::AssignedReinforcement(){
    _command = new string(ISSUE_ORDER);
}

AssignedReinforcement::~AssignedReinforcement(){
    delete _command;
}

void AssignedReinforcement::transition(GameEngine* engine, string input){

    LOG("Deploy Phase - New Round");

    //Displays the current cars each player have
    for (Player* player : engine->get_players()) {
        cout << *player->getName() << " card info: \n " << *player->getHand() << endl;
    }

    //if(input == *_command){

        // Add new reinforcements
        engine->addReinforcementsPhase(); 
        engine->deployReinforcementPhase();

        engine->change_state(new IssueOrders());
        engine->getCurrentState() ->transition(engine, "");
        

    //}else{
       // std::cout << "ERROR: Please enter a valid command." << endl;
    //}
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

bool AssignedReinforcement::validate(string command){
    if (command == *_command) return true;
    return false;
}

string AssignedReinforcement::getName(){
    return "Assignedreinforcement";
}
/**********************************************************************
****************Play :***************************
***********************************************************************/

/**********************************************************************
****************Reinforcement State:***************************
***********************************************************************/
//ReinforcementPhase::ReinforcementPhase() {
//    _command1 = new string(REINFORCEMENT_PHASE)
//}

/**********************************************************************
******************Issue Orders State:**********************************
***********************************************************************/
IssueOrders::IssueOrders(){
    _command1 = new string(ISSUE_ORDER);
    _command2 = new string("issueordersend");
}

IssueOrders::~IssueOrders(){
    delete _command1;
    delete _command2;
}

void IssueOrders::transition(GameEngine* engine, string input){

    //if(input == *_command1){ // TODO: Never called 

    //}else if(input == *_command2){
        engine->change_state(new ExecuteOrders());
        engine->getCurrentState()->transition(engine, "");

    //}else{
     //   std::cout << "ERROR: Please enter a valid command." << endl;
   // }
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

bool IssueOrders::validate(string command){
    if (command == *_command1 || command == *_command2) return true;
        
    return false;
}
string IssueOrders::getName(){
    return "IssueOrders";
}
/**********************************************************************
******************Execute Orders State:********************************
***********************************************************************/
ExecuteOrders::ExecuteOrders(){
    _command1 = new string("execorder");
    _command2 = new string("endexecorders");
    _command3 = new string("win");
}

ExecuteOrders::~ExecuteOrders(){
    delete _command1;
    delete _command2;
    delete _command3;
}

void ExecuteOrders::transition(GameEngine* engine, string input){

    if (engine->checkWin(*engine)) {
        engine->change_state(new Win());
        engine->getCurrentState()->transition(engine, "");

        cout << "Going to Win state" << endl;
    }
    else{
        //get currentTunrsLeftInt points to the same address as the property max_turns
        
        cout << "current turn left:" << *engine->getCommandProcessor()->getMaxTurns() <<endl;
        int currentTunrsLeftInt = std::stoi(*engine->getCommandProcessor()->getMaxTurns());
        if(currentTunrsLeftInt == 0){
            cout << "Reached the maximum number of turns" <<endl;
            cout << endl;
            cout << "Exiting the game with a Draw..." << endl;
            cout << endl;
            engine->change_state(new Win());
            //engine->getCurrentState()->transition(engine, "");

        }else{
            engine->excecuteOrdersPhase();
            engine->change_state(new AssignedReinforcement());

             // modify the turn number by decreasing by 1 after each turn
            currentTunrsLeftInt -= 1;
            //assign it back to the max_turn value
            engine->getCommandProcessor()->getMaxTurns()->assign(std::to_string(currentTunrsLeftInt));
            cout << "current turn left AFTER EXECUTION:" << *engine->getCommandProcessor()->getMaxTurns() <<endl;

            engine->getCurrentState()->transition(engine, "");
        
           
        } 
    }


 //   if(input == *_command1){

        

    //}
    //    else if(input == *_command2){
        

       
    //}else if(input == *_command3){
    //    engine->change_state(new Win());

    //    cout << "CONGRATES!! You won the game!!" << endl;
    //}
    //else{
    //    std::cout << "ERROR: Please enter a valid command." << endl;
    //}
}

ExecuteOrders::ExecuteOrders(const ExecuteOrders& other){
    this->_command1 = new string(*(other._command1));
    this->_command2 = new string(*(other._command2));
    this->_command3 = new string(*(other._command3));
}

ExecuteOrders& ExecuteOrders::operator = (const ExecuteOrders& e){
    this->_command1 = new string(*(e._command1));
    this->_command2 = new string(*(e._command2));
    this->_command3 = new string(*(e._command3));
    return *this;
}

GameState* ExecuteOrders::clone() const{
    return new ExecuteOrders(*this);
}

void ExecuteOrders::toString(){
    cout << "We are in the Execute Orders State";
}

void ExecuteOrders::commandMessage(){
    ExecuteOrders e;
    cout << e;
}

bool ExecuteOrders::validate(string command){
    if (command == *_command1 || command == *_command2 || command == *_command3) {
        return true;
    }
    return false;
}

string ExecuteOrders::getName(){
    return "ExcecuteOrders";
}
/**********************************************************************
*************************Win State:************************************
***********************************************************************/
Win::Win(){
    _command1 = new string("replay");
    _command2 = new string("quit");
}

Win::~Win(){
    delete _command1;
    delete _command2;
}

void Win::transition(GameEngine* engine, string input){

    if(input == *_command2){
        engine->change_state(new End());
        cout << endl;
        std::cout << "**************************" << endl;
        std::cout << "*********Game Ends********" << endl;
        std::cout << "**************************" << endl;
        cout << endl;
        engine->setStatus(false); //set the _continue to false
        engine->fileReader = false;
    }else if(input == *_command1){
        engine->change_state(new Start());
        cout << endl;
        cout << "************************************" << endl;
        cout << "**********Game restarted!!**********" << endl;
        cout << "************************************" << endl;
        cout << endl;
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

bool Win::validate(string command){
    if(command == *_command1 || command == *_command2){
        return true;
    }
    return false;
}

string Win::getName(){
    return "Win";
}
/**********************************************************************
*************************End State:************************************
***********************************************************************/
End::End(){}

End::~End(){}

void End::transition(GameEngine* engine, string input){

    delete engine->getCurrentState(); //delete the last object to prevent memeory leak
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

bool End::validate(string command){
    return false;
}
string End::getName(){
    return "End";
}
/**********************************************************************
*************************GameEngine Class:*****************************
***********************************************************************/
GameEngine::GameEngine(){

    _orders = new queue<Order*>();
    _players_ptr = new std::vector<Player*>();
    _currentState = new Start(); //All game begin with Start state
    _continue = true;
    fileReader = false;
    _armyPool = new std::vector<int*>();
    _deck = new Deck();
    _conqBool = new vector<bool*>();
    _myProcessor = new CommandProcessor();
    std::cout << "**************************" << endl;
    std::cout << "********Game starts*******" << endl;
    std::cout << "**************************" << endl;

    //logger:
    // special case for Start state:
    ILoggable::_currentState->assign("Start");

    // By implementing the CommandProcessor and FileCommandAdaptor, when a
    //game is initialized (or STARTED) it will ask for commands from the 
    //command processor using the getCommand() funcction
    //--> In this case, command processor has all the command for this game
    //--> Later, Game engine would validate the command everytime before transit
    //    to next state using the validate() function provided by the Commandprocessor
    string input_option;
    bool pass = true;
    do{
        cout << endl;
        cout << "How would you like to input commands?" << endl;
        cout << "Please choose from the following:" << endl;
        cout << "1. -console" << endl;
        cout << "2. -file <filename>" <<endl;
        getline(cin, input_option);
        string option_prefix = input_option.substr(0, 5);
        if(input_option == "-console"){
            pass = true;
            fileReader = false;
            _myProcessor = new CommandProcessor();
        }else if(option_prefix == "-file"){
            pass = true;
            fileReader = true;
            size_t pos = input_option.find(" ");
            string pathIn = input_option.substr(pos+1);
            _myProcessor = new FileCommandProcessorAdapter(pathIn);
    }else{
        cout << "Please enter a correct option." << endl;
        pass = false;
    }
    }
    while(!pass);
    //After the type of commandprocessor is known
    //Get the commands from the command processor:
    _myProcessor->getCommand();
    
}

GameEngine::~GameEngine(){
    delete _currentState;
    delete _myProcessor;
    for (Player* p : *_players_ptr) delete p;
    for (int* i : *_armyPool) delete i;
    for (bool* b : *_conqBool) delete b;
    delete _deck;
}

std::string GameEngine::stringToLog(){
    return "Game Engine new state: " + *ILoggable::_currentState;
}

std::vector<Player*>& GameEngine::get_players() {
    return *_players_ptr;
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


Deck * GameEngine::getDeck() {
    return _deck;
}

vector<int*>& GameEngine::get_ArmyPools()
{
    return *_armyPool;
}

int* GameEngine::get_ArmyPoolAt(int index) {
    return (*_armyPool)[index];
}

CommandProcessor* GameEngine::getCommandProcessor(){
    return _myProcessor;
}

//function setState receives a pointer to the current state
//and assign the new state to the current state
void GameEngine::setState(GameState* newState){
    _currentState = newState; //change state now
}

//function transit receives a string (the user input)
//then triggers the transition() funtion of the current state
void GameEngine::transit(string input){
    // print out the Start State:
    if(this->getCurrentState()->getName() == "Start"){
        notify(this);
    }
    _currentState->transition(this, input); //transit to next state
    ILoggable::_currentState->assign(this->getCurrentState()->getName());
    notify(this);
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


// MapDriver
void GameEngine::map_picker() {

#define BERLIN "berlin"
#define CANADA "canada"
#define COW "cow"
#define ESTONIA "estonia"
#define FORTERESS "fortress"
#define INVALID1 "invalid1"
#define INVALID2 "invalid2"
#define INVALID3 "invalid3"
#define TINY "tiny"

#define UPPERLIMIT 8

    Map::get_instance()->unload();

    for (Command c : *(this->getCommandProcessor())->getCommandList()) {

        size_t space = c.getCommandName().find(" ") + 1;
        string map = c.getCommandName().substr(space);

        if (this->getCommandProcessor()->tournament_mode) {
            cout << "Tournament mode" << endl;
                 if (map == "1") MapLoader::get_instance()->load_map(BERLIN);
            else if (map == "2") MapLoader::get_instance()->load_map(CANADA);
            else if (map == "3") MapLoader::get_instance()->load_map(COW);
            else if (map == "4") MapLoader::get_instance()->load_map(ESTONIA);
            else if (map == "5") MapLoader::get_instance()->load_map(FORTERESS);
            else if (map == "6") MapLoader::get_instance()->load_map(INVALID1);
            else if (map == "7") MapLoader::get_instance()->load_map(INVALID2);
            else if (map == "8") MapLoader::get_instance()->load_map(INVALID3);
            else if (map == "9") MapLoader::get_instance()->load_map(TINY);
        }
        else { // Normal mode
            cout << "Normal mode" << endl;

                 if (map == BERLIN) MapLoader::get_instance()->load_map(BERLIN);
            else if (map == CANADA) MapLoader::get_instance()->load_map(CANADA);
            else if (map == COW) MapLoader::get_instance()->load_map(COW);
            else if (map == ESTONIA) MapLoader::get_instance()->load_map(ESTONIA);
            else if (map == FORTERESS) MapLoader::get_instance()->load_map(FORTERESS);
            else if (map == INVALID1)MapLoader::get_instance()->load_map(INVALID1);
            else if (map == INVALID2)MapLoader::get_instance()->load_map(INVALID2);
            else if (map == INVALID3)MapLoader::get_instance()->load_map(INVALID3);
            else if (map == TINY)MapLoader::get_instance()->load_map(TINY);
        }
    }
}

// Add a new player
void GameEngine::add_new_player() {

    list<Command>* commands = this->getCommandProcessor()->getCommandList();

    int aggressiveIndex = 0;
    int benevolentIndex = 0;
    int neutralIndex = 0;
    int cheaterIndex = 0;

    for (Command c : *commands) {
         
        size_t pos1 = (c.getCommandName()).find(" ");
        size_t pos2 = 0;
        int length = pos1 - pos2;
        string commandprefix = (c.getCommandName()).substr(0, length);

        if (commandprefix == "addplayer") {
            size_t space = c.getCommandName().find(" ") + 1;
            string playerName = c.getCommandName().substr(space);
            if (!already.contains(playerName)) {
                already.insert(playerName);

                if (this->getCommandProcessor()->tournament_mode) {
                    if (playerName == "1")this->get_players().push_back(new Player("Aggressive" + to_string(++aggressiveIndex), this->getDeck(), (LogObserver*)this->getObservers().at(0), new AggressivePlayerStrategy()));
                    else if (playerName == "2")this->get_players().push_back(new Player("Benevolent" + to_string(++benevolentIndex), this->getDeck(), (LogObserver*)this->getObservers().at(0), new BenevolentPlayerStrategy()));
                    else if (playerName == "3")this->get_players().push_back(new Player("Neutral" + to_string(++neutralIndex), this->getDeck(), (LogObserver*)this->getObservers().at(0), new NeutralPlayerStrategy()));
                    else if (playerName == "4")this->get_players().push_back(new Player("Cheater" + to_string(++cheaterIndex), this->getDeck(), (LogObserver*)this->getObservers().at(0), new CheaterPlayerStrategy()));
                    else cout << "ERROR: Unkown behavior" << endl;
                }
                else { // Normal Mode
                    this->get_players().push_back(new Player(playerName, this->getDeck(), (LogObserver*)this->getObservers().at(0)));
                }
                std::cout << "Current player count: " << this->get_players().size();

            }
        }
    }
}

// Assign territory to players
void GameEngine::assign_territories() {
    cout << "DEBUG: Assign Territories" << endl; // DEBUG LINE

    Map* map = Map::get_instance();
    
    int territories_count = map->get_territories().size();
    int territories_per_player = territories_count / this->get_players().size();
    int num; // Territories index starts at 1
    Territory* territory;

    for (Player* player : this->get_players()) {

        for (int claimed_count = 0; claimed_count < territories_per_player; claimed_count++) {
            do
            {
                num = rand() % map->get_territories().size() + 1;
                territory = map->get_territory(num);
            } while (territory->get_claimant() != nullptr); // RNG pick territory
            territory->claim(player, false);
            player->get_territories().push_back(territory);
        }
    }

    // DEBUG LINE
    for (Player* player : this->get_players()) {
        cout << *(player->getName()) << " has " << player->get_territories().size() << endl;
    }

    cout << *Map::get_instance(); // DEBUG LINE
}

void GameEngine::order_of_play() {
    auto rng = std::default_random_engine{};
    shuffle(begin(this->get_players()), end(this->get_players()), rng);         
    cout << "The order of play is the following: " << endl;     
    int i = 0; 
    for (Player* player : this->get_players()) {
        cout << ++i << ": \t" << *player->getName() << endl;
    }
}

void GameEngine::give_initial_armies() {
    int size = this->get_players().size();
    int i = 0;
    for (i; i < size; i++) {
        this->get_ArmyPools().push_back(new int(50));
    }
    cout << "The army pool sizes are the following: " << endl;
    int j = 0;

    for (int* i: this->get_ArmyPools()) {
        cout << "Player " << j << " has " << *i << " armies" << endl;
        j++;
    }
}

bool GameEngine::has_army(int i) {
    if (*this->get_ArmyPoolAt(i) == 0)  return false; 
    return true;
}

void GameEngine::draw_initial_cards() {
    
    for (Player* player : this->get_players()) {
        player->getHand()->addCard(this->getDeck()->draw());
        player->getHand()->addCard(this->getDeck()->draw());
        cout << *player->getName() << " card info: \n " << * player->getHand() << endl;
    }
}

void GameEngine::give_card(Player* player) {
    player->getHand()->addCard(this->getDeck()->draw());
}


queue<Order*>& GameEngine::get_orders() {
    return *_orders;
}

// Add new reinforcements
void GameEngine::addReinforcementsPhase() {

    LOG("Reinforcement Phase")

    cout << "After previous army" << endl;
    for (int* army : this->get_ArmyPools()) cout << *army << endl;


    // # Territories / 3 to floor added to army pool 
    for (Player* player : this->get_players()) {
        *(this->get_ArmyPools()[player->getIndex()]) += (int)(player->get_territories().size() / 3);
    }

    // Bonus Army
    for (Continent* c : Map::get_instance()->get_continents()) {
        if (c->get_claimant() != nullptr) {
            *(this->get_ArmyPools()[c->get_claimant()->getIndex()]) += c->get_army_bonus_value(); //current army += bonus
        }
    }

    // 3 min army points per round
    for (int* army : this->get_ArmyPools()) *army += 3; 

    cout << "After new army" << endl;
    for (int* army : this->get_ArmyPools()) cout << *army << endl;
}

void GameEngine::deployReinforcementPhase() {
    for (Player* p : this->get_players()) {
        //This calls the deploy_phase() method of GameEngine internally IF the player is human. Otherwise does it differently.
        p->issueOrder(this, "deploy");
        //deploy_phase(*p);
    }
}

void GameEngine::excecuteOrdersPhase() {

    LOG("Executing Orders")

    set<Player*> done;

    // Requeue round-robin orders
    while (true) {
        for (Player* p : this->get_players()) {

            if (done.contains(p)) continue;

            if (p->getOrdersList()->size() > 0) {

                this->get_orders().push(p->getOrdersList()->get_order_list().front());
                p->getOrdersList()->remove();

                if (p->getOrdersList()->size() < 1) {
                    done.insert(p);
                }
            }
        }

        if (done.size() == get_players().size()) break;

    }

    int size = this->get_orders().size();
    // Execute orders round-robin way
    for (size_t i = 0; i < size; i++) {
        Order* order = this->get_orders().front();
        order->execute();
        cout << "Executing: " << *order << endl;
        this->get_orders().pop();
        delete order;
    }

    cout << "Finished executing orders. " << endl;
}

void GameEngine::startupPhase(Observer* observer) {
    CommandProcessor* processor = getCommandProcessor();
    processor->attach(observer);
    list<Command>* commandList = processor->getCommand(); // get the command of gameengine from its commandprocessor object
    bool valid = false;
    //For all the command it has:
    // validate each of them in current state
    // if it is valide, execute and save the effect
    // else, reject and save "INVALID COMMAND" 
    do {
        for (Command& command : *commandList) {
            command.attach(observer);
            processor->validate(this, &command); // Goes through all states prior to gamestart(game startup state)
            if (getCurrentState()->getName() == "Assignedreinforcement") {
                //when it gets to the play phase, stop reading
                valid = true;
                cout << ">>> STARTUP PHASE ENDED!!" << endl;
                break;
            }
        }

        if (valid) break;

        valid = false;
        commandList->clear();
        if (this->fileReader) {
            cout << "Start up phase failed!!" << endl;
            cout << "please enter a new file name:" << endl;
            string newPath;
            getline(cin, newPath);
            processor->setPath(newPath);
        }
        //get a new command list try to finish the start-up phase:
        commandList = processor->getCommand();
    } while (!valid);
}


bool GameEngine::cardValidator(Player& player, string type) {
    int cardIndex = 0;
    for (Card* c : player.getHand()->getCards()) {
        if (c->getType() == type) {
            player.getHand()->playAndReturnToDeck(cardIndex, this->getDeck());
            LOG(*player.getName() << " has played card " << type);
            return true;
        }
        cardIndex++;
    }
    cout << "Player " << *player.getName() << " does not have " << type << " card" << endl;
    return false;
}



void GameEngine::validateMap() {
    if (Map::get_instance()->exist())
    {
        bool valid = Map::get_instance()->validate();

        cout << "> Map is " << (valid ? "VALID" : "INVALID") << endl;

        if (valid) 
            this->change_state(new MapValidated());
        
    }
    else std::cout << "WARNING: No map loaded." << endl;
}

void GameEngine::deploy_phase(Player& player) {

    

    while (has_army(player.getIndex())) {
        
        std::cout << "Please enter deploy army for player " << *player.getName() << endl;
        cout << "Remaining army to deploy: " << *(*_armyPool)[player.getIndex()] << endl;

        int army_to_deploy;
        std::cin >> army_to_deploy;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else {
            if (army_to_deploy > *(*_armyPool)[player.getIndex()]) {
                cout << "ERROR: Number to big. " << endl;
            }
            else {
                Deploy* deployOrder = new Deploy(&player, territory_picker(player), army_to_deploy);
                deployOrder->attach(this->getObservers().at(0));

                player.getOrdersList()->addOrder(deployOrder);
                *(*_armyPool)[player.getIndex()] -= army_to_deploy;

                if (has_army(player.getIndex()))
                    cout << "You must deploy all your armies before any other order" << endl;
                else {
                    ordersPicker(player);
                }
            }
        }
    }
}


void GameEngine::ordersPicker(Player& player) {

    LOG("Order Picker")

    int option;

    while(true) {
        try {
            do {
                std::cout << "Please enter a number between 1 to 6."
                    "\n 1. Diplomacy"
                    "\n 2. Airlift"
                    "\n 3. Blockade"
                    "\n 4. Bomb"
                    "\n 5. Advance"
                    "\n 6. Finish"
                    "\n> ";

                std::cin >> option;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    option = -1;
                }
            } while (option > UPPERLIMIT || option < 1);
            cout << endl;

            switch (option)
            {
            case 1:
                if (cardValidator(player, "diplomacy")) {
                    player.issueOrder(this, "diplomacy");
                    //diplomacyHelper(player);
                }
                break;

            case 2:
                if (cardValidator(player, "airlift")) {
                    player.issueOrder(this, "airlift");
                    //airliftHelper(player);
                }
                break;

            case 3:
                if (cardValidator(player, "blockade")) {
                    player.issueOrder(this, "blockade");
                    //blockadeHelper(player);
                }
                break;

            case 4:
                if (cardValidator(player, "bomb")) {
                    player.issueOrder(this, "bomb");
                    //bombHelper(player);
                }
                break;

            case 5:
                player.issueOrder(this, "advance");
                //advanceHelper(player);
                break;
            }
        }
        catch (std::runtime_error e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }

        if (option == 6) break;

        cin.ignore();
    }
}

void GameEngine::ordersPicker_Bot(Player& player, int option) {

    switch (option)
    {
    case 1:
        cardValidator(player, "diplomacy");
        break;

    case 2:
        cardValidator(player, "airlift");
        break;

    case 3:
        cardValidator(player, "blockade");
        break;

    case 4:
        cardValidator(player, "bomb");
        break;

    case 5:
        player.issueOrder(this, "advance");
        //advanceHelper(player);
        break;
    }
}


bool GameEngine::checkWin(GameEngine& engine) {
    string temp;

    Player* tempP = (Map::get_instance()->get_territories()[0])->get_claimant();
    for (auto ter : Map::get_instance()->get_territories()) {
        
        if (ter->get_claimant() == nullptr) {
            return false;
        }
        if (!(ter->get_claimant() == tempP)) {
            return false;
        }
    }
    return true;
}

void GameEngine::popConqBool() {

    for (int i = 0; i < get_players().size(); i++) {
        this->getConq().push_back(new bool(false));
    }
}

vector<bool*>& GameEngine::getConq() {
    return *_conqBool;
}

void GameEngine::setConq(int i) {
    *(this->getConq()[i]) = true;
}


void GameEngine::resetAllConq() {
    for (auto tracker : getConq()) {
        *tracker = false;
    }
}

void GameEngine::change_state(GameState* newState) {
    delete this->getCurrentState();
    this->setState(newState);
}
