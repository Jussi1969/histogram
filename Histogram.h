#pragma once

#include <memory>
#include <vector>

/*
Toteuta HistogramBase - luokalle aliluokka Histogram :

Luokan olioille voi syöttää tietoaineiston alkioita, eli EInteger - enumeraation alkioita.
Histogrammilta voi pyytää tietoaineiston moodin, eli arvon joka esiintyy useimmin aineistossa, sekä aineiston pienimmän ja suurimman arvon.
Dokumentoi mahdolliset virhe - tai poikkeustilanteet lyhyesti luokan esittelyn yhteyteen Doxygen(Javadoc) tyylillä.
Anna aliluokan esittely ja toteutus tiedostoissa Histogram.h ja Histogram.cpp.
HistogramBase tarvitsee toimiakseen osoittimen Logger - luokan olioon.Logger - luokalla on oletusrakentaja.
Luokan testaamista varten toteuta luokalle RandomEintegerGeneratorBase aliluokka RandomEintegerGenerator, joka luo EInteger -
tyyppisiä arvoja.Arvojen satunnaisuuden laadulla ei ole tässä suurta merkitystä.Anna aliluokan esittely ja toteutus tiedostoissa RandomEintegerGenerator.h ja RandomEintegerGenerator.cpp.
*/


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
        //RandomEintegerGeneratorBase() {}
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

        virtual void add(EInteger) = 0;

        /** Return the value that occurrs most often in the data set(I.e.there exists no other value that occurs more often than the return value)
        * @throw length_error Exception if histogram does not contain data
        */
        virtual EInteger getMode() const = 0;

        /** Return the smallest value in the data set, according to default ordering relation of integer numbers
        * @throw length_error Exception if histogram does not contain data
        */
        virtual EInteger getMinValue() const = 0;

        /** Return the largest value in the data set
         * @throw length_error Exception if histogram does not contain data
        */
        virtual EInteger getMaxValue() const = 0;

    private:
        std::unique_ptr<Logger> m_log;

    };

    // ************************************************************************************

    class Histogram : public HistogramBase
    {
    public:
        Histogram(std::unique_ptr<Logger> logger);
        Histogram(const HistogramBase& base);
        Histogram(HistogramBase&&);
        virtual ~Histogram();

        /** 
          * @throw out_of_range Exception if input data is not in acceptable range
          */
        virtual void add(EInteger val);

        /** Return the value that occurrs most often in the data set(I.e.there exists no other value that occurs more often than the return value)
         * @throw length_error Exception if histogram does not contain data
         */
        virtual EInteger getMode() const;

        /** Return the smallest value in the data set, according to default ordering relation of integer numbers
        * @throw length_error Exception if histogram does not contain data
        */
        virtual EInteger getMinValue() const;

        /** Return the largest value in the data set
          * @throw length_error Exception if histogram does not contain data
         */
        virtual EInteger getMaxValue() const;

    private:
        std::vector<EInteger> m_values;

    };

}

class MyCustomException : public std::exception {
private:
    char* message;

public:
    MyCustomException(char* msg) : message(msg) {}
    char* what() {
        return message;
    }
};
//#endif

