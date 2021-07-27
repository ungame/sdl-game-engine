#ifndef SEQUENCEANIMATION_H
#define SEQUENCEANIMATION_H

#include "Animation.h"

#include <string>
#include <vector>
#include <map>

#include <SDL2/SDL.h>

struct Sequence
{
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureIDs;
};

class SequenceAnimation : public Animation
{
    public:
        SequenceAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Parse(std::string source);
        void SetCurrentSequence(std::string seqID);
        void SetRepeat(bool repeat) { m_Repeat = repeat; }
        void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSequence;
        std::map<std::string, Sequence> m_SeqMap;
};

#endif 