// netmon.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "urlmon/urlmonservice.h"
#include "kpfw/netmonsp.h"
#include "kascom/kascom.h"
#include "kpfw/netmon_compatible.h"
#include "common/utility.h"

class KNetmonImpl: public INetMonServiceProvider
{
public:
	KNetmonImpl()
	{

	}

	~KNetmonImpl()
	{

	}

	virtual int __stdcall InitializeService( )
	{
        WinMod::CWinPath    path;
        // �˱�������kis����
        int                 npri = NETMON_FOR_KSAFE;
        CNetmonPri          priMgr;


        CAppPath::GetLeidianAppPath( path.m_strPath, FALSE );

        priMgr.Initialize( npri, path );

        if ( priMgr.HashHighPriVersion() )
        {
            return E_FAIL;
        }
        else
        {
            priMgr.SetPriInfomation();
        }

		return 0;
	}

	virtual int __stdcall UninitializeService()
	{
		return 0;
	}

	virtual int __stdcall StartService()
	{
		m_urlservice.Initialize();
		return 0;
	}

	virtual int __stdcall StopService()
	{
		m_urlservice.Uninitialize();
		return 0;
	}


	KAS_BEGIN_COM_MAP( KNetmonImpl )
		KAS_COM_INTERFACE_ENTRY( INetMonServiceProvider )
	KAS_END_COM_MAP()
private:
	KUrlMonService		m_urlservice;
    CNetmonPri          m_primgr;
};


KAS_BEGIN_OBJECT_MAP()
	KAS_OBJECT_ENTRY( INetMonServiceProvider, KNetmonImpl )
KAS_END_OBJECT_MAP()

USE_DEFAULT_COM_PROCEX
