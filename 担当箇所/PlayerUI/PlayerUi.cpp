#include"PlayerUi.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"

PlayerUi::PlayerUi(const int player_no) : _player_index(player_no)
{
	_tag		 = PLAYER_TAG + std::to_string(_player_index + 1);

	_i_player_data = std::make_unique<IPrayerData>();
	_i_arm_data	   = std::make_unique<IArmData>();
}

PlayerUi::~PlayerUi()
{
	_i_player_data.reset();
	_i_arm_data.reset();
}

bool PlayerUi::Initialize(const Vector3& banner_pos, RectWH banner_rectWH)
{
	_banner_sprite   = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/banner_0127.png"));
	_banner_sprite_2 = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/banner_0128_h.png"));
	_banner_position = banner_pos;
	_banner_rw       = banner_rectWH;
	_item_icon       = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/item_.png"));
	_player_icon     = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/player0122.png"));

	_ranking = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/runking.png"));

	_score_font = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));

	_score = 0;
	_prev_rank_point = 0;
	_font_size = 0.6f;
	_add_point = 0;
	_delta_point = 0;

	_anchor_point_banner_number = Vector3(32 * _font_size, 32 * _font_size, 0);

	if (_player_index == 1 || _player_index == 3) {
		_icon_pos     = Vector3(122, -110, 1);
		_icon_pos_n1  = Vector3(130, -97, 1);
	}
	else
	{
		_icon_pos    = Vector3( -12, -110, 1);
		_icon_pos_n1 = Vector3( -13,  -97, 1);
	}

	
	
	_player_pos = Vector3_Zero;
	
	return true;
}

int PlayerUi::Update()
{
	PlayerWorldToScreen();
	PlayerProcessing(_player_pos);
	RegisterPointAnimation(_player_pos);
	MovePointAnimation(_player_pos);

    return 0;
}

void PlayerUi::Draw2D()
{
	DrawPontAnimation();
	DrawPlayerItem();
	DrawPlayerBanner();
	DrawPlayerRanking();
}

//プレイヤーの座標を三次元から二次元に変換
Vector3 PlayerUi::PlayerWorldToScreen()
{
	auto player_num = WorldToScreen(_i_player_data->GetPosition(_tag), SceneCamera::Instance().GetCamera());
	player_num.z = SpriteBatch_TopMost;
	_player_pos.x = player_num.x;
	_player_pos.y = player_num.y;
	return _player_pos;
}

//直前のスコアと現在のスコアの比較
void PlayerUi::PlayerProcessing(Vector3 player_num)
{
	auto rank_point = _i_player_data->GetRankingPoint(_tag);

	//! 配列のerase時と今のスコア比較
	if (_score < _add_point)
	{
		_score += _delta_point;
		if (_score > _add_point)
			_score = _add_point;
	}
	else
	{
		_font_size = _font_size_default;
	}

	//! 配列のerase時と今のスコア比較
	if (_score > rank_point)
	{
		_score -= _score_down;
		_add_point = rank_point;
	}
}

//ポイントの処理
void PlayerUi::RegisterPointAnimation(Vector3 player_num)
{
	auto rank_point = _i_player_data->GetRankingPoint(_tag);

	//! ポイントを入手した時
	if (rank_point > _prev_rank_point)
	{
		auto pointAnim     = PointAnimation();
		pointAnim.point    = rank_point - _prev_rank_point;
		pointAnim.position = player_num;
		pointAnim.theta    = 0.0f;
		pointAnim.alpha    = 1.0f;
		_pointAnimation.push_back(pointAnim);

		for (int i = 0; i < _pointAnimation.size(); ++i) {
			_add_point  += _pointAnimation[i].point;
			_font_size   = _font_size_default + ((float)(_add_point - _score) / (float)1000);
			_delta_point = (_add_point - _score) / GameTimer.GetFPS() * _point_up_speed;
	    }
	}
	_prev_rank_point = rank_point;
	
}

//入手ポイントの動き
void PlayerUi::MovePointAnimation(Vector3 player_num)
{
	if (_pointAnimation.size() == 0)
	{
		return;
	}

	//! 入手ポイントの移動
	for (int i = 0; i < _pointAnimation.size(); ++i)
	{
		Vector3 tmp_bezier_pos1, tmp_bezier_pos2, tmp_bezier_pos3, tmp_bezier_pos4;
		tmp_bezier_pos1 = Vector3(-10, -10, 0);tmp_bezier_pos2 = Vector3(-10, -20, 0);
		tmp_bezier_pos3 = Vector3(-10, -20, 0);tmp_bezier_pos4 = Vector3(-10, -40, 0);

    	Vector3 bezier3 = Vector3_Bezier(player_num + tmp_bezier_pos1, player_num + tmp_bezier_pos2,
			player_num + tmp_bezier_pos3, player_num + tmp_bezier_pos4, _pointAnimation[i].theta);
		_pointAnimation[i].theta += _point_animation_theta_up;

		_pointAnimation[i].position.y = bezier3.y;
		_pointAnimation[i].position.x = bezier3.x;

		_pointAnimation[i].alpha -= _point_animation_alpha_down;

		if (_pointAnimation[i].alpha <= 0)
		{
			_pointAnimation[i].alpha = 0;
		}

		if (_pointAnimation[i].position.y <= player_num.y - _point_animation_erase_pos) {
			_pointAnimation.erase(_pointAnimation.begin() + i);
		}
	}
}

