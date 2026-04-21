#pragma once
#include <memory>
#include "Common/Object2D.h"

class ResourceManager;
class SceneManager;

class ActorBase2D : public std::enable_shared_from_this<ActorBase2D>
{
public:
	// コンストラクタ
	ActorBase2D();

	// デストラクタ
	virtual ~ActorBase2D();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const Object2D& GetObject() const;

protected:
	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// オブジェクトの基本情報
	Object2D object2D_;

};
