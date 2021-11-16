#include "hotspotvariable.h"

HotspotVariable::HotspotVariable(const QString _name, Interaction _interaction):
    name(_name),
    interaction(_interaction)
{

}

const QString &HotspotVariable::GetName() const
{
    return name;
}

const HotspotVariable::Interaction HotspotVariable::GetInteraction() const
{
    return interaction;
}

//const unsigned int HotspotVariable::GetThreshold() const
//{
//    return threshold;
//}
