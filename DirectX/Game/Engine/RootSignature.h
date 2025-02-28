//RootSignature.h
#pragma once

// [계약서 / 결재]

// CPU [		]		GPU	[		]
// 한국	[		]		베트남	[		]

// 임대를 해서 사용한다?
// 레지스터를 명시해서 사용하게 만드는 파트.
// 어떤땅을 어떻게 이용할지 계약하는 것.
class RootSignature
{

public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature> _signature; // GPU 에게 계약서를 넘기는 느낌.
};

