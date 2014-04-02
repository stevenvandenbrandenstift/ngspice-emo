/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Kanwar Jit Singh
**********/
/*
 * singh@ic.Berkeley.edu
 */

#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "asrcdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


/*ARGSUSED*/
int
ASRCsetup(SMPmatrix *matrix, GENmodel *inModel, CKTcircuit *ckt, int *states)
        /* load the voltage source structure with those 
     * pointers needed later for fast matrix loading 
         */

{
    ASRCinstance *here;
    ASRCmodel *model = (ASRCmodel*)inModel;
    int error, i, j;
    int v_first;
    CKTnode *tmp;

    NG_IGNORE(states);

    /*  loop through all the user models*/
    for( ; model != NULL; model = model->ASRCnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->ASRCinstances; here != NULL ;
                here=here->ASRCnextInstance) {
            
            if(!here->ASRCtc1Given) here->ASRCtc1 = 0.0;
            if(!here->ASRCtc2Given) here->ASRCtc2 = 0.0;
            if(!here->ASRCreciproctcGiven) here->ASRCreciproctc = 0;

            here->ASRCposptr = NULL;
            j=0; /*strchr of the array holding ptrs to SMP */
            v_first = 1;
            if( here->ASRCtype == ASRC_VOLTAGE){
                if(here->ASRCbranch==0) {
                    error = CKTmkCur(ckt,&tmp,here->ASRCname,"branch");
                    if(error) return(error);
                    here->ASRCbranch = tmp->number;
                }
            }


/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
do { if((here->ptr = SMPmakeElt(matrix, here->first, here->second)) == NULL){\
    return(E_NOMEM);\
} } while(0)

#define MY_TSTALLOC(ptr,first,second) \
do { if((here->ptr = SMPmakeElt(matrix, here->first, (second)->number)) == NULL){\
    return(E_NOMEM);\
} } while(0)

            /* For each controlling variable set the entries
            in the vector of the positions of the SMP */
            if (!here->ASRCtree)
		return E_PARMVAL;

	    if( here->ASRCtype == ASRC_VOLTAGE) {

                if(here->ASRCposNode == here->ASRCnegNode) {
                    SPfrontEnd->IFerror (ERR_FATAL,
                              "instance %s is a shorted ASRC", &here->ASRCname);
                    return(E_UNSUPP);
                }

            	here->ASRCposptr = TREALLOC(double *, here->ASRCposptr, j + 5);
            	TSTALLOC(ASRCposptr[j++],ASRCposNode,ASRCbranch);
            	TSTALLOC(ASRCposptr[j++],ASRCnegNode,ASRCbranch);
            	TSTALLOC(ASRCposptr[j++],ASRCbranch,ASRCnegNode);
            	TSTALLOC(ASRCposptr[j++],ASRCbranch,ASRCposNode);
	    }
                
            for( i=0; i < here->ASRCtree->numVars; i++){
                switch(here->ASRCtree->varTypes[i]){
                case IF_INSTANCE:
                    here->ASRCcont_br = CKTfndBranch(ckt,
                            here->ASRCtree->vars[i].uValue);
                    if(here->ASRCcont_br == 0) {
                        IFuid namarray[2];
                        namarray[0] =  here->ASRCname;
                        namarray[1] = here->ASRCtree->vars[i].uValue;
                        SPfrontEnd->IFerror (ERR_FATAL,
                                "%s: unknown controlling source %s",namarray);
                        return(E_BADPARM);
                    }
                    if( here->ASRCtype == ASRC_VOLTAGE){
                        /* CCVS */
                        if(v_first){
                            TSTALLOC(ASRCposptr[j++],ASRCbranch,ASRCcont_br);
                            v_first = 0;
                        } else{
                            here->ASRCposptr = TREALLOC(double *, here->ASRCposptr, j + 1);
                            TSTALLOC(ASRCposptr[j++],ASRCbranch,ASRCcont_br);
                        }
                    } else if(here->ASRCtype == ASRC_CURRENT){
                        /* CCCS */
            here->ASRCposptr = TREALLOC(double *, here->ASRCposptr, j + 2);
            TSTALLOC(ASRCposptr[j++],ASRCposNode,ASRCcont_br);
            TSTALLOC(ASRCposptr[j++],ASRCnegNode,ASRCcont_br);
                    } else{
                        return (E_BADPARM);
                    }
                    break;
                case IF_NODE:
                    if( here->ASRCtype == ASRC_VOLTAGE){
                        /* VCVS */
                        if(v_first){
        MY_TSTALLOC(ASRCposptr[j++],ASRCbranch,here->ASRCtree->vars[i].nValue);
                            v_first = 0;
                        } else{
                            here->ASRCposptr = TREALLOC(double *, here->ASRCposptr, j + 1);
        MY_TSTALLOC(ASRCposptr[j++],ASRCbranch,here->ASRCtree->vars[i].nValue);
                        }
                    } else if(here->ASRCtype == ASRC_CURRENT){
                        /* VCCS */
                        here->ASRCposptr = TREALLOC(double *, here->ASRCposptr, j + 2);
        MY_TSTALLOC(ASRCposptr[j++],ASRCposNode,here->ASRCtree->vars[i].nValue);
        MY_TSTALLOC(ASRCposptr[j++],ASRCnegNode,here->ASRCtree->vars[i].nValue);
                    } else{
                        return (E_BADPARM);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return(OK);
}

int
ASRCunsetup(
    GENmodel *inModel,
    CKTcircuit *ckt)
{
    ASRCmodel *model;
    ASRCinstance *here;

    for (model = (ASRCmodel *)inModel; model != NULL;
	    model = model->ASRCnextModel)
    {
        for (here = model->ASRCinstances; here != NULL;
                here=here->ASRCnextInstance)
	{
	    if (here->ASRCbranch) {
		CKTdltNNum(ckt, here->ASRCbranch);
		here->ASRCbranch = 0;
	    }
	}
    }
    return OK;
}
