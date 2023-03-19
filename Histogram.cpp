#include "Histogram.h"

#include <algorithm>
#include <map>
#include <random>
#include <stdexcept> 

using namespace std;

namespace Hist {

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

	// *********************  Histogram  **********************************
	bool sort_values(int i, int j) { return (i < j); }

	Histogram::Histogram(unique_ptr<Logger> logger) :
		HistogramBase(std::move(logger))
	{
	}

	Histogram::Histogram(const HistogramBase& other) : HistogramBase(other)
	{
	}

	Histogram::Histogram(HistogramBase&& other) : HistogramBase(other)
	{
	}

	Histogram::~Histogram()
	{
	}

	void Histogram::add(EInteger val)
	{
		if ( val< EInteger::Zero || val > EInteger::Four)
			throw out_of_range("Given value is out of required range");
		m_values.push_back(val);
		std::sort(m_values.begin(), m_values.end(), sort_values);
	}

	EInteger Histogram::getMode() const
	{
		if (m_values.size()<1)
			throw length_error("Histogram has no data. Cannot calculate value.");

		std::map<EInteger, int> counterMap;
		for (auto val : m_values)
			counterMap[val]++;
		EInteger mostFrequentEnu = EInteger::Undefined;
		int countMostFrequent = 0;
		for (auto it = counterMap.begin(); it != counterMap.end(); it++)
		{
			if (it->second > countMostFrequent)
			{
				countMostFrequent = it->second;
				mostFrequentEnu = it->first;
			}
		}
		return mostFrequentEnu;
	}

	EInteger Histogram::getMinValue() const
	{
		if (m_values.size() < 1)
			throw length_error("Histogram has no data. Cannot calculate value.");

		if (m_values.size() > 0)
			return m_values[0];
		return EInteger::Undefined;
	}

	// Return the largest value in the data set
	EInteger Histogram::getMaxValue() const
	{
		if (m_values.size() < 1)
			throw length_error("Histogram has no data. Cannot calculate value.");
		if (m_values.size() > 0)
			return m_values.back();
		return EInteger::Undefined;
	}

} // namespace Hist