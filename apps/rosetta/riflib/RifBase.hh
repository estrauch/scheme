// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://wsic_dockosettacommons.org. Questions about this casic_dock
// (c) addressed to University of Waprotocolsgton UW TechTransfer, email: license@u.washington.eprotocols

#ifndef INCLUDED_riflib_RifBase_hh
#define INCLUDED_riflib_RifBase_hh

#include <riflib/types.hh>

#include <string>
#include <vector>
#include <boost/any.hpp>


namespace scheme { namespace search { struct HackPackOpts; }}

namespace devel {
namespace scheme {

struct RifBase
{
	RifBase() : type_("") {}
	RifBase( std::string type ) : type_(type){}
	std::string type() const { return type_; }
	std::string type_;

	virtual void get_rotamers_for_xform( EigenXform const & x, std::vector< std::pair< float, int > > & rotscores ) const = 0;
	virtual void get_rotamer_ids_in_use( std::vector<bool> & using_rot ) const = 0;
	virtual void print( std::ostream & out ) const = 0;
	virtual void collision_analysis( std::ostream & out ) const = 0;
	virtual std::string value_name() const = 0;

	virtual size_t size() const = 0;
	virtual float  load_factor() const = 0;
	virtual float  cart_resl() const = 0;
	virtual float  ang_resl() const = 0;
	virtual size_t mem_use() const = 0;
	virtual size_t sizeof_value_type() const = 0;
	virtual bool  has_sat_data_slots() const = 0;

	template< class XMap > bool get_xmap_ptr( shared_ptr<XMap> & xmap_ptr );
	template< class XMap > bool get_xmap_const_ptr( shared_ptr<XMap const> & xmap_ptr ) const;
	template< class XMap > bool set_xmap_ptr( shared_ptr<XMap> const & xmap_ptr );
	virtual bool set_xmap_ptr( boost::any * any_p ) = 0;
	virtual bool get_xmap_ptr( boost::any * any_p ) = 0;
	virtual bool get_xmap_const_ptr( boost::any * any_p ) const = 0;

	virtual bool load( std::istream & in , std::string & description ) = 0;
	virtual bool save( std::ostream & out, std::string & description ) = 0;

	virtual void finalize_rif() = 0;

};

typedef shared_ptr<RifBase> RifPtr;
typedef shared_ptr<RifBase const> RifConstPtr;

template< class XMap >
bool RifBase::get_xmap_ptr( shared_ptr<XMap> & xmap_ptr )
{
	boost::any any = static_cast< shared_ptr<XMap> const>( xmap_ptr );
	if( get_xmap_ptr( &any ) ){
		xmap_ptr = boost::any_cast< shared_ptr<XMap> const>( any );
		return true;
	}
	return false;
}
template< class XMap >
bool RifBase::get_xmap_const_ptr( shared_ptr<XMap const> & xmap_ptr ) const
{
	boost::any any = static_cast< shared_ptr<XMap const> const>( xmap_ptr );
	if( get_xmap_const_ptr( &any) ){
		xmap_ptr = boost::any_cast< shared_ptr<XMap const> const>( any );
		return true;
	}
	return false;
}
template< class XMap >
bool RifBase::set_xmap_ptr( shared_ptr<XMap> const & xmap_ptr )
{
	boost::any any = static_cast< shared_ptr<XMap> >( xmap_ptr );
	return set_xmap_ptr( &any );
}


}}

#endif
