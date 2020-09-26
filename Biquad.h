#ifndef BIQUAD_H
#define BIQUAD_H
#include <list>
#include <cmath>
#include <cfloat>
#include <cstdint>

#include "FilterType.h"

typedef struct customFilter_s{
    double a0;
    double a1;
    double a2;
    double b0;
    double b1;
    double b2;
}customFilter_t;

class Biquad
{
public:
    enum Stability
    {
        UNSTABLE = 0,
        STABLE = 1,
        PARTIALLY_STABLE = 2
    };

    Biquad();
    void RefreshFilter(uint32_t id, FilterType type,double dbGain, double centreFreq, double fs, double dBandwidthOrQOrS, bool isBandwidthOrS);
    void RefreshFilter(uint32_t id, FilterType type, customFilter_t c441, customFilter_t c48);
    std::list<double> ExportCoeffs(FilterType type,double dbGain, double centreFreq, double fs, double dBandwidthOrQOrS, bool isBandwidthOrS);
    std::list<double> ExportCoeffs(double dSamplingRate);
    std::list<double> ExportCoeffs(customFilter_t coeffs);

    double GainAt(double centreFreq, double fs);
    double PhaseResponseAt(double centreFreq, double fs);
    double GroupDelayAt(double centreFreq, double fs);

    void iirroots(double b, double c, double *roots);
    int complexResponse(double centreFreq, double fs, double *HofZReal, double *HofZImag);
    double toMs(double sample, double fs);

    Stability IsStable() const {
        return m_isStable;
    };

    uint32_t GetId() const{
        return m_id;
    }

    FilterType GetFilterType() const{
        return m_dFilterType;
    };

    double GetFrequency() const{
        return m_dFilterFreq;
    };

    double GetBandwithOrSlope() const{
        return m_dFilterFreq;
    };

    double GetGain() const{
        return m_dFilterFreq;
    };

    bool IsCustomFilter() const{
        return m_dFilterType == FilterType::CUSTOM;
    };

    customFilter_t GetCustomFilter(int samplerate) const{
        return samplerate == 44100 ? m_custom441 : m_custom48;
    };

private:
    double internalBiquadCoeffs[5];
    double m_dFilterBQ;
    double m_dFilterFreq;
    double m_dFilterGain;
    FilterType m_dFilterType;
    bool m_isBandwidthOrS;
    Stability m_isStable;
    bool m_isCustom;
    uint32_t m_id;
    customFilter_t m_custom441;
    customFilter_t m_custom48;

    inline void complexMultiplicationRI(double *zReal, double *zImag, double xReal, double xImag, double yReal, double yImag)
    {
        *zReal = xReal * yReal - xImag * yImag;
        *zImag = xReal * yImag + xImag * yReal;
    }
    inline void complexDivisionRI(double *zReal, double *zImag, double xReal, double xImag, double yReal, double yImag)
    {
        *zReal = (xReal * yReal + xImag * yImag) / (yReal * yReal + yImag * yImag);
        *zImag = (xImag * yReal - xReal * yImag) / (yReal * yReal + yImag * yImag);
    }
};

#endif // BIQUAD_H
