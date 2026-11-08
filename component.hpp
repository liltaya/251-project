// component.hpp
// ENSC 251 Final Project - virus.exe
// Author: Jackson Brhelle
//
// Represents a single computer component (CPU, Memory, Network, or Storage).
// Stores the component's HP and shield status, and handles taking damage,
// healing, and shielding. HP always stays between 0 and the maximum HP.
// Once a component reaches 0 HP it is destroyed and cannot be healed.

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
    public:
        // Creates a component with the given name and maximum HP
        // The component starts at full HP with no shield
        Component(std::string name, int maxHP);
        
        // destructor 
        ~Component();
        
        // Accessors
        
        // Returns the component's name 
        std::string getName() const;
        
        // Returns the component's current HP
        int getCurrentHP() const;
        
        // Returns the component's maximum HP
        int getMaxHP() const;
        
        // Returns true if the component's HP is 0
        bool isDestroyed() const;
        
        // Returns true if the component has an active shield
        bool isShielded() const;
        
        // card effects
        
        // Reduces HP by the given amount, stopping at 0
        // No effect if the component is shielded or already destroyed
        // Returns the amount of damage actually dealt
        int takeDamage(int amount);
        
        // Increases HP by the given amount, stopping at the maximum HP
        // No effect if the component is destroyed 
        // Returns the amount of HP actually restored 
        int heal(int amount); 
        
        // Activates a shield on this component. The shield blocks attacks
        // during the opponent's next turn. Does not stack or extend an 
        // existing shield. No effect if the component is destroyed 
        void activateShield();
        
        // Removes the shield. Called by Game at the start of the 
        // shielding player's next turn
        void removeShield();
        
        // Restores the component to full HP with no shield (used for replay)
        void reset();
        
    private:
        std::string name; // component name: "CPU", "MEMORY", "NETWORK", or "STORAGE"
        int currentHP;    // current HP, always between 0 and maxHP
        int maxHP;        // starting / maximum HP
        bool shielded;  // true while a shield is active
};

#endif //COMPONENT_H

