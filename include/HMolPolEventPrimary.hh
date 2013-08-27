/********************************************
 * \author <b>Programmer:<\b> Valerie Gray
 * \author <b>Assisted By:<\b> Wouter Deconinck
 *
 * \brief <b>Purpose:</b> This is header file for the Primary event.
 *
 * \date <b>Date:</b> 07-17-2013
 * \date <b>Modified:</b> 07-26-2013
 *
 * \note <b>Entry Conditions:</b> none
 *
********************************************/


#ifndef HMOLPOLPRIMARYEVENT_HH_
#define HMOLPOLPRIMARYEVENT_HH_

// root include
#include <TObject.h>

class HMolPolEventPrimary: public TObject {
  public:
    HMolPolEventPrimary();  ///< constructor for the primary event
    virtual ~HMolPolEventPrimary();  ///< destuctor for the primary event

    Double_t fCrossSection;  ///< the cross section
    Double_t fPhiLab;        ///< the lab phi angle (same as CM phi angle)
    Double_t fThetaLab1;     ///< the lab theta angle for one particle
    Double_t fThetaLab2;     ///< the lab theta angle for one particle
    Double_t fPhiCenterOfMass;   ///< the CM phi angle
    Double_t fThetaCenterOfMass;        ///< the CM theta angle
    Double_t fInteractionVertexPositionX; ///< Interaction vertex position in X
    Double_t fInteractionVertexPositionY; ///< Interaction vertex position in Y
    Double_t fInteractionVertexPositionZ; ///< Interaction vertex position in Z
    Double_t fInteractionVertexMomentumX; ///< Interaction vertex momentum in X
    Double_t fInteractionVertexMomentumY; ///< Interaction vertex momentum in Y
    Double_t fInteractionVertexMomentumZ; ///< Interaction vertex momentum in Z

    // define a new Class known to ROOT? Huh?
    ClassDef(HMolPolEventPrimary,1)

};

#endif /* HMOLPOLPRIMARYEVENT_HH_ */
