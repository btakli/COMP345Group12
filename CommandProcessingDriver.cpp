//#include "CommandProcessing.h"
//#include <iostream>
////#include "GameEngine.h"
//using namespace std;
//
//int main(){
//    string input_option;
//    /*GameEngine* myGame;
//    myGame = new GameEngine();*/
//
//    CommandProcessor* cp = new CommandProcessor();
//    
//    cout << endl;
//    cout << "How would you like to input commands?" << endl;
//    cout << "Please choose from the following:" << endl;
//    cout << "1. -console" << endl;
//    cout << "2. -file <filename>" <<endl;
//    getline(cin, input_option);
//    string option_prefix = input_option.substr(0, 4);
//    if(input_option == "-console"){
//        list<Command>* l1 = cp->getCommand();
//        //list<Command> myConsoleInputs = *l1;
//        //loop through the list:
//        cout << "get here" <<endl;
//        list<Command>::iterator itConsole;
//        for(itConsole = l1->begin(); itConsole != l1->end(); ++itConsole){
//                cout << "get in loop" << endl;
//                cout << itConsole -> getCommandName() << endl;
//            
//        }
//    }else if(option_prefix == "-file"){
//        size_t pos = input_option.find("<");
//        string pathIn = input_option.substr(pos+1);
//        FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(pathIn);
//        list<Command>* l2 = fcpa->getCommand();
//        list<Command> myFileInputs = *l2;
//        //loop through the list:
//        list<Command>::iterator itFile;
//        for(itFile = myFileInputs.begin(); itFile != myFileInputs.end(); ++itFile){
//            cout << itFile -> getCommandName() << endl;
//        }
//        delete fcpa;   
//    }else{
//        cout << "Please enter a correct option." << endl;
//    }
//    delete cp;                                                                                                                                                                                                                                                                                                
//    return 0;
//}