//
//  Creature.hpp
//  GameOfLife
//
//  Created by Fumiya Amano on 2016/04/25.
//
//

#ifndef Creature_hpp
#define Creature_hpp

class Creature : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Creature);
    
    bool init() override;

    void setLivingNeighborsCount(int livingNeighborsCount);
    int getLivingNeighborsCount();
    
    void setIsAlive(bool isAlive);
    bool getIsAlive();
protected:
    int livingNeighborsCount;
    bool isAlive;
    
};

#endif /* Creature_hpp */
