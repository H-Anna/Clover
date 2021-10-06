#ifndef ENUMCONVERTER_H
#define ENUMCONVERTER_H

#include <surface_enums.h>

#include <QString>
#include <QMap>

class EnumConverter
{
public:
    static DrawMethod GetDrawMethod(const QString& dm) {

        return drawMethodMap.value(dm, DrawMethod::Base);
    };
    static QString GetDrawMethod(DrawMethod dm) {

        return drawMethodMap.key(dm, "");
    };

    static Frequency GetFrequency(const QString& f) {

        return frequencyMap.value(f, Frequency::Never);
    };
    static QString GetFrequency(Frequency f) {

        return frequencyMap.key(f, "");
    };

private:
    const static inline QMap<QString,DrawMethod> drawMethodMap = {
            {"base", DrawMethod::Base},
            {"overlay", DrawMethod::Overlay},
            {"clip", DrawMethod::Clip},
            {"replace", DrawMethod::Replace}
        };

    const static inline QMap<QString,Frequency> frequencyMap = {
        {"always", Frequency::Always},
        {"never", Frequency::Never}
    };
};

#endif // ENUMCONVERTER_H
