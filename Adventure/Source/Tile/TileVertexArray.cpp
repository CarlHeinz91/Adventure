#include "stdafx.h"
#include "Source\Tile\TileVertexArray.hpp"


TileVertexArray::TileVertexArray(TileMap const & tileMap)
	: pVertexArray(new sf::VertexArray(sf::Quads)),
	  pTextureAtlasOfTiles(TextureManager::getTexture(TextureManager::TextureName::TILE_TEXTURE_ATLAS))
{
	this->setTileMap(tileMap);
}

TileVertexArray::~TileVertexArray()
{
	delete pVertexArray;
	pVertexArray = nullptr;
}


void TileVertexArray::setTileMap(TileMap const & tileMap)
{
	pVertexArray->clear();
	unsigned int ySize = tileMap.getYSize();
	for (unsigned int y = 0; y < ySize; ++y)
	{
		unsigned int xSize = tileMap.getXSizeAt(y);
		for (unsigned int x = 0; x < xSize; ++x)
		{
			TileType tileType = tileMap.at(x, y).tileType;
			sf::FloatRect textureRect = static_cast<sf::FloatRect>(TileMap::getTextureRectForTileType(tileType));
			sf::Vector2f textRectPos = sf::Vector2f(textureRect.left, textureRect.top);
			sf::Vertex vertexUL(static_cast<sf::Vector2f>(sf::Vector2i((x + 0) * TileMap::sSizeOfATile, (y + 0) * TileMap::sSizeOfATile)), sf::Color::White, textRectPos + sf::Vector2f(mEpsilon, mEpsilon));
			sf::Vertex vertexDL(static_cast<sf::Vector2f>(sf::Vector2i((x + 0) * TileMap::sSizeOfATile, (y + 1) * TileMap::sSizeOfATile)), sf::Color::White, textRectPos + sf::Vector2f(0.f, textureRect.height) + sf::Vector2f(mEpsilon, -mEpsilon));
			sf::Vertex vertexDR(static_cast<sf::Vector2f>(sf::Vector2i((x + 1) * TileMap::sSizeOfATile, (y + 1) * TileMap::sSizeOfATile)), sf::Color::White, textRectPos + sf::Vector2f(textureRect.width, textureRect.height) + sf::Vector2f(-mEpsilon, -mEpsilon));
			sf::Vertex vertexUR(static_cast<sf::Vector2f>(sf::Vector2i((x + 1) * TileMap::sSizeOfATile, (y + 0) * TileMap::sSizeOfATile)), sf::Color::White, textRectPos + sf::Vector2f(textureRect.width, 0.f) + sf::Vector2f(-mEpsilon, mEpsilon));
			pVertexArray->append(vertexUL);
			pVertexArray->append(vertexDL);
			pVertexArray->append(vertexDR);
			pVertexArray->append(vertexUR);
		}
	}
}

void TileVertexArray::render(sf::RenderWindow* renderWindow) const
{
	renderWindow->draw(*pVertexArray, pTextureAtlasOfTiles);
}

