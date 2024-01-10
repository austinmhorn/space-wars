#ifndef Animation_hpp
#define Animation_hpp

#include <iostream>           // std::cout, std::cin
#include <vector>             // std::vector
#include <cmath>

struct Frame
{
   sf::IntRect rect;
   double duration; // in seconds
};

class Animation
{
private:
    std::vector<Frame> frames;
    std::vector<Frame>::iterator iter;
    double totalLength;
    double totalProgress;
    sf::Sprite *target;
    bool repeat;
public:
    Animation(bool loop = false)
    {
        this->target = nullptr;
        totalProgress = 0.0;
        repeat = loop;
    }
    Animation(sf::Sprite& target, bool loop = false)
    {
        this->target = &target;
        totalProgress = 0.0;
        repeat = loop;
    }

    void addFrame(Frame&& frame)
    {
        frames.push_back(std::move(frame));
        totalLength += frame.duration;
    }

    void setRepeat(bool loop)
    {
        repeat = loop;
    }

    void reset()
    {
        target->setTextureRect(frames.begin()->rect);
        totalProgress = 0.0;
    }

    bool complete() const
    {
        return target->getTextureRect().left == frames.back().rect.left;
    }

    double currentFrameTime()
    {
        return (*iter).duration * std::round(totalProgress / (*iter).duration);
    }

    void update(double elapsed)
    {
        totalProgress += elapsed;
        double progress = totalProgress;
        for(this->iter = frames.begin(); iter != frames.end(); iter++)
        {
            progress -= (*iter).duration;

            if ( repeat  &&  (progress + totalLength/frames.size()) > totalLength )
                totalProgress = 0.f;

            if (progress <= 0.0 || iter == frames.end())
            {
                target->setTextureRect((*iter).rect);
                break; 
            }
        }
    }
};

#endif /* Animation_hpp */