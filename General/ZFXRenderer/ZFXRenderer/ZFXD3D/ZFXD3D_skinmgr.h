//File: ZFXD3D_skinmgr.h

#pragma once

#include <d3d9.h>
#include "ZFXD3D.h"
#include "ZFX.h"

#define MAX_ID 65535

class ZFXD3DSkinManager : public ZFXSkinManager
{
	friend class ZFXD3DVCache;

public:
	
	ZFXD3DSkinManager(LPDIRECT3DDEVICE9 pDevice, FILE *pLog);
	~ZFXD3DSkinManager();

	HRESULT AddSkin(const ZFXCOLOR *pcAmbient, const ZFXCOLOR *pcDiffuse, const ZFXCOLOR *pcEmissive,
					const ZFXCOLOR *pcSpecular, float fSpecPower, UINT *nSkinID);

	HRESULT AddTexture(UINT nSkinID, const wchar_t *chName, bool bAlpha, float fAlpha,
					ZFXCOLOR *cColorKeys, DWORD dwNumColorKeys);

	HRESULT AddTextureHeightMapAsBump(UINT nSkinID, const wchar_t *chName);
	HRESULT ConvertToNormalMap(ZFXTEXTURE *pTexture);
	DWORD   VectorToRGBA(ZFXVector *vc, float fHeight);


	bool MaterialEqual(const ZFXMATERIAL *pMat0, const ZFXMATERIAL *pMat1);

	ZFXSKIN		 GetSkin(UINT nSkinID);

	ZFXMATERIAL	 GetMaterial(UINT nMatID);

	ZFXTEXTURE	 GetTexture(UINT nTexID);

	const wchar_t* GetTextureName(UINT nTexID, float *pfAlpha, ZFXCOLOR *pAK, UCHAR *pNum);

protected:
	LPDIRECT3DDEVICE9  m_pDevice;
	FILE			   *m_pLog;

	inline	bool ColorEqual(const ZFXCOLOR *pCol0, const ZFXCOLOR *pCol1);

	HRESULT CreateTexture(ZFXTEXTURE *pTexture, bool bAlpha);

	HRESULT SetAlphaKey( LPDIRECT3DTEXTURE9 *ppTexture, UCHAR R, UCHAR G, UCHAR B, UCHAR A );

	HRESULT SetTransparency(LPDIRECT3DTEXTURE9 *ppTexture, UCHAR Alpha);

	DWORD	MakeD3DColor(UCHAR R, UCHAR G, UCHAR B, UCHAR A);


	void	Log(wchar_t *, ...);
};