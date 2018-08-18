#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

public:
    TileMap(sf::Vector2u tileSize, unsigned int width, unsigned int height);
    void setState(sf::Vector2u position, bool state);
    sf::Vector2u getTilePosition(sf::Vector2i mousePosition);
    bool isMousePositionOK(sf::Vector2i mousePosition) const;
    void calculateNewStates();
    void calculateNewState(sf::Vector2u cellPosition);
    int cellNeighborsSum(sf::Vector2u cellPosition) const;
    void updateVertices();
    void fillWithRandomValues(double threshold);
    uint getLivingCellsNumber();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Vector2u m_tileSize;
    int m_width;
    int m_height;
    std::vector<std::vector<bool>> m_cells;
};

double generateRandomNumber();