#pragma once

// [유니티짱]과 같이 정점으로 이루어진 물체

class Mesh
{
public:
	//const를 넣은 이유는 바뀔 일은 없으니까.
	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexbuffer); // 인덱스 버퍼도 받아야지.
	void Render();

	void SetTransform(const Transform& t) { _transform = t; }

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint32>& buffer);
	
private:
	//인덱스 버퍼랑 중복되는 것을 빼주는 것.
	ComPtr<ID3D12Resource>		_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
	uint32 _vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView;
	uint32 _indexCount = 0;

	Transform _transform = {};
};

