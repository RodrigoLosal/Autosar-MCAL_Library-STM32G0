#include "Dio.h"
#include "Platform_Types.h"
#include "Register.h"


static Dio_ConfigChannel *Dio_PortChannels;
static Dio_PortType *Dio_Ports;
static Dio_ChannelGroupType *Dio_ChannelGroups;


void Dio_Init(const Dio_ConfigType *ConfigPtr)
{
	Dio_PortChannels = ConfigPtr->Channels; 
	Dio_Ports = ConfigPtr->Ports;
	Dio_ChannelGroups = ConfigPtr->Groups;
}


Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType ChannelLevel;

	if( DIO_CONFIGURED_CHANNLES => ChannelId )
	{
		switch( Dio_PortChannels[ ChannelId ].Port_Num)
		{
			case 0:	
				ChannelLevel = GET_1_BIT( DIOA->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
			
			case 1:
				ChannelLevel = GET_1_BIT( DIOB->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
			
			case 2:	
				ChannelLevel = GET_1_BIT( DIOC->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
			
			case 3:
				ChannelLevel = GET_1_BIT( DIOD->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
			
			case 4:
				ChannelLevel = GET_1_BIT( DIOE->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
			
			case 5:	
				ChannelLevel = GET_1_BIT( DIOF->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
			break;
		}
		
	}
	else
	{
		
	}

	return ChannelLevel ;
}


void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	
}

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	if( DIO_CONFIGURED_CHANNLES => ChannelId )
	{
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
			case 0:	
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOA->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOA->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}

			break;
			
			case 1:
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOB->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOB->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
			break;
			
			case 2:	
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOC->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOC->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
			break;
			
			case 3:
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOD->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOD->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
			break;
			
			case 4:
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOE->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOE->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
			break;
			
			case 5:	
				if( Level == STD_HIGH )
				{
					SET_1_BIT( DIOF->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
				else
				{
					CLEAR_1_BIT( DIOF->ODR , Dio_PortChannels[ ChannelId ].Ch_Num );
				}
			break;
		}
	}	
	else
	{

	}

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




