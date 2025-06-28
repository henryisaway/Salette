#pragma once
#include <includes.h>
#include "../renderer/PrimitiveModel.h"

class PrimitiveModelFactory {
public:
    PrimitiveModel* makeTriangle();
    PrimitiveModel* makeQuad();
};
