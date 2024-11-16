#pragma once
#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"Renderer.h"

// �X�}�[�g�|�C���^
using Microsoft::WRL::ComPtr;

//=======================================================================================
// IndexBuffer�N���X
//=======================================================================================
class IndexBuffer {
private:
	ComPtr<ID3D11Buffer> m_IndexBuffer;
public:
	void Create(const std::vector<unsigned int>& _indicies) {

		// �f�o�C�X�擾
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);	// �擾�m�F

		// �C���f�b�N�X�o�b�t�@�̍쐬
		bool sts = CreateIndexBuffer(
			device,								// �f�o�C�X
			(unsigned int)(_indicies.size()),	// �C���f�b�N�X�̐�
			(void*)_indicies.data(),			// �C���f�b�N�X�f�[�^�̐擪�A�h���X
			&m_IndexBuffer);					// �C���f�b�N�X�o�b�t�@
		// �쐬���ʂ̊m�F
		assert(sts == true);
	}
	void SetGPU() {
		// �f�o�C�X�R���e�L�X�g�擾
		ID3D11DeviceContext* deviceContext = nullptr;
		deviceContext = Renderer::GetDeviceContext();

		// �C���f�b�N�X�o�b�t�@���Z�b�g
		deviceContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
};



