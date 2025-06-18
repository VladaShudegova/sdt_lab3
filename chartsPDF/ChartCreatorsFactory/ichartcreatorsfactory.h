#ifndef ICHARTCREATORSFACTORY_H
#define ICHARTCREATORSFACTORY_H

#include <memory>

#include "ChartCreators/ichartcreator.h"

using std::shared_ptr;
using std::make_shared;


class IChartCreatorsFactory {
public:
    virtual ~IChartCreatorsFactory() = default;

    virtual std::shared_ptr<IChartCreator> getCreator(const ChartType& type) const = 0;
};

#endif // ICHARTCREATORSFACTORY_H
