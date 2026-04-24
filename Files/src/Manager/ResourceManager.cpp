#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
}

ResourceManager& ResourceManager::GetInstance()
{
	return *instance_;
}

void ResourceManager::DeleteInstance()
{
	if (instance_ == nullptr) return;

	instance_->Release();
	for (auto& res : instance_->resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	instance_->resourcesMap_.clear();

	delete instance_;
	instance_ = nullptr;
}

void ResourceManager::Init()
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;

	Resource* res;

	// タイトルロゴ
	res = new RES(RES_T::IMAGE, Application::PATH_IMAGE + "Title.png");
	resourcesMap_.emplace(SRC::TITLE_LOGO, res);

	// プレイヤー自機
	res = new RES(RES_T::IMAGE, Application::PATH_IMAGE + "Player1.png");
	resourcesMap_.emplace(SRC::PLAYER1, res);
	res = new RES(RES_T::IMAGE, Application::PATH_IMAGE + "Player2.png");
	resourcesMap_.emplace(SRC::PLAYER2, res);
}

void ResourceManager::Release()
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager()
{
}

Resource& ResourceManager::_Load(SRC src)
{
	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
