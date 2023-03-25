#pragma once

#include <memory>

#include <map>


namespace Hist
{
    enum EInteger : int
    {
        Undefined = -1,
        Zero = 0,
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4
    };

    class Logger
    {
    public:
        Logger() {}
    };

    class RandomEintegerGeneratorBase
    {
    public:
        // Returns a pseudo-random EInteger value
        virtual EInteger operator()() = 0;
    };

    class HistogramBase
    {
    public:
        HistogramBase() = delete;
        HistogramBase(std::unique_ptr<Logger> ptr);
        HistogramBase(const HistogramBase&);
        HistogramBase(HistogramBase&&);
        virtual ~HistogramBase();

        /** Add EInteger data values into histogram
        */
        virtual void add(EInteger) = 0;

        /** Return the value that occurrs most often in the data set(I.e.there exists no other value that occurs more often than the return value)
        */
        virtual EInteger getMode() const = 0;

        /** Return the smallest value in the data set, according to default ordering relation of integer numbers
        */
        virtual EInteger getMinValue() const = 0;

        /** Return the largest value in the data set
        */
        virtual EInteger getMaxValue() const = 0;

    private:
        std::unique_ptr<Logger> m_log;

    };

    /** 
    *   Histogram class to calculate EInteger average/min/max values
    */
    class Histogram : public HistogramBase
    {
    public:
        explicit Histogram(std::unique_ptr<Logger> logger);
        explicit Histogram(const Histogram& base);
        explicit Histogram(Histogram&&);
        virtual ~Histogram();

        /** Add EInteger data values into histogram
          * @throw out_of_range Exception if input data is not in acceptable range
          */
        virtual void add(EInteger val) override;

        /** Return the value that occurrs most often in the data set(I.e.there exists no other value that occurs more often than the return value)
         * @throw length_error Exception if histogram does not contain data
         */
        virtual EInteger getMode() const override;

        /** Return the smallest value in the data set, according to default ordering relation of integer numbers
        * @throw length_error Exception if histogram does not contain data
        */
        virtual EInteger getMinValue() const override;

        /** Return the largest value in the data set
          * @throw length_error Exception if histogram does not contain data
         */
        virtual EInteger getMaxValue() const override;

    private:
        
        std::map<EInteger, int> m_countMap;

    };

}


