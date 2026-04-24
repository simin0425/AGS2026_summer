#pragma once
#include <string>
#include <vector>

class ScoreManager
{
public:
	static void CreateInstance(int pad_max) { if (instance_ == nullptr) instance_ = new ScoreManager(pad_max); }
	static ScoreManager& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

private:
	static ScoreManager* instance_;

	ScoreManager(int pad_max);
	~ScoreManager() {}

	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
	ScoreManager(ScoreManager&&) = delete;
	ScoreManager& operator=(ScoreManager&&) = delete;

public:
	bool Init();
	bool Update();
	void Reset();
	bool Release();

	void AddScore(size_t index, unsigned int score);
	unsigned int GetScore(size_t index) const;
	std::string GetScoreText(size_t index) const;
	unsigned int GetHighScore() const;
	void SetExtendScore(unsigned int first = EXTEND_1ST_INIT, unsigned int second = EXTEND_2ND_INIT, unsigned int every = EXTEND_EVERY_INIT);

private:
	static constexpr unsigned int SCORE_MAX = 99999999;
	static constexpr unsigned int SCORE_MIN_DIGIT = 2;

	static constexpr unsigned int EXTEND_1ST_INIT = 20000;
	static constexpr unsigned int EXTEND_2ND_INIT = 50000;
	static constexpr unsigned int EXTEND_EVERY_INIT = 50000;
	static constexpr unsigned int HIGH_SCORE_INIT = 10000;

	std::vector<unsigned int> scores_;
	std::vector<unsigned int> prevScores_;
	std::vector<unsigned int> extendReserve_;

	unsigned int highScore_;

	unsigned int extend1st_;
	unsigned int extend2nd_;
	unsigned int extendEvery_;

	bool ScoreCheck(size_t index);

};

