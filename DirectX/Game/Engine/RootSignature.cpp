// RootSignature.cpp

#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//D3D12_DESCRIPTOR_RANGE_TYPE_CBV 뷰로 사용할 것이다. 0번부터 4번까지..~ (레지스터에 올려져있는 것.)
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0), // b0~b4
	};

	//서명 부분.
	//CD3DX12_ROOT_PARAMETER param[2]; // 초록색 root CBV를 만들겠다고 서명한 것.
	//번호를 겹치면 당연히 안 되겠지? Adding a root Constant Buffer View.
	// 
	//Constructor 방식 -> Table로 변경 Constructor은 한도가 있기 때문에 Table로 넘어갈 것.
	//param[0].InitAsConstantBufferView(0); // 0번 ->b0 -> CBV
	//param[1].InitAsConstantBufferView(1); // 1번 ->b1 -> CBV 

	CD3DX12_ROOT_PARAMETER param[1]; // DescriptorTable은 하나만 만들거니까 1로 고정.
	param[0].InitAsDescriptorTable(_countof(ranges), ranges); // 이거는 꼭 하나만 해야한다 마지막으로. 맞나?
	
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param); // 배열 받아내기
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}