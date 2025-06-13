#include "chartcreatorsfactory.h"

ChartCreatorsFactory::ChartCreatorsFactory() {
    registerReader<BarChartCreator>(ChartType::Bar);
    registerReader<PieChartCreator>(ChartType::Pie);
}

std::shared_ptr<IChartCreator> ChartCreatorsFactory::getCreator(const ChartType& type) const {
    auto it = ChartCreatorsFactory::creators.find(type);
    if (it != ChartCreatorsFactory::creators.end()) {
        return it->second();
    }
    return nullptr;
}
