#include "Dio.h"
#include "Platform_Types.h"
#include "Register.h"

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	
}

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	
}

Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{

}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{

}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    
}


Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_PortLevelType * PIN_Ptr = NULL_PTR;
	boolean error = FALSE;
	Dio_LevelType ChannelLevel ;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}


	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PIN register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
			case 0:	PIN_Ptr = &(DIOA->ODR);
			break;
			
			case 1:	PIN_Ptr = &(DIOB->ODR);
			break;
			
			case 2:	PIN_Ptr = &(DIOC->ODR);
			break;
			
			case 3:	PIN_Ptr = &(DIOD->ODR);
			break;
			
			case 4:	PIN_Ptr = &(DIOE->ODR);
			break;
			
			case 5:	PIN_Ptr = &(DIOF->ODR);
			break;
		}
		/* Read the required channel */
		ChannelLevel = READ_BIT(*PIN_Ptr,Dio_PortChannels[ChannelId].Ch_Num) ;
	}
	else
	{
		/* No Action Required */
	}

	return ChannelLevel ;
}


