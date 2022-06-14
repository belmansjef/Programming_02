#pragma once
#include <vector>

struct Point2f;
class Particle;

class ParticleSystem final
{
public:
	ParticleSystem(int numParticles);
	~ParticleSystem();

	ParticleSystem(const ParticleSystem& other) = delete;
	ParticleSystem& operator=(const ParticleSystem& other) = delete;
	ParticleSystem(ParticleSystem&& other) = delete;
	ParticleSystem& operator=(ParticleSystem&& other) = delete;

	bool IsPlaying() const;

	void PlayAtPos(const Point2f& pos);
	void Stop();

	void Initialize(const Point2f& minVelocity, const Point2f& maxVelocity, const Point2f& startSizeRange, const Point2f& endSizeRange, const Point2f& lifetimeRange);
	void Update();
	void Draw() const;

private:
	bool m_IsPlaying;
	std::vector<Particle*> m_pParticles;
};