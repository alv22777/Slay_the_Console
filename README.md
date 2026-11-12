# **Slay The Console - A Slay The Spire C++ console recreation**



C++ console based implementation of many of Slay The Spire's combat mechanics (for now).



### **Features**



* Playable Characters: The Ironclad, The Silent, The Defect, and The Watcher
* Card-based combat and energy management
* Enemy intents and turn-based enemy actions
* Effects and Power implementation
* Event queue for managing effect resolution
* Combat event log for presentation
* UI Features to make the experience more immersive and intuitive



### **Requirements**



* Windows
* MinGW-w64 (GCC)
* C++ 17 compiler



### **Build**



* Option 1: Run launch.bat	
* Option 2: From root, run: 
g++ -std=c++17 src/main.cpp src/game\_logic/\*.cpp src/character/\*.cpp src/card/\*.cpp src/ui/\*.cpp src/data/\*.cpp src/item/\*.cpp -Iinclude -static -static-libgcc -static-libstdc++ -o SLAY.exe



Then launch executable **SLAY.exe**



### **Project Structure**

src/

├── card/        Cards and piles

├── character/   Player/Enemy logic

├── data/        Game constants, card object definitions

├── game\_logic/  Game, effect/power and queue, RNG 

├── item/        Potions/relics (WIP)

├── ui/          Formatting and logging

└── main.cpp     Entry



### **Development**



This is a personal project that i have started to learn OOP in C++ while also recreating one of my favorite games of all time! I am having tons of fun rediscovering all the little design puzzles that Mega Crit originally faced.



## **Roadmap**

1. **Dynamic effect value calculation used for cards like Wallop and to improve UI presentation**
2. **Potion implementation**
3. **Relic implementation**
4. **Card cost changing, enchantments (Slay The Spire II), card upgrades**
5. **Implementation of Character specific mechanics (Stances, Orbs)**
6. **Transition cards to data driven rather than hardcoded**
7. **Different floor types (Campfire, Shop, Events, Elites, Boss)** 
8. **Map procedural generation and Acts (one, two, three, ~~four~~)**
9. **Dynamic score calculation and persistent save files with run logs and seeds that allow reproducibility**
10. **Implementing content from Slay The Spire II.**



## **License**

Since this is supposed to be a 1:1 recreation of the original game, I have decided to leave the license pending for now, as I would not want to incur in any copyright infringement.



