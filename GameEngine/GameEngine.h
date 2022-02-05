//To prevent mutiple inclusion:
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
using namespace std;

class Game; //solve dependencies
            //Game is defined at the end

//An abstract class:
class GameState
{
    public:
    virtual void transition(Game* Game, string command) = 0; //pure cirtual function
                                                            //needs to be overrided 
    virtual ~GameState(){} //inline destructor
};

//Start/Initial State:
class Start : public GameState {
    public:
    void transition(Game* Game, string command);
    static Start& getInstance(); //returns a reference to the class
                                //used reference so we don't need to handle memory leak later
    void validate(Game* Game);

    private:
    Start(){};
    Start(const Start& other); //copy constructor
    Start& operator = (const Start& s); //assignment operator
};

//MapLoaded State:
class MapLoaded : public GameState {
    public:
    void transition(Game* Game, string command);
    static MapLoaded& getInstance();

    private:
    MapLoaded(){};
    MapLoaded(const MapLoaded& other);
    MapLoaded& operator = (const MapLoaded& m);
};

//MapValidated State:
class MapValidated : public GameState {
    public:
    void transition(Game* Game, string command);
    static MapValidated& getInstance();

    private:
    MapValidated(){};
    MapValidated(const MapValidated& other);
    MapValidated& operator = (const MapValidated& mv);
};

//PlayersAdded State:
class PlayersAdded : public GameState {
    public:
    void transition(Game* Game, string command);
    static PlayersAdded& getInstance();

    private:
    PlayersAdded(){};
    PlayersAdded(const PlayersAdded& other);
    PlayersAdded& operator = (const PlayersAdded& p);
};

//AssignedReinforcement State:
class AssignedReinforcement : public GameState {
    public:
    void transition(Game* Game, string command);
    static AssignedReinforcement& getInstance();

    private:
    AssignedReinforcement(){};
    AssignedReinforcement(const AssignedReinforcement& other);
    AssignedReinforcement& operator = (const AssignedReinforcement& a);
};

//Issue Orders State:
class IssueOrders : public GameState {
    public:
    void transition(Game* Game, string command);
    static IssueOrders& getInstance();

    private:
    IssueOrders(){};
    IssueOrders(const IssueOrders& other);
    IssueOrders& operator = (const IssueOrders& i);
};

//Execute Orders State:
class ExcecuteOrders : public GameState {
    public:
    void transition(Game* Game, string command);
    static ExcecuteOrders& getInstance();

    private:
    ExcecuteOrders(){};
    ExcecuteOrders(const ExcecuteOrders& other);
    ExcecuteOrders& operator = (const ExcecuteOrders& e);
};

//Win State:
class Win : public GameState {
    public:
    void transition(Game* Game, string command);
    static Win& getInstance();

    private:
    Win(){};
    Win(const Win& other);
    Win& operator = (const Win& w);
};

//End State:
class End: public GameState{
    public:
    void transition(Game* Game, string command);
    static End& getInstance();

    private:
    End(){};
    End(const End& other);
    End& operator = (const End& e);
    
};


//The Game Class:
/*Game class would be used to create new object which contains
the current state of the game, and transit between states when 
received a command from the console.*/
class Game{
    public:
    Game();
    inline GameState* getCurrentState() const {return _currentState;} //returns pointer of current state

    void transition(string c); //transition function according to command inputs
    void setState(GameState& newState); //used to set Game object to next stats

    //setter is used to set the status to false when we reach the End state
    inline void setStatus(bool b){ _continue = b; }
    //getter is used to get the current status of the game
    inline bool getStatus(){ return _continue; }

    private:
    GameState* _currentState; //current state
    bool _continue; //status of the game(false if game is ended)
};

#endif