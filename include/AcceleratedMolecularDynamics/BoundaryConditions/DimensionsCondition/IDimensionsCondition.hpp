#pragma once
#ifndef TAHD_INTERFACE_DIMENSIONS_CONDITION_H
#define TAHD_INTERFACE_DIMENSIONS_CONDITION_H

namespace md
{
    class IDimensionsCondition
    {
    public:
        virtual double getSize() const noexcept = 0;
        virtual double normalizeProjection(double coordinate) const = 0;
        virtual double normalizeProjectionsDifference(double projectionFirst, double projectionSecond) const = 0;
        virtual ~IDimensionsCondition() = 0;
    };
}

#endif  //TAHD_INTERFACE_DIMENSIONS_CONDITION_H
