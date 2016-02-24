#pragma once 

// by pptt0617@163.com
// 创建工作者线程基础类 继承该类可方便创建线程


class CTheardBase
{
public:
	CTheardBase();
	virtual ~CTheardBase();

public:
	virtual BOOL Start();
	virtual BOOL Stop();
	virtual BOOL IsRun();

public:
	static unsigned int WINAPI ThreadFunc(LPVOID lpParameter);
	virtual void OnThreadFunc(HANDLE hStopEvent);

protected:
	HANDLE	m_hThread;
	HANDLE  m_hStopEvent;
};