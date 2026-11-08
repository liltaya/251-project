
//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe GameUI Class

#include "gameui.hpp" //include GameUI class
#include <iostream> //for input and output
#include <sstream> //for converting text into number
#include <string> //for storing user input

using namespace std;

GameUI::GameUI() { //default constructor
    //game object is created automatically
}

void GameUI::showMenu() { //show main menu
    cout << "--- VIRUS.EXE ---" << endl;
    cout << "1. Player vs. Player" << endl;
    cout << "2. Rules" << endl;
    cout << "3. Quit" << endl;
}

void GameUI::showRules() { //show game rules
    cout << "--- GAME RULES ---" << endl;

    cout << "Each player has 4 computer components." << endl;
    cout << "CPU: 20 HP" << endl;
    cout << "Memory: 10 HP" << endl;
    cout << "Network: 5 HP" << endl;
    cout << "Storage: 15 HP" << endl;

    cout << "Each player starts with 5 cards." << endl;
    cout << "Draw or play one card per turn." << endl;

    cout << "Cards 2-10 deal damage." << endl;
    cout << "Jack heals 2 HP." << endl;
    cout << "Queen heals 4 HP." << endl;
    cout << "King heals 6 HP." << endl;
    cout << "Ace gives a shield for one turn." << endl;

    cout << "Destroy all opponent components to win." << endl;
    cout << "If the deck is empty, highest HP wins." << endl;
}

void GameUI::showComponents() { //show component health
    cout << "--- COMPONENT STATUS ---" << endl;

    for (int i = 1; i <= 2; i++) {
        Player& player = game.getPlayer(i); //get player

        cout << player.getName() << endl; //show player name

        display CPU HP; //show CPU health
        display Memory HP; //show Memory health
        display Network HP; //show Network health
        display Storage HP; //show Storage health

        display active shields; //show protected components
    }
}

void GameUI::showHand() { //show current player cards
    cout << "--- YOUR CARDS ---" << endl;

    Player& player = game.getCurrentPlayer(); //get player

    for (int i = 0; i < player.getHandSize(); i++) {
        cout << i + 1 << ". "; //show card number
        cout << player.getCard(i) << endl; //show card
    }
}

void GameUI::showGame() { //show current game status
    cout << "--- CURRENT TURN ---" << endl;

    cout << "Player: "
         << game.getCurrentPlayer().getName() << endl;

    showComponents(); //show both systems
    showHand(); //show current player cards

    cout << "Cards left in deck: "
         << game.getDeck().getNumCards() << endl;
}

int GameUI::getValidInput(int min, int max) { //check user input
    string input; //store entered text
    int choice; //store choice number

    while (true) {
        getline(cin, input); //read user input

        istringstream inputStream(input); //convert text to number
        char extra; //check for extra characters

        if ((inputStream >> choice) && !(inputStream >> extra)) {
            if (choice >= min && choice <= max) {
                return choice; //return valid choice
            }
        }

        cout << "Invalid input. Try again: " << endl;
    }
}

int GameUI::getMenuChoice() { //get menu selection
    cout << "Enter your choice: ";
    return getValidInput(1, 3); //accept 1 to 3
}

int GameUI::getCardChoice() { //get selected card
    int numCards = game.getCurrentPlayer().getHandSize(); //count cards

    cout << "Select card to play: ";
    return getValidInput(1, numCards) - 1; //convert to index
}

void GameUI::showTurnMenu() { //show player actions
    int numCards = game.getCurrentPlayer().getHandSize(); //count cards

    cout << "--- CHOOSE ACTION ---" << endl;

    if (numCards < 5 && !game.getDeck().isEmpty()) {
        cout << "1. Draw Card" << endl; //draw is available
    }

    if (numCards > 0) {
        cout << "2. Play Card" << endl; //play is available
    }
}

void GameUI::showWinner() { //show final game result
    cout << "--- GAME OVER ---" << endl;

    if (game.getWinner() == "Draw") {
        cout << "The game is a draw." << endl;
    }
    else {
        cout << "Winner: " << game.getWinner() << endl;
    }
}

void GameUI::run() { //run game interface
    bool running = true; //control program loop

    while (running) {
        showMenu(); //display main menu

        int choice = getMenuChoice(); //get menu choice

        if (choice == 1) {
            game.startGame(); //start new game

            bool replay = true; //control replay

            while (replay) {
                while (!game.isGameOver()) {
                    showGame(); //show game status
                    showTurnMenu(); //show available actions

                    get player action; //read action choice

                    if (player chooses draw) {
                        if (game.drawCard()) {
                            cout << "Card drawn successfully." << endl;
                            game.nextTurn(); //finish turn
                        }
                        else {
                            cout << "Cannot draw card." << endl;
                        }
                    }
                    else if (player chooses play) {
                        int cardIndex = getCardChoice(); //select card

                        if (game.playCard(cardIndex)) {
                            cout << "Card played successfully." << endl;
                            game.nextTurn(); //finish turn
                        }
                        else {
                            cout << "Invalid move. Try again." << endl;
                        }
                    }

                    if (no actions are available) {
                        game.nextTurn(); //skip turn
                    }
                }

                showWinner(); //display game result

                cout << "1. Play Again" << endl;
                cout << "2. Main Menu" << endl;
                cout << "3. Quit" << endl;

                get replay choice; //read replay selection

                if (player chooses replay) {
                    game.startGame(); //start another game
                }
                else if (player chooses main menu) {
                    replay = false; //return to menu
                }
                else if (player chooses quit) {
                    replay = false; //stop replay
                    running = false; //exit program
                }
            }
        }
        else if (choice == 2) {
            showRules(); //display game rules
        }
        else if (choice == 3) {
            running = false; //exit program
        }
    }

    cout << "--- END OF PROGRAM ---" << endl;
}
