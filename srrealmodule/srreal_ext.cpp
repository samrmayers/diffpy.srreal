/*****************************************************************************
*
* diffpy.srreal     by DANSE Diffraction group
*                   Simon J. L. Billinge
*                   (c) 2010 Trustees of the Columbia University
*                   in the City of New York.  All rights reserved.
*
* File coded by:    Pavol Juhas
*
* See AUTHORS.txt for a list of people who contributed.
* See LICENSE.txt for license information.
*
******************************************************************************
*
* srreal_ext - boost python interface to the srreal C++ codes in libdiffpy
*
* $Id$
*
*****************************************************************************/

#include <boost/python.hpp>

// Declaration of the external wrappers --------------------------------------

namespace srrealmodule {
void wrap_Attributes();
void wrap_BaseBondGenerator();
void wrap_PairQuantity();
void wrap_PeakWidthModel();
void wrap_PeakProfile();
void wrap_BVSCalculator();
void wrap_PDFBaseline();
void wrap_PDFEnvelope();
void wrap_PDFCalculators();
}   // namespace srrealmodule

// Module Definitions --------------------------------------------------------

BOOST_PYTHON_MODULE(srreal_ext)
{
    using namespace srrealmodule;
    // execute external wrappers
    wrap_Attributes();
    wrap_BaseBondGenerator();
    wrap_PairQuantity();
    wrap_PeakWidthModel();
    wrap_PeakProfile();
    wrap_BVSCalculator();
    wrap_PDFBaseline();
    wrap_PDFEnvelope();
    wrap_PDFCalculators();
}

// End of file
