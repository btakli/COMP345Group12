//To prevent mutiple inclusion:
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include "Map.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"
#include <set>
#include "PlayerStrategies.h"

using std::cout;
using std::endl;

class CommandProcessor;
//solve dependencies
//Game is defined at the end
class GameEngine; 

//An abstract class:
class GameState 
{
    public:
    //pure virtual function
    //needs to be overridden
    virtual void transition(GameEngine* GameEngine, string command)=0; 
    virtual ~GameState(); //destructor
    virtual bool validate(string command) = 0;
    virtual string getName() = 0;
    //implemented when called to print current state
    //pure virtual function needs to be overridden
    virtual void toString() = 0; 
    //clone() function needed by the copy constructor of GameEngine
    //Reason: GameState is abstract, and _currentState is of type GameState
    //        We cannot create object with GameState, so we need a vritual 
    //        clone() methhod to get a deep copy of each state
    virtual GameState* clone() const = 0;

    virtual void commandMessage() = 0;

};

ostream& operator<<(ostream& os, const GameState& s);
/**********************************************************************
********************Start/Initial State:*******************************
***********************************************************************/
class Start : public GameState {
    
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
    //Constructor
    Start();
    //Destructor
    ~Start();
    bool validate(string command);
    string getName();

    Start(const Start& other); //copy constructor
    Start& operator = (const Start& s); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const Start& s);

    //overridden clone() function
    GameState* clone() const;

    //toString()
    void toString();

    void commandMessage();

    private:
    string* _command;
    
};

/**********************************************************************
********************MapLoaded State:***********************************
***********************************************************************/
class MapLoaded : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
    MapLoaded(); //constructor
    ~MapLoaded(); //destructor
    bool validate(string command);
    string getName();


    MapLoaded(const MapLoaded& other); //deep copy constructor
    MapLoaded& operator = (const MapLoaded& m); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const MapLoaded& m);

    GameState* clone() const; //clone() overridden

    //toString() overriden
    void toString();

    void commandMessage();

    private:
    string* _command1;
    string* _command2;
};

/**********************************************************************
********************MapValidated State:********************************
***********************************************************************/

class MapValidated : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
  
    MapValidated(); //constructor
    ~MapValidated(); //destructor

    bool validate(string command);
    string getName();

    MapValidated(const MapValidated& other); //deep copy constructor
    MapValidated& operator = (const MapValidated& mv); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const MapValidated& mv);

    GameState* clone() const; //clone() overridden

    //toString() overridden
    void toString();

    void commandMessage();

    private:
    string* _command;
};

/**********************************************************************
********************PlayersAdded State:********************************
***********************************************************************/
class PlayersAdded : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
   
    PlayersAdded(); //constructor
    ~PlayersAdded(); //destructor

    bool validate(string command);
    string getName();  

    PlayersAdded(const PlayersAdded& other); //deep copy constructor
    PlayersAdded& operator = (const PlayersAdded& p); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const PlayersAdded& p);

    GameState* clone() const; //clone() overridden

    //toString() overridden:
    void toString();

    void commandMessage();

    private:
    string* _command1;
    string* _command2;
    string* _commandGame;
};

/**********************************************************************
****************AssignedReinforcement State:***************************
***********************************************************************/
class AssignedReinforcement : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
  
    AssignedReinforcement(); //constructor
    ~AssignedReinforcement(); //destructor

    bool validate(string command);
    string getName();

    AssignedReinforcement(const AssignedReinforcement& other); //deep copy constructor
    AssignedReinforcement& operator = (const AssignedReinforcement& a); //assignment operator
    friend ostream& operator<<(ostream& os, const AssignedReinforcement& a);


    GameState* clone() const; //clone() overridden

    //toString() overridden
    void toString();

    void commandMessage();

    private:
    string* _command;
};

/**********************************************************************
******************Issue Orders State:**********************************
***********************************************************************/
class ReinforcementPhase : public GameState {
public:
       /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);

    ReinforcementPhase(); //constructor
    ~ReinforcementPhase(); //destructor

    ReinforcementPhase(const ReinforcementPhase& other); //deep copy constructor
    ReinforcementPhase& operator = (const ReinforcementPhase& i); //assignment operator
        //stream insertion operator:
    friend ostream& operator<<(ostream& os, const ReinforcementPhase& i);
    GameState* clone() const; //clone() overridden
         //toString overridden:
    void toString();
    void commandMessage();

private:
    string* _command1;
    string* _command2;

};
/**********************************************************************
******************Issue Orders State:**********************************
***********************************************************************/
class IssueOrders : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
   
    IssueOrders(); //constructor
    ~IssueOrders(); //destructor

    bool validate(string command);
    string getName();

    IssueOrders(const IssueOrders& other); //deep copy constructor
    IssueOrders& operator = (const IssueOrders& i); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const IssueOrders& i);

   GameState* clone() const; //clone() overridden

    //toString overridden:
    void toString();

    void commandMessage();

    private:
    string* _command1;
    string* _command2;
};

