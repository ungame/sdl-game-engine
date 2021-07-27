#include "SequenceAnimation.h"
#include "Animation.h"
#include "TextureManager.h"

#include "../Vendor/TinyXML/tinyxml.h"
#include <SDL2/SDL.h>

SequenceAnimation::SequenceAnimation(bool repeat) : Animation(repeat) {}

void SequenceAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip)
{
    std::string textureID = m_CurrentSequence.TextureIDs[m_CurrentFrame];
    int width = m_CurrentSequence.Width;
    int height = m_CurrentSequence.Height;
    TextureManager::GetInstance()->Draw(textureID, x, y, width, height, xScale, yScale, 0.0, flip);
}

void SequenceAnimation::Update(float dt)
{
    if ( m_Repeat || !m_IsEnded )
    {
        m_IsEnded = false;
        m_CurrentFrame = ( SDL_GetTicks() / m_CurrentSequence.Speed ) % m_CurrentSequence.FrameCount;
    }

    if ( !m_Repeat && m_CurrentFrame == (m_CurrentSequence.FrameCount - 1) )
    {
        m_IsEnded = true;
        m_CurrentFrame = (m_CurrentSequence.FrameCount - 1);
    }
}

void SequenceAnimation::SetCurrentSequence(std::string seqID)
{
    if( m_SeqMap.count(seqID) > 0 )
    {
        m_CurrentSequence = m_SeqMap[seqID];
    }
    else
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "The given Sequence animation is not matching: %s", seqID.c_str());
    }
}

void SequenceAnimation::Parse(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if ( xml.Error() )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load animation file: %s", source.c_str());
        return;
    }

    TiXmlElement* root = xml.RootElement();

    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {

        if ( e->Value() == std::string("sequence") )
        {
            Sequence sequence;
            std::string seqID = e->Attribute("id");
            e->Attribute("speed", &sequence.Speed);
            e->Attribute("width", &sequence.Width);
            e->Attribute("height", &sequence.Height);
            e->Attribute("frameCount", &sequence.FrameCount);

            for(TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
            {
                sequence.TextureIDs.push_back(frame->Attribute("textureID"));
            }

            SDL_Log("Sequence: Id=%s, FrameCount=%d, Width=%d, Height=%d, Speed=%d", seqID.c_str(), sequence.FrameCount, sequence.Width, sequence.Height, sequence.Speed);

            m_SeqMap[seqID] = sequence;
        }
    }
}