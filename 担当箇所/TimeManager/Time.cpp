#include "Time.h"

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Initialize()
{
	_limitTime  = 34.9f;
	_time       = 0.0f;

	_startTime  = 181.0f;
	_countTime  = 4;

	_startFlag = false;

	_game_end = false;

	_transition_time = 0;
}
 

void TimeManager::Update()
{
	MeasurementOfTime();
	MeasurementOfCountdown();
}

//制限時間のどの位を取るか
std::vector<int> TimeManager::TimeCalaculation()
{
	std::vector<int> time;
	time.push_back(GetTimeMinutes());
	time.push_back(GetTimeTensPlace());
	time.push_back(GetTimeOnesPlace());
	return time;
}

// @brief 制限時間（分）
// @return 制限時間を分で返す
int TimeManager::GetTimeMinutes()
{
	int ret = 0;

	ret = ((int)(GetTimeLeft()) % 3600) / 60;

	return ret;
}

// @brief 制限時間（秒）
// @return 制限時間を秒で返す(10の位)
int TimeManager::GetTimeTensPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 / 10;

	return ret;
}

// @brief 制限時間（秒）
// @return 制限時間を秒で返す(1の位)
int TimeManager::GetTimeOnesPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 % 10;

	return ret;
}

// @brief カウントダウン
// @return カウントダウンの秒を返す
int  TimeManager::Countdown()
{
	return _countTime;
}

// @brief カウントダウン
// @return カウントダウンをfloatで返す
float TimeManager::GetStartTime()
{
	return _startTime;
}

// @brief ゲームが始まっているかどうか
// @return ゲームがスタートしていればtrue,スタートしていなければfalse
// @detail ゲームがスタートして制限時間を計測しているかどうか
bool TimeManager::StartFlag()
{ 
	return 	_startFlag;
}

//ゲーム内の時間計測
void TimeManager::MeasurementOfTime()
{

	if (_startFlag == true) {
		if (_time < _limitTime - 0.9f)
		{
			_time += (float)GameTimer.GetElapsedSecond();
		}
	}

	if (GetTimeLeft() <= 1) {
		_game_end = true;
		if (_game_end == true)
		{
			_transition_time += (float)GameTimer.GetElapsedSecond();
		}
	}
}

//カウントダウン計測
void TimeManager::MeasurementOfCountdown()
{
	_startTime--;

	for (int i = 3; i > -2; i--)
	{
		if (_startTime == i * 60)
		{
			_countTime--;
		}
	}

	if (_countTime == -1) {
		_startFlag = true;
	}
}