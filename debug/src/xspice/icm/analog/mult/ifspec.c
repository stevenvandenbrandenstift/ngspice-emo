
/*
 * Structures for model: mult
 *
 * Automatically generated by cmpp preprocessor
 *
 * !!! DO NOT EDIT !!!
 *
 */


#include "ngspice/ngspice.h"
#include <stdio.h>
#include "ngspice/devdefs.h"
#include "ngspice/ifsim.h"
#include "ngspice/mifdefs.h"
#include "ngspice/mifproto.h"
#include "ngspice/mifparse.h"


static IFparm MIFmPTable[] = {
    IOP("in_offset", 0, (IF_REAL|IF_VECTOR), "input offset array"),
    IOP("in_gain", 1, (IF_REAL|IF_VECTOR), "input gain array"),
    IOP("out_gain", 2, IF_REAL, "output gain"),
    IOP("out_offset", 3, IF_REAL, "output offset"),
};


static Mif_Port_Type_t MIFportEnum0[] = {
	MIF_VOLTAGE,
	MIF_DIFF_VOLTAGE,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
	MIF_VSOURCE_CURRENT,
};


static char *MIFportStr0[] = {
	"v",
	"vd",
	"i",
	"id",
	"vnam",
};


static Mif_Port_Type_t MIFportEnum1[] = {
	MIF_VOLTAGE,
	MIF_DIFF_VOLTAGE,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
};


static char *MIFportStr1[] = {
	"v",
	"vd",
	"i",
	"id",
};


static Mif_Conn_Info_t MIFconnTable[] = {
  {
    "in",
    "input array",
    MIF_IN,
    MIF_VOLTAGE,
    "v",
    5,
    MIFportEnum0,
    MIFportStr0,
    MIF_TRUE,
    MIF_TRUE,
    2,
    MIF_FALSE,
    0,
    MIF_FALSE,
  },
  {
    "out",
    "output",
    MIF_OUT,
    MIF_VOLTAGE,
    "v",
    4,
    MIFportEnum1,
    MIFportStr1,
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
  },
};


static Mif_Param_Info_t MIFparamTable[] = {
  {
    "in_offset",
    "input offset array",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 0.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_TRUE,
    MIF_TRUE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
  {
    "in_gain",
    "input gain array",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_TRUE,
    MIF_TRUE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
  {
    "out_gain",
    "output gain",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
  {
    "out_offset",
    "output offset",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 0.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
};


extern void cm_mult(Mif_Private_t *);

static int val_terms             = 0;
static int val_numNames          = 0;
static int val_numInstanceParms  = 0;
static int val_numModelParms     = 4;
static int val_sizeofMIFinstance = sizeof(MIFinstance);
static int val_sizeofMIFmodel    = sizeof(MIFmodel);

SPICEdev cm_mult_info = {
    { "mult",
      "multiplier block",
      &val_terms,
      &val_numNames,
      NULL,
      &val_numInstanceParms,
      NULL,
      &val_numModelParms,
      MIFmPTable,
      cm_mult,
      2,
      MIFconnTable,
      4,
      MIFparamTable,
      0,
      NULL,
      0,         /* flags */
    },
NULL,          
MIFmParam,     
MIFload,       
MIFsetup,      
MIFunsetup,    
NULL,          
NULL,          
MIFtrunc,      
NULL,          
MIFload,       
NULL,          
MIFdestroy,    
MIFmDelete,    
MIFdelete,     
NULL,          
MIFask,        
MIFmAsk,       
NULL,          
MIFconvTest,   
NULL,          
NULL,          
NULL,          
NULL,          
NULL,          
NULL,          
NULL,          
NULL,          
NULL,          
#ifdef CIDER   
NULL,          
NULL,          
#endif         
&val_sizeofMIFinstance,
&val_sizeofMIFmodel,

};

