
// MFC-ProducerConsumerDlg.h : header file
//

#pragma once
#include <deque>
#include <mutex>

// CMFCProducerConsumerDlg dialog
class CMFCProducerConsumerDlg : public CDialogEx
{
// Construction
public:
	CMFCProducerConsumerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPRODUCERCONSUMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnApendLineMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNumber();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void AppendLine(const CString& string) const;

private:
	static UINT ProducerThread(LPVOID Param);

	CString m_strAppendedString;
	int m_nNumber = 0;
	std::deque<CString> m_deque;
	std::mutex m_mutex;
};
