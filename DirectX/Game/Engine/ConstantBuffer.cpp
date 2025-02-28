//ConstantBuffer.cpp
#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h" //Device 에러는 이거 include 하면 됨

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer() // 더이상 필요없다 할 때 뚜껑을 닫아주는 것.
{
	if (_cbvBuffer)
	{
		if (_cbvBuffer != nullptr)
			_cbvBuffer->Unmap(0, nullptr); // 깔끔하게 정리해주는 것 Unmap

		_cbvBuffer = nullptr;
	}
}



void ConstantBuffer::Init(uint32 size, uint32 count)
{
	// 상수 버퍼는 256 바이트 배수로 만들어야 한다
	// 0 256 512 768 배수로 설정
	_elementSize = (size + 255) & ~255; // -255 <- 하위 8바이트를 전부 꺼주겠다.
	_elementCount = count;

	CreateBuffer();
}

void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_cbvBuffer));

	_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&_mappedBuffer));
	// We do not need to unmap until we are done with the resource.  However, we must not write to
	// the resource while it is in use by the GPU (so we must use synchronization techniques).
}

void ConstantBuffer::Clear()
{
	_currentIndex = 0;
}


void ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size) // DRAM 부분을 복사해주고 GPU로 알아서 작업 처리하게 해주는 것.
{
	assert(_currentIndex < _elementSize); // 조건을 만족하지 않으면 Crash를 내는 디버깅 용도 코드다.

	// 해당 index 위치에다가 buffer을 복사해주는 것. DRAM -> GRAM 복사
	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size);

	D3D12_GPU_VIRTUAL_ADDRESS address = GetGpuVirtualAddress(_currentIndex);
	CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address); // 데이터를 레지스터로 올려주는 작업
	_currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 index) 
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += index * _elementSize;
	return objCBAddress;
}