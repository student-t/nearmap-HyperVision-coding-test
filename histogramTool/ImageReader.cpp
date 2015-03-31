#include <QImage>
#include <QColor>
#include "ImageReader.h"
#include "ThreadCoord.h"
#include "FileNotFoundException.h"

/*
 * A trait class used to construct RGB histogram
 */
template<typename T> class RGBHistogramTrait
{
public:
    RGBHistogramTrait(const QImage &image, RGBHistogram<T> &hist) : _hist(hist), _base((QRgb *) (image.bits())) {}

    void operator()(std::size_t i)
    {
        const QRgb color = *(_base + i);

        _hist.redHist.count(qRed(color));
        _hist.greenHist.count(qGreen(color));
        _hist.blueHist.count(qBlue(color));
    }

private:
    const QRgb *_base;
    RGBHistogram<T> &_hist;
};

template<typename T> void ImageReader<T>::calculate(RGBHistogram<T> &hist)
{
    QImage image;

    if (image.load(QString::fromUtf8(_file.c_str())))
    {
        ThreadCoord::start(image.width() * image.height(), _threads, RGBHistogramTrait<T>(image, hist));
    }
    else
    {
        throw FileNotFoundException(_file);
    }
}

template class ImageReader<int>;
