# virus.exe

A two-player strategy card game in C++, built by a team of four for ENSC 251, Software Design and Analysis for Engineers, at Simon Fraser University (Fall 2026).

Each player defends a computer made of four parts. Every card in an ordinary 52-card deck targets one part by its suit, and the last computer standing wins.

## Rules

| Suit | Part | Health |
|---|---|---|
| Hearts | CPU | 20 HP |
| Diamonds | Memory | 10 HP |
| Clubs | Network | 5 HP |
| Spades | Storage | 15 HP |

- Each player starts with five cards and either draws or plays one card per turn.
- Cards 2 to 10 deal damage to the matching part.
- Jack heals 2 HP, Queen heals 4 HP and King heals 6 HP. A destroyed part cannot be healed.
- An Ace raises a shield on its part that blocks attacks during the opponent's next turn.
- Destroy all four of the opponent's parts to win. If the cards run out, the player with the most total HP left wins.

## How the code fits together

```
main()
 ├── GameUI          menus, input checks, turn display
 └── Game            turn order, card effects, shields, win check
      ├── Deck ── Card
      └── Player (x2)
           ├── hand of Cards (up to 5)
           └── ComputerSystem ── Component (x4)
```

| Files | Classes | Written by |
|---|---|---|
| `card.hpp`, `deck.hpp` | `Card`, `Deck` | Alina Beg |
| `component.hpp`, `computersystem.hpp` | `Component`, `ComputerSystem` | Jackson Brhelle |
| `player.hpp`, `player.cpp`, `main.cpp` | `Player`, `main()` | Vijeta Dhalla |
| `game.hpp`, `game.cpp`, `gameui.hpp`, `gameui.cpp` | `Game`, `GameUI` | Taya Mamenko |

`proposalfiles/` holds the class headers from the original project proposal.

## Status

In progress. The class interfaces are in place and the team is joining the implementations into one build this term.
