#include "cli.hpp"

using namespace std;

void banner() {
    cout << "\033[1;32m====== The Game of Life ====== \033[0m\n" << endl;
}

sf::Vector2u getMapParameters() {
    cout << "=== OPTIONS ===" << endl;

    sf::Vector2u parameters;

    cout << "Map width (pixels): ";
    cin >> parameters.x;

    cout << "Map height (pixels): ";
    cin >> parameters.y;

    return parameters;
}

int getRefreshFrequency() {
    int refreshFrequency;

    cout << "Refresh frequency (milliseconds): ";
    cin >> refreshFrequency;
    
    return refreshFrequency;
}

void printDashboard(uint width, uint height, uint generation, uint livingCellsNumber) {
    cout << "\033[2J\033[1;1H";
    banner();
    cout << "=== MAP ===" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << endl;
    cout << "=== CELLS ===" << endl;
    cout << "Generation: " << generation << endl;
    cout << "\033[1;32mAlive: \033[0m" << livingCellsNumber << endl;
    cout << "\033[1;31mDead: \033[0m" << width * height - livingCellsNumber << endl;
}