#include "PRALRenderDevice.h"

class  PRALRenderer
{
public:
	 PRALRenderer(HINSTANCE hInst);
	 ~PRALRenderer(void);

	 HRESULT		CreateDevice(char* chAPI);
	 void			Release(void);
	 LPPRALRENDERDEVICE	GetDevice(void)
	 {
		 return m_pDevice;
	 }
	 HINSTANCE		GetModule(void)
	 {
		 return m_hDLL;
	 }

private:
	PRALRenderDevice* m_pDevice;
	HINSTANCE			m_hInst;
	HMODULE				m_hDLL;
}; // class
typedef struct PRALRenderer* LPPRALRENDERER;

 PRALRenderer:: PRALRenderer(HINSTANCE hInst)
{
	 m_hInst = hInst;
	 m_hDLL = NULL;
	 m_pDevice = NULL;
}

 PRALRenderer::~ PRALRenderer(void)
{
	 Release();
}