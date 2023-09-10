#define MAX_3DHWND 8

class PRALRenderDevice
{
	protected:
		HWND	m_hWndMain;				// main window
		HWND	m_hWnd[MAX_3DHWND];		// render window(s)
		UINT	m_nNumhWnd;				// number of render-windows
		UINT	m_nActivehWnd;			// active window
		HINSTANCE	m_hDLL;				// DDL module
		DWORD	m_dwWidth;				// screen width
		DWORD	m_dwHeight;				// screen height
		bool	m_bWindowed;			// windowed mode?
		char	m_chAdapter[256];		// graphics adapter
		FILE *m_pLog;					// logfile
		bool m_bRunning;

	public:
		PRALRenderDevice(void) {};
		virtual ~PRALRenderDevice(void) {};

		// INIT/RELEASE STUFF:
		// ==================
		virtual HRESULT Init(HWND, const HWND*, int, int, int, bool) = 0;
		virtual void Release(void) = 0;
		virtual bool IsRunning(void) = 0;

		// RENDERING STUFF:
		// ===============

		virtual HRESULT UseWindow(UINT nHwnd) = 0;
		virtual HRESULT BeginRendering(bool bClearPixel, bool bClearDepth, bool bClearStencil) = 0;
		virtual void EndRendering(void) = 0;
		virtual HRESULT Clear(bool bClearPixel, bool bClearDepth, bool bClearStencil) = 0;
		virtual void SetClearColor(float fRed, float fGreen, float fBlue) = 0;

}; // class

typedef struct PRALRenderDevice* LPPRALRENDERDEVICE;

extern "C"
{
	HRESULT CreateRenderDevice(HINSTANCE hDLL, PRALRenderDevice** pInterface);

	typedef HRESULT(*CREATERENDERDEVICE) (HINSTANCE hDLL, PRALRenderDevice** pInterface);

	HRESULT ReleaseRenderDevice(PRALRenderDevice** pInterface);

	typedef HRESULT(*RELEASERENDERDEVICE) (PRALRenderDevice** pInterface);
}

HRESULT PRALRenderer::CreateDevice(char* chAPI)
{
	char buffer[300];

	if (strcmp(chAPI, "Direct3D") == 0)
	{
		m_hDLL = LoadLibrary("PRALD3D.dll");
		if (!m_hDLL)
		{
			MessageBox(NULL, "Loading PRALD3D.dll failed.",
				"PRALEngine - error", MB_OK | MB_ICONERROR);
			return E_FAIL;
		}
	}
	else
	{
		_snprintf(buffer, 300, "API '%s' not supported.", chAPI);
		MessageBox(NULL, buffer, "PRALEngine - error",
			MB_OK | MB)ICONERROR);
		return E_FAIL;
	}

	CREATERENDERDEVICE _CreateRenderDevice = 0;
	HRESULT hr;

	// pointer to DLL function 'CreateRenderDevice'
	_CreateRenderDevice = (CREATERENDERDEVICE)GetProcAddress(m_hDLL, "CreateRenderDevice");

	if (!_CreateRenderDevice) return E_FAIL;

	// call DLL function to create the device
	hr = _CreateRenderDevice(m_hDLL, &m_pDevice);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			"CreateRenderDevice() from lib failed.",
			"PRALEngine - error", MB_OK | MB_ICONERROR);
		m_pDevice = NULL;
		return E_FAIL;
	}

	return S_OK;
} // CreateDevice

HINSTANCE LoadLibrary(LPCTSTR lpLibFileName);

FARPROC GetProcAddress(HMODULE hModule, LPCTSTR lpProcName);

void PRALRenderer::Release(void)
{
	RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
	HRESULT hr;

	if (m_hDLL)
	{
		// pointer to DLL function 'ReleaseRenderDevice'
		_ReleaseRenderDevice = (RELEASERENDERDEVICE)GetProcAddress(m_hDLL, "ReleaseRenderDevice");
	}
	// call DLL's release function
	if (m_pDevice)
	{
		hr = _ReleaseRenderDevice(&m_pDevice);
		if (FAILED(hr))
		{
			m_pDevice = NULL;
		}
	}
} // Release