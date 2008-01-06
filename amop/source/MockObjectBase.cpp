#include "MockObjectBase.h"

#include "VirtualTable.h"
#include "CheckOffsetFunc.h"
#include "CallHandler.h"
#include "Any.h"
#include "ObjectHolder.h"
#include "ReturnMatchBuilder.h"
#include "MockObjectException.h"
#include "Comparable.h"

#include <map>

namespace amop
{

namespace Detail
{

//------------------------------------------------------------------
TMockObjectBase::TMockObjectBase()
{
	mVirtualTable = Detail::CreateVirtualTable(
		this);
}

//------------------------------------------------------------------
TMockObjectBase::~TMockObjectBase()
{
}		

//------------------------------------------------------------------
void TMockObjectBase::AddCallCounter(size_t idx)
{
	mCallCounter[idx]++;
}

//------------------------------------------------------------------
void TMockObjectBase::SetReturnDefault(size_t idx, const any& result)
{
	mReturnDefaults[idx] = result;
}

//------------------------------------------------------------------
void TMockObjectBase::SetReturn(size_t idx, const any& result)
{
	mReturns[idx].push_back(result);
}

//------------------------------------------------------------------
any& TMockObjectBase::GetReturn(size_t idx)
{
	size_t callCounter = mCallCounter[idx] - 1;
	
	if( mReturns.count(idx) && 
		callCounter < mReturns[idx].size())
	{
		return (mReturns[idx])[callCounter] ;
	}	
	
	return mReturnDefaults[idx];
}

//------------------------------------------------------------------
void TMockObjectBase::SetActual(size_t idx, size_t paramId, const any& param)
{
	if(!mExpects.count(idx)) return ;
	TParamMap& paramMap = mExpects[idx];	

	if(!paramMap.count(paramId)) return ;
	
	TComparableList& clist = paramMap[paramId];
	size_t callCounter = mCallCounter[idx];

	if( clist.size() <= callCounter )
	{
		if(!mExpectDefaults.count(idx)) return ;
		TParamDefaultMap& paramDefaultMap = mExpectDefaults[idx];
		
		if( paramDefaultMap.count(paramId) ) return ;

		if( paramDefaultMap[paramId] != param )
			throw TNotEqualException(paramId, paramDefaultMap[paramId], param);
	}

	if( clist[callCounter] != param )
		throw TNotEqualException(paramId, clist[callCounter], param);
}

//------------------------------------------------------------------
void TMockObjectBase::SetExpectDefault(size_t idx, size_t paramId, const TComparable& param)
{
	(mExpectDefaults[idx])[paramId] = param;
}

//------------------------------------------------------------------
void TMockObjectBase::SetExpect(size_t idx, size_t paramId, const TComparable& param)
{
	(mExpects[idx])[paramId].push_back(param);
}

//------------------------------------------------------------------
void* TMockObjectBase::GetVptr()
{
	return &mVirtualTable->mVtpr;
}

}
}