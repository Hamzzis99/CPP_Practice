#pragma once
#include "Component.h"

struct TransformMatrix
{
	Vec4 offset;
};


class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	virtual void FinalUpdate() override;
	void PushData();

	// TODO : 온갖 Parent/Child 관계

public:
	// Parent 기준
	const Vec3& GetLocalPosition() { return _localPosition; }
	const Vec3& GetLocalRotation() { return _localRotation; }
	const Vec3& GetLocalScale() { return _localScale; }

	const Matrix& GetLocalToWorldMatrix() { return _matWorld; }
	const Vec3& GetWorldPosition() { return _matWorld.Translation(); } // 41 42 43 추출 그게 월드포지션을 구한다..? 뭔 소리야

	//어떤 물체를 바라보는 방향으로 가야할 때 계산할 필요 없이 오로지 룩벡터로만 이동하는데 사용하기 좋음.
	//임시 값을 뱉기 때문에 const를 안 단거임.
	Vec3 GetRight() { return _matWorld.Right(); } // 카메라 위치 좌표 right
	Vec3 GetUp() { return _matWorld.Up(); } // 카메라 위
	Vec3 GetLook() { return _matWorld.Backward(); } // 바라보는 방향

	void SetLocalPosition(const Vec3& position) { _localPosition = position; }
	void SetLocalRotation(const Vec3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const Vec3& scale) { _localScale = scale; }


public:
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	weak_ptr<Transform> GetParent() { return _parent; }

private:
	// TODO : World 위치 관련
	

	//좌표 관련의 것들이 들어갈 것.
	// 부모 기준의 로컬 좌표
	Vec3 _localPosition = {};
	Vec3 _localRotation = {};
	Vec3 _localScale = {1.f, 1.f, 1.f};

	Matrix _matLocal = {}; // 부모를 기준으로 한.
	Matrix _matWorld = {};

	weak_ptr<Transform> _parent; // 부모에대한 정보를 가진 포인터 순환 관계 때문에. weak_ptr 사용
};

