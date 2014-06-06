#include "AnimatedSprite.hpp"

#include "GraphicDefs.hpp"

#include <Phobos/Register/Manager.h>
#include <Phobos/Register/Table.h>
#include <Phobos/Register/Hive.h>

#include <fstream>
#include <iostream>

namespace deimos
{
    AnimatedSprite::AnimatedSprite():
        m_visible(true),
        m_playAnim(true),
        m_reverse(false),
        m_time(0.5f),
        m_currentFrame(0)
    {
        m_timer.Reset();
    }

    AnimatedSprite::~AnimatedSprite()
    {}

    void AnimatedSprite::Draw()
    {
        if (!m_visible)
            return;

        auto meshIndex = m_animations[m_currentAnimation][m_currentFrame];
        m_mesh.Draw(Primitives::TRIANGLES, meshIndex*6, 6);
    }

    void AnimatedSprite::Update()
    {
        if (!m_playAnim)
            return;

        float elapsedTime = m_timer.Elapsed();

        if (m_timer.Elapsed() < m_time)
            return;

        //inc frames 
        if (m_reverse)
        {
            m_currentFrame--;
            if (m_currentFrame < 0)
                m_currentFrame = m_animations[m_currentAnimation].size()-1;
        }
        else
        {
            m_currentFrame++;
            if (m_currentFrame >= m_animations[m_currentAnimation].size())
                m_currentFrame = 0;
        }

        m_timer.Reset();
    }

    void AnimatedSprite::SetCurrentAnimation(const Phobos::String_t& anim)
    {
        m_currentAnimation = anim;
    }

    void AnimatedSprite::SetCurrentFrame(int frame)
    {
        m_currentFrame = frame;
    }

    void AnimatedSprite::SetAnimations(const Animations& anim)
    {
        if (anim.empty())
            return;

        if (!m_texture)
            return;

        //free space of old animations
        m_animations.clear();

        int index = 0;
        std::vector<Vertex> vertex;

        //for each animation
        for (auto animation : anim)
        {
            std::vector<int> indexVector;

            //for each frame
            for (auto frame : animation.second)
            {
                std::vector<Vertex> tmpVector = FrameToVertex(frame);
                std::copy(tmpVector.begin(), 
                          tmpVector.end(), 
                          std::back_inserter(vertex));

                indexVector.push_back(index);
                index++;
            }

            m_animations[animation.first] = indexVector;
        }

        m_mesh.SetVertexData(vertex);
        m_currentAnimation = m_animations.begin()->first;
    }

    void AnimatedSprite::SetTime(float time)
    {
        m_time = time;
    }

    void AnimatedSprite::SetTexture(TexturePtr_t& texture)
    {
        m_texture = texture;
    }

    void AnimatedSprite::SetTexture(const Phobos::String_t& img)
    {
        SetTexture(std::make_shared<Texture>(img));
    }

    void AnimatedSprite::Reset()
    {
        m_timer.Reset();
        m_currentFrame = 0;
    }

    void AnimatedSprite::PlayAnimation(bool playAnim)
    {
        m_playAnim = playAnim;
        m_timer.Reset();
    }

    void AnimatedSprite::LoadAnimation(const Phobos::String_t& file)
    {
        Phobos::Register::Init();

        std::ifstream ifs(file);
        Phobos::Register::Load(ifs);

        float frameWidth = 0,
              frameHeight = 0;
        //int startIndex = 0;
        auto &entityDef = Phobos::Register::GetTable("EntityDef", "InfoPlayerAnimation");
        
        frameWidth = entityDef.GetFloat("FrameWidth");
        frameHeight = entityDef.GetFloat("FrameHeight");
        //startIndex = entityDef.GetInt("StartIndex");
        SetTexture(entityDef.GetString("ImageFile"));

        auto &allEntity = Phobos::Register::GetHive("EntityDef");
        auto &nodes = allEntity.GetNodes();

        Animations animations;
        int framesPerWidth = m_texture->getWidth() / frameWidth;
        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            auto *table = static_cast<Phobos::Register::Table*>(i->second);
            if (table->GetString("Type").compare("animation") == 0)
            {
                //TODO: it can be turned into only one!!!
                if (table->TryGetString("Index"))
                {
                    //only one frame
                    int index = table->GetInt("Index"),
                        x = index % framesPerWidth,
                        y = index / framesPerWidth;

                    x *= frameWidth;
                    y *= frameHeight;

                    Frame frame(x, y, frameWidth, frameHeight);
                    animations[table->GetName()].push_back(frame);
                }
                else if (table->TryGetString("StartIndex") && 
                         table->TryGetString("EndIndex"))
                {
                    //more than one frame
                    int startIndex = table->GetInt("StartIndex"),
                        endIndex   = table->GetInt("EndIndex");

                    for (int index = startIndex; index <= endIndex; index++)
                    {
                        int x = index % framesPerWidth,
                            y = index / framesPerWidth;

                        x *= frameWidth;
                        y *= frameHeight;

                        Frame frame(x, y, frameWidth, frameHeight);
                        animations[table->GetName()].push_back(frame);
                    }
                }
            }
        }

        SetAnimations(animations);
        
        Phobos::Register::Finalize();
    }

    std::vector<Vertex> AnimatedSprite::FrameToVertex(Frame& frame)
    {
        /* t1          t2
             +--------+
             |        |
             |        |
             |        |
             +--------+
          t3           t4
        */

        Vertex t1, t2, t3, t4;
        float width  = m_texture->getWidth(), 
              height = m_texture->getHeight();

        t1.position.x = 0;
        t1.position.y = 0;
        t1.texture.x = frame.m_tOrigin[0] / width;
        t1.texture.y = frame.m_tOrigin[1] / height;

        t2.position.x = frame.m_tSize.m_tWidth;
        t2.position.y = 0;
        t2.texture.x = (frame.m_tOrigin[0] + frame.m_tSize.m_tWidth) / width;
        t2.texture.y = frame.m_tOrigin[1] / height;

        t3.position.x = 0;
        t3.position.y = frame.m_tSize.m_tHeight;
        t3.texture.x = frame.m_tOrigin[0] / width;
        t3.texture.y = (frame.m_tOrigin[1] + frame.m_tSize.m_tHeight) / height;

        t4.position.x = frame.m_tSize.m_tWidth;
        t4.position.y = frame.m_tSize.m_tHeight;
        t4.texture.x = (frame.m_tOrigin[0] + frame.m_tSize.m_tWidth) / width;
        t4.texture.y = (frame.m_tOrigin[1] + frame.m_tSize.m_tHeight) / height;

        std::vector<Vertex> meshVector;
        meshVector.reserve(4);
        //first triangle
        meshVector.push_back(t1);
        meshVector.push_back(t3);
        meshVector.push_back(t4);
        //second triangle
        meshVector.push_back(t1);
        meshVector.push_back(t4);
        meshVector.push_back(t2);

        return meshVector;
    }
}