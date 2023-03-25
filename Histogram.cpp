#include "Histogram.h"

#include <algorithm>
#include <map>
//#include <random>
#include <stdexcept> 

using namespace std;

namespace Hist {

	// *********************  HistogramBase class  **********************************

	HistogramBase::HistogramBase(std::unique_ptr<Logger> logger)
	{
		m_log = std::move(logger);
	}

	HistogramBase::HistogramBase(const HistogramBase& other) :
		m_log(unique_ptr<Logger>(other.m_log.get()))
	{
	}

	HistogramBase::HistogramBase(HistogramBase&& other) :
		m_log(unique_ptr<Logger>(other.m_log.get()))
	{
	}

	HistogramBase::~HistogramBase() {}

	// *********************  Histogram class **********************************

	EInteger calculateMode(const std::map<EInteger, int>& countMap);

	Histogram::Histogram(unique_ptr<Logger> logger) :
		HistogramBase(std::move(logger))
	{
		m_countMap = { 
			{EInteger::Zero , 0},
			{EInteger::One , 0},
			{EInteger::Two , 0},
			{EInteger::Three , 0},
			{EInteger::Four , 0}
		};
	}

	Histogram::Histogram(const Histogram& other) 
		: HistogramBase(other),
		m_countMap(other.m_countMap)
	{
	}

	Histogram::Histogram(Histogram&& other) 
		: HistogramBase(other),
		m_countMap(other.m_countMap)
	{
	}

	Histogram::~Histogram()
	{
	}

	void Histogram::add(EInteger val)
	{
		if ( val< EInteger::Zero || val > EInteger::Four)
			throw out_of_range("Given value is out of required range");
		m_countMap[val]++;
	}

	EInteger Histogram::getMode() const
	{
		if (m_countMap.size()<1)
			throw length_error("Histogram has no data. Cannot calculate value.");

		return calculateMode(m_countMap);
	}

	EInteger Histogram::getMinValue() const
	{
		if (m_countMap.size() < 1)
			throw length_error("Histogram has no data. Cannot calculate value.");
		for (auto iter = m_countMap.begin(); iter != m_countMap.end(); ++iter) {
			if (iter->second > 0)
				return iter->first;
		}
		return EInteger::Undefined;
	}

	// Return the largest value in the data set
	EInteger Histogram::getMaxValue() const
	{
		if (m_countMap.size() < 1)
			throw length_error("Histogram has no data. Cannot calculate value.");
		for (auto iter = m_countMap.rbegin(); iter != m_countMap.rend(); ++iter) {
			if (iter->second > 0)
				return iter->first;
		}
		return EInteger::Undefined;
	}

	EInteger calculateMode(const std::map<EInteger, int>& countMap)
	{
		int biggestCount = 0;
		EInteger biggestType = EInteger::Undefined;
		for (auto iter = countMap.begin(); iter != countMap.end(); ++iter) {
			if (iter->second > biggestCount)
			{
				biggestCount = iter->second;
				biggestType = iter->first;
			}
		}
		return biggestType;
	}
} // namespace Hist