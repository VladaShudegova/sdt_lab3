#ifndef CHARTCREATORSFACTORY_H
#define CHARTCREATORSFACTORY_H

#include <memory>

#include "ChartCreators/ichartcreator.h"
#include "ChartCreators/barchartcreator.h"
#include "ChartCreators/piechartcreator.h"
#include "ChartData/charttype.h"
#include "ichartcreatorsfactory.h"

using std::shared_ptr;
using std::make_shared;

class ChartCreatorsFactory: public IChartCreatorsFactory{
private:
    using CreatorFunc = std::function<std::shared_ptr<IChartCreator>()>;
    std::unordered_map<ChartType, CreatorFunc> creators;

public:
    template<typename T>
    void registerCreator(const ChartType& type) {
        creators[type] = []() { return std::make_shared<T>(); };
    }

    ChartCreatorsFactory();

    std::shared_ptr<IChartCreator> getCreator(const ChartType& type) const override;
};


#endif // CHARTCREATORSFACTORY_H
