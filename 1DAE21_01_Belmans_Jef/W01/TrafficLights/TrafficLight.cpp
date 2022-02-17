#include "TrafficLight.h"
#include "utils.h"

TrafficLight::TrafficLight(const Point2f& pos)
    : m_Position{ pos }
    , m_State{ State::off }
{
}

void TrafficLight::Update(float elapsedSec)
{
    TrafficLight::m_AccumulatedSec += elapsedSec;

    switch (m_State)
    {
    case TrafficLight::State::green:
        if (TrafficLight::m_AccumulatedSec >= 4.0f)
        {
            m_State = State::orange;
            TrafficLight::m_AccumulatedSec = 0.0f;
        }
        break;
    case TrafficLight::State::orange:
        if (TrafficLight::m_AccumulatedSec >= 1.0f)
        {
            m_State = State::red;
            TrafficLight::m_AccumulatedSec = 0.0f;
        }
        break;
    case TrafficLight::State::red:
        if (TrafficLight::m_AccumulatedSec >= 4.0f)
        {
            m_State = State::green;
            TrafficLight::m_AccumulatedSec = 0.0f;
        }
        break;
    }
}

void TrafficLight::DoHitTest(const Point2f& point) const
{
    if (utils::IsOverlapping(point,))
    {

    }
}

float TrafficLight::GetWidth() const
{
    return TrafficLight::m_Armature.width;
}

float TrafficLight::GetHeight() const
{
    return TrafficLight::m_Armature.height;
}
