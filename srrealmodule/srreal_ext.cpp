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

#include <string>

#include <boost/python.hpp>

#include <diffpy/srreal/DebyePDFCalculator.hpp>
#include <diffpy/srreal/PDFCalculator.hpp>
#include <diffpy/srreal/PythonStructureAdapter.hpp>
#include <diffpy/srreal/ScatteringFactorTable.hpp>

#include "srreal_converters.hpp"
#include "srreal_docstrings.hpp"

// Declaration of the external wrappers --------------------------------------

namespace srrealmodule {
void wrap_Attributes();
void wrap_BaseBondGenerator();
void wrap_PairQuantity();
void wrap_PeakProfile();
void wrap_BVSCalculator();
}   // namespace srrealmodule

// Result converters ---------------------------------------------------------

namespace srrealmodule {

using namespace diffpy::srreal;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setsft_overloads,
        setScatteringFactorTable, 1, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getpkf_overloads,
        getPeakProfile, 0, 0)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getbaseline_overloads,
        getBaseline, 0, 0)

// DebyePDFCalculator and PDFCalculator wrappers

DECLARE_PYARRAY_METHOD_WRAPPER(getPDF, getPDF_asarray)
DECLARE_PYARRAY_METHOD_WRAPPER(getRDF, getRDF_asarray)
DECLARE_PYARRAY_METHOD_WRAPPER(getRgrid, getRgrid_asarray)
DECLARE_PYARRAY_METHOD_WRAPPER(getF, getF_asarray)
DECLARE_PYARRAY_METHOD_WRAPPER(getQgrid, getQgrid_asarray)
DECLARE_PYSET_FUNCTION_WRAPPER(getPeakWidthModelTypes,
        getPeakWidthModelTypes_asset)
DECLARE_PYSET_FUNCTION_WRAPPER(getScatteringFactorTableTypes,
        getScatteringFactorTableTypes_asset)
DECLARE_PYSET_FUNCTION_WRAPPER(getPeakProfileTypes, getPeakProfileTypes_asset)
DECLARE_PYSET_FUNCTION_WRAPPER(getPDFEnvelopeTypes, getPDFEnvelopeTypes_asset)
DECLARE_PYSET_FUNCTION_WRAPPER(getPDFBaselineTypes, getPDFBaselineTypes_asset)

}   // namespace srrealmodule

// Module Definitions --------------------------------------------------------

BOOST_PYTHON_MODULE(srreal_ext)
{
    using namespace boost::python;
    using namespace srrealmodule;

    // execute external wrappers
    wrap_Attributes();
    wrap_BaseBondGenerator();
    wrap_PairQuantity();
    wrap_PeakProfile();
    wrap_BVSCalculator();

    // DebyePDFCalculator

    class_<DebyePDFCalculator, bases<PairQuantity> >("DebyePDFCalculator_ext")
        .def("getPDF", getPDF_asarray<DebyePDFCalculator>)
        .def("getRgrid", getRgrid_asarray<DebyePDFCalculator>)
        .def("getF", getF_asarray<DebyePDFCalculator>)
        .def("getQgrid", getQgrid_asarray<DebyePDFCalculator>)
        .def("setOptimumQstep", &DebyePDFCalculator::setOptimumQstep)
        .def("isOptimumQstep", &DebyePDFCalculator::isOptimumQstep)
        .def("setScatteringFactorTable",
                (void(DebyePDFCalculator::*)(const std::string&)) NULL,
                setsft_overloads())
        .def("getRadiationType",
                &DebyePDFCalculator::getRadiationType,
                return_value_policy<copy_const_reference>())
        // static methods
        .def("getPeakWidthModelTypes",
                getPeakWidthModelTypes_asset,
                doc_getPeakWidthModelTypes)
        .staticmethod("getPeakWidthModelTypes")
        .def("getScatteringFactorTableTypes",
                getScatteringFactorTableTypes_asset,
                doc_getScatteringFactorTableTypes)
        .staticmethod("getScatteringFactorTableTypes")
        ;

    // PDFCalculator

    class_<PDFCalculator, bases<PairQuantity> >("PDFCalculator_ext")
        .def("getPDF", getPDF_asarray<PDFCalculator>)
        .def("getRDF", getRDF_asarray<PDFCalculator>)
        .def("getRgrid", getRgrid_asarray<PDFCalculator>)
        // PDF peak profile
        .def("getPeakProfile",
                (PeakProfilePtr(PDFCalculator::*)()) NULL,
                getpkf_overloads())
        .def("setPeakProfile", &PDFCalculator::setPeakProfile)
        .def("setPeakProfileByType", &PDFCalculator::setPeakProfileByType)
        .def("getPeakProfileTypes",
                getPeakProfileTypes_asset, doc_getPeakProfileTypes)
        .staticmethod("getPeakProfileTypes")
        .def("setScatteringFactorTable",
                (void(PDFCalculator::*)(const std::string&)) NULL,
                setsft_overloads())
        .def("getRadiationType",
                &PDFCalculator::getRadiationType,
                return_value_policy<copy_const_reference>())
        .def("getPeakWidthModelTypes",
                getPeakWidthModelTypes_asset,
                doc_getPeakWidthModelTypes)
        .staticmethod("getPeakWidthModelTypes")
        .def("getScatteringFactorTableTypes",
                getScatteringFactorTableTypes_asset,
                doc_getScatteringFactorTableTypes)
        .staticmethod("getScatteringFactorTableTypes")
        .def("getPDFEnvelopeTypes",
                getPDFEnvelopeTypes_asset, doc_getPDFEnvelopeTypes)
        .staticmethod("getPDFEnvelopeTypes")
        // PDF baseline
        .def("getBaseline",
                (PDFBaselinePtr(PDFCalculator::*)()) NULL,
                getbaseline_overloads())
        .def("setBaseline", &PDFCalculator::setBaseline)
        .def("setBaselineByType", &PDFCalculator::setBaselineByType)
        .def("getPDFBaselineTypes",
                getPDFBaselineTypes_asset, doc_getPDFBaselineTypes)
        .staticmethod("getPDFBaselineTypes")
        ;
}

// End of file
