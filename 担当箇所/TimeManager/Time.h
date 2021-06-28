#pragma once
#include "../TimeManager/Time.h"
#include "../../../ESGLib.h"

class TimeManager
{
private:
	TimeManager(const TimeManager&) = delete;
	void operator=(const TimeManager&) = delete;

public:
	TimeManager();
    ~TimeManager();

	static TimeManager& Instance() {
		static TimeManager instance;
		return instance;
	};

	void Initialize();
	void Update();
	
	inline float GetLimitTime() const { return _limitTime; }
	inline float GetTime()		const { return _time; }
	inline float GetTimeLeft()  const { return _limitTime - _time; }
	std::vector<int> TimeCalaculation();
	int GetTimeMinutes();
	int GetTimeOnesPlace();
	int GetTimeTensPlace();
	int Countdown();
	float GetStartTime();
	bool StartFlag();
	float GetTransitionTimer() const { return _transition_time; }
	void MeasurementOfTime();
	void MeasurementOfCountdown();

private:
	//! 制限時間
	float _limitTime;
	float _time;

	//! 終了後のタイマー
	float _transition_time;
	bool  _game_end;

	//! カウントダウン
	float _startTime;
	int   _countTime;

	//! スタートしてるかどうか
	bool _startFlag;
	};

