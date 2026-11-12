//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe GameUI Class

#include "gameui.hpp" //include GameUI class
#include "game.hpp" //include Game class
#include "player.hpp" //include Player class
#include "computersystem.hpp" //include ComputerSystem class
#include "component.hpp" //include Component class
#include <iostream> //for input and output
#include <sstream> //for checking input
#include <stdexcept> //for reporting errors
#include <string> //for text values

using namespace std;

GameUI::GameUI() { //create game interface
}

int GameUI::getValidInput(int min, int max) { //validate input

    while (true) { //repeat until valid input

        string line; //store input line

        if (!getline(cin, line)) { //read user input
            throw runtime_error("Input stream closed"); //report error
        }

        istringstream stream(line); //process input
        int value = 0; //store selected number
        char extra; //check extra characters

        if ((stream >> value) &&
            !(stream >> extra) &&
            value >= min &&
            value <= max) { //check valid number

            return value; //return selected number
        }

        displayInvalidInput(); //show error message

        cout << "Enter a number from "
             << min << " to " << max << ": "; //request input
    }
}

void GameUI::displayTitleScreen() { //show main menu

    cout << "\n========== VIRUS.EXE ==========\n"; //game title
    cout << "1. Player vs. Player\n"; //start game
    cout << "2. Rules\n"; //view rules
    cout << "3. Quit\n"; //exit program
}

int GameUI::getMenuChoice() { //read menu choice

    cout << "Choose an option: "; //request choice

    return getValidInput(1, 3); //return valid option
}

string GameUI::getPlayerName(int playerNumber) { //read player name

    cout << "Player " << playerNumber
         << " name: "; //request name

    string name; //store player name

    if (!getline(cin, name)) { //read player name
        throw runtime_error("Input stream closed"); //report error
    }

    if (name.empty()) { //check empty name
        return "Player " + to_string(playerNumber); //default name
    }

    return name; //return entered name
}

void GameUI::displayRules() { //show game rules

    cout << "\n========== RULES ==========\n"; //rules title

    cout << "Each player has four components:\n"; //component information
    cout << "CPU: 20 HP\n"; //CPU health
    cout << "Memory: 10 HP\n"; //Memory health
    cout << "Network: 5 HP\n"; //Network health
    cout << "Storage: 15 HP\n"; //Storage health

    cout << "\nCard suits:\n"; //show card suits
    cout << "Hearts: CPU\n"; //heart target
    cout << "Diamonds: Memory\n"; //diamond target
    cout << "Clubs: Network\n"; //club target
    cout << "Spades: Storage\n"; //spade target

    cout << "\nCard effects:\n"; //show card abilities
    cout << "2-10: Damage equal to card rank\n"; //attack cards
    cout << "Jack: Heal 2 HP\n"; //Jack ability
    cout << "Queen: Heal 4 HP\n"; //Queen ability
    cout << "King: Heal 6 HP\n"; //King ability
    cout << "Ace: Shield for one turn\n"; //Ace ability

    cout << "\nEach player starts with 5 cards.\n"; //starting hand
    cout << "Players may draw or play one card per turn.\n"; //turn actions
    cout << "Maximum hand size is 5 cards.\n"; //hand limit
    cout << "Discarded cards do not return to the deck.\n"; //discard rule
    cout << "Destroyed components cannot be healed.\n"; //repair restriction
    cout << "Shields do not stack or extend.\n"; //shield restriction

    cout << "\nDestroy all opponent components to win.\n"; //win condition
    cout << "Results are checked after each full round.\n"; //round rule
    cout << "If all cards are used, highest HP wins.\n"; //deck condition
    cout << "Equal remaining HP results in a draw.\n"; //draw condition
}

void GameUI::displayGameResult(GameResult result) { //show result

    cout << "\n========== GAME OVER ==========\n"; //game end title

    if (result == GameResult::Player1Win) { //first player wins
        cout << "Player 1 wins!\n"; //show winner
    }
    else if (result == GameResult::Player2Win) { //second player wins
        cout << "Player 2 wins!\n"; //show winner
    }
    else { //game ends in draw
        cout << "It's a draw!\n"; //show draw
    }
}

