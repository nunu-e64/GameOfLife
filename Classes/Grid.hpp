//
//  Grid.hpp
//  GameOfLife
//
//  Created by Fumiya Amano on 2016/04/25.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "cocos2d.h"
#include "Creature.hpp"

class Grid : public cocos2d::Node
{
public:
    CREATE_FUNC(Grid);
    
    bool init() override;
    
    void onEnter() override;
    
    void evolveStep();
    
    int getGenerationCount();
    
    int getPopulationCount();
    
protected:
    int generationCount;
    int populationCount;
    float cellWidth;
    float cellHeight;
    cocos2d::Vector<Creature*> gridArray;
    
    void setupGrid();
    void setupTouchHandling();
    void updateNeighborCount();
    void updateCreatures();
    Creature* creatureForTouchLocation(cocos2d::Vec2 touchLocation);
    bool isValidIndex(int row, int col);
    int indexForRowColumn(int row, int col);
};
#endif /* Grid_hpp */
