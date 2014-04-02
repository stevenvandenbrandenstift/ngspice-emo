#line 1 "../../../../src/xspice/icm/digital/d_jkff/cfunc.mod"
#include "ngspice/cm.h"
extern void cm_d_jkff(Mif_Private_t *);
#line 1 "../../../../src/xspice/icm/digital/d_jkff/cfunc.mod"
/*.......1.........2.........3.........4.........5.........6.........7.........8
================================================================================

FILE d_jkff/cfunc.mod

Copyright 1991
Georgia Tech Research Corporation, Atlanta, Ga. 30332
All Rights Reserved

PROJECT A-8503-405
               

AUTHORS                      

    21 Jun 1991     Jeffrey P. Murray


MODIFICATIONS   

    12 Aug 1991    Jeffrey P. Murray
    30 Sep 1991    Jeffrey P. Murray
    29 Jan 1992    Jeffrey P. Murray
                                   

SUMMARY

    This file contains the functional description of the d_jkff
    code model.


INTERFACES       

    FILE                 ROUTINE CALLED     

    CMutil.c             void cm_toggle_bit(); 
       
    CMevt.c              void *cm_event_alloc()
                         void *cm_event_get_ptr()
                         


REFERENCED FILES

    Inputs from and outputs to ARGS structure.
                     

NON-STANDARD FEATURES

    NONE

===============================================================================*/

/*=== INCLUDE FILES ====================*/


                                      

/*=== CONSTANTS ========================*/




/*=== MACROS ===========================*/



  
/*=== LOCAL VARIABLES & TYPEDEFS =======*/                         


    
           
/*=== FUNCTION PROTOTYPE DEFINITIONS ===*/




                   
/*==============================================================================

FUNCTION cm_toggle_bit()


AUTHORS                      

    27 Sept 1991     Jeffrey P. Murray


MODIFICATIONS   

    NONE


SUMMARY

    Alters the state of a passed digital variable to its
    complement. Thus, a ONE changes to a ZERO. A ZERO changes
    to a ONE, and an UNKNOWN remains unchanged.


INTERFACES       

    FILE                 ROUTINE CALLED     

    N/A                  N/A


RETURNED VALUE
    
    No returned value. Passed pointer to variable is used 
    to redefine the variable value.
           

GLOBAL VARIABLES
    
    NONE


NON-STANDARD FEATURES

    NONE
                                                   

===============================================================================*/

/*=== CM_TOGGLE_BIT ROUTINE ===*/

static void cm_toggle_bit(Digital_State_t *bit) 

{
    /* Toggle bit from ONE to ZERO or vice versa, unless the
       bit value is UNKNOWN. In the latter case, return 
       without changing the bit value.                      */

    if ( UNKNOWN != *bit ) {
        if ( ONE == *bit ) {
            *bit = ZERO;
        }
        else { 
            *bit = ONE;
        }
    }

}
                   
/*==============================================================================

FUNCTION cm_eval_jk_result

AUTHORS                      

    30 Sept 1991     Jeffrey P. Murray

MODIFICATIONS   

    NONE

SUMMARY

    Evaluates the J and K input states, plus the last state of
    the flip flop, and returns the expected output value.

INTERFACES       

    FILE                 ROUTINE CALLED     

    CMutil.c             void cm_toggle_bit(); 


RETURNED VALUE
    
    A Digital_State_t.           

GLOBAL VARIABLES
    
    NONE

NON-STANDARD FEATURES

    NONE

==============================================================================*/

/*=== CM_EVAL_JK_RESULT ROUTINE ===*/

static Digital_State_t cm_eval_jk_result(Digital_State_t j_input,
                                         Digital_State_t k_input,
                                         Digital_State_t old_output)
{                                                          
    Digital_State_t     output; /* returned output value */


    switch (j_input) {

    case ZERO:
        switch (k_input) {
        case ZERO: 
            output = old_output;
            break;
        case ONE:
            output = ZERO;
            break;
        case UNKNOWN:
            output = UNKNOWN;
            break;
        }
        break; 

    case ONE:
        switch (k_input) {
        case ZERO: 
            output = ONE;
            break;
        case ONE:
            output = old_output;
            cm_toggle_bit(&output);
            break;
        case UNKNOWN:
            output = UNKNOWN;
            break;
        }
        break; 

            
    case UNKNOWN:
        output = UNKNOWN;
        break; 
    }
    
    return output;

}

