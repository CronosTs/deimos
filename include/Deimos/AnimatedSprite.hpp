
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
            void SetDelay(float); // time between frames
            void SetTexture(TexturePtr_t&);
            void SetTexture(const Phobos::String_t&);
            void Reset(); //reset fo frame 0 of the current animation
            void PlayAnimation(bool playAnim = true);
            void LoadAnimation(const Phobos::String_t&);
            
            inline void SetVisible(bool visible = true)
            {
                m_visible = visible;
            }

            inline void SetReverseMode(bool reverseMode = true)
            {
                m_reverse = reverseMode;
            }

            inline float GetDelay()
            {
                return m_delay;
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
            
            bool m_visible,
                 m_playAnim,
                 m_reverse;
            float m_delay;
            int m_currentFrame;

            //we store just the name and the indices. The frames will be in
            //the mesh.
            std::map<Phobos::String_t, std::vector<int>> m_animations;
            Mesh m_mesh;
            TexturePtr_t m_texture;
            Phobos::String_t m_currentAnimation;
            Phobos::System::Timer m_timer;
            
    };
}

#endif