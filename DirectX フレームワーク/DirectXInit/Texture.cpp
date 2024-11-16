#include <iostream>
#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"

using std::cout;
using std::cin;
using std::endl;

//=======================================================================================
// テクスチャをロード
//=======================================================================================
bool Texture::Load(const std::string& filename)
{
	bool sts = true;
	unsigned char* pixels;

	// 画像読み込み
	pixels = stbi_load(filename.c_str(), &m_width, &m_height, &m_bpp, 4);
	// 読み込み失敗の場合…
	if (pixels == nullptr) {
		cout << filename.c_str() << " Load error " << endl;
		return false;
	}

	ComPtr<ID3D11Texture2D> pTexture;
	
	// テクスチャの初期化と設定
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	// 読み込んだ画像データの設定
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	// テクスチャ2Dリソースを生成
	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV(シェーダーリソースビュー)の作成
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		// 画像データを解放する
		stbi_image_free(pixels);
		return false;
	}

	// 画像データの解放
	stbi_image_free(pixels);
	// 成功を返す
	return true;
}

// テクスチャをメモリからロード
bool Texture::LoadFromFemory(const unsigned char* _Data, int _len) {

	bool sts = true;
	unsigned char* pixels;

	// 画像読み込み
	pixels = stbi_load_from_memory(_Data,
		_len,
		&m_width,
		&m_height,
		&m_bpp,
		STBI_rgb_alpha);

	ComPtr<ID3D11Texture2D> pTexture;
	
	// テクスチャの初期化と設定
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	// 読み込んだ画像データの設定
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	// テクスチャ2Dリソースを生成
	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV(シェーダーリソースビュー)の作成
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	// 作成が失敗した場合…
	if (FAILED(hr)) {
		// 画像データの解放
		stbi_image_free(pixels);
		return false;
	}

	// 画像データの解放
	stbi_image_free(pixels);
	// 成功を返す
	return true;
}

// テクスチャをGPUにセット
void Texture::SetGPU()
{
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();
	devicecontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}
