#include "FarmWarsGameModeBase.h"

#include "PlayerCharacter.h"
#include "ConstructorHelpers.h"

AFarmWarsGameModeBase::AFarmWarsGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerCharacterBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
    if (PlayerCharacterBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerCharacterBPClass.Class;
    }
}
