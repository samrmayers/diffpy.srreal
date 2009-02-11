/*****************************************************************************
*
* diffpy.srreal     by DANSE Diffraction group
*                   Simon J. L. Billinge
*                   (c) 2009 Trustees of the Columbia University
*                   in the City of New York.  All rights reserved.
*
* File coded by:    Christopher Farrow, Pavol Juhas
*
* See AUTHORS.txt for a list of people who contributed.
* See LICENSE.txt for license information.
*
******************************************************************************
*
* class ConstantPeakWidth -- constant peak width
*
* $Id$
*
*****************************************************************************/

#ifndef CONSTANTPEAKWIDTH_HPP_INCLUDED
#define CONSTANTPEAKWIDTH_HPP_INCLUDED

#include <diffpy/srreal/BasePeakWidthModel.hpp>

namespace diffpy {
namespace srreal {


class ConstantPeakWidth : public BasePeakWidthModel
{
    public:

        // constructors
        ConstantPeakWidth();
        virtual BasePeakWidthModel* create() const;
        virtual BasePeakWidthModel* copy() const;

        // comparison with derived classes
        virtual bool operator==(const BasePeakWidthModel&) const;

        // methods
        virtual const std::string& type() const;
        virtual double calculate(const BaseBondGenerator&) const;

        // data access
        const double& getWidth() const;
        void setWidth(double);

    private:

        // data
        double mwidth;

};


}   // namespace srreal
}   // namespace diffpy

#endif  // CONSTANTPEAKWIDTH_HPP_INCLUDED
