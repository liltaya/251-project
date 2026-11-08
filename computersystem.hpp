// computersystem.hpp
// ENSC 251 Final Project - virus.exe
// Author: Jackson Brhelle
//
// Represents a player's whole computer system: the four components
// CPU (20 HP), Memory (10 HP), Network (5 HP), and Storage (15 HP).
// Gives access to the component matching a card's suit, calculates total
// remaining HP, and reports whether the whole system is destroyed.
//
// Suits are passed as ints, matching the suit constants in card.hpp:
//   0 = HEARTS   -> CPU
//   1 = DIAMONDS -> Memory
//   2 = CLUBS    -> Network
//   3 = SPADES   -> Storage

#ifndef COMPUTERSYSTEM_HPP
#define COMPUTERSYSTEM_HPP

#include <vector>
#include "component.hpp"

class ComputerSystem { 
    public: 
        // Creates the four components at full HP:
        // CPU 20, Memory 10, Network 5, Storage 15.
        ComputerSystem(); 
        
        // Destructor
        ~ComputerSystem();
        
        
        // component access
        
        // Returns the component targeted by a card of the given suit,
        // so Game can apply damage, healing, or a shield to it
        // Precondition: 0 <= suit <= 3 
        Component& getComponent(int suit);
        
        // Read only version, used by GameUI to display component status
        // Precondition: 0 <= suit <= 3
        const Component& getComponent(int suit) const;
        
        
        // system status
        
        // Returns the sum of the current HP of all four components
        // Used to decide the winner when the draw pile and both hands are empty
        int getTotalHP() const;
        
        // Returns true if all four components are destroyed
        bool isSystemDestroyed() const;
        
        // turn and game management 
        
        // Removes the shields from all four components
        // Called by Game at the start of this player's turn
        void removeAllShields();
        
        // Resets all four components to full HP with no shields (used for replay)
        void reset(); 
        
        
    private:
        // The four components, indexed by the suit
        // index 0 = CPU, 1 = Memory, 2 = Network, 3 = Storage
        std::vector<Component> component;
};

#endif // COMPUTERSYSTEM_HPP