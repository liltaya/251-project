//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe GameUI Class

#include "gameui.hpp" //include GameUI class
#include "game.hpp" //include GameResult definition
#include <iostream> //for input and output
#include <sstream> //for converting text into number
#include <stdexcept> //for input errors
#include <string> //for storing user input

using namespace std;

GameUI::GameUI() { //default constructor
    //interface has no stored game object
}

void GameUI::displayTitleScreen() { //show main menu
    cout << "\n--- VIRUS.EXE ---" << endl;
    cout << "1. Player vs. Player" << endl;
    cout << "2. Rules" << endl;
    cout << "3. Quit" << endl;
}

int GameUI::getValidInput(int min, int max) { //check user input
    string input; //store entered text
    int choice; //store choice number

    while (true) { //repeat until input is valid
        if (!getline(cin, input)) { //read user input
            throw runtime_error("Input stream closed"); //stop on EOF
        }

        istringstream inputStream(input); //convert text to number
        char extra; //check for extra characters

        if ((inputStream >> choice) &&
            !(inputStream >> extra)) { //accept only whole numbers

            if (choice >= min && choice <= max) { //check range
                return choice; //return valid choice
            }
        }

        displayInvalidInput(); //show invalid input message
    }
}

int GameUI::getMenuChoice() { //get main menu selection
    cout << "Enter your choice: "; //ask for menu option
    return getValidInput(1, 3); //accept options 1 to 3
}

string GameUI::getPlayerName(int playerNumber) { //get player name
    string name; //store player name

    cout << "Enter Player " << playerNumber
         << " name: "; //ask for player name

    if (!getline(cin, name)) { //read name
        throw runtime_error("Input stream closed"); //stop on EOF
    }

    if (name.empty()) { //check for empty name
        return "Player " + to_string(playerNumber); //use default
    }

    return name; //return entered name
}

void GameUI::displayRules() { //show game rules
    cout << "\n--- GAME RULES ---" << endl;

    cout << "Each player has 4 computer components." << endl;
    cout << "CPU: 20 HP" << endl;
    cout << "Memory: 10 HP" << endl;
    cout << "Network: 5 HP" << endl;
    cout << "Storage: 15 HP" << endl;

    cout << "\nEach player starts with 5 cards." << endl;
    cout << "Draw or play one card per turn." << endl;

    cout << "\nCards 2-10 deal damage." << endl;
    cout << "Jack heals 2 HP." << endl;
    cout << "Queen heals 4 HP." << endl;
    cout << "King heals 6 HP." << endl;
    cout << "Ace gives a shield for one turn." << endl;

    cout << "\nDestroy all opponent components to win." << endl;
    cout << "If the deck runs out, highest HP wins." << endl;
}

void GameUI::displayGameResult(GameResult result) { //show result
    cout << "\n--- GAME OVER ---" << endl;

    if (result == GameResult::Player1Win) { //first player wins
        cout << "Winner: Player 1" << endl; //show first player
    }
    else if (result == GameResult::Player2Win) { //second player wins
        cout << "Winner: Player 2" << endl; //show second player
    }
    else { //both players have equal result
        cout << "The game is a draw." << endl; //show draw
    }
}

void GameUI::displayGameEndMenu() { //show end menu
    cout << "\n--- GAME FINISHED ---" << endl;
    cout << "1. Play Again" << endl;
    cout << "2. Quit" << endl;
}

int GameUI::getGameEndChoice() { //read end menu choice
    cout << "Enter your choice: "; //ask for selection
    return getValidInput(1, 2); //accept replay or quit
}

void GameUI::displayInvalidInput() { //show input error
    cout << "Invalid input. Try again." << endl;
}

void GameUI::displayGoodbye() { //show goodbye message
    cout << "\n--- END OF PROGRAM ---" << endl;
}

void GameUI::displayTurn(
    const string& playerName) { //show current turn

    cout << "\n--- CURRENT TURN ---" << endl;
    cout << "Player: " << playerName << endl; //show player name
}

void GameUI::displayComponents(
    const string& playerName,
    int totalHP) { //show component health summary

    cout << playerName << " total HP: "
         << totalHP << endl; //show combined component HP

    //TODO: display individual components and shields
    //requires System and Component interfaces
}

void GameUI::displayHand(int handSize) { //show player hand
    cout << "\n--- YOUR CARDS ---" << endl;
    cout << "Cards in hand: " << handSize << endl; //show hand size

    //TODO: display card ranks and suits
    //requires Card display interface
}

void GameUI::displayTurnMenu(
    bool canDraw,
    bool canPlay) { //show available turn actions

    cout << "\n--- CHOOSE ACTION ---" << endl;

    if (canDraw) { //drawing is available
        cout << "1. Draw Card" << endl; //show draw option
    }

    if (canPlay) { //playing is available
        cout << "2. Play Card" << endl; //show play option
    }

    if (!canDraw && !canPlay) { //no action available
        cout << "No actions available." << endl;
    }
}

int GameUI::getTurnChoice(
    bool canDraw,
    bool canPlay) { //read current player's action

    if (!canDraw && !canPlay) { //check for unavailable actions
        return 0; //skip current turn
    }

    while (true) { //repeat until action is valid
        cout << "Choose action: "; //ask for action
        int choice = getValidInput(1, 2); //read action

        if (choice == 1 && canDraw) { //check draw action
            return 1; //return draw choice
        }

        if (choice == 2 && canPlay) { //check play action
            return 2; //return play choice
        }

        displayInvalidInput(); //reject unavailable action
    }
}

int GameUI::getCardChoice(int handSize) { //select card
    if (handSize <= 0) { //check for empty hand
        return -1; //no valid card index
    }

    cout << "Select card to play: "; //ask for card number

    return getValidInput(1, handSize) - 1; //convert to index
}

void GameUI::displayMessage(
    const string& message) { //show game message

    cout << message << endl; //print message
}
