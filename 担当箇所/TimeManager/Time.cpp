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

//�������Ԃ̂ǂ̈ʂ���邩
std::vector<int> TimeManager::TimeCalaculation()
{
	std::vector<int> time;
	time.push_back(GetTimeMinutes());
	time.push_back(GetTimeTensPlace());
	time.push_back(GetTimeOnesPlace());
	return time;
}

// @brief �������ԁi���j
// @return �������Ԃ𕪂ŕԂ�
int TimeManager::GetTimeMinutes()
{
	int ret = 0;

	ret = ((int)(GetTimeLeft()) % 3600) / 60;

	return ret;
}

// @brief �������ԁi�b�j
// @return �������Ԃ�b�ŕԂ�(10�̈�)
int TimeManager::GetTimeTensPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 / 10;

	return ret;
}

// @brief �������ԁi�b�j
// @return �������Ԃ�b�ŕԂ�(1�̈�)
int TimeManager::GetTimeOnesPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 % 10;

	return ret;
}

// @brief �J�E���g�_�E��
// @return �J�E���g�_�E���̕b��Ԃ�
int  TimeManager::Countdown()
{
	return _countTime;
}

// @brief �J�E���g�_�E��
// @return �J�E���g�_�E����float�ŕԂ�
float TimeManager::GetStartTime()
{
	return _startTime;
}

// @brief �Q�[�����n�܂��Ă��邩�ǂ���
// @return �Q�[�����X�^�[�g���Ă����true,�X�^�[�g���Ă��Ȃ����false
// @detail �Q�[�����X�^�[�g���Đ������Ԃ��v�����Ă��邩�ǂ���
bool TimeManager::StartFlag()
{ 
	return 	_startFlag;
}

//�Q�[�����̎��Ԍv��
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

//�J�E���g�_�E���v��
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