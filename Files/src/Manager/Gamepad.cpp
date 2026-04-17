#include <DxLib.h>
#include "Gamepad.h"

Gamepad::Gamepad(int pad_num)
	:
	PAD_NUM(pad_num)
{
	nowButton_.fill(0);
	prevButton_.fill(0);
}

Gamepad::~Gamepad()
{
}

void Gamepad::Update()
{
	// DirectInput
	DINPUT_JOYSTATE dIn = {};
	GetJoypadDirectInputState(PAD_NUM, &dIn);

	// XInput（XBOX対応コントローラー専用）
	XINPUT_STATE xIn = {};
	bool xFlg = CheckJoypadXInput(PAD_NUM) ? true : false;
	if (xFlg) GetJoypadXInputState(PAD_NUM, &xIn);

	// 更新
	prevButton_ = nowButton_;
	nowButton_.fill(0);

	// 左スティック
	if (!xFlg)
	{ // DirectInput
		// X軸
		if (dIn.X < 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_L] = abs(dIn.X);
		else if (dIn.X > 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_R] = abs(dIn.X);
		// Y軸
		if (dIn.Y > 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_U] = abs(dIn.Y);
		else if (dIn.Y < 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_D] = abs(dIn.Y);
	}
	else
	{ // XInput
		// X軸
		if (xIn.ThumbLX < 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_L] = (int)abs(xIn.ThumbLX * XINPUT_STICK_MULT);
		else if (xIn.ThumbLX > 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_R] = (int)abs(xIn.ThumbLX * XINPUT_STICK_MULT);
		// Y軸
		if (xIn.ThumbLY > 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_U] = (int)abs(xIn.ThumbLY * XINPUT_STICK_MULT);
		else if (xIn.ThumbLY < 0)
			nowButton_[(int)RAW_BUTTON::LSTICK_D] = (int)abs(xIn.ThumbLY * XINPUT_STICK_MULT);
	}

	// 右スティック
	if (!xFlg)
	{ // DirectInput
		// DirectInputは、右スティック専用のパラメーターを持たない（RxやRyなどは本来、スティックの回転量である）ため
		// ここに記述してあるプログラムでは反応しない場合がある

		// X軸
		if (dIn.Rx < 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_L] = abs(dIn.Rx);
		else if (dIn.X > 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_R] = abs(dIn.Rx);
		// Y軸
		if (dIn.Ry > 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_U] = abs(dIn.Ry);
		else if (dIn.Ry < 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_D] = abs(dIn.Ry);
	}
	else
	{ // XInput
		// X軸
		if (xIn.ThumbRX < 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_L] = (int)abs(xIn.ThumbRX * XINPUT_STICK_MULT);
		else if (xIn.ThumbRX > 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_R] = (int)abs(xIn.ThumbRX * XINPUT_STICK_MULT);
		// Y軸
		if (xIn.ThumbRY < 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_U] = (int)abs(xIn.ThumbRY * XINPUT_STICK_MULT);
		else if (xIn.ThumbRY > 0)
			nowButton_[(int)RAW_BUTTON::RSTICK_D] = (int)abs(xIn.ThumbRY * XINPUT_STICK_MULT);
	}

	// ハットスイッチ／十字キー
	if (dIn.POV[0] != 0xFFFFFFFFU)
	{
		/*
		// POVは、出力に弧度×100のunsigned int型1つを用いているため
		// 取り出した値を100で割った後、弧度からラジアンに変換すると良い
		double rad = DegToRad(static_cast<double>(dIn.POV[0]) / 100.0);
		// 計算時の誤差に対するマージン
		double margin = 0.01;

		// 本来はx = cos、y = sinだが、0が上から始まるので
		// cosとsinを入れ替えた方が良い
		double sinRet = sin(rad);
		double cosRet = cos(rad);

		// X軸
		if (sinRet < margin)
			nowButton_[(int)RAW_BUTTON::DPAD_L] = 1;
		else if (sinRet > margin)
			nowButton_[(int)RAW_BUTTON::DPAD_R] = 1;
		// Y軸
		if (cosRet > margin)
			nowButton_[(int)RAW_BUTTON::DPAD_U] = 1;
		else if (cosRet < margin)
			nowButton_[(int)RAW_BUTTON::DPAD_D] = 1;
		*/

		// 上の処理が上手く行かないため、代わりの処理
		switch (dIn.POV[0] / 100u) {
		case 0u:
			nowButton_[(int)RAW_BUTTON::DPAD_U] = 1;
			break;
		case 45u:
			nowButton_[(int)RAW_BUTTON::DPAD_R] = 1;
			nowButton_[(int)RAW_BUTTON::DPAD_U] = 1;
			break;
		case 90u:
			nowButton_[(int)RAW_BUTTON::DPAD_R] = 1;
			break;
		case 135u:
			nowButton_[(int)RAW_BUTTON::DPAD_R] = 1;
			nowButton_[(int)RAW_BUTTON::DPAD_D] = 1;
			break;
		case 180u:
			nowButton_[(int)RAW_BUTTON::DPAD_D] = 1;
			break;
		case 225u:
			nowButton_[(int)RAW_BUTTON::DPAD_L] = 1;
			nowButton_[(int)RAW_BUTTON::DPAD_D] = 1;
			break;
		case 270u:
			nowButton_[(int)RAW_BUTTON::DPAD_L] = 1;
			break;
		case 315u:
			nowButton_[(int)RAW_BUTTON::DPAD_L] = 1;
			nowButton_[(int)RAW_BUTTON::DPAD_U] = 1;
			break;
		}
	}

	// Buttons（ボタン）
	if (!xFlg)
	{ // DirectInput
		// 最大32ボタン
		for (int index = 0; index <= (int)RAW_BUTTON::BUTTON_31 - (int)RAW_BUTTON::BUTTON_0; index++)
			nowButton_[(int)RAW_BUTTON::BUTTON_0 + index] = dIn.Buttons[index];
	}
	else
	{ // XInput
		// 最大12ボタン＋ハットスイッチ
		for (int index = 0; index <= (int)RAW_BUTTON::BUTTON_11 - (int)RAW_BUTTON::BUTTON_0; index++)
			nowButton_[(int)RAW_BUTTON::BUTTON_0 + index] = dIn.Buttons[index];

		// トリガーを余った領域に割り当て
		nowButton_[(int)RAW_BUTTON::BUTTON_12] = xIn.LeftTrigger;
		nowButton_[(int)RAW_BUTTON::BUTTON_13] = xIn.RightTrigger;
	}
}

int Gamepad::NowButton(RAW_BUTTON b) const
{
	return nowButton_[(int)b];
}

int Gamepad::PrevButton(RAW_BUTTON b) const
{
	return prevButton_[(int)b];
}

bool Gamepad::DownButton(RAW_BUTTON b) const
{
	return NowButton(b) && !PrevButton(b);
}

bool Gamepad::UpButton(RAW_BUTTON b) const
{
	return !NowButton(b) && PrevButton(b);
}