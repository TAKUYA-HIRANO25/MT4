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


Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t) {
	float dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	Quaternion aq0 = q1;
	float aDot = dot;
	if (dot < 0) {
		aq0.x = -q1.x;
		aq0.y = -q1.y;
		aq0.z = -q1.z;
		aq0.w = -q1.w;

		dot = -aDot;
	}

	// なす角を求める
	const float epsilon = 1e-6f; // ゼロ割防止用の閾値
	if (dot > 1.0f - epsilon) {
		// ほぼ同じ方向の場合、線形補間を使用
		Quaternion result;
		result.w = q1.w * (1.0f - t) + aq0.w * t;
		result.x = q1.x * (1.0f - t) + aq0.x * t;
		result.y = q1.y * (1.0f - t) + aq0.y * t;
		result.z = q1.z * (1.0f - t) + aq0.z * t;
		// 正規化して返す
		float length = result.w * result.w + result.x * result.x + result.y * result.y + result.z * result.z;
		return { result.w / length, result.x / length, result.y / length, result.z / length };
	}

	// なす角
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);

	// 補間係数を計算
	float scale0 = std::sin((1.0f - t) * theta) / sinTheta;
	float scale1 = std::sin(t * theta) / sinTheta;

	return {
		aq0.x * scale0 + q1.x * scale1,
		aq0.y * scale0 + q1.y * scale1,
		aq0.z * scale0 + q1.z * scale1,
		aq0.w * scale0 + q1.w * scale1
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

	Vector3 v1{ 1.0f, 3.0f, -5.0f };
	Vector3 v2{ 4.0f, -1.0f, 2.0f };
	float k = { 4.0f };

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
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Quaternion rotation0 = Make

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