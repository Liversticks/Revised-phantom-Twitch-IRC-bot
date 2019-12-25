/**
	platformTime.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#define __STDC_WANT_LIB_EXT1__ 1

#include "../include.h"

#define TEST_BUF_SIZE 64
#define TEST_TIMESTAMP 1204

UFC32 GTime::fetchTimestamp() {
	static ACHAR timestamp[TEST_TIMESTAMP];
	*timestamp = NULL;
	fetchDateString(timestamp);
	strcat_s((ACHAR *)timestamp, TEST_TIMESTAMP, " ");
	fetchSysTime(timestamp + strlen((UFC32)timestamp));
	return timestamp;
}

void GTime::fetchSysTime(ACHAR *dst) {
	TimeVars t;
	Time::sysTime(t);
	ACHAR buffer[TEST_BUF_SIZE];
	sprintf_s(buffer, TEST_BUF_SIZE, "%02d:%02d:%02d", t.hours, t.minutes, t.seconds);
	strcpy_s(dst, TEST_BUF_SIZE, buffer);
}

void GTime::fetchDateString(ACHAR *dst) {
	TimeVars t;
	Time::sysTime(t);
	ACHAR buffer[TEST_BUF_SIZE];
	sprintf_s(buffer, TEST_BUF_SIZE, "%02d/%02d/%02d", t.months, t.dayNum, (t.years % 100));
	strcpy_s(dst, TEST_BUF_SIZE, buffer);
}

#if USE_SYS_TIME == 1

	void GTime::sysTime(TimeVars &c) {
		timeval tv;
		gettimeofday(&tv, NULL);
		tm local;
		localtime_r(&tv.tv_sec, &local);

		c.years = local.tm_year + 1900;
		c.months = local.tm_mon + 1;
		c.dayOfWeek = local.tm_wday;
		c.dayNum = local.tm_mday;
		c.hours = local.tm_hour;
		c.minutes = local.tm_min;
		c.seconds = local.tm_sec;
		c.miliseconds = tv.tv_usec / 1000;
	}

	void GTime::utcTime(TimeVars &c) {
		timeval tv;
		gettimeofday(&tv, NULL);
		tm local;
		gmtime_r(&tv.tv_sec, &local);

		c.years = local.tm_year + 1900;
		c.months = local.tm_mon + 1;
		c.dayOfWeek = local.tm_wday;
		c.dayNum = local.tm_mday;
		c.hours = local.tm_hour;
		c.minutes = local.tm_min;
		c.seconds = local.tm_sec;
		c.miliseconds = tv.tv_usec / 1000;
	}

#endif
