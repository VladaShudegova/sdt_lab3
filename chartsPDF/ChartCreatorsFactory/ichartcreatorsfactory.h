#ifndef ICHARTCREATORSFACTORY_H
#define ICHARTCREATORSFACTORY_H

#include <memory>

#include "ChartCreators/ichartcreator.h"

using std::shared_ptr;
using std::make_shared;

class IChartCreatorsFactory
{
public:
    shared_ptr<IChartCreator> getCreator(int) = 0;
};

#endif // ICHARTCREATORSFACTORY_H
