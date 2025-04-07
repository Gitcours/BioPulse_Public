#include "Map.hpp"
#include "EntityManager.h"

void Map::loadLab(vector<shared_ptr<Tile>>& tileMap, Player& player, string path)
{
    tileMap.clear();

    managerMutex.lock();
    for (auto ennemi : manager->getAllEnnemies())
    {
        manager->deleteEntity(ennemi);
    }
    managerMutex.unlock();

    fstream map(path);
    string line;
    Vector2f tilePosition = Vector2f(0, 0);
    bool run = true;
    while (run) {
        getline(map, line);
        if (line == ";") {
            run = false;
            break;
        }
        if (line.size() > 0) {
            if (line[0] == ';') {
                run = false;
                break;
            }
        }
        for (char tileChar : line) {
            if (tileChar == 'B') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.background_boss_room_1Texture);
                newTile->getSprite()->setTextureRect(IntRect(0, 0, text.background_boss_room_1Texture.getSize().x, text.background_boss_room_1Texture.getSize().y));
                tileMap.push_back(newTile);
            }if (tileChar == '1') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.background_room_1Texture);
                newTile->getSprite()->setTextureRect(IntRect(0, 0, text.background_room_1Texture.getSize().x, text.background_room_1Texture.getSize().y));
                tileMap.push_back(newTile);
            }if (tileChar == '2') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.background_room_2Texture);
                newTile->getSprite()->setTextureRect(IntRect(0, 0, text.background_room_2Texture.getSize().x, text.background_room_2Texture.getSize().y));
                tileMap.push_back(newTile);
            }if (tileChar == '3') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.background_room_3Texture);
                newTile->getSprite()->setTextureRect(IntRect(0, 0, text.background_room_3Texture.getSize().x, text.background_room_3Texture.getSize().y));
                tileMap.push_back(newTile);
            }if (tileChar == '7') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.background_room_4Texture);
                newTile->getSprite()->setTextureRect(IntRect(0, 0, text.background_room_4Texture.getSize().x, text.background_room_4Texture.getSize().y));
                tileMap.push_back(newTile);
            }
            //normal wall
            if (tileChar == 'w' or tileChar == 'M' or tileChar == 'H' or tileChar == 'h' or tileChar == 'c' or tileChar == 'K' or tileChar == 'R' or tileChar == 'f' or tileChar == 'g') {
                shared_ptr<Wall> newTile = make_shared<Wall>(tilePosition);
                if (tileChar == 'h') {
                    newTile->getSprite()->setScale(-1, 1);
                    newTile->getSprite()->move(Vector2f(tileRes, 0));
                }
                else if (tileChar == 'M') {
                    newTile->getSprite()->setTexture(text.wallFloorTileTexture);
                }
                else if (tileChar == 'c') {
                    newTile->getSprite()->setTexture(text.wallCeilingTexture);
                }
                else if (tileChar == 'w') {
                    newTile->getSprite()->setTexture(text.wallPlainTileTexture);
                }
                else if (tileChar == 'K' or tileChar == 'R' or tileChar == 'f' or tileChar == 'g') {
                    newTile->getSprite()->setTexture(text.wallCornerInsideTileTexture);
                    if (tileChar == 'R') {
                        newTile->getSprite()->setScale(-1, 1);
                        newTile->getSprite()->move(Vector2f(tileRes, 0));
                    }
                    else if (tileChar == 'f') {
                        newTile->getSprite()->setScale(1, -1);
                        newTile->getSprite()->move(Vector2f(0, tileRes));
                    }
                    else if (tileChar == 'g') {
                        newTile->getSprite()->setScale(-1, -1);
                        newTile->getSprite()->move(Vector2f(tileRes, tileRes));
                    }
                }
                //color
                if (levelsColors[getCurrentMap()]) {
                    newTile->getSprite()->setColor(Color(150, 195, 170));
                }
                else {
                    newTile->getSprite()->setColor(Color(135, 100, 190));
                }
                tileMap.push_back(newTile);
            }

            //sticky wall
            else if (tileChar == 'J' or tileChar == 'L' or tileChar == 'Q' or tileChar == 'P' or tileChar == '4' or tileChar == '5') {
                shared_ptr<StickyWall> newTile = make_shared<StickyWall>(tilePosition);
                if (tileChar == 'L') {
                    newTile->getSprite()->setScale(Vector2f(-1, 1));
                    newTile->getSprite()->move(tileRes, 0);
                    newTile->setType("StickyWallL");
                }
                else if (tileChar == 'Q') {
                    newTile->getSprite()->setTexture(text.wallStickyBottomTileTexture);
                    newTile->setType("StickyWallR");
                }
                else if (tileChar == 'P') {
                    newTile->getSprite()->setTexture(text.wallStickyBottomTileTexture);
                    newTile->getSprite()->setScale(Vector2f(-1, 1));
                    newTile->getSprite()->move(tileRes, 0);
                    newTile->setType("StickyWallL");
                }
                else if (tileChar == '4') {
                    newTile->getSprite()->setTexture(text.wallStickyBottomTileTexture);
                    newTile->getSprite()->setScale(Vector2f(1, -1));
                    newTile->getSprite()->move(0, tileRes);
                    newTile->setType("StickyWallR");
                }
                else if (tileChar == '5') {
                    newTile->getSprite()->setTexture(text.wallStickyBottomTileTexture);
                    newTile->getSprite()->setScale(Vector2f(-1, -1));
                    newTile->getSprite()->move(tileRes, tileRes);
                    newTile->setType("StickyWallL");
                }
                //color
                if (levelsColors[getCurrentMap()]) {
                    newTile->getSprite()->setColor(Color(150, 195, 170));
                }
                else {
                    newTile->getSprite()->setColor(Color(135, 100, 190));
                }
                tileMap.push_back(newTile);
            }

            //platform floor
            else if (tileChar == 'T' or tileChar == 'z' or tileChar == 'p' or tileChar == 'q' or tileChar == '8' or tileChar == '6' or tileChar == '9') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                newTile->getSprite()->setTexture(text.floorTileTexture);
                if (tileChar == 'z') {
                    newTile->getSprite()->setTexture(text.floorMiddleTileTexture);
                }
                if (tileChar == 'p') {
                    newTile->getSprite()->setTexture(text.floorEndTileTexture);
                }
                if (tileChar == 'q') {
                    newTile->getSprite()->setTexture(text.floorEndTileTexture);
                    newTile->getSprite()->setScale(Vector2f(-1, 1));
                    newTile->getSprite()->move(tileRes, 0);
                }
                if (tileChar == '8' or tileChar == '6' or tileChar == '9') {
                    newTile->getSprite()->setTexture(text.floorMiddleTileTexture);
                    newTile->isMoving = true;
                    newTile->waypoints = { tilePosition, tilePosition + Vector2f(tileRes, 0) * 8.f };
                    newTile->currentWaypoint = 1;
                    if (tileChar == '6' or tileChar == '9') {
                        newTile->getSprite()->setTexture(text.floorEndTileTexture);
                        if (tileChar == '9') {
                            newTile->getSprite()->setOrigin(tileRes, 0);
                            newTile->getSprite()->setScale(-1, 1);
                            
                        }
                    }
                }
                tileMap.push_back(newTile);
            }
            //platform base
            else if (tileChar == 'v') {
                shared_ptr<Tile> newTile = make_shared<Tile>(tilePosition);
                newTile->getSprite()->setTexture(text.wallPlainTileTexture);
                tileMap.push_back(newTile);

                if (levelsColors[getCurrentMap()]) {
                    newTile->getSprite()->setColor(Color(150, 195, 170));
                }
                else {
                    newTile->getSprite()->setColor(Color(135, 100, 190));
                }
            }
            //Climable Tiles
            else if (tileChar == 'l')
            {
                shared_ptr<ClimbTile> newTile = make_shared<ClimbTile>(tilePosition);
                newTile->getSprite()->setTexture(text.climbTileTexture);
                tileMap.push_back(newTile);

            }
            //spawnpoint
            else if (tileChar == '$') {
                player.entitySprite.setPosition(tilePosition + Vector2f(tileRes / 2, 0));
                manager->getAllPets()[0]->entitySprite.setPosition(player.entitySprite.getPosition().x + 10, player.entitySprite.getPosition().y - 25);
            }

            else if (tileChar == '&') {
                shared_ptr<Door> newTile = make_shared<Door>(tilePosition);
                tileMap.push_back(newTile);
            }

            //mobSpawn

            else if (tileChar == 'm')
            {
				manager->createMedusa(tilePosition, text.medusaPhase1Text, 200.f, 81);
            }
            
			else if (tileChar == 'C')
			{
				manager->createCrabe(tilePosition + Vector2f(16,16), text.crabeText, 75.f, 1, tilePosition.x - 32 * 6, tilePosition.x);
			}

            else if (tileChar == 'y')
            {
				manager->createHippocampe(tilePosition + Vector2f(16, 5), text.hippocampesText, 0.f, 1, "RIGHT");
            }
            else if (tileChar == 'Y')
            {
                manager->createHippocampe(tilePosition + Vector2f(16, 5), text.hippocampesText, 0.f, 1, "LEFT");
            }
            else if (tileChar == 'n') {
                manager->createPoissonGlobe(tilePosition + Vector2f(16, 22), text.poissonGlobeIdleText, 0.f, 1, "RIGHT");
            }
            else if (tileChar == 'N') {
                manager->createPoissonGlobe(tilePosition + Vector2f(16, 22), text.poissonGlobeIdleText, 0.f, 1, "LEFT");
            }
            else if (tileChar == 'o') {
				manager->createMoney(tilePosition, text.monnaieTexture, 1);
            }

            tilePosition.x += tileRes;
        }
        tilePosition.y += tileRes;
        tilePosition.x = 0;
    }
}


int Map::getCurrentMap() {
    return currentMap;
}

void Map::setCurrentMap(int value) {
    currentMap = value;
}

vector<string> Map::getLevels()
{
    return levels;
}

vector<bool> Map::getLevelsColors()
{
    return levelsColors;
}

void Map::setLevels(vector<string> value, vector<bool> colors)
{
    levels = value;
    levelsColors = colors;
}

Map mapReference;
vector<shared_ptr<Tile>> tileMap;
