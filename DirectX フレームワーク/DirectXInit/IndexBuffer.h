#pragma once
#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"Renderer.h"

// スマートポインタ
using Microsoft::WRL::ComPtr;

//=======================================================================================
// IndexBufferクラス
//=======================================================================================
class IndexBuffer {
private:
	ComPtr<ID3D11Buffer> m_IndexBuffer;
public:
	void Create(const std::vector<unsigned int>& _indicies) {

		// デバイス取得
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);	// 取得確認

		// インデックスバッファの作成
		bool sts = CreateIndexBuffer(
			device,								// デバイス
			(unsigned int)(_indicies.size()),	// インデックスの数
			(void*)_indicies.data(),			// インデックスデータの先頭アドレス
			&m_IndexBuffer);					// インデックスバッファ
		// 作成結果の確認
		assert(sts == true);
	}
	void SetGPU() {
		// デバイスコンテキスト取得
		ID3D11DeviceContext* deviceContext = nullptr;
		deviceContext = Renderer::GetDeviceContext();

		// インデックスバッファをセット
		deviceContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
};



