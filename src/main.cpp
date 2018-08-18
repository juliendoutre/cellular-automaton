#include "TileMap.hpp"
#include "cli.hpp"
#include "constants.hpp"

int main()
{   
    banner();
    sf::Vector2u mapParameters = getMapParameters();
    int refreshFrequency = getRefreshFrequency();

    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * mapParameters.x, TILE_SIZE * mapParameters.y), "The Game of Life", sf::Style::Titlebar | sf::Style::Close);

    TileMap map(sf::Vector2u(TILE_SIZE, TILE_SIZE), mapParameters.x, mapParameters.y);
    uint generation = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        map.calculateNewStates();
        generation++;

        window.clear();
        window.draw(map);
        window.display();
        
        printDashboard(mapParameters.x, mapParameters.y, generation, map.getLivingCellsNumber());

        sf::sleep(sf::milliseconds(refreshFrequency));
    }

    return 0;
}