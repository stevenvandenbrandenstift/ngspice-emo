
/*
 * Structures for model: oneshot
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
    IOP("cntl_array", 0, (IF_REAL|IF_VECTOR), "control in array"),
    IOP("pw_array", 1, (IF_REAL|IF_VECTOR), "pulse width array"),
    IOP("clk_trig", 2, IF_REAL, "clock trigger value"),
    IOP("pos_edge_trig", 3, IF_FLAG, "pos/neg edge trigger switch"),
    IOP("out_low", 4, IF_REAL, "output low value"),
    IOP("out_high", 5, IF_REAL, "output high value"),
    IOP("rise_time", 6, IF_REAL, "output rise time"),
    IOP("rise_delay", 7, IF_REAL, "output delay from trigger"),
    IOP("fall_delay", 8, IF_REAL, "output delay from pw"),
    IOP("fall_time", 9, IF_REAL, "output rise time"),
    IOP("retrig", 10, IF_FLAG, "retrigger switch"),
};


static IFparm MIFpTable[] = {
    OP("locdata", 11, IF_STRING, "local static data"),
};


static Mif_Port_Type_t MIFportEnum0[] = {
	MIF_VOLTAGE,
	MIF_DIFF_VOLTAGE,
	MIF_VSOURCE_CURRENT,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
};


static char *MIFportStr0[] = {
	"v",
	"vd",
	"vnam",
	"i",
	"id",
};


static Mif_Port_Type_t MIFportEnum1[] = {
	MIF_VOLTAGE,
	MIF_VSOURCE_CURRENT,
	MIF_DIFF_VOLTAGE,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
};


static char *MIFportStr1[] = {
	"v",
	"vnam",
	"vd",
	"i",
	"id",
};


static Mif_Port_Type_t MIFportEnum2[] = {
	MIF_VOLTAGE,
	MIF_DIFF_VOLTAGE,
	MIF_VSOURCE_CURRENT,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
};


static char *MIFportStr2[] = {
	"v",
	"vd",
	"vnam",
	"i",
	"id",
};


static Mif_Port_Type_t MIFportEnum3[] = {
	MIF_VOLTAGE,
	MIF_DIFF_VOLTAGE,
	MIF_CURRENT,
	MIF_DIFF_CURRENT,
};


static char *MIFportStr3[] = {
	"v",
	"vd",
	"i",
	"id",
};


static Mif_Conn_Info_t MIFconnTable[] = {
  {
    "clk",
    "clock input",
    MIF_IN,
    MIF_VOLTAGE,
    "v",
    5,
    MIFportEnum0,
    MIFportStr0,
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_FALSE,
  },
  {
    "cntl_in",
    "input",
    MIF_IN,
    MIF_VOLTAGE,
    "v",
    5,
    MIFportEnum1,
    MIFportStr1,
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
  {
    "clear",
    "clear signal",
    MIF_IN,
    MIF_VOLTAGE,
    "v",
    5,
    MIFportEnum2,
    MIFportStr2,
    MIF_FALSE,
    MIF_FALSE,
    0,
    MIF_FALSE,
    0,
    MIF_TRUE,
  },
  {
    "out",
    "output",
    MIF_OUT,
    MIF_VOLTAGE,
    "v",
    4,
    MIFportEnum3,
    MIFportStr3,
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
    "cntl_array",
    "control in array",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 0.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_TRUE,
    MIF_FALSE,
    0,
    MIF_TRUE,
    2,
    MIF_FALSE,
    0,
    MIF_FALSE,
  },
  {
    "pw_array",
    "pulse width array",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e-06, {0.0, 0.0}, NULL},
    MIF_TRUE,
    {MIF_FALSE, 0, 0.000000e+00, {0.0, 0.0}, NULL},
    MIF_FALSE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
    MIF_TRUE,
    MIF_FALSE,
    0,
    MIF_TRUE,
    2,
    MIF_FALSE,
    0,
    MIF_FALSE,
  },
  {
    "clk_trig",
    "clock trigger value",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 5.000000e-01, {0.0, 0.0}, NULL},
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
    MIF_FALSE,
  },
  {
    "pos_edge_trig",
    "pos/neg edge trigger switch",
    MIF_BOOLEAN,
    MIF_TRUE,
    {MIF_TRUE, 0, 0.0, {0.0, 0.0}, NULL},
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
    MIF_FALSE,
  },
  {
    "out_low",
    "output low value",
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
  {
    "out_high",
    "output high value",
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
    "rise_time",
    "output rise time",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e-09, {0.0, 0.0}, NULL},
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
    "rise_delay",
    "output delay from trigger",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e-09, {0.0, 0.0}, NULL},
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
    "fall_delay",
    "output delay from pw",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e-09, {0.0, 0.0}, NULL},
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
    "fall_time",
    "output rise time",
    MIF_REAL,
    MIF_TRUE,
    {MIF_FALSE, 0, 1.000000e-09, {0.0, 0.0}, NULL},
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
    "retrig",
    "retrigger switch",
    MIF_BOOLEAN,
    MIF_TRUE,
    {MIF_FALSE, 0, 0.0, {0.0, 0.0}, NULL},
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


static Mif_Inst_Var_Info_t MIFinst_varTable[] = {
  {
    "locdata",
    "local static data",
    MIF_STRING,
    MIF_FALSE,
  },
};


extern void cm_oneshot(Mif_Private_t *);

static int val_terms             = 0;
static int val_numNames          = 0;
static int val_numInstanceParms  = 1;
static int val_numModelParms     = 11;
static int val_sizeofMIFinstance = sizeof(MIFinstance);
static int val_sizeofMIFmodel    = sizeof(MIFmodel);

SPICEdev cm_oneshot_info = {
    { "oneshot",
      "one-shot",
      &val_terms,
      &val_numNames,
      NULL,
      &val_numInstanceParms,
      MIFpTable,
      &val_numModelParms,
      MIFmPTable,
      cm_oneshot,
      4,
      MIFconnTable,
      11,
      MIFparamTable,
      1,
      MIFinst_varTable,
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
