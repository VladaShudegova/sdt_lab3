#ifndef CHARTCREATORSFACTORY_H
#define CHARTCREATORSFACTORY_H

#include <memory>

#include "ChartCreators/ichartcreator.h"
#include "ChartCreators/barchartcreator.h"
#include "ChartCreators/piechartcreator.h"
#include "ChartData/charttype.h"

using std::shared_ptr;
using std::make_shared;

class ChartCreatorsFactory
{
public:
    ChartCreatorsFactory();
    shared_ptr<IChartCreator> getCreator(const ChartType type);
};

#endif // CHARTCREATORSFACTORY_H
