//EnginePch.cpp
#include "pch.h"
#include "EnginePch.h"
#include "Engine.h"

//��ټ� ������ ������ nullptr ������ �� �߱� ������.
unique_ptr<Engine> GEngine = make_unique<Engine>(); //�����̱� ������ GEngine