#include "DamageBlockManager.h"
#include "DamageBlock.h"
#include "Health.h"
#include "SVGParser.h"
#include "utils.h"
#include "Avatar.h"
#include "Camera.h"

DamageBlockManager::~DamageBlockManager()
{
	for (DamageBlock* block : m_pItems)
	{
		DeleteBlock(block);
	}
}

DamageBlock* DamageBlockManager::AddItem(const Point2f& bottomLeft)
{
	m_pItems.push_back(new DamageBlock(bottomLeft.x, bottomLeft.y));
	return m_pItems.back();
}

bool DamageBlockManager::Initialize(const std::string& filePath)
{
	std::vector<std::vector<Point2f>> vertices;
	SVGParser::GetVerticesFromSvgFile(filePath, vertices);

	if (vertices[0].empty()) return false;

	const int blockSize{ 8 };
	for (std::vector<Point2f> polygon : vertices)
	{
		const float width = utils::GetDistance(polygon[2], polygon[3]);
		const float height = utils::GetDistance(polygon[1], polygon[2]);

		for (size_t i = 0; i < height / blockSize; i++)
		{
			for (size_t j = 0; j < width / blockSize; j++)
			{
				const Point2f bottomLeft
				{
					polygon[3].x + (blockSize * j),
					polygon[3].y + (blockSize * i)
				};

				AddItem(bottomLeft);
			}
		}
	}

	return true;
}

void DamageBlockManager::Draw() const
{
	for (DamageBlock* block : m_pItems)
	{
		block->Draw();
	}
}

void DamageBlockManager::Update(Avatar& playerAvatar)
{
	for (DamageBlock* block : m_pItems)
	{
		block->Update();
	}

	PlayerCollisionCheck(playerAvatar);
}

void DamageBlockManager::PlayerCollisionCheck(Avatar& playerAvatar)
{
	for (DamageBlock* block : m_pItems)
	{
		if (block->IsOverlapping(playerAvatar.GetShape()))
		{
			playerAvatar.TakeDamage(1);

		}
	}
}

void DamageBlockManager::DeleteBlock(const DamageBlock* block) const
{
	delete block;
	block = nullptr;
}
