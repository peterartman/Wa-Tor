// main.cpp --- 
// 
// Filename: test.cpp
// Description: 
// Author: Joseph
// Editor: Piotr Artman, student No. C00220223
// Created: Fri Nov  3 15:51:15 2023 (+0000)
// Last-Updated: Fri Nov  3 16:49:06 2023 (+0000)
//           By: Joseph
//     Update #: 19
// 
// 

// Commentary: 
// 
// 
// 
// 
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// some helpful code here!
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// https://www.sfml-dev.org/tutorials/2.5/start-linux.php
// https://learnsfml.com/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Code:


#include <SFML/Graphics.hpp>

// UI settings

const int xdim = 400;
const int ydim = 400;
int WindowXSize = 1600;
int WindowYSize = 1200;
int cellXSize = WindowXSize / xdim;
int cellYSize = WindowYSize / ydim;
sf::RectangleShape watorUIarray[xdim][ydim];

// END of UI settings

//array container for population simulation
int populationArray[xdim][ydim];
//END of array container for population simulation

//parameters of Wa-Tor simulation 

// size of fish population
int fishPopulationSize = 200;
// size of shark population
int sharkPopulationSize = 200;
// number of steps without food before shark dies
int sharkLifespan = 20;
// number of steps necessary for fish to mature and repoduce
int fishTimeToReproduce = 4;
// number of steps necessary for fish to mature and repoduce
int energyInFish = 4;
// number of steps necessary for shark to mature and repoduce
int sharkTimeToReproduce = 7;


enum swimmingDirections
{
    north,
    south,
    east,
    west,
};



//END parameters of Wa-Tor simulation 

void populateFish()
{

}


void populateShark()
{

}


int main()
{

    //each shape will represent either a fish, shark or empty space
    //e.g. blue for empty, red for shark and green for fish
    
    for (int i = 0;i < xdim;++i) {
        for (int k = 0;k < ydim;++k) {//give each one a size, position and color
            watorUIarray[i][k].setSize(sf::Vector2f(80.f, 60.f));
            watorUIarray[i][k].setPosition(i * cellXSize, k * cellYSize);//position is top left corner!
            int id = i * 1 - +k;
            if (id % 2 == 0) watorUIarray[i][k].setFillColor(sf::Color::Green);
            else watorUIarray[i][k].setFillColor(sf::Color::Blue);
        }
    }
    sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Wa-Tor world");



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //loop these three lines to draw frames
        window.clear(sf::Color::Black);
        for (int i = 0;i < xdim;++i) {
            for (int k = 0;k < ydim;++k) {
                window.draw(watorUIarray[i][k]);
            }
        }
        window.display();
    }

    return 0;
}

// 
// main.cpp ends here
