
#ifndef DEIMOS_ANIMATED_SPRITE_H_INCLUDED
#define DEIMOS_ANIMATED_SPRITE_H_INCLUDED

#include "Mesh.hpp"
#include "Texture.hpp"

#include <Phobos/BaseAPI.h>
#include <Phobos/String.h>
#include <Phobos/Types.h>
#include <Phobos/System/Timer.h>

#include <map>
#include <vector>
#include <memory>

namespace deimos
{
    class PH_BASE_API AnimatedSprite
    {
        public:

            //frame is relative to texture
            typedef Phobos::Rect_s<float> Frame;
            typedef std::vector<Frame> Animation;
            typedef std::map<Phobos::String_t, Animation> Animations;
            typedef std::shared_ptr<Texture> TexturePtr_t;

            AnimatedSprite();
            ~AnimatedSprite();

            void Draw();
            void Update();
            void SetCurrentAnimation(const Phobos::String_t&);
            void SetCurrentFrame(int); //unsigned ?
            void SetAnimations(const Animations&);
            void SetTime(float); // time between frames
            void SetTexture(TexturePtr_t&);
            void SetTexture(const Phobos::String_t&);

            inline float GetCurrentTime()
            {
                return m_time;
            }

            inline int GetCurrentFrame()
            {
                return m_currentFrame;
            }

            inline const Phobos::String_t& GetCurrentAnimation()
            {
                return m_currentAnimation;
            }

            inline const TexturePtr_t GetTexture()
            {
                return m_texture;
            }

        private:

            std::vector<Vertex> FrameToVertex(Frame& frame);

            //we store just the name and the indices. The frames will be in
            //the mesh.
            std::map<Phobos::String_t, std::vector<int>> m_animations;
            Mesh m_mesh;
            TexturePtr_t m_texture;
            float m_time; //time between frames
            int m_currentFrame;
            Phobos::String_t m_currentAnimation;
            Phobos::System::Timer m_timer;

    };
}

#endif