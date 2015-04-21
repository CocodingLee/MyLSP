#include "Global.h"
#include "WSP.h"

bool versionNegotiation(WORD wVersionRequested, LPWSPDATA lpWSPData)
{
	// TODO check wVersionRequested

	// set lpWSPData, support 2.2 only

	lpWSPData->wVersion = MAKEWORD(2, 2);
	lpWSPData->wHighVersion = lpWSPData->wVersion;
	
	return true;
}

void fillProcTable(LPWSPPROC_TABLE lpProcTable)
{
	lpProcTable->lpWSPAccept				= WSPAccept;
	lpProcTable->lpWSPAddressToString		= WSPAddressToString;
	lpProcTable->lpWSPAsyncSelect			= WSPAsyncSelect;
	lpProcTable->lpWSPBind					= WSPBind;
	lpProcTable->lpWSPCancelBlockingCall	= WSPCancelBlockingCall;
	lpProcTable->lpWSPCleanup				= WSPCleanup;
	lpProcTable->lpWSPCloseSocket			= WSPCloseSocket;
	lpProcTable->lpWSPConnect				= WSPConnect;
	lpProcTable->lpWSPDuplicateSocket		= WSPDuplicateSocket;
	lpProcTable->lpWSPEnumNetworkEvents		= WSPEnumNetworkEvents;
	lpProcTable->lpWSPEventSelect			= WSPEventSelect;
	lpProcTable->lpWSPGetOverlappedResult	= WSPGetOverlappedResult;
	lpProcTable->lpWSPGetPeerName			= WSPGetPeerName;
	lpProcTable->lpWSPGetSockName			= WSPGetSockName;
	lpProcTable->lpWSPGetSockOpt			= WSPGetSockOpt;
	lpProcTable->lpWSPGetQOSByName			= WSPGetQOSByName;
	lpProcTable->lpWSPIoctl					= WSPIoctl;
	lpProcTable->lpWSPJoinLeaf				= WSPJoinLeaf;
	lpProcTable->lpWSPListen				= WSPListen;
	lpProcTable->lpWSPRecv					= WSPRecv;
	lpProcTable->lpWSPRecvDisconnect		= WSPRecvDisconnect;
	lpProcTable->lpWSPRecvFrom				= WSPRecvFrom;
	lpProcTable->lpWSPSelect				= WSPSelect;
	lpProcTable->lpWSPSend					= WSPSend;
	lpProcTable->lpWSPSendDisconnect		= WSPSendDisconnect;
	lpProcTable->lpWSPSendTo				= WSPSendTo;
	lpProcTable->lpWSPSetSockOpt			= WSPSetSockOpt;
	lpProcTable->lpWSPShutdown				= WSPShutdown;
	lpProcTable->lpWSPSocket				= WSPSocket;
	lpProcTable->lpWSPStringToAddress		= WSPStringToAddress;
}

int WSPAPI WSPStartup(
		WORD wVersionRequested,
		LPWSPDATA lpWSPData,
		LPWSAPROTOCOL_INFO lpProtocolInfo,
		WSPUPCALLTABLE UpcallTable,
		LPWSPPROC_TABLE lpProcTable
	)
{
	// ʹ���ٽ�����������ǰ����ִ��ʱ������Ϊ���������

	g.Enter();

	// ���� WSPStartup() �� WSPCleanup() ���ܻᱻ�������ö��
	// �˴�ʹ�����ü�������֤��Դ����������ʱ����ȷ��

	g.IncRefCount();

	// ���ܵ�ǰ�����ǵڼ��α����ã����Ǹ����ϵ����������� MSDN Ҫ���
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms742296(v=vs.85).aspx
	
	g.SetUpcallTable(UpcallTable);

	if (g.GetRefCount() > 1) {
		// �Ѿ��������������ظ�ִ��
		g.Leave();
		return 0;
	}

	// ��δ���������������жಽ��������������Ӧ��ɰ汾Э��

	if (!versionNegotiation(wVersionRequested, lpWSPData)) {
		// Э��ʧ�ܣ��޷���������ߵ�����
		g.Leave();
		return WSAVERNOTSUPPORTED;
	}

	// ��д����ʵ�ֱ�
	
	fillProcTable(lpProcTable);

	// �ɹ��ˣ�һ�о���

	return 0;
}