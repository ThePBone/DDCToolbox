#ifndef BIQUAD_H
#define BIQUAD_H
#include <list>

class biquad
{
public:
    enum Type
    {
        LOW_PASS, HIGH_PASS, BAND_PASS, NOTCH, ALL_PASS, PEAKING, LOW_SHELF, HIGH_SHELF, UNITY_GAIN
    };
    biquad();
    void RefreshFilter(Type type,double dbGain, double centreFreq, double fs, double dBandwidthOrQOrS, bool isBandwidthOrS);
    std::list<double> ExportCoeffs(Type type,double dbGain, double centreFreq, double fs, double dBandwidthOrQOrS, bool isBandwidthOrS);
    std::list<double> ExportCoeffs(double dSamplingRate);
    double GainAt(double centreFreq, double fs);
    double GroupDelayAt(double centreFreq, double fs);


private:
    double internalBiquadCoeffs[4];
    double a0;
    double m_dFilterBQ;
    double m_dFilterFreq;
    double m_dFilterGain;
    Type m_dFilterType;
    bool m_isBandwidthOrS;
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
