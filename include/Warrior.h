#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"

class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Clean();  
        virtual void Update(float dt);

        void Log();

    private:
        Animation* m_Animation;
        
};

#endif