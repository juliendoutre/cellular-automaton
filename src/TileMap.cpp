#include "TileMap.hpp"
#include <random>
#include <chrono>

using namespace std;

TileMap::TileMap(sf::Vector2u tileSize, unsigned int width, unsigned int height) {
    m_tileSize = tileSize;
    m_width = width;
    m_height = height;
    m_cells = vector<vector<bool>>(height, vector<bool>(width, false));
    fillWithRandomValues(0.7);
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    updateVertices();
}

void TileMap::fillWithRandomValues(double threshold) {
    for (unsigned int i = 0; i < m_width; ++i) {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            if (generateRandomNumber() < threshold) {
                m_cells[i][j] = true;
            }
        }
    }
}

void TileMap::updateVertices() {
    for (unsigned int i = 0; i < m_width; ++i) {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            sf::Color newColor;

            if (m_cells[i][j]) {
                newColor = sf::Color::White;
            } else {
                newColor = sf::Color::Black;
            }

            for (int i=0;i<4;i++) {
                quad[i].color = newColor;
            }
        }
    }
}

void TileMap::setState(sf::Vector2u position, bool state) {
    m_cells[position.x][position.y] = state;
}

bool TileMap::isMousePositionOK(sf::Vector2i mousePosition) const {
    if (mousePosition.x > 0 && mousePosition.x < m_width*m_tileSize.x && mousePosition.y > 0 && mousePosition.y < m_height*m_tileSize.y) {
        return true;
    } else {
        return false;
    }
}

sf::Vector2u TileMap::getTilePosition(sf::Vector2i mousePosition) {
    return sf::Vector2u((uint)mousePosition.x / m_tileSize.x, (uint)mousePosition.y / m_tileSize.y);
}

void TileMap::calculateNewStates() {
    for (unsigned int i = 0; i < m_width; ++i) {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            calculateNewState(sf::Vector2u(i, j));
        }
    }
    updateVertices();
}

void TileMap::calculateNewState(sf::Vector2u cellPosition) {
    int sum = cellNeighborsSum(cellPosition);
    bool cellState = m_cells[cellPosition.x][cellPosition.y];
    bool newCellState = ((sum == 3) || (cellState && sum == 2));
    setState(cellPosition, newCellState);
}

int TileMap::cellNeighborsSum(sf::Vector2u cellPosition) const {
    int sum = 0;
    uint x = cellPosition.x;
    uint y = cellPosition.y;
    
    if (x == 0 && y == 0) {
        sum += m_cells[x + 1][y] + m_cells[x][y + 1] + m_cells[x + 1][y + 1];
    } else if (x == 0 && y == m_height - 1) {
        sum += m_cells[x + 1][y] + m_cells[x + 1][y - 1] + m_cells[x][y - 1];
    } else if (x == m_width - 1 && y == 0) {
        sum += m_cells[x - 1][y] + m_cells[x][y + 1] + m_cells[x - 1][y + 1];
    } else if (x == m_width - 1 && y == m_height - 1) {
        sum += m_cells[x - 1][y] + m_cells[x - 1][y - 1] + m_cells[x][y - 1];
    } else if (x == 0) {
        sum += m_cells[x][y-1] + m_cells[x+1][y-1] + m_cells[x+1][y] + m_cells[x][y+1] + m_cells[x+1][y+1];
    } else if (x == m_width - 1) {
        sum += m_cells[x-1][y-1] + m_cells[x][y-1] + m_cells[x-1][y] + m_cells[x-1][y+1] + m_cells[x][y+1];
    } else if (y == 0) {
        sum += m_cells[x-1][y] + m_cells[x+1][y] + m_cells[x-1][y+1] + m_cells[x][y+1] + m_cells[x+1][y+1];
    } else if (y == m_height - 1) {
        sum += m_cells[x-1][y-1] + m_cells[x][y-1] + m_cells[x+1][y-1] + m_cells[x-1][y] + m_cells[x+1][y];
    } else {
        sum += m_cells[x-1][y-1] + m_cells[x][y-1] + m_cells[x+1][y-1] + m_cells[x-1][y] + m_cells[x+1][y] + m_cells[x-1][y+1] + m_cells[x][y+1] + m_cells[x+1][y+1];
    }

    return sum;
}


uint TileMap::getLivingCellsNumber() {
    uint livingCellsNumber = 0;
    for (unsigned int i = 0; i < m_width; ++i) {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            if (m_cells[i][j])
                livingCellsNumber++;
        }
    }
    return livingCellsNumber; 
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vertices, states);
}

double generateRandomNumber() {
    std::mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);
    return unif(rng);
}