/**********************************************************************
******************Execute Orders State:********************************
***********************************************************************/
class ExecuteOrders : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
    ExecuteOrders(); //constructor
    ~ExecuteOrders(); //destructor

    bool validate(string command);
    string getName();

    ExecuteOrders(const ExecuteOrders& other); //deep copy constructor
    ExecuteOrders& operator = (const ExecuteOrders& e); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const ExecuteOrders& e);

    GameState* clone() const; //clone() overridden

    //toString() overridden
    void toString();

    void commandMessage();

    private:
    string* _command1;
    string* _command2;
    string* _command3;
};

/**********************************************************************
*************************Win State:************************************
***********************************************************************/
class Win : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
    Win(); //constructor
    ~Win(); //destructor

    bool validate(string command);
    string getName();

    Win(const Win& other); //deep copy constructor
    Win& operator = (const Win& w); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const Win& w);

    GameState* clone() const; //clone() overridden

    //toString() overridden
    void toString();

    void commandMessage();

    private:
    string* _command1;
    string* _command2;
};

/**********************************************************************
*************************End State:************************************
***********************************************************************/
class End: public GameState{
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);

    End();
    ~End();

    bool validate(string command);
    string getName();
    
    End(const End& other);
    End& operator = (const End& e);
    GameState* clone() const;
    void toString();
    void commandMessage();
};

/**********************************************************************
*************************GameEngine Class:*****************************
***********************************************************************/
/*Game class would be used to create new object which contains
the current state of the game, and transit between states when 
received a command from the console.*/
class GameEngine : public ILoggable, public Subject{
    //vector pointing to players
    std::vector<Player*>* _players_ptr;
    //vector showing each players army pool. ordered by player index
    vector<int*>* _armyPool;
    //vector to track if a player conquered a territory this round
    vector<bool*>* _conqBool;
    //The deck for the game
    Deck * _deck;
    
    queue<Order*>* _orders;
    queue<string>* _mapQ;

public:
    int* _round;
    // Returns a pointer to the current players in game
    std::vector<Player*>& get_players();
    //Constructor
    GameEngine();
    //Deconstructor
    ~GameEngine();
    //returns pointer of current state
    GameState* getCurrentState() const; 
    //Used for logging
    string stringToLog();
    //transition function according to command inputs
    void transit(string c); 
    //used to set Game object to next stats
    void setState(GameState* newState); 

    //setter is used to set the status to false when we reach the End state
    void setStatus(bool b);
    //getter is used to get the current status of the game
    bool getStatus();
    bool fileReader;
    //returns the _armyPool
    vector<int*>& get_ArmyPools();
    //return amount in army pool at index
    int* get_ArmyPoolAt(int index);
    //returns the _deck
    Deck* getDeck();
    //Copy Constructor and operator:
    GameEngine(const GameEngine& other);
    GameEngine& operator = (const GameEngine& e);
    //get orders
    queue<Order*>& get_orders();
    set<string> already;
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const GameEngine& g);
    //return the command processor:
    CommandProcessor* getCommandProcessor();
    //startup phase
    void startupPhase(Observer* observer);
    //add new player state
    void add_new_player();
    //map picker state
    void map_picker();
    //assign territores state
    void assign_territories();
    //determines order of play
    void order_of_play();
    //give each army pool initial value of 50
    void give_initial_armies();
    //Checks if an interval in army pool of 0 
    bool has_army(int i);
    //draw 2 cards per player
    void draw_initial_cards();
    //Draws a card
    void give_card(Player*);
    //goes to reinforcement phase
    void addReinforcementsPhase();
    //goes to issue order phase
    void deployReinforcementPhase();
    //goes to execute order phase
    void excecuteOrdersPhase();
    //goes to orders picker phase
    void ordersPicker(Player&);
    //pick a card type for a player
    bool cardValidator(Player& player, string type);
    //validate a loaded map
    void validateMap();
    //Checks to see if the territories are all owned by the same player
    bool checkWin(GameEngine& engine);
    //Initializes the _conqBool
    void popConqBool();
    //Get the vector remembering if a player has conquered this round
    vector<bool*>& getConq();
    //Change value to true
    void setConq(int i);
    // Reset all conquered to false
    void resetAllConq();
    // Deploy new troops phase
    void deploy_phase(Player& player);
    // Change a human to a different strategy of player.
    void changePlayerStrategy(Player& player);
    // Changes the game state
    void change_state(GameState*);
    // Read all the maps from command
    void get_all_map_commands();
    // Get the maps read in queue
    queue<string>& get_mapQ();

    /*******************
     ********a3*********
     *******************/
     // Gets winner name
    string* getWinnerName(); 
    // Game game number
    string* getGameNum(); 
    // Get map number
    string* getMapNum(); 
    // set a winner
    void setWinner(string w); 
    // set a game number
    void setGameNum(string g); 
    // set a map number
    void setMapNum(string m); 
   
    // get end game results
    string* getResult(); 
    // the results
    string* result; 
    
    private:
    //current state, used for logging
    GameState* _currentState; 
    bool _continue;
    CommandProcessor* _myProcessor;

    /*******************
     ********a3*********
     *******************/
    string* _winner;
    string* _game_num;
    string* _map_num;

};



#endif