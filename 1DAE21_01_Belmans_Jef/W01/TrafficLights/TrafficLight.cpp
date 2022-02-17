#include "TrafficLight.h"
#include "utils.h"

TrafficLight::TrafficLight(const Point2f& pos)
    : m_Position{ pos }
    , m_State{ State::off }
    , m_AccumulatedSec{ 0.0f }
    , m_pArmature{new Rectf(m_Position.x, m_Position.y, 100.0f, 300.0f)}
    , m_pGreenLight{new Circlef(m_Position.x + 50.0f, m_Position.y + 50.0f, 80.0f)}
    , m_pOrangeLight{new Circlef(m_Position.x + 50.0f, m_Position.y + 150.0f, 80.0f)}
    , m_pRedLight{new Circlef(m_Position.x + 50.0f, m_Position.y + 250.0f, 80.0f)}
{
}

void TrafficLight::Update(float elapsedSec)
{
    m_AccumulatedSec += elapsedSec;

    switch (m_State)
    {
    case TrafficLight::State::green:
        if (m_AccumulatedSec >= 4.0f)
        {
            m_State = State::orange;
            m_AccumulatedSec = 0.0f;
        }
        break;
    case TrafficLight::State::orange:
        if (m_AccumulatedSec >= 1.0f)
        {
            m_State = State::red;
            m_AccumulatedSec = 0.0f;
        }
        break;
    case TrafficLight::State::red:
        if (m_AccumulatedSec >= 4.0f)
        {
            m_State = State::green;
            m_AccumulatedSec = 0.0f;
        }
        break;
    }
}

void TrafficLight::Draw()
{
    utils::SetColor(Color4f(0.2f, 0.2f, 0.2f, 1.0f));
    utils::DrawRect(*m_pArmature, 5.0f);

    switch (m_State)
    {
    case TrafficLight::State::green:
        utils::SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
        break;
    case TrafficLight::State::orange:
        break;
    case TrafficLight::State::red:
        break;
    case TrafficLight::State::off:
        break;
    default:
        break;
    }
}

void TrafficLight::DoHitTest(const Point2f& point)
{
    const Rectf mouseRect
    {
        point.x - 5.0f,
        point.y - 5.0f,
        10.0f,
        10.0f
    };

    if (utils::IsOverlapping(mouseRect, *m_pGreenLight))
    {
        m_State = State::green;
        m_AccumulatedSec = 0.0f;
    }
    else if (utils::IsOverlapping(mouseRect, *m_pOrangeLight))
    {
        m_State = State::orange;
        m_AccumulatedSec = 0.0f;
    }
    else if (utils::IsOverlapping(mouseRect, *m_pRedLight))
    {
        m_State = State::red;
        m_AccumulatedSec = 0.0f;
    }
    else if (utils::IsOverlapping(mouseRect, *m_pArmature))
    {
        m_State = State::off;
        m_AccumulatedSec = 0.0f;
    }
}

float TrafficLight::GetWidth() const
{
    return TrafficLight::m_pArmature.width;
}

float TrafficLight::GetHeight() const
{
    return TrafficLight::m_pArmature.height;
}
