#define MAX_3DHWND 8

class PRALD3D : public PRALRenderDevice
{
public:
	PRALD3D(HINSTANCE hDLL);
	~PRALD3D(void);

	// initialization
	HRESULT Init(HWND, const HWND*, int, int, int, bool);

	BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

	// interface functions
	void Release(void);
	bool IsRunning(void) { return m_bRunning; }
	HRESULT BeginRendering(bool, bool, bool);
	HRESULT Clear(bool, bool, bool);
	void EndRendering(float, float, float);
	HRESULT UseWindow(UNIT nHwnd);

private:
	PRALD3DEnum* m_pEnum;
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DSWAPCHAIN9 m_pChain[MAX_3DHWND];
	D3DPRESENT_PARAMETERS m_d3dpp;
	D3DCOLOR m_ClearColor;
	bool m_bIsSceneRunning;
	bool m_bStencil;

	// start the API
	HRESULT Go(void);

	void Log(char*, ...);
}; // class