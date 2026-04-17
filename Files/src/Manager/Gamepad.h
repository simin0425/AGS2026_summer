#pragma once
#include <array>

class Gamepad
{
public:
	// àÍó•Ç≈ãKäiâªÇµÇΩê∂ÇÃÉ{É^Éìì¸óÕ
	enum class RAW_BUTTON
	{
		NONE,

		LSTICK_L,
		LSTICK_R,
		LSTICK_U,
		LSTICK_D,

		RSTICK_L,
		RSTICK_R,
		RSTICK_U,
		RSTICK_D,

		DPAD_L,
		DPAD_R,
		DPAD_U,
		DPAD_D,

		BUTTON_0,
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
		BUTTON_9,
		BUTTON_10,
		BUTTON_11,
		BUTTON_12,
		BUTTON_13,
		BUTTON_14,
		BUTTON_15,
		BUTTON_16,
		BUTTON_17,
		BUTTON_18,
		BUTTON_19,
		BUTTON_20,
		BUTTON_21,
		BUTTON_22,
		BUTTON_23,
		BUTTON_24,
		BUTTON_25,
		BUTTON_26,
		BUTTON_27,
		BUTTON_28,
		BUTTON_29,
		BUTTON_30,
		BUTTON_31,

		END
	};

	using BUTTON_STATE_ARRAY = std::array<int, (size_t)RAW_BUTTON::END>;

	Gamepad(int pad_num);
	~Gamepad();

	void Update();

	int NowButton(RAW_BUTTON) const;
	int PrevButton(RAW_BUTTON) const;
	bool DownButton(RAW_BUTTON) const;
	bool UpButton(RAW_BUTTON) const;

private:
	static constexpr double XINPUT_STICK_MULT = 1000.0 / (short)0x7fff;

	const int PAD_NUM;

	BUTTON_STATE_ARRAY nowButton_;
	BUTTON_STATE_ARRAY prevButton_;

};

