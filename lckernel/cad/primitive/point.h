#pragma once

#include "cad/const.h"
#include "cad/interface/entitydispatch.h"


#include "cad/geometry/geocoordinate.h"
#include "cad/base/cadentity.h"
#include "cad/vo/entitycoordinate.h"

#include "cad/interface/snapable.h"
#include "cad/interface/draggable.h"

#include <cad/meta/layer.h>

#include <cad/builders/point.h>

namespace lc {
namespace entity {
class Point : public std::enable_shared_from_this<Point>, public CADEntity, public geo::Coordinate, public Snapable, public Draggable, virtual public Visitable {
    friend class builder::PointBuilder;

public:
    /**
    * @brief Coordinate, Default Coordinate Constructor
    * @param geo::Coordinate coord
    * @param Layer_CSPtr layer
    * @param MetaTypes_CSPtr metaTypes
    */
    Point(geo::Coordinate coord,
          meta::Layer_CSPtr layer,
          meta::MetaInfo_CSPtr metaInfo = nullptr,
          meta::Block_CSPtr block = nullptr);

    /**
     * @brief Coordinate, Coordinate constructor with metatypes
     * @param double x
     * @param double y
     * @param Layer_CSPtr layer
     * @param MetaTypes_CSPtr metaTypes
     */
    Point(double x, double y,
          meta::Layer_CSPtr layer, meta::MetaInfo_CSPtr metaInfo = nullptr, meta::Block_CSPtr block = nullptr);

    Point(const Point_CSPtr& other, bool sameID = false);

private:
    Point(const builder::PointBuilder& builder);

public:
    CADEntity_CSPtr move(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr copy(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr rotate(const geo::Coordinate &rotation_center, double rotation_angle) const override;
    CADEntity_CSPtr scale(const geo::Coordinate &scale_center,
                          const geo::Coordinate &scale_factor) const override;
    CADEntity_CSPtr mirror(const geo::Coordinate& axis1,
                           const geo::Coordinate& axis2) const override;
    const geo::Area boundingBox() const override;
    CADEntity_CSPtr modify(meta::Layer_CSPtr layer, meta::MetaInfo_CSPtr metaInfo, meta::Block_CSPtr block) const override;
    std::vector<EntityCoordinate> snapPoints(const geo::Coordinate &coord,
            const SimpleSnapConstrain& constrain,
            double minDistanceToSnap,
            int maxNumberOfSnapPoints) const override;
    std::map<unsigned int, lc::geo::Coordinate> dragPoints() const override;
    CADEntity_CSPtr setDragPoints(std::map<unsigned int, lc::geo::Coordinate> dragPoints) const override;
    geo::Coordinate nearestPointOnPath(const Coordinate& coord) const;
    geo::Coordinate nearestPointOnEntity(const Coordinate& coord) const;

public:
    void accept(GeoEntityVisitor &v) const override {
        v.visit(*this);
    }

    void dispatch(EntityDispatch &ed) const override {
        ed.visit(shared_from_this());
    }

    PropertiesMap availableProperties() const override;
    CADEntity_CSPtr setProperties(const PropertiesMap& propertiesMap) const override;
};

DECLARE_SHORT_SHARED_PTR(Point)
}
}

