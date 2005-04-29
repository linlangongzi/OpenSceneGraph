/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2005 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
//osgIntrospection - Copyright (C) 2005 Marco Jez

#include <osgIntrospection/MethodInfo>

using namespace osgIntrospection;

void MethodInfo::getInheritedProviders(CustomAttributeProviderList &providers) const
{
    for (int i=0; i<decltype_.getNumBaseTypes(); ++i)
    {
        const MethodInfo *mi = decltype_.getBaseType(i).getMethod(name_, params_, false);
        if (mi)
        {
            providers.push_back(mi);
        }
    }
}

bool MethodInfo::overrides(const MethodInfo *other) const
{
	if (isConst() != other->isConst()) return false;
	if (decltype_ != other->decltype_) return false;
	if (rtype_ != other->rtype_) return false;
	if (name_ != other->name_) return false;
	if (params_.size() != other->params_.size()) return false;

	ParameterInfoList::const_iterator i=params_.begin();
	ParameterInfoList::const_iterator j=other->params_.begin();
	for (; i!=params_.end(); ++i, ++j)
	{
		if (&(*i)->getParameterType() != &(*j)->getParameterType())
			return false;
	}

	return true;

/*
	std::size_t num_fixed_1 = 0;
	std::size_t num_optional_1 = 0;
	for (ParameterInfoList::const_iterator i=params_.begin(); i!=params_.end(); ++i)
	{
		if ((*i)->getDefaultValue().isEmpty())
			++num_fixed_1;
		else
			++num_optional_1;
	}

	std::size_t num_fixed_2 = 0;
	std::size_t num_optional_2 = 0;
	for (ParameterInfoList::const_iterator i=other->params_.begin(); i!=other->params_.end(); ++i)
	{
		if ((*i)->getDefaultValue().isEmpty())
			++num_fixed_2;
		else
			++num_optional_2;
	}

	if (num_fixed_1 > num_fixed_2)
	{
	}
*/
}
