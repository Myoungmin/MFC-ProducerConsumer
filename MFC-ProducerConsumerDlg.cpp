
// MFC-ProducerConsumerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC-ProducerConsumer.h"
#include "MFC-ProducerConsumerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMFCProducerConsumerDlg::CMFCProducerConsumerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPRODUCERCONSUMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCProducerConsumerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCProducerConsumerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedNumber)
	ON_MESSAGE(UM_APPENDLINE, OnApendLineMessage)
END_MESSAGE_MAP()


// CMFCProducerConsumerDlg message handlers

BOOL CMFCProducerConsumerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCProducerConsumerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCProducerConsumerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CMFCProducerConsumerDlg::OnApendLineMessage(WPARAM wParam, LPARAM lParam)
{
	CString* pstrString = (CString*)lParam;

	AppendLine(*pstrString);

	return LRESULT();
}


void CMFCProducerConsumerDlg::AppendLine(const CString& string) const
{
	CString strBefore;
	CString strAfter;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strBefore);

	if (strBefore.IsEmpty())
	{
		strAfter = string;
	}
	else
	{
		strAfter = strBefore + "\r\n" + string;
	}

	GetDlgItem(IDC_EDIT1)->SetWindowText(strAfter);
}


void CMFCProducerConsumerDlg::OnBnClickedNumber()
{
	m_nNumber++;
	m_strAppendedString.Format(_T("New Line {%d)"), m_nNumber);
	PostMessage(UM_APPENDLINE, NULL, (LPARAM)&m_strAppendedString);
}


BOOL CMFCProducerConsumerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		//CString string;
		GetDlgItem(IDC_EDIT2)->GetWindowText(m_strAppendedString);

		if (m_strAppendedString.IsEmpty()) return TRUE;

		// 입력 내용 CString을 LPARAM 파라미터로 전달.
		// PostMessage를 실행하여 메시지 큐로 보낸다.
		PostMessage(UM_APPENDLINE, NULL, (LPARAM)&m_strAppendedString);

		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

		// Enter Key Dialog 종료 방지
		return TRUE;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}