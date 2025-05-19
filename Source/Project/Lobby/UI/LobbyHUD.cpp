#include "Lobby/UI/LobbyHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULobbyHUD::NativeConstruct()
{
	Super::NativeConstruct();

	//GameStartButton 
	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));
	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &ULobbyHUD::ClickGameStartButton);
	}
}

void ULobbyHUD::ClickGameStartButton()
{
	UGameplayStatics::OpenLevel(this, TEXT("/Game/GamePlay/Map/MainLevel"));
}
