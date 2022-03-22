//To prevent mutiple inclusion:
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include "Map.h"

using std::vector;

using std::cout;
using std::endl;

//solve dependencies
//Game is defined at the end
class GameEngine; 

//An abstract class:
class GameState
{
    public:
    //pure virtual function
    //needs to be overridden
    virtual void transition(GameEngine* GameEngine, string command) = 0; 
    virtual ~GameState(); //destructor

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
class IssueOrders : public GameState {
    public:
    //transition function:
    /*Takes two arguments, validate the input command and makes decision about
    whether stay in current ststate or transit to next state*/
    void transition(GameEngine* GameEngine, string command);
   
    IssueOrders(); //constructor
    ~IssueOrders(); //destructor

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
class GameEngine{

    std::vector<Player*>* _players_ptr;
    vector<int*>* _armyPool;
    Deck * _deck;
    
public:
    
    // Returns a pointer to the current players in game
    std::vector<Player*>& get_players();
    
    GameEngine();
    ~GameEngine();
    GameState* getCurrentState() const; //returns pointer of current state

    void transit(string c); //transition function according to command inputs
    void setState(GameState* newState); //used to set Game object to next stats

    //setter is used to set the status to false when we reach the End state
    void setStatus(bool b);
    //getter is used to get the current status of the game
    bool getStatus();
    //retunrs the _armyPool
    vector<int*>& get_ArmyPools();
    //returns the _deck
    Deck* getDeck();
    //Set deck
    void setDeck();
    //Copy Constructor and operator:
    GameEngine(const GameEngine& other);
    GameEngine& operator = (const GameEngine& e);
    
    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const GameEngine& g);

    private:
    GameState* _currentState; //current state
    bool _continue; 
    
};



#endif