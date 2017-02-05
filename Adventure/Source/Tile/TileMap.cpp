#include "stdafx.h"
#include "Source\Tile\TileMap.hpp"

TileMap::TileMap()
{

}
TileMap::~TileMap()
{

}

TileContents& TileMap::at(unsigned int x, unsigned int y)
{
	return mMatrixOfTileContents.at(y).at(x);
}
TileContents& TileMap::at(sf::Vector2u const & pos)
{
	return mMatrixOfTileContents.at(pos.y).at(pos.x);
}

TileContents const & TileMap::at(unsigned int x, unsigned int y) const
{
	return mMatrixOfTileContents.at(y).at(x);
}
TileContents const & TileMap::at(sf::Vector2u const & pos) const
{
	return mMatrixOfTileContents.at(pos.y).at(pos.x);
}

void TileMap::loadFromFile(std::string const & path)
{
	//Clear mVectorOfTileContents
	mMatrixOfTileContents.clear();

	//Extract lines from File
	std::ifstream inputFileStream(path);
	std::vector<std::string> linesOfFile;
	if (inputFileStream.good())
	{
		while (inputFileStream.good())
		{
			std::string line;
			std::getline(inputFileStream, line);
			linesOfFile.push_back(line);
		}
	}
	else
	{
		std::cerr << "Could not open File: " << path << std::endl;
		throw "TileMap::loadFromFile(std::string const & path) : Could not open File!";
	}

	//Use extracted lines and cut into integers and write into vectors
	std::vector<std::vector<TileType>> matOfTileTypes;
	for (auto line : linesOfFile)
	{
		std::vector<TileType> tileTypeVector;
		std::stringstream stringStream(line);
		while (stringStream.good())
		{
			int intData;
			stringStream >> intData;
			tileTypeVector.push_back(static_cast<TileType>(intData));
		}
		matOfTileTypes.push_back(tileTypeVector);
	}

	//Combine all extracted data (e.g. TileType, ItemType, Border, ...)
	mMatrixOfTileContents.reserve(matOfTileTypes.size());
	for (auto vecOfTileType : matOfTileTypes)
	{
		std::vector<TileContents> vecOfTileContents;
		vecOfTileContents.reserve(vecOfTileType.size());
		for (auto tileType : vecOfTileType)
		{
			TileContents tileContents;
			tileContents.tileType = tileType;
			vecOfTileContents.push_back(tileContents);
		}
		mMatrixOfTileContents.push_back(vecOfTileContents);
	}
}

unsigned int TileMap::getYSize() const
{
	return mMatrixOfTileContents.size();
}
unsigned int TileMap::getXSizeAt(unsigned int y) const
{
	return mMatrixOfTileContents.at(y).size();
}

void TileMap::outputOnTerminal() const
{
	for (auto vec : mMatrixOfTileContents)
	{
		for (auto tileContents : vec)
		{
			std::cout << tileContents;
		}
		std::cout << std::endl;
	}
}
