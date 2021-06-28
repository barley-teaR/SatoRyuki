#pragma once
#include "../../../ESGLib.h"
#include "../../Data/IData.h"
#include "../../Managers/TimeManager/Time.h"
#include "../UiAlgorithm/UiAlgorithm.h"

// @brief ����|�C���g�̏���
struct PointAnimation
{
	Vector3 position;
	float theta;
	int point;
	float alpha;
	PointAnimation()
	{
		position = Vector3_Zero;
		theta = 0.0f;
		point = 0;
		alpha = 0;
	}
};

class PlayerUi
{
public:
	PlayerUi() {}
	PlayerUi(const int player_no);
	~PlayerUi();

	bool Initialize(const Vector3& banner_pos, RectWH banner_rectWH);
	int  Update();
	void Draw2D();
	Vector3 PlayerWorldToScreen();
	void RegisterPointAnimation(Vector3 _player_pos);
	void MovePointAnimation(Vector3 _player_pos);
	void PlayerProcessing(Vector3 _player_pos);
	void DrawPontAnimation();
	void DrawPlayerItem();
	void DrawPlayerBanner();
	void DrawPlayerRanking();

private:
	//�v���C���[�ƃA�[�����̎擾
	std::unique_ptr<IPrayerData> _i_player_data;
	std::unique_ptr<IArmData>    _i_arm_data;

	//�v���C���[�i���o�[
	int         _player_index;
	std::string _tag;

	//�e�v���C���[�̃o�i�[
	SPRITE  _banner_sprite;
	SPRITE  _banner_sprite_2;
	Vector3 _banner_position;
	RectWH  _banner_rw;

	//�e�v���C���[�̃A�C�R��
	SPRITE      _player_icon;
	Vector3     _icon_pos_n1;
	Vector3     _icon_pos;
	const float _joy_icon_size  = 1.1f;
	const float _joy_icon_scale = 128.0f;

	//�e�v���C���[�̃A�C�e��
	SPRITE        _item_icon;
	const Vector3 _item_pos                 = Vector3(37, 40, -1);
	const RectWH  _item_player_speedup_rect = RectWH(  0, 0, 64, 64);
	const RectWH  _item_arm_speedup_rect    = RectWH( 64, 0, 64, 64);
	const RectWH  _item_powerdown_rect      = RectWH(128, 0, 64, 64);
	const RectWH  _item_thunder_rect        = RectWH(192, 0, 64, 64);
	const float   _item_icon_size           = 0.7f;

	//�v���C���[�̈ʒu
	Vector3 _player_pos;

	//�v���C���[�̏���
	SPRITE      _ranking;
	const float _ranking_pos_x = -60.0f;
	const float _ranking_pos_y = 40.0f;
	const float _ranking_size  =   0.7f;
	
	//�e�v���C���[�̃o�i�[�̃X�R�A
	SPRITE      _score_font;
	int         _score;	
	int         _add_point;
	int         _delta_point;
	float       _font_size;
	const float _font_size_default = 0.5;
	const int   _score_down        = 10;

	//�o�i�[�X�R�A�̒����l
	Vector3   _anchor_point_banner_number;
	const int _banner_score_pos_x           = 10;
	const int _banner_score_animation_pos_x = 90;
	const int _banner_score_animation_pos_y = 57;
	const int _banner_score_animation_pos_z = -1;
	
	//�����摜�̑傫���Ǝg�p���鐔�̍ő�̈�
	static const int _NUMBER_PLACE_MAX = 4;
	const float      _number_scale     = 64.0f;
	
	//�l���|�C���g
	std::vector<PointAnimation> _pointAnimation;
	int                         _prev_rank_point;
	const float                 _point_up_speed = 4.0f;

	//�l���|�C���g�̒����l
	const int   _default_point               = 100;
	const int   _pointAnimation_pos_x        = 10;
	const int   _pointAnimation_pos_y        = -25;
	const float _get_score_font_size_default = 0.3f;
	const float _get_score_font_size         = 0.1f;

	//�l���|�C���g�̕ϓ��l
	const float _point_animation_theta_up   = 0.01;
	const float _point_animation_alpha_down = 0.03;
	const float _point_animation_erase_pos  = 41;
};