void GameUI::displayGameEndMenu() { //show end menu

    cout << "\n1. Replay\n"; //restart game
    cout << "2. Quit\n"; //exit game
}

int GameUI::getGameEndChoice() { //read end menu choice

    cout << "Choose an option: "; //request choice

    return getValidInput(1, 2); //return valid choice
}

void GameUI::displayInvalidInput() { //show invalid input

    cout << "Invalid input. Please try again.\n"; //error message
}

void GameUI::displayGoodbye() { //show goodbye message

    cout << "Goodbye from virus.exe!\n"; //exit message
}

void GameUI::displayTurn(const string& playerName) { //show turn

    cout << "\n---------- "
         << playerName
         << "'s turn ----------\n"; //current player
}

void GameUI::displayComponents(
    const string& playerName,
    int totalHP
) { //show player health

    cout << playerName
         << " - Total HP: "
         << totalHP
         << "/50\n"; //show total health
}

void GameUI::displaySystem(const Player& player) { //show components

    displayComponents(
        player.getName(), //player name
        player.getTotalHP() //player health
    );

    const ComputerSystem& system =
        player.getSystem(); //get computer system

    for (int suit = 0; suit < 4; suit++) { //check each component

        const Component& part =
            system.getComponent(suit); //get component

        cout << "  "
             << part.getName()
             << ": "
             << part.getCurrentHP()
             << "/"
             << part.getMaxHP(); //show component health

        if (part.isDestroyed()) { //check destroyed status
            cout << " [DESTROYED]"; //show destroyed component
        }
        else if (part.isShielded()) { //check shield status
            cout << " [SHIELDED]"; //show active shield
        }

        cout << "\n"; //move to next line
    }
}

void GameUI::displayHand(int handSize) { //show hand size

    cout << "Cards in hand: "
         << handSize
         << "/5\n"; //display card count
}

void GameUI::displayCards(const Player& player) { //show cards

    displayHand(
        static_cast<int>(player.getHandSize())
    ); //show hand size

    const auto& hand =
        player.getHand(); //get player's cards

    for (int i = 0;
         i < static_cast<int>(hand.size());
         i++) { //loop through cards

        cout << "  "
             << i + 1
             << ". "
             << hand[i].getDescription()
             << "\n"; //show card information
    }
}

void GameUI::displayTurnMenu(
    bool canDraw,
    bool canPlay
) { //show available actions

    cout << "Choose an action:\n"; //show menu title

    if (canDraw) { //check draw availability
        cout << "1. Draw a card\n"; //show draw action
    }

    if (canPlay) { //check play availability
        cout << "2. Play a card\n"; //show play action
    }
}

int GameUI::getTurnChoice(
    bool canDraw,
    bool canPlay
) { //read turn choice

    if (!canDraw && !canPlay) { //check available actions
        return 0; //no actions available
    }

    while (true) { //repeat until valid choice

        displayTurnMenu(canDraw, canPlay); //show actions

        cout << "Action: "; //request action

        int choice = getValidInput(1, 2); //read choice

        if (choice == 1 && canDraw) { //valid draw action
            return 1; //return draw choice
        }

        if (choice == 2 && canPlay) { //valid play action
            return 2; //return play choice
        }

        displayInvalidInput(); //reject unavailable action
    }
}

int GameUI::getCardChoice(int handSize) { //select card

    if (handSize <= 0) { //check empty hand
        throw logic_error(
            "Cannot select from empty hand"
        ); //report error
    }

    cout << "Card number (1-"
         << handSize
         << "): "; //request card number

    return getValidInput(1, handSize) - 1; //convert to index
}

void GameUI::displayMessage(const string& message) { //show message

    cout << message << "\n"; //display text
}
