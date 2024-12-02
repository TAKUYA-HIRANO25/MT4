#include <Novice.h>
#include <iostream>
#include <cmath>

const char kWindowTitle[] = "LE2C_19_ヒラノ＿タクヤ";

struct Vector3 {
	float x, y, z;
};

struct Quaternion {
	float x, y, z, w;
};

struct Matrix4x4 {
	float m[4][4];
};

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	Quaternion result;
	// 回転角度の半分を計算
	float halfAngle = angle * 0.5f;

	// sin(半分の角度) と cos(半分の角度) を計算
	float sinHalfAngle = sinf(halfAngle);
	float cosHalfAngle = cosf(halfAngle);

	// クォータニオンの成分を計算
	result.x = axis.x * sinHalfAngle;
	result.y = axis.y * sinHalfAngle;
	result.z = axis.z * sinHalfAngle;
	result.w = cosHalfAngle;

	return result;
}


Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t) {
	float dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	Quaternion aq0 = q1;
	if (dot < 0) {
		aq0.x = -q1.x;
		aq0.y = -q1.y;
		aq0.z = -q1.z;
		aq0.w = -q1.w;

		dot = -dot;
	}

	// 角
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);

	// 補間係数
	float scale0 = std::sin((1.0f - t) * theta) / sinTheta;
	float scale1 = std::sin(t * theta) / sinTheta;

	return {
		aq0.x * scale0 + q2.x * scale1,
		aq0.y * scale0 + q2.y * scale1,
		aq0.z * scale0 + q2.z * scale1,
		aq0.w * scale0 + q2.w * scale1
	};
}



static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.03f",
				matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void QuaternionScreenPrintf(int x, int y, Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///

		///
		/// ↓描画処理ここから
		///

		Quaternion rotation0 = MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = MakeRotateAxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);
		Quaternion interpolate0 = slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = slerp(rotation0, rotation1, 0.5f); 
		Quaternion interpolate3 = slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = slerp(rotation0, rotation1, 1.0f);

		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0, " : interpolate0, Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1, " : interpolate1, Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, " : interpolate2, Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, " : interpolate3 Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, " : interpolate4, Slerp(q0, q1, 1.0f)");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}