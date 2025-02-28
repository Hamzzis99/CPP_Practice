//EnginePch.cpp
#include "pch.h"
#include "EnginePch.h"
#include "Engine.h"

//대다수 엑세스 위반은 nullptr 지정을 안 했기 때문에.
unique_ptr<Engine> GEngine = make_unique<Engine>(); //전역이기 때문에 GEngine