#pragma once
#include <vector>
#include "../../Common/Geometry.h"

class Object2D
{
public:
	Object2D() = default;
	Object2D(int image_id);
	Object2D(std::vector<int> image_ids);

	void Release();

	int handleId;
	std::vector<int> handleIds;

	Vector2 position;
	double scale;
	double rotation;

};
