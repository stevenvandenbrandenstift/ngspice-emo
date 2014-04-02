#line 1 "../../../../src/xspice/icm/xtradev/res_emo/cfunc.mod"
#include "ngspice/cm.h"
extern void cm_res_emo(Mif_Private_t *);
#line 1 "../../../../src/xspice/icm/xtradev/res_emo/cfunc.mod"
/*.......1.........2.........3.........4.........5.........6.........7.........8
================================================================================

FILE res_emo/cfunc.mod

Copyright 1991
Georgia Tech Research Corporation, Atlanta, Ga. 30332
All Rights Reserved

PROJECT A-8503-405
               

AUTHORS                      

    6 Jun 1991     Jeffrey P. Murray


MODIFICATIONS   

     2 Oct 1991    Jeffrey P. Murray
                                   

SUMMARY

    This file contains the model-specific routines used to
    functionally describe the resitor emotion code model.


INTERFACES       

    FILE                 ROUTINE CALLED     

    CMutil.c             void cm_smooth_corner(); 


REFERENCED FILES

    Inputs from and outputs to ARGS structure.
                     

NON-STANDARD FEATURES

    NONE

===============================================================================*/

/*=== INCLUDE FILES ====================*/

#include <math.h>

                                      

/*=== CONSTANTS ========================*/




/*=== MACROS ===========================*/



  
/*=== LOCAL VARIABLES & TYPEDEFS =======*/                         


    
           
/*=== FUNCTION PROTOTYPE DEFINITIONS ===*/




                   
/*==============================================================================

FUNCTION void cm_divide()

AUTHORS                      

     2 Oct 1991     Jeffrey P. Murray

MODIFICATIONS   

    NONE

SUMMARY

    This function implements the divide code model.

INTERFACES       

    FILE                 ROUTINE CALLED     

    CMutil.c             void cm_smooth_corner(); 

RETURNED VALUE
    
    Returns inputs and outputs via ARGS structure.

GLOBAL VARIABLES
    
    NONE

NON-STANDARD FEATURES

    NONE

==============================================================================*/


/*=== CM_DIVIDE ROUTINE ===*/


void cm_res_emo(Mif_Private_t *mif_private)  

{
   	double res_resistance;
	double res_power ;
	double connection1;
	double connection2;
	double res_activity;
	double res_working_zone;
	double res_i;
	double res_u;
	float working_zone;
	double res_power_over_unit;
    
    Mif_Complex_t ac_gain;



    /* Retrieve frequently used parameters... */

    res_resistance = mif_private->param[0]->element[0].rvalue;
    res_power = mif_private->param[1]->element[0].rvalue;
	
    res_i=mif_private->conn[1]->port[0]->input.rvalue-mif_private->conn[0]->port[0]->input.rvalue;
    res_u=res_resistance*res_i;
    res_power_over_unit=res_u*res_i;

    working_zone=res_power_over_unit/res_power;


}
