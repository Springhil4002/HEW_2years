#pragma once
#include <vector>
#include <wrl/client.h>
#include "dx11helper.h"
#include "Renderer.h"

// �X�}�[�g�|�C���^
using Microsoft::WRL::ComPtr;

//=======================================================================================
// VertexBuffer�N���X
//=======================================================================================
template <typename T>
class VertexBuffer {
private:
	ComPtr<ID3D11Buffer> m_VertexBuffer;
public:
	// ���_�o�b�t�@���쐬����֐�
	void Create(const std::vector<T>& _vertices) {
		
		// �f�o�C�X�̎擾
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);	// �擾�m�F
		
		// ���_�o�b�t�@�̍쐬
		bool sts = CreateVertexBufferWrite(
			device,
			sizeof(T),
			(unsigned int)_vertices.size(),
			(void*)_vertices.data(),
			&m_VertexBuffer);
		// �쐬���ʂ̊m�F
		assert(sts == true);
	}

	// GPU�ɃZ�b�g
	void SetGPU() {
		
		// �f�o�C�X�R���e�L�X�g�擾
		ID3D11DeviceContext* deviceContext = nullptr;
		deviceContext = Renderer::GetDeviceContext();

		// ���_�o�b�t�@���Z�b�g����
		unsigned int stride = sizeof(T);
		unsigned offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	}
	
	// �����̒��_�o�b�t�@�̓��e��V�������e�ɏ���������
	void Modify(const std::vector<T>& _vertices)
	{
		// ���_�f�[�^��������
		D3D11_MAPPED_SUBRESOURCE msr;
		HRESULT hr = Renderer::GetDeviceContext()->Map(
			m_VertexBuffer.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		// �V�������_�f�[�^���������ɃR�s�[
		if (SUCCEEDED(hr)) {
			memcpy(msr.pData, _vertices.data(), _vertices.size() * sizeof(T));
			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
		}
	}
};