/*==============================================================================

FUNCTION cm_d_jkff()

AUTHORS                      

    21 Jun 1991     Jeffrey P. Murray

MODIFICATIONS   

    12 Aug 1991    Jeffrey P. Murray
    30 Sep 1991    Jeffrey P. Murray
    29 Jan 1992    Jeffrey P. Murray

SUMMARY

    This function implements the d_jkff code model.

INTERFACES       

    FILE                 ROUTINE CALLED     

    CMutil.c             void cm_toggle_bit(); 
       
    CMevt.c              void *cm_event_alloc()
                         void *cm_event_get_ptr()

RETURNED VALUE
    
    Returns inputs and outputs via ARGS structure.

GLOBAL VARIABLES
    
    NONE

NON-STANDARD FEATURES

    NONE

==============================================================================*/

                   
/*=== CM_D_JKFF ROUTINE ===*/

/************************************************
*      The following is the model for the       *
*   digital jk-type flip flop for the           *
*   ATESSE Version 2.0 system.                  *
*                                               *
*   Created 6/21/91               J.P.Murray    *
************************************************/


void cm_d_jkff(Mif_Private_t *mif_private) 

{
    /*int                    i;*/   /* generic loop counter index */
                        

    Digital_State_t     *clk,   /* current clk value    */
                    *clk_old,   /* previous clk value   */
                        *set,   /* current set value for dff    */
                    *set_old,   /* previous set value for dff   */
                      *reset,   /* current reset value for dff      */
                  *reset_old,   /* previous reset value for dff     */
                        *out,   /* current output for dff   */
                    *out_old,   /* previous output for dff  */                            

                     j_input,   /* current j input value    */                            
                     k_input,   /* current k input value    */                            

                        temp;   /* temp storage for state values    */                            



    /*** Setup required state variables ***/

    if(mif_private->circuit.init) {  /* initial pass */ 

        /* allocate storage */
        cm_event_alloc(0,sizeof(Digital_State_t));
        cm_event_alloc(1,sizeof(Digital_State_t));
        cm_event_alloc(2,sizeof(Digital_State_t));
        cm_event_alloc(3,sizeof(Digital_State_t));

        /* declare load values */
        mif_private->conn[0]->port[0]->load = mif_private->param[6]->element[0].rvalue;
        mif_private->conn[1]->port[0]->load = mif_private->param[6]->element[0].rvalue;
        mif_private->conn[2]->port[0]->load = mif_private->param[7]->element[0].rvalue;
        if ( !mif_private->conn[3]->is_null ) {
            mif_private->conn[3]->port[0]->load = mif_private->param[8]->element[0].rvalue;
        }
        if ( !mif_private->conn[4]->is_null ) {
        mif_private->conn[4]->port[0]->load = mif_private->param[9]->element[0].rvalue;
        }
        
        /* retrieve storage for the outputs */
        clk = clk_old = (Digital_State_t *) cm_event_get_ptr(0,0);
        set = set_old = (Digital_State_t *) cm_event_get_ptr(1,0);
        reset = reset_old = (Digital_State_t *) cm_event_get_ptr(2,0);
        out = out_old = (Digital_State_t *) cm_event_get_ptr(3,0);

    }
    else {      /* Retrieve previous values */
                                              
        /* retrieve storage for the outputs */
        clk = (Digital_State_t *) cm_event_get_ptr(0,0);
        clk_old = (Digital_State_t *) cm_event_get_ptr(0,1);
        set = (Digital_State_t *) cm_event_get_ptr(1,0);
        set_old = (Digital_State_t *) cm_event_get_ptr(1,1);
        reset = (Digital_State_t *) cm_event_get_ptr(2,0);
        reset_old = (Digital_State_t *) cm_event_get_ptr(2,1);
        out = (Digital_State_t *) cm_event_get_ptr(3,0);
        out_old = (Digital_State_t *) cm_event_get_ptr(3,1);
    }



    /******** load current input values if set or reset 
              are not connected, set to zero... ********/
    *clk = ((Digital_t*)(mif_private->conn[2]->port[0]->input.pvalue))->state;
    if ( mif_private->conn[3]->is_null ) {
        *set = *set_old = ZERO;
    }
    else {
        *set = ((Digital_t*)(mif_private->conn[3]->port[0]->input.pvalue))->state;
    }
    if ( mif_private->conn[4]->is_null ) {
        *reset = *reset_old = ZERO;
    }
    else {
        *reset = ((Digital_t*)(mif_private->conn[4]->port[0]->input.pvalue))->state;
    }


         
                            

    /******* Determine analysis type and output appropriate values *******/

    if (0.0 == mif_private->circuit.time) {   /****** DC analysis...output w/o delays ******/
                                                            
        temp = (Digital_State_t) mif_private->param[3]->element[0].ivalue;

        /** Modify output if set or reset lines are active **/
        if ( (*set==ONE) && (*reset==ZERO) ) temp = ONE;
        if ( (*set==ZERO) && (*reset==ONE) ) temp = ZERO;
        if ( (*set==ONE) && (*reset==ONE) ) temp = UNKNOWN;

        *out = *out_old = temp;

        if ( !mif_private->conn[5]->is_null ) {
            ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = temp;
        }

        cm_toggle_bit(&temp);

        if ( !mif_private->conn[6]->is_null ) {
            ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = temp;
        }

    }

    else {      /****** Transient Analysis ******/


        /***** Find input that has changed... *****/

        /**** Test set value for change ****/
        if ( *set != *set_old ) { /* either set or set release */
            switch ( *set ) {

            case ONE:
                if ( ONE != *reset) {
                    if (*out_old != ONE) {  /* set will change output */
                        /* output goes to ONE */
                        *out = ONE;

                        if ( !mif_private->conn[5]->is_null ) {
                            ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ONE;
                            mif_private->conn[5]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ZERO;
                            mif_private->conn[6]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                    }
                    else {
                        *out = *out_old;     /* output already set */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                    }
                }
                else {
                    if (*out_old != UNKNOWN) {  /* set will change output */
                        /* output goes to UNKNOWN */
                        *out = UNKNOWN;

                        if ( !mif_private->conn[5]->is_null ) {
                            ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = UNKNOWN;
                            mif_private->conn[5]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = UNKNOWN;
                            mif_private->conn[6]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                    }
                    else {
                        *out = *out_old;     /* output already unknown */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                    }
                }
                break;

            case ZERO:
                if ( ONE != *reset) {
                    /* output remains at current value */
                    *out = *out_old;
                    if ( !mif_private->conn[5]->is_null ) {
                        mif_private->conn[5]->port[0]->changed = FALSE;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        mif_private->conn[6]->port[0]->changed = FALSE;
                    }
                }
                else {
                    if (*out_old != ZERO) {  /* set will change output */
                        /* output returns to reset condition */
                        *out = ZERO;

                        if ( !mif_private->conn[5]->is_null ) {
                            ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ZERO;
                            mif_private->conn[5]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ONE;
                            mif_private->conn[6]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                        }
                    }
                    else {
                        *out = *out_old;     /* output already reset */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                    }
                }
                break;

            case UNKNOWN:

                if ( ONE == *reset ) {
                    /* output goes to ZERO */
                    *out = ZERO;

                    if ( !mif_private->conn[5]->is_null ) {
                        ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ZERO;
                        mif_private->conn[5]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ONE;
                        mif_private->conn[6]->port[0]->delay = mif_private->param[1]->element[0].rvalue;
                    }
                }
                else {
                    *out = *out_old;     /* output already unknown */
                    if ( !mif_private->conn[5]->is_null ) {
                        mif_private->conn[5]->port[0]->changed = FALSE;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        mif_private->conn[6]->port[0]->changed = FALSE;
                    }
                }
                break;
            }
        }
        else {

            /**** Test reset value for change ****/
            if ( *reset != *reset_old ) { /* either reset or reset release */
                switch ( *reset ) {
    
                case ONE:
                    if ( ONE != *set) {
                        if (*out_old != ZERO) {  /* reset will change output */
                            /* output goes to ZERO */
                            *out = ZERO;

                            if ( !mif_private->conn[5]->is_null ) {
                                ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ZERO;
                                mif_private->conn[5]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ONE;
                                mif_private->conn[6]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                        }
                        else {
                            *out = *out_old;     /* output already reset */
                            if ( !mif_private->conn[5]->is_null ) {
                                mif_private->conn[5]->port[0]->changed = FALSE;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                mif_private->conn[6]->port[0]->changed = FALSE;
                            }
                        }
                    }
                    else {
                        if (*out_old != UNKNOWN) {  /* reset will change output */
                            /* output goes to UNKNOWN */
                            *out = UNKNOWN;

                            if ( !mif_private->conn[5]->is_null ) {
                                ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = UNKNOWN;
                                mif_private->conn[5]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = UNKNOWN;
                                mif_private->conn[6]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                        }
                        else {
                            *out = *out_old;     /* output already unknown */
                            if ( !mif_private->conn[5]->is_null ) {
                                mif_private->conn[5]->port[0]->changed = FALSE;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                mif_private->conn[6]->port[0]->changed = FALSE;
                            }
                        }
                    }
                    break;

                case ZERO:
                    if ( ONE != *set) {
                        /* output remains at current value */
                        *out = *out_old;
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                    }
                    else {
                        if (*out_old != ONE) {  /* reset will change output */
                            /* output returns to set condition */
                            *out = ONE;

                            if ( !mif_private->conn[5]->is_null ) {
                                ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ONE;
                                mif_private->conn[5]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ZERO;
                                mif_private->conn[6]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                            }
                        }
                        else {
                            *out = *out_old;     /* output already reset */
                            if ( !mif_private->conn[5]->is_null ) {
                                mif_private->conn[5]->port[0]->changed = FALSE;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                mif_private->conn[6]->port[0]->changed = FALSE;
                            }
                        }
                    }
                    break;
    
                case UNKNOWN:
                    if ( ONE == *set ) {
                        /* output goes to ONE */
                        *out = ONE;

                        if ( !mif_private->conn[5]->is_null ) {
                            ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = ONE;
                            mif_private->conn[5]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = ZERO;
                            mif_private->conn[6]->port[0]->delay = mif_private->param[2]->element[0].rvalue;
                        }
                    }
                    else {
                        *out = *out_old;     /* output already unknown */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                    }
                    break;
                }
            }
            else {

                /**** Test clk value for change ****/
                if ( (*clk != *clk_old) && (*reset != ONE) &&
                     (*set != ONE) ) { /* clock or clock release */
                    switch ( *clk ) {          

                    case ONE:
                        /* active edge...calculate new data output  */
                        j_input = ((Digital_t*)(mif_private->conn[0]->port[0]->input.pvalue))->state;
                        k_input = ((Digital_t*)(mif_private->conn[1]->port[0]->input.pvalue))->state;
                        temp = cm_eval_jk_result(j_input,k_input,*out_old);
                         

                        if (*out_old != temp) {  /* clk will change output */
                            *out = temp;   

                            if ( !mif_private->conn[5]->is_null ) {
                                ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->state = temp;
                                mif_private->conn[5]->port[0]->delay = mif_private->param[0]->element[0].rvalue;
                            }
                            cm_toggle_bit(&temp);       

                            if ( !mif_private->conn[6]->is_null ) {
                                ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->state = temp;
                                mif_private->conn[6]->port[0]->delay = mif_private->param[0]->element[0].rvalue;
                            }
                        }
                        else {
                            *out = *out_old;     /* output same as before */
                            if ( !mif_private->conn[5]->is_null ) {
                                mif_private->conn[5]->port[0]->changed = FALSE;
                            }
                            if ( !mif_private->conn[6]->is_null ) {
                                mif_private->conn[6]->port[0]->changed = FALSE;
                            }
                        }
                        break;

                    case ZERO:
                    case UNKNOWN:
                        /* inactive edge...return previous values */
                        *out = *out_old;
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->changed = FALSE;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->changed = FALSE;
                        }
                        break;
                    }
                }

                else {   /* data value must have changed...
                            return previous output value.    */
                    *out = *out_old;
                    if ( !mif_private->conn[5]->is_null ) {
                        mif_private->conn[5]->port[0]->changed = FALSE;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        mif_private->conn[6]->port[0]->changed = FALSE;
                    }
                }
            }        
        }


        /***** Add additional rise or fall delays, if appropriate *****/

        if ( *out != *out_old ) { /*** output value is changing ***/

            switch ( *out ) {
                                                 
            /** fall to zero value **/
            case 0: 
                    if ( !mif_private->conn[5]->is_null ) {
                        mif_private->conn[5]->port[0]->delay += mif_private->param[5]->element[0].rvalue;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        mif_private->conn[6]->port[0]->delay += mif_private->param[4]->element[0].rvalue;
                    }
                    break;
    
            /** rise to one value **/
            case 1: 
                    if ( !mif_private->conn[5]->is_null ) {
                        mif_private->conn[5]->port[0]->delay += mif_private->param[4]->element[0].rvalue;
                    }
                    if ( !mif_private->conn[6]->is_null ) {
                        mif_private->conn[6]->port[0]->delay += mif_private->param[5]->element[0].rvalue;
                    }
                    break;
                                    
            /** unknown output **/
            default:
                    /* based on old value, add rise or fall delay */
                    if (0 == *out_old) {  /* add rising delay */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->delay += mif_private->param[4]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->delay += mif_private->param[5]->element[0].rvalue;
                        }
                    }
                    else {                /* add falling delay */
                        if ( !mif_private->conn[5]->is_null ) {
                            mif_private->conn[5]->port[0]->delay += mif_private->param[5]->element[0].rvalue;
                        }
                        if ( !mif_private->conn[6]->is_null ) {
                            mif_private->conn[6]->port[0]->delay += mif_private->param[4]->element[0].rvalue;
                        }
                    }   
                    break;
            }
        }
    }
              
    /*** output strength values ***/
    if ( !mif_private->conn[5]->is_null ) {
        ((Digital_t*)(mif_private->conn[5]->port[0]->output.pvalue))->strength = STRONG;
    }
    if ( !mif_private->conn[6]->is_null ) {
        ((Digital_t*)(mif_private->conn[6]->port[0]->output.pvalue))->strength = STRONG;
    }
} 

      



