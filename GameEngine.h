//To prevent mutiple inclusion:
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include "Map.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"

using std::cout;
using std::endl;

class CommandProcessor;
//solve dependencies
//Game is defined at the end
class GameEngine; 

//An abstract class:
class GameState : public ILoggable, public Subject
{
    public:
    //pure virtual function
    //needs to be overridden
    void transition(GameEngine* GameEngine, string command); 
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
    string stringToLog();
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
class ExcecuteOrders : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
    ExcecuteOrders(); //constructor
    ~ExcecuteOrders(); //destructor

    bool validate(string command);
    string getName();

    ExcecuteOrders(const ExcecuteOrders& other); //deep copy constructor
    ExcecuteOrders& operator = (const ExcecuteOrders& e); //assignment operator
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const ExcecuteOrders& e);

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

    std::vector<Player*>* _players_ptr;
    vector<int*>* _armyPool;
    Deck * _deck;
    queue<Order*>* _orders;

public:
    
    // Returns a pointer to the current players in game
    std::vector<Player*>& get_players();
    
    GameEngine();
    ~GameEngine();
    GameState* getCurrentState() const; //returns pointer of current state

    string stringToLog();
    void transit(string c); //transition function according to command inputs
    void setState(GameState* newState); //used to set Game object to next stats

    /*void transitCommandProcessor();
    void transitCommandAdaptor();*/
    //setter is used to set the status to false when we reach the End state
    void setStatus(bool b);
    //getter is used to get the current status of the game
    bool getStatus();
    //retunrs the _armyPool
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
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const GameEngine& g);
    //return the command processor:
    CommandProcessor* getCommandProcessor();
    //startup phase
    void startupPhase();


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
    void draw_initial_cards();
    void reinforcementPhase();
    void issueOrdersPhase();
    void excecuteOrdersPhase();
    void ordersPicker(Player&);
    void cardPicker(Player&);
    void cardPicker2(Player& player, string type);
    void validateMap();
   

    private:
    GameState* _currentState; //current state
    bool _continue; 
    CommandProcessor* _myProcessor;
};



#endif