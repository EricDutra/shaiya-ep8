USE [PS_GameData]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[usp_Read_Char_Items_Skin_R]
    @CharID int
AS
SET NOCOUNT ON;

SELECT 
    ISNULL(MAX(CASE WHEN Slot = 14 THEN Type    END), 0) AS PetType,
    ISNULL(MAX(CASE WHEN Slot = 14 THEN TypeID  END), 0) AS PetTypeID,
    
    ISNULL(MAX(CASE WHEN Slot = 15 THEN Type    END), 0) AS CostumeType,
    ISNULL(MAX(CASE WHEN Slot = 15 THEN TypeID  END), 0) AS CostumeTypeID,
    
    ISNULL(MAX(CASE WHEN Slot = 16 THEN Type    END), 0) AS WingType,
    ISNULL(MAX(CASE WHEN Slot = 16 THEN TypeID  END), 0) AS WingTypeID

FROM PS_GameData.dbo.CharItems WITH (NOLOCK)
WHERE CharID = @CharID 
  AND Bag     = 0 
  AND Del     = 0 
  AND Slot    IN (14,15,16);

RETURN;