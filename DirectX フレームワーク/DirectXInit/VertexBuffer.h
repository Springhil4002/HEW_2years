#pragma once
#include <vector>
#include <wrl/client.h>
#include "dx11helper.h"
#include "Renderer.h"

// スマートポインタ
using Microsoft::WRL::ComPtr;

//=======================================================================================
// VertexBufferクラス
//=======================================================================================
template <typename T>
class VertexBuffer {
private:
	ComPtr<ID3D11Buffer> m_VertexBuffer;
public:
	// 頂点バッファを作成する関数
	void Create(const std::vector<T>& _vertices) {
		
		// デバイスの取得
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);	// 取得確認
		
		// 頂点バッファの作成
		bool sts = CreateVertexBufferWrite(
			device,
			sizeof(T),
			(unsigned int)_vertices.size(),
			(void*)_vertices.data(),
			&m_VertexBuffer);
		// 作成結果の確認
		assert(sts == true);
	}

	// GPUにセット
	void SetGPU() {
		
		// デバイスコンテキスト取得
		ID3D11DeviceContext* deviceContext = nullptr;
		deviceContext = Renderer::GetDeviceContext();

		// 頂点バッファをセットする
		unsigned int stride = sizeof(T);
		unsigned offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	}
	
	// 既存の頂点バッファの内容を新しい内容に書き換える
	void Modify(const std::vector<T>& _vertices)
	{
		// 頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		HRESULT hr = Renderer::GetDeviceContext()->Map(
			m_VertexBuffer.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		// 新しい頂点データをメモリにコピー
		if (SUCCEEDED(hr)) {
			memcpy(msr.pData, _vertices.data(), _vertices.size() * sizeof(T));
			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
		}
	}
};