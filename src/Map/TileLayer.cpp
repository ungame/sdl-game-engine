#include "TileLayer.h"
#include "TextureManager.h"

#include <SDL2/SDL.h>

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tilesets)
    : m_Tilesets(tilesets)
{
    m_TileSize = tileSize;
    m_RowCount = rowCount;
    m_ColCount = colCount;
    m_TileMap = tileMap;

    for(unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        std::string filepath =  "assets\\maps\\" + m_Tilesets[i].Source;
        bool ok = TextureManager::GetInstance()->Load(m_Tilesets[i].Name, filepath);
        if(!ok)
        {
            SDL_LogError(1, "Failed Load asset: %s", filepath.c_str());
        } 
        else {
            SDL_Log("Load asset: Name = %s, Source = %s", m_Tilesets[i].Name.c_str(), filepath.c_str());
        }
    }
}

void TileLayer::Render()
{
    for(int i = 0; i < m_RowCount; i++)
    {
        for(int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_TileMap[i][j];

            if(tileID == 0)
            {
                continue;
            } 
            else {

                int index = 0;

                if(m_Tilesets.size() > 1)
                {
                    for(unsigned int k = 1; k < m_Tilesets.size(); k++)
                    {
                        if(tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                    
                Tileset ts = m_Tilesets[index];
                int tileRow = tileID / ts.ColCount;
                int tileCol = tileID - tileRow * ts.ColCount - 1;

                // if este tile esta na ultima coluna
                if(tileID % ts.ColCount == 0)
                {
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }

                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
            }

        }
    }
}

void TileLayer::Update()
{

}
