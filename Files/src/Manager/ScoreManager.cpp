#include "ScoreManager.h"

ScoreManager* ScoreManager::instance_ = nullptr;

ScoreManager::ScoreManager(int pad_max)
{
	scores_.resize(pad_max + 1, 0);
	prevScores_.resize(pad_max + 1, 0);
	extendReserve_.resize(pad_max + 1, 0);

	highScore_ = HIGH_SCORE_INIT;
	extend1st_ = EXTEND_1ST_INIT;
	extend2nd_ = EXTEND_2ND_INIT;
	extendEvery_ = EXTEND_EVERY_INIT;
}

bool ScoreManager::Init()
{
	return true;
}

bool ScoreManager::Update()
{
	bool ret = false;
	for (size_t i = 1; i < scores_.size(); ++i)
	{
		if (ScoreCheck(i)) ret = true;
	}
	return ret;
}

void ScoreManager::Reset()
{
	for (size_t i = 0; i < scores_.size(); ++i)
		scores_[i] = 0;
}

bool ScoreManager::Release()
{
	return true;
}

void ScoreManager::AddScore(size_t index, unsigned int score)
{
	if (index >= scores_.size()) return;

	scores_[index] += score;

	ScoreCheck(index);
}

unsigned int ScoreManager::GetScore(size_t index) const
{
	if (index >= scores_.size()) return 0;

	return scores_[index];
}

unsigned int ScoreManager::GetHighScore() const
{
	return highScore_;
}

void ScoreManager::SetExtendScore(unsigned int first, unsigned int second, unsigned int every)
{
	extend1st_ = first;
	extend2nd_ = second;
	extendEvery_ = every;
}

bool ScoreManager::ScoreCheck(size_t index)
{
	if (index >= scores_.size()) return false;

	bool ret = false;

	if (scores_[index] > SCORE_MAX) scores_[index] = SCORE_MAX;

	if (scores_[index] > highScore_) highScore_ = scores_[index];

	{
		if (prevScores_[index] < extend1st_ && scores_[index] >= extend1st_)
		{
			extendReserve_[index]++;
			ret = true;
		}

		if (prevScores_[index] < extend2nd_ && scores_[index] >= extend2nd_)
		{
			extendReserve_[index]++;
			ret = true;
		}

		int n1 = (prevScores_[index] - extend2nd_) / extendEvery_;
		int n2 = (scores_[index] - extend2nd_) / extendEvery_;
		int res = n2 - n1;
		if (res > 0)
		{
			extendReserve_[index] += res;
			ret = true;
		}
	}

	prevScores_[index] = scores_[index];

	return ret;
}
