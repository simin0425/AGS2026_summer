#pragma once
#include <memory>
#include <list>
#include "Common/Collider2D.h"
#include "Common/Object2D.h"

class ResourceManager;
class SceneManager;
class Collider2D;
class Object2D;

class ActorBase2D : public std::enable_shared_from_this<ActorBase2D>
{
public:
	// コンストラクタ
	ActorBase2D();

	// デストラクタ
	~ActorBase2D();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const Object2D& GetObject2D() const;

protected:
	// シングルトン参照
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// オブジェクトの基本情報
	Object2D object2D_;

	// 衝突判定を取る相手のコライダ
	std::list<std::weak_ptr<Collider2D>> awayColliders_;

};
