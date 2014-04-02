#line 1 "../../../../src/xspice/icm/xtradev/resemo/cfunc.mod"
#include "ngspice/cm.h"
extern void cm_resemo(Mif_Private_t *);
#line 1 "../../../../src/xspice/icm/xtradev/resemo/cfunc.mod"
/*.......1.........2.........3.........4.........5.........6.........7.........8
================================================================================

FILE cfunc.mod
*/
/*=== INCLUDE FILES ====================*/

#include <math.h>

                                    

/*=== CONSTANTS ========================*/




/*=== MACROS ===========================*/



  
/*=== LOCAL VARIABLES & TYPEDEFS =======*/                         


    
           
/*=== FUNCTION PROTOTYPE DEFINITIONS ===*/




                   
/*==============================================================================

FUNCTION void cm_resemo()

AUTHORS                      

     3 Maart 2014     Steven Vanden Branden

MODIFICATIONS   

    NONE

SUMMARY

    This function implements the emotional resister model.

INTERFACES       

    FILE                 ROUTINE CALLED     

RETURNED VALUE
    
    Returns inputs and outputs via ARGS structure.

GLOBAL VARIABLES
    
    NONE

NON-STANDARD FEATURES

    NONE

==============================================================================*/

#define RV 0
#define RES_POWER 1

	double res_activity;
	double res_working_zone;
	double res_power_over_unit;
   	double res_resistance;
	double res_power ;

void cm_resemo(Mif_Private_t *mif_private)  

{
    /* Retrieve frequently used parameters... */
    double *rval;
    double *res_power_data;
    
    if(mif_private->circuit.init) {
    	cm_analog_alloc(RV,sizeof(double));
    	cm_analog_alloc(RES_POWER,sizeof(double));
    	res_power_data=(double *) cm_analog_get_ptr(RES_POWER,0);
    	*res_power_data=mif_private->param[1]->element[0].rvalue;
    	rval=(double *) cm_analog_get_ptr(RV,0);
    	*rval=mif_private->param[0]->element[0].rvalue;
    	
    }else{
    	res_power_data=(double *) cm_analog_get_ptr(RES_POWER,0);
    	rval=(double*) cm_analog_get_ptr(RV,0);
    }

    res_resistance = mif_private->param[0]->element[0].rvalue;
    
    /*	
	if(ANALYSYS==TRANSIENT){
	} else if(ANALYSIS==AC){
		
	}
	*/
	cm_analog_auto_partial();
    mif_private->conn[0]->port[0]->output.rvalue=mif_private->conn[0]->port[0]->input.rvalue*(*rval);
    //res_power_over_unit=INPUT(res)*OUTPUT(res);
    //res_working_zone=res_power_over_unit/res_power;


}
