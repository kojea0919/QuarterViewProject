// Fill out your copyright notice in the Description page of Project Settings.


#include "DragImage.h"
#include "Components/Image.h"

void UDragImage::SetMaterial(UMaterialInstanceDynamic* Material)
{
	DragImageMaterial = Material;
}

void UDragImage::NativeConstruct()
{
	Super::NativeConstruct();

	DragImage = Cast<UImage>(GetWidgetFromName(FName("Img_DragImage")));

	if (DragImageMaterial)
		DragImage->SetBrushFromMaterial(DragImageMaterial);
}


