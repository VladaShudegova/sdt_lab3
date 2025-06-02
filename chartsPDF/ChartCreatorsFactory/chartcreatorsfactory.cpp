#include "chartcreatorsfactory.h"

ChartCreatorsFactory::ChartCreatorsFactory() {}

shared_ptr<IChartCreator> ChartCreatorsFactory::getCreator(const ChartType type)
{
    switch (type) {
    case ChartType::Bar: return make_shared<BarChartCreator>();
        break;
    case ChartType::Pie: return make_shared<PieChartCreator>();
        break;
    default:
        return nullptr;
        break;
    }
}
