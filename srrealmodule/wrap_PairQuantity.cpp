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
* Bindings to the PairQuantity class.  The business protected methods
* can be overloaded from Python to create custom calculator.
* The class provides bindings to the eval and value methods for all derived
* calculators and also the double attributes access that is inherited from
* the Attributes wrapper in wrap_Attributes.
*
* Exported classes in Python:
*
* class BasePairQuantity_ext -- base class to all calculators in Python

* class PairQuantity_ext -- derived class with publicized protected methods
* _addPairContribution, _resetValue, etc.  Allows their overload from Python.
*
* $Id$
*
*****************************************************************************/

#include <boost/python.hpp>

#include <diffpy/srreal/PairQuantity.hpp>
#include <diffpy/srreal/BaseBondGenerator.hpp>
#include <diffpy/srreal/PythonStructureAdapter.hpp>

#include "srreal_converters.hpp"

namespace srrealmodule {
namespace nswrap_PairQuantity {

using namespace boost;
using namespace boost::python;
using namespace diffpy::srreal;

DECLARE_PYARRAY_METHOD_WRAPPER(value, value_asarray)

// PairQuantity::eval is a template non-constant method and
// needs an explicit wrapper function.

python::object eval_asarray(PairQuantity& obj, const python::object& a)
{
    python::object rv = convertToNumPyArray(obj.eval(a));
    return rv;
}


// Helper C++ class for publicizing the protected methods.

class PairQuantityExposed : public PairQuantity
{
    public:

        void resizeValue(size_t sz)
        {
            this->PairQuantity::resizeValue(sz);
        }


        void resetValue()
        {
            this->PairQuantity::resetValue();
        }


        void configureBondGenerator(BaseBondGenerator& bnds)
        {
            this->PairQuantity::configureBondGenerator(bnds);
        }


        void addPairContribution(const BaseBondGenerator& bnds)
        {
            this->PairQuantity::addPairContribution(bnds);
        }
};


// The second helper class allows overload of the exposed PairQuantity
// methods from Python.

class PairQuantityWrap :
    public PairQuantityExposed,
    public wrapper<PairQuantityExposed>
{
    public:

        // Make the protected virtual methods public so they
        // can be exported to Python and overloaded as well.

        void resizeValue(size_t sz)
        {
            override f = this->get_override("_resizeValue");
            if (f)  f(sz);
            else    this->default_resizeValue(sz);
        }

        void default_resizeValue(size_t sz)
        {
            this->PairQuantityExposed::resizeValue(sz);
        }


        void resetValue()
        {
            override f = this->get_override("_resetValue");
            if (f)  f();
            else    this->default_resetValue();
        }

        void default_resetValue()
        {
            this->PairQuantityExposed::resetValue();
        }


        void configureBondGenerator(BaseBondGenerator& bnds)
        {
            override f = this->get_override("_configureBondGenerator");
            if (f)  f(ptr(&bnds));
            else    this->default_configureBondGenerator(bnds);
        }

        void default_configureBondGenerator(BaseBondGenerator& bnds)
        {
            this->PairQuantityExposed::configureBondGenerator(bnds);
        }


        void addPairContribution(const BaseBondGenerator& bnds)
        {
            override f = this->get_override("_addPairContribution");
            if (f)  f(ptr(&bnds));
            else    this->default_addPairContribution(bnds);
        }

        void default_addPairContribution(const BaseBondGenerator& bnds)
        {
            this->PairQuantityExposed::addPairContribution(bnds);
        }

};  // class PairQuantityWrap

}   // namespace nswrap_PairQuantity

// Wrapper definition --------------------------------------------------------

void wrap_PairQuantity()
{
    using namespace nswrap_PairQuantity;
    using diffpy::Attributes;

    class_<PairQuantity, bases<Attributes> >("BasePairQuantity_ext")
        .def("value", value_asarray<PairQuantityWrap>)
        .def("eval", eval_asarray)
        ;

    class_<PairQuantityWrap, noncopyable,
        bases<PairQuantity> >("PairQuantity_ext")
        .def("_resizeValue",
                &PairQuantityExposed::resizeValue,
                &PairQuantityWrap::default_resizeValue)
        .def("_resetValue",
                &PairQuantityExposed::resetValue,
                &PairQuantityWrap::default_resetValue)
        .def("_configureBondGenerator",
                &PairQuantityExposed::configureBondGenerator,
                &PairQuantityWrap::default_configureBondGenerator)
        .def("_addPairContribution",
                &PairQuantityExposed::addPairContribution,
                &PairQuantityWrap::default_addPairContribution)
        ;
}

}   //  namespace srrealmodule

// End of file