//入手ポイントの描画
void PlayerUi::DrawPontAnimation()
{
	//入手ポイントのアニメーション
	for (int i = 0; i < _pointAnimation.size(); i++)
	{
		const int POINT_RATIO = _pointAnimation[i].point / _default_point;
		for (int s = 0; s < POINT_RATIO; s++) {
			for (int n = 1; n < _NUMBER_PLACE_MAX; n++)
			{
				const float pos_x = (_pointAnimation_pos_x + (n * _number_scale)) * ((_get_score_font_size * s) + _get_score_font_size_default);
				SpriteBatch.Draw(*_score_font, _pointAnimation[i].position +
					Vector3(pos_x, _pointAnimation_pos_y, 0),
					RectWH((CalculationOfPlace(_pointAnimation[i].point)[n] * _number_scale), 0, _number_scale, _number_scale),
					_pointAnimation[i].alpha,
					Vector3_Zero, Vector3_Zero, (_get_score_font_size * s) + _get_score_font_size_default);
			}
			break;
		}
	}
}

//入手のアイテムの描画
void PlayerUi::DrawPlayerItem()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);
		if (name == _tag)
		{
			if (_i_player_data->GetStatusTag(_tag) == ITEM_PLAYER_SPEEDUP)
			{
				SpriteBatch.Draw(*_item_icon, _banner_position + _item_pos, _item_player_speedup_rect, 1.0f,
					Vector3_Zero, Vector3_Zero, _item_icon_size);
			}
			else if (_i_player_data->GetStatusTag(_tag) == ITEM_ARM_SPEEDUP)
			{
				SpriteBatch.Draw(*_item_icon, _banner_position + _item_pos, _item_arm_speedup_rect, 1.0f,
					Vector3_Zero, Vector3_Zero, _item_icon_size);
			}
			else if (_i_player_data->GetStatusTag(_tag) == ITEM_POWERDOWN)
			{
				SpriteBatch.Draw(*_item_icon, _banner_position + _item_pos, _item_powerdown_rect, 1.0f,
					Vector3_Zero, Vector3_Zero, _item_icon_size);
			}
			else if (_i_player_data->GetStatusTag(_tag) == ITEM_THUNDER)
			{
				SpriteBatch.Draw(*_item_icon, _banner_position + _item_pos, _item_thunder_rect, 1.0f,
					Vector3_Zero, Vector3_Zero, _item_icon_size);
			}
			break;
		}
	}
}

//バナーの描画
void PlayerUi::DrawPlayerBanner()
{
	if (_player_index == 0 || _player_index == 2) {
    SpriteBatch.Draw(*_banner_sprite, _banner_position, _banner_rw);
	}
	else
	{
	SpriteBatch.Draw(*_banner_sprite_2, _banner_position, _banner_rw);
	}

	//バナースコアアニメーション
	SpriteElement se;
	se = _score_font;
	se.anchorPoint = _anchor_point_banner_number;
	se.SetScale(_font_size);
	for (int i = 0; i < _NUMBER_PLACE_MAX; i++)
	{
		int x = ((_banner_score_pos_x + (i * _number_scale)) * _font_size) + _banner_score_animation_pos_x;
		int y = _banner_score_animation_pos_y;
		int z = _banner_score_animation_pos_z;
		se.position = _banner_position + Vector3(x, y, z);
		se.srcRect = RectWH((CalculationOfPlace(_score)[i] * _number_scale), 0, _number_scale, _number_scale);
		SpriteBatch.Draw(se);
	}
	//プレイヤーのアイコン
	if (TimeManager::Instance().GetTimeLeft() >= 110) {
		SpriteBatch.Draw(*_player_icon, _banner_position + _icon_pos,
			RectWH(SceneManager::Instance().GetPlayerTexture(_tag) * _joy_icon_scale - _joy_icon_scale,
				_joy_icon_scale, _joy_icon_scale, _joy_icon_scale),
			(DWORD)Color_White, Vector3_Zero, Vector3_Zero, _joy_icon_size);
	}
	else if (_i_player_data->GetRankNum(_tag) + 1 == 1)
	{
		SpriteBatch.Draw(*_player_icon, _banner_position + _icon_pos_n1,
			RectWH(SceneManager::Instance().GetPlayerTexture(_tag) * _joy_icon_scale - _joy_icon_scale,
				0, _joy_icon_scale, _joy_icon_scale),
			(DWORD)Color_White, Vector3_Zero, Vector3_Zero, 1.0f);
	}
	else
	{
		SpriteBatch.Draw(*_player_icon, _banner_position + _icon_pos,
			RectWH(SceneManager::Instance().GetPlayerTexture(_tag) * _joy_icon_scale - _joy_icon_scale,
				_joy_icon_scale, _joy_icon_scale, _joy_icon_scale),
			(DWORD)Color_White, Vector3_Zero, Vector3_Zero, _joy_icon_size);
	}
}

//順位の描画
void PlayerUi::DrawPlayerRanking()
{
	//開始十秒後に順位表示
	if (TimeManager::Instance().GetTimeLeft() <= 110 && TimeManager::Instance().GetTimeLeft() >= 1) {
		SpriteBatch.Draw(*_ranking, _player_pos + Vector3(_ranking_pos_x * _ranking_size, (-_joy_icon_scale - _ranking_pos_y)
			* _ranking_size, 0),
			RectWH((_i_player_data->GetRankNum(_tag)) * _joy_icon_scale, 0, _joy_icon_scale, _joy_icon_scale),
			(DWORD)Color_White, Vector3_Zero, Vector3_Zero, _ranking_size);
	}
}

