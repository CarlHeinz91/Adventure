#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileContents.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


class TileMap
{
private:
	std::vector<std::vector<TileContents>> mMatrixOfTileContents;
	bool mHasChanged = false;

public:
	TileMap();
	~TileMap();

	TileContents& at(unsigned int x, unsigned int y);
	TileContents& at(sf::Vector2u const & pos);

	TileContents const & at(unsigned int x, unsigned int y) const;
	TileContents const & at(sf::Vector2u const & pos) const;


	void loadFromFile(std::string const & path);

	unsigned int getYSize() const;
	unsigned int getXSizeAt(unsigned int y) const;

	void outputOnTerminal() const;



};



#endif //TILEMAP_HPP
