// RootSignature.cpp

#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//D3D12_DESCRIPTOR_RANGE_TYPE_CBV ��� ����� ���̴�. 0������ 4������..~ (�������Ϳ� �÷����ִ� ��.)
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0), // b0~b4
	};

	//���� �κ�.
	//CD3DX12_ROOT_PARAMETER param[2]; // �ʷϻ� root CBV�� ����ڴٰ� ������ ��.
	//��ȣ�� ��ġ�� �翬�� �� �ǰ���? Adding a root Constant Buffer View.
	// 
	//Constructor ��� -> Table�� ���� Constructor�� �ѵ��� �ֱ� ������ Table�� �Ѿ ��.
	//param[0].InitAsConstantBufferView(0); // 0�� ->b0 -> CBV
	//param[1].InitAsConstantBufferView(1); // 1�� ->b1 -> CBV 

	CD3DX12_ROOT_PARAMETER param[1]; // DescriptorTable�� �ϳ��� ����Ŵϱ� 1�� ����.
	param[0].InitAsDescriptorTable(_countof(ranges), ranges); // �̰Ŵ� �� �ϳ��� �ؾ��Ѵ� ����������. �³�?
	
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param); // �迭 �޾Ƴ���
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // �Է� ������ �ܰ�

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}