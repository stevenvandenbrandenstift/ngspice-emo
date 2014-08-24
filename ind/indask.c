/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "ngspice/ngspice.h"
#include "inddefs.h"
#include "ngspice/ifsim.h"
#include "ngspice/cktdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"

/*ARGSUSED*/
int
INDask(CKTcircuit *ckt, GENinstance *inst, int which, IFvalue *value,
       IFvalue *select)
{
    INDinstance *here = (INDinstance*)inst;
    double vr;
    double vi;
    double sr;
    double si;
    double vm;
    double energy;
    char *activityString;
    double activity;   
    char *workingZoneString;
    double workingZone;
    static char *msg = "Current and power not available for ac analysis";

    switch(which) {
        case IND_FLUX:
            value->rValue = *(ckt->CKTstate0+here->INDflux);
            return(OK);
        case IND_VOLT:
            value->rValue = *(ckt->CKTstate0+here->INDvolt);
            return(OK);
        case IND_IND:
            value->rValue = here->INDinduct;
            return(OK);
        case IND_IC:
            value->rValue = here->INDinitCond;
            return(OK);
        case IND_TEMP:
            value->rValue = here->INDtemp - CONSTCtoK;
            return(OK);
        case IND_DTEMP:
            value->rValue = here->INDdtemp;
            return(OK);
        case IND_M:
            value->rValue = here->INDm;
            return(OK);
        case IND_TC1:
            value->rValue = here->INDtc1;
            return(OK);
        case IND_TC2:
            value->rValue = here->INDtc2;
            return(OK);
        case IND_SCALE:
            value->rValue = here->INDscale;
            return(OK);
        case IND_NT:
            value->rValue = here->INDnt;
            return(OK);
        case IND_CURRENT :
            if (ckt->CKTcurrentAnalysis & DOING_AC) {
                errMsg = TMALLOC(char, strlen(msg) + 1);
                errRtn = "INDask";
                strcpy(errMsg,msg);
                return(E_ASKCURRENT);
            } else {
                value->rValue = *(ckt->CKTrhsOld + here->INDbrEq);
            }
            return(OK);
        case IND_POWER :
            if (ckt->CKTcurrentAnalysis & DOING_AC) {
                errMsg = TMALLOC(char, strlen(msg) + 1);
                errRtn = "INDask";
                strcpy(errMsg,msg);
                return(E_ASKPOWER);
            } else {
                value->rValue = *(ckt->CKTrhsOld + here->INDbrEq) *
                        *(ckt->CKTstate0+here->INDvolt);
            }
            return(OK);
        case IND_QUEST_SENS_DC:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_Sap[select->iValue + 1]+
                        here->INDsenParmNo);
            }
            return(OK);
        case IND_QUEST_SENS_REAL:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                    here->INDsenParmNo);
            }
            return(OK);
        case IND_QUEST_SENS_IMAG:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        here->INDsenParmNo);
            }
            return(OK);
        case IND_QUEST_SENS_MAG:
            if(ckt->CKTsenInfo){
                vr = *(ckt->CKTrhsOld + select->iValue + 1);
                vi = *(ckt->CKTirhsOld + select->iValue + 1);
                vm = sqrt(vr*vr + vi*vi);
                if(vm == 0){
                    value->rValue = 0;
                    return(OK);
                }
                sr = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        here->INDsenParmNo);
                si = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        here->INDsenParmNo);
                value->rValue = (vr * sr + vi * si)/vm;
            }
            return(OK);
        case IND_QUEST_SENS_PH:
            if(ckt->CKTsenInfo){
                vr = *(ckt->CKTrhsOld + select->iValue + 1);
                vi = *(ckt->CKTirhsOld + select->iValue + 1);
                vm = vr*vr + vi*vi;
                if(vm == 0){
                    value->rValue = 0;
                    return(OK);
                }
                sr = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        here->INDsenParmNo);
                si = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        here->INDsenParmNo);
                value->rValue = (vr * si - vi * sr)/vm;
            }
            return(OK);
        case IND_QUEST_SENS_CPLX:
            if(ckt->CKTsenInfo){
                value->cValue.real=
                        *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        here->INDsenParmNo);
                value->cValue.imag=
                        *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        here->INDsenParmNo);
            }
            return(OK);
    case IND_ENERGY:
        value->rValue = (here->INDratedCurrent*here->INDratedCurrent*here->INDinduct)/2;
        return(OK);
    
   case IND_RATED_CURRENT:
        value->rValue = here->INDratedCurrent;
        return(OK);

    case IND_WORKING_ZONE:
    		if (ckt->CKTrhsOld) {
         
    		workingZone = *(ckt->CKTrhsOld + here->INDbrEq) *
                            here->INDinduct* (1/2) *
                            ( *(ckt->CKTrhsOld + here->INDbrEq));
            if(workingZone<0){
    		workingZone*=-1;
    		}
    		workingZone=workingZone/here->INDenergy;
            workingZone *= here->INDm;
            if(workingZone<0.5){
            workingZoneString = TMALLOC(char, strlen("Sub-optimal") + 10);
            sprintf(workingZoneString, "suboptimal:%f",workingZone);
            value->sValue=workingZoneString;
            }else if(workingZone<=1){
               workingZoneString = TMALLOC(char, strlen("Optimal") + 10);
               sprintf(workingZoneString, "optimal:%f",workingZone);
            	value->sValue=workingZoneString;
            }else if(workingZone<1.1){
                workingZoneString = TMALLOC(char, strlen("Out of Range") + 10);
                sprintf(workingZoneString, "outofrange:%f",workingZone);
            	value->sValue=workingZoneString;
            }else{
                workingZoneString = TMALLOC(char, strlen("Destructive") + 10);
                sprintf(workingZoneString, "destructive:%f",workingZone);
            	value->sValue=workingZoneString;
            }
            }else{
            	workingZoneString = TMALLOC(char, strlen("Unknown"));
                sprintf(workingZoneString, "Unknown");
               	value->sValue=workingZoneString;
            }

        //value->rValue /= here->RESm;
        return(OK);
        
        case IND_ACTIVITY:
        	if(ckt->CKTrhsOld){
			   energy = ( *(ckt->CKTrhsOld + here->INDbrEq)) *
                            here->INDinduct * (1/2) *
                            ( *(ckt->CKTrhsOld + here->INDbrEq));
			   energy *= here->INDm;
           		if(ckt->CKTcurrentAnalysis &  (DOING_AC | DOING_TRAN)){
        	   	activity=here->INDenergySum/ckt->CKTtimePoints[ckt->CKTtimeIndex]; // energy in cap
        		activity+=energy/ckt->CKTdeltaList[ckt->CKTtimeIndex]; //divide by time lapse
        		activity/=(here->INDenergy*here->INDm); // normalize
        		}else{ //dc or op
            		activity=energy/(here->INDenergy*here->INDm);
        		}
        	if(activity<0.1){
            activityString = TMALLOC(char, strlen("Inactive") + 10);
            sprintf(activityString, "inactive:%f",activity);
            value->sValue=activityString;
            }else if(activity<0.3){
                activityString = TMALLOC(char, strlen("Sub-active") + 10);
                sprintf(activityString, "subactive:%f",activity);
            	value->sValue=activityString;
            }else if(activity<=1.0){
                activityString = TMALLOC(char, strlen("Normal-active") + 10);
                sprintf(activityString, "normalactive:%f",activity);
            	value->sValue=activityString;
            }else{
                activityString = TMALLOC(char, strlen("Over-active") + 10);
                sprintf(activityString, "overactive:%f",activity);
            	value->sValue=activityString;
            }
            }else{
            	activityString = TMALLOC(char, strlen("Unknown"));
                sprintf(activityString, "Unknown");
            	value->sValue=activityString;
            }
	  return(OK); 
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}
