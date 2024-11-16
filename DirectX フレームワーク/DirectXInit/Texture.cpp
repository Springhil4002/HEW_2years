#include <iostream>
#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"

using std::cout;
using std::cin;
using std::endl;

//=======================================================================================
// �e�N�X�`�������[�h
//=======================================================================================
bool Texture::Load(const std::string& filename)
{
	bool sts = true;
	unsigned char* pixels;

	// �摜�ǂݍ���
	pixels = stbi_load(filename.c_str(), &m_width, &m_height, &m_bpp, 4);
	// �ǂݍ��ݎ��s�̏ꍇ�c
	if (pixels == nullptr) {
		cout << filename.c_str() << " Load error " << endl;
		return false;
	}

	ComPtr<ID3D11Texture2D> pTexture;
	
	// �e�N�X�`���̏������Ɛݒ�
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

	// �ǂݍ��񂾉摜�f�[�^�̐ݒ�
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	// �e�N�X�`��2D���\�[�X�𐶐�
	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV(�V�F�[�_�[���\�[�X�r���[)�̍쐬
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		// �摜�f�[�^���������
		stbi_image_free(pixels);
		return false;
	}

	// �摜�f�[�^�̉��
	stbi_image_free(pixels);
	// ������Ԃ�
	return true;
}

// �e�N�X�`�������������烍�[�h
bool Texture::LoadFromFemory(const unsigned char* _Data, int _len) {

	bool sts = true;
	unsigned char* pixels;

	// �摜�ǂݍ���
	pixels = stbi_load_from_memory(_Data,
		_len,
		&m_width,
		&m_height,
		&m_bpp,
		STBI_rgb_alpha);

	ComPtr<ID3D11Texture2D> pTexture;
	
	// �e�N�X�`���̏������Ɛݒ�
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

	// �ǂݍ��񂾉摜�f�[�^�̐ݒ�
	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	// �e�N�X�`��2D���\�[�X�𐶐�
	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV(�V�F�[�_�[���\�[�X�r���[)�̍쐬
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	// �쐬�����s�����ꍇ�c
	if (FAILED(hr)) {
		// �摜�f�[�^�̉��
		stbi_image_free(pixels);
		return false;
	}

	// �摜�f�[�^�̉��
	stbi_image_free(pixels);
	// ������Ԃ�
	return true;
}

// �e�N�X�`����GPU�ɃZ�b�g
void Texture::SetGPU()
{
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();
	devicecontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}
