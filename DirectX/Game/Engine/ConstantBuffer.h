//ConstantBuffer.h
#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(uint32 size, uint32 count);

	void Clear();
	D3D12_CPU_DESCRIPTOR_HANDLE PushData(int32 rootParamIndex, void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 index);

private:
	void CreateBuffer();
	void CreateView();

private:
	ComPtr<ID3D12Resource>	_cbvBuffer; // GPU쪽 데이터 GDDR4 영역에 생성해주는 것.
	BYTE* _mappedBuffer = nullptr; // CPU쪽에다 데이터를 밀어넣을때 쓰는 것.
	uint32					_elementSize = 0;
	uint32					_elementCount = 0;

	// DESCRIPTOR 구성요소들
	ComPtr<ID3D12DescriptorHeap>		_cbvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE			_cpuHandleBegin = {}; //시작 핸들 주소
	uint32								_handleIncrementSize = 0; // 몇 칸을 띄어야 할지.

	uint32					_currentIndex = 0; // 모든 그림이 다 그려지면 다시 0번부터.
};


