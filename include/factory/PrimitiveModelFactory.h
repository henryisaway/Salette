#pragma once
#include "../core/config.h"
#include "../renderer/PrimitiveModel.h"

class PrimitiveModelFactory {
public:
    PrimitiveModel* makeTriangle();
    PrimitiveModel* makeQuad();
};
