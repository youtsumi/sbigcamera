#include <stdio.h>
#include <stdlib.h>
#include"sbigudrv.h"

int ControlOverscan( bool bEnable ) {
    PAR_ERROR        err;
    CustomerOptionsParams params;
    CustomerOptionsResults results;
    short command = CC_CUSTOMER_OPTIONS;

    params.bSetCustomerOptions = 0;  //  just read

    //  read the initial state
    err = (PAR_ERROR)SBIGUnivDrvCommand(command, &params, &results);
    fprintf(stderr, "----------------------------------------------\n");
    fprintf(stderr, "CC_CUSTOMER_OPTIONS err: %d\n", err);
    if (err != CE_NO_ERROR)
    {
	                return err;
    }
    fprintf(stderr, "Original configuration for overscan is %d", params.bOverscanRegions);

    //  set the overscan enabled
    if ( bEnable )
	params.bOverscanRegions = 1;  //  a bit for overscan
    else
	params.bOverscanRegions = 0;  //  a bit for overscan

    params.bSetCustomerOptions = 1;  //  try to write
    params.bWindowHeater = results.bWindowHeater;
    params.bPreflashCcd = results.bPreflashCcd;
    params.bVddNormallyOff = results.bVddNormallyOff;

    err = (PAR_ERROR)SBIGUnivDrvCommand(command, &params, &results);
    fprintf(stderr, "----------------------------------------------\n");
    fprintf(stderr, "CC_CUSTOMER_OPTIONS err: %d\n", err);
    if (err != CE_NO_ERROR)
    {
	                return err;
    } else {
	fprintf(stderr, "overscan configured %d", params.bOverscanRegions);
    }

    return 0;
}

int main( int argc, char* argv[] ) {
    ControlOverscan( true );
//    ControlOverscan( false );
    return 0;
}
