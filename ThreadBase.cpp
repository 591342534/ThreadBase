#include "stdafx.h"
#include "ThreadBase.h"

struct _THREAD_PARAM
{
	void*	pThis;
	HANDLE	hStepEvent;
};

CTheardBase::CTheardBase() : m_hThread(NULL), m_hStopEvent(NULL)
{

}

CTheardBase::~CTheardBase()
{
	Stop();
}

BOOL CTheardBase::Start()
{
	if (m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	if (m_hStopEvent)
	{
		::SetEvent(m_hStopEvent);
		m_hStopEvent = NULL;
	}

	if (!(m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return FALSE;

	_THREAD_PARAM* pParam = new _THREAD_PARAM;
	if (! pParam)
		return FALSE;

	pParam->pThis = this;
	pParam->hStepEvent = m_hStopEvent;
	if (!(m_hThread = (HANDLE)_beginthreadex( NULL, 0, CTheardBase::ThreadFunc, pParam, 0, NULL)))
		return FALSE;

	return TRUE;
}

BOOL CTheardBase::Stop()
{
	if (m_hStopEvent)
	{
		SetEvent(m_hStopEvent);
		m_hStopEvent = NULL;
	}

	if (m_hThread)
	{
		WaitForSingleObject( m_hThread, 100000 );
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	return TRUE;
}

BOOL CTheardBase::IsRun()
{
	return m_hThread && WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT;
}

unsigned int WINAPI CTheardBase::ThreadFunc(LPVOID lpParameter)
{
	_THREAD_PARAM* pParam = (_THREAD_PARAM*)lpParameter;
	if (! pParam || !pParam->pThis)
		return 0;

	CTheardBase* pThis = (CTheardBase*)pParam->pThis;
	HANDLE hHandle = pParam->hStepEvent;
	delete pParam;
	pParam = NULL;

	if (pThis)
	{
		::CoInitialize(NULL);
		pThis->OnThreadFunc(hHandle);
		::CoUninitialize();
	}

	if (hHandle)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}
	return 0;
}

void CTheardBase::OnThreadFunc(HANDLE hStopEvent)
{
	